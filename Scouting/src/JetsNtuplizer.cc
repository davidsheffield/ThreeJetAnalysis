// -*- C++ -*-
//
// Package:    ThreeJetAnalysis/Scouting
// Class:      JetsNtuplizer
//
/**\class JetsNtuplizer JetsNtuplizer.cc ThreeJetAnalysis/Scouting/src/JetsNtuplizer.cc

 Description: Code to monitor scouting streams.

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  David Sheffield
//         Created:  Wed, 28 Oct 2015
//
//

#include "ThreeJetAnalysis/Scouting/interface/JetsNtuplizer.h"

using namespace std;
using namespace edm;

//
// constructors and destructor
//
JetsNtuplizer::JetsNtuplizer(const edm::ParameterSet& iConfig):
    token_jets(consumes<ScoutingPFJetCollection>(
                   iConfig.getParameter<InputTag>("jet_collection"))),
    token_candidates(consumes<ScoutingParticleCollection>(
                         iConfig.getParameter<InputTag>(
                             "candidate_collection"))),
    token_vertices(consumes<ScoutingVertexCollection>(
                       iConfig.getParameter<InputTag>("vertex_collection"))),
    token_rho(consumes<double>(
                  iConfig.getParameter<InputTag>("rho"))),
    file_name(iConfig.getParameter<string>("output_file_name"))
{
    //now do what ever initialization is needed
    file = new TFile(file_name.c_str(), "RECREATE");

    tree = new TTree("events", "Tree for scouting data");

    tree->Branch("jet_num", &jet_num, "jet_num/I");
    tree->Branch("jet_pt", &jet_pt);
    tree->Branch("jet_eta", &jet_eta);
    tree->Branch("jet_phi", &jet_phi);
    tree->Branch("jet_mass", &jet_mass);
    tree->Branch("jet_csv", &jet_csv);
    tree->Branch("jet_vertex_index", &jet_vertex_index);
    tree->Branch("vertex_num", &vertex_num, "vertex_num/I");
    tree->Branch("rho", &rho, "rho/F");
    tree->Branch("Run", &run, "Run/I");
    tree->Branch("Lumi", &lumi, "Lumi/I");
    tree->Branch("Event", &event, "Event/I");
}


JetsNtuplizer::~JetsNtuplizer()
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
JetsNtuplizer::analyze(const edm::Event& iEvent,
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

    for (auto &jet: *jets) {
        jet_pt.push_back(jet.pt());
        jet_eta.push_back(jet.eta());
        jet_phi.push_back(jet.phi());
        jet_mass.push_back(jet.m());
        jet_csv.push_back(jet.csv());

        vector<pair<int, double>> index_vector;
        for (auto index: jet.constituents()) {
            index_vector.emplace_back(candidates->at(index).vertex(),
                                      candidates->at(index).pt());
        }
        sort(index_vector.begin(), index_vector.end(), SortVertexIndices);
        int index = -1;
        int pt2_index = 0.0;
        double pt2_current = 0.0;
        int last = -1;
        for (auto i: index_vector) {
            if (i.first != last)
                pt2_current = 0.0;
            pt2_current += i.second*i.second;
            if (pt2_current > pt2_index) {
                index = i.first;
                pt2_index = pt2_current;
            }
            last = i.first;
        }
        jet_vertex_index.push_back(index);
    }

    vertex_num = vertices->size();
    rho = *handle_rho;

    tree->Fill();

    return;
}


// ------- method called once each job just before starting event loop  -------
void JetsNtuplizer::beginJob()
{
}

// ------- method called once each job just after ending the event loop  -------
void JetsNtuplizer::endJob()
{
}


// -- method fills 'descriptions' with the allowed parameters for the module  --
void JetsNtuplizer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}


void JetsNtuplizer::ResetVariables()
{
    jet_num = 0;
    jet_pt.clear();
    jet_eta.clear();
    jet_phi.clear();
    jet_mass.clear();
    jet_csv.clear();
    jet_vertex_index.clear();

    vertex_num = 0;

    rho = 0.0;

    run = 0;
    lumi = 0;
    event = 0;

    return;
}

int JetsNtuplizer::GetCollections(const edm::Event& iEvent)
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

    // Get candidates
    iEvent.getByToken(token_candidates, candidates);
    if (!candidates.isValid()) {
        throw edm::Exception(edm::errors::ProductNotFound)
	    << "Could not find ScoutingParticleCollection." << endl;
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


bool SortVertexIndices(const pair<int, double> a, const pair<int, double> b)
{
    return (a.first > b.first);
}


//define this as a plug-in
DEFINE_FWK_MODULE(JetsNtuplizer);
