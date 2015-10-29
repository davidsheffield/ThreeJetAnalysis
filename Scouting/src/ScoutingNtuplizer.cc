// -*- C++ -*-
//
// Package:    ThreeJetAnalysis/Scouting
// Class:      ScoutingNtuplizer
//
/**\class ScoutingNtuplizer ScoutingNtuplizer.cc ThreeJetAnalysis/Scouting/src/ScoutingNtuplizer.cc

 Description: Code to monitor scouting streams.

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  David Sheffield
//         Created:  Wed, 28 Oct 2015
//
//

#include "ThreeJetAnalysis/Scouting/interface/ScoutingNtuplizer.h"

using namespace std;
using namespace edm;

//
// constructors and destructor
//
ScoutingNtuplizer::ScoutingNtuplizer(const edm::ParameterSet& iConfig):
    token_jets(consumes<ScoutingPFJetCollection>(
                   iConfig.getParameter<InputTag>("jet_collection"))),
    token_candidates(consumes<ScoutingParticleCollection>(
                         iConfig.getParameter<InputTag>(
                             "candidate_collection"))),
    token_vertices(consumes<ScoutingVertexCollection>(
                       iConfig.getParameter<InputTag>("vertex_collection"))),
    token_rho(consumes<double>(
                  iConfig.getParameter<InputTag>("rho"))),
    cut_nJets_min(iConfig.getParameter<int>("cut_nJets_min")),
    file_name(iConfig.getParameter<string>("output_file_name"))
{
    //now do what ever initialization is needed
    file = new TFile(file_name.c_str(), "RECREATE");

    tree = new TTree("events", "Tree for scouting data");

    tree->Branch("HT", &Ht, "HT/F");
    tree->Branch("triplet_mass", &triplet_mass);
    tree->Branch("triplet_scalar_pt", &triplet_scalar_pt);
    tree->Branch("triplet_delta", &triplet_delta);
    tree->Branch("triplet_dalitz_high", &triplet_dalitz_high);
    tree->Branch("triplet_dalitz_mid", &triplet_dalitz_mid);
    tree->Branch("triplet_dalitz_low", &triplet_dalitz_low);
    tree->Branch("triplet_lowest_pt", &triplet_lowest_pt);
    tree->Branch("jet_num", &jet_num, "jet_num/I");
    tree->Branch("jet_pt", &jet_pt);
    tree->Branch("jet_eta", &jet_eta);
    tree->Branch("jet_phi", &jet_phi);
    tree->Branch("jet_m", &jet_m);
    tree->Branch("jet_csv", &jet_csv);
    tree->Branch("vertex_num", &vertex_num, "vertex_num/I");
    tree->Branch("rho", &rho, "rho/F");
    tree->Branch("Run", &run, "Run/I");
    tree->Branch("Lumi", &lumi, "Lumi/I");
    tree->Branch("Event", &event, "Event/I");
}


ScoutingNtuplizer::~ScoutingNtuplizer()
{

    // do anything here that needs to be done at desctruction time
    // (e.g. close files, deallocate resources etc.)
    file->cd();
    tree->Write();
    file->Close();

}


//
// member functions
//

// ------------ method called for each event  ------------
void
ScoutingNtuplizer::analyze(const edm::Event& iEvent,
                         const edm::EventSetup& iSetup)
{
    ResetVariables();

    run = iEvent.id().run();
    lumi = iEvent.id().luminosityBlock();
    event = iEvent.id().event();

    int getCollectionsResult = GetCollections(iEvent);
    if (getCollectionsResult)
	return;

    jet_num = jets->size();
    if (jet_num < cut_nJets_min)
        return;

    for (auto &j: *jets) {
        Ht += j.pt();
        jet_pt.push_back(j.pt());
        jet_eta.push_back(j.eta());
        jet_phi.push_back(j.phi());
        jet_m.push_back(j.m());
        jet_csv.push_back(j.csv());

        TLorentzVector tmp_vector;
        tmp_vector.SetPtEtaPhiM(j.pt(), j.eta(), j.phi(), j.m());
        jet.push_back(tmp_vector);
    }

    vertex_num = vertices->size();
    rho = *handle_rho;

    MakeTriplets();

    tree->Fill();

    return;
}


// ------- method called once each job just before starting event loop  -------
void ScoutingNtuplizer::beginJob()
{
}

// ------- method called once each job just after ending the event loop  -------
void ScoutingNtuplizer::endJob()
{
}


// -- method fills 'descriptions' with the allowed parameters for the module  --
void ScoutingNtuplizer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

void normalizeHistogram(TH1D *hist)
{
    int nbins = hist->GetNbinsX();
    for (int i=1; i<nbins+1; ++i) {
        double content = hist->GetBinContent(i);
        double error = hist->GetBinError(i);
        double width = hist->GetXaxis()->GetBinWidth(i);
        hist->SetBinContent(i, content/width);
        hist->SetBinError(i, error/width);
    }
    return;
}

void ScoutingNtuplizer::ResetVariables()
{
    Ht = 0.0;

    triplet_mass.clear();
    triplet_scalar_pt.clear();
    triplet_delta.clear();
    triplet_dalitz_high.clear();
    triplet_dalitz_mid.clear();
    triplet_dalitz_low.clear();
    triplet_lowest_pt.clear();

    jet_num = 0;
    jet_pt.clear();
    jet_eta.clear();
    jet_phi.clear();
    jet_m.clear();
    jet_csv.clear();

    vertex_num = 0;

    rho = 0.0;

    run = 0;
    lumi = 0;
    event = 0;

    return;
}

int ScoutingNtuplizer::GetCollections(const edm::Event& iEvent)
{
    // Get collections from ntuple
    // Returns nonzero if there is a problem getting a collection

    // Get jets
    iEvent.getByToken(token_jets, jets);
    if (!jets.isValid()) {
        throw edm::Exception(edm::errors::ProductNotFound)
	    << "Could not find ScoutingPFJetCollection." << endl;
	return 1;
    }

    // Get vertices
    iEvent.getByToken(token_vertices, vertices);
    if (!vertices.isValid()) {
        throw edm::Exception(edm::errors::ProductNotFound)
	    << "Could not find ScoutingVertexCollection." << endl;
	return 1;
    }

    // Get rho
    iEvent.getByToken(token_rho, handle_rho);
    if (!handle_rho.isValid()) {
        throw edm::Exception(edm::errors::ProductNotFound)
	    << "Could not find rho." << endl;
	return 1;
    }

    return 0;
}

void ScoutingNtuplizer::MakeTriplets()
{
    for (int i=0; i<jet_num-2; ++i) {
        for (int j=i+1; j<jet_num-1; ++j) {
            for (int k=j+1; k<jet_num; ++k) {
                double mass = (jet[i] + jet[j] + jet[k]).M();
                double scalar_pt = jet[i].Pt() + jet[j].Pt() + jet[k].Pt();
                triplet_mass.push_back(mass);
                triplet_scalar_pt.push_back(scalar_pt);
                triplet_delta.push_back(scalar_pt - mass);
                triplet_lowest_pt.push_back(jet[k].Pt());

                double Dalitz_variable[3];
                double denominator = (jet[i] + jet[j] + jet[k]).M()
                                   * (jet[i] + jet[j] + jet[k]).M()
                                   + jet[i].M()*jet[i].M()
                                   + jet[j].M()*jet[j].M()
                                   + jet[k].M()*jet[k].M();
                Dalitz_variable[2] = (jet[i] + jet[j]).M()*(jet[i] + jet[j]).M()
                                   / denominator;
                Dalitz_variable[1] = (jet[i] + jet[k]).M()*(jet[i] + jet[k]).M()
                                   / denominator;
                Dalitz_variable[0] = (jet[j] + jet[k]).M()*(jet[j] + jet[k]).M()
                                   / denominator;
                sort(begin(Dalitz_variable), end(Dalitz_variable));
                triplet_dalitz_high.push_back(Dalitz_variable[2]);
                triplet_dalitz_mid.push_back(Dalitz_variable[1]);
                triplet_dalitz_low.push_back(Dalitz_variable[0]);
            }
        }
    }

    return;
}

//define this as a plug-in
DEFINE_FWK_MODULE(ScoutingNtuplizer);
