// -*- C++ -*-
//
// Package:    ThreeJetAnalysis/Resolved
// Class:      ResolvedNtuplizer
//
/**\class ResolvedNtuplizer ResolvedNtuplizer.cc ThreeJetAnalysis/Resolved/src/ResolvedNtuplizer.cc

 Description: Code to monitor scouting streams.

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  David Sheffield
//         Created:  Sat, 14 Nov 2015
//
//

#include "ThreeJetAnalysis/Resolved/interface/ResolvedNtuplizer.h"

using namespace std;
using namespace edm;

//
// constructors and destructor
//
ResolvedNtuplizer::ResolvedNtuplizer(const edm::ParameterSet& iConfig):
    token_jet_pt(consumes<vector<float>>(
                     iConfig.getParameter<InputTag>("jet_pt"))),
    token_jet_eta(consumes<vector<float>>(
                      iConfig.getParameter<InputTag>("jet_eta"))),
    token_jet_phi(consumes<vector<float>>(
                      iConfig.getParameter<InputTag>("jet_phi"))),
    token_jet_E(consumes<vector<float>>(
                    iConfig.getParameter<InputTag>("jet_E"))),
    token_jet_mass(consumes<vector<float>>(
                       iConfig.getParameter<InputTag>("jet_mass"))),
    token_jet_CSV(consumes<vector<float>>(
                      iConfig.getParameter<InputTag>("jet_csv"))),
    token_vertex_z(consumes<vector<float>>(
                       iConfig.getParameter<InputTag>("vertex_z"))),
    token_genpart_ID(consumes<vector<float>>(
                         iConfig.getParameter<InputTag>("genpart_ID"))),
    token_genpart_status(consumes<vector<float>>(
                             iConfig.getParameter<InputTag>("genpart_status"))),
    token_genpart_momID(consumes<vector<float>>(
                            iConfig.getParameter<InputTag>("genpart_momID"))),
    token_genpart_pt(consumes<vector<float>>(
                         iConfig.getParameter<InputTag>("genpart_pt"))),
    token_genpart_eta(consumes<vector<float>>(
                          iConfig.getParameter<InputTag>("genpart_eta"))),
    token_genpart_phi(consumes<vector<float>>(
                          iConfig.getParameter<InputTag>("genpart_phi"))),
    token_genpart_E(consumes<vector<float>>(
                        iConfig.getParameter<InputTag>("genpart_E"))),
    cut_nJets_min(iConfig.getParameter<int>("cut_nJets_min")),
    cut_pt(iConfig.getParameter<double>("cut_pt")),
    cut_eta(iConfig.getParameter<double>("cut_eta")),
    is_signal(iConfig.getParameter<bool>("is_signal")),
    file_name(iConfig.getParameter<string>("output_file_name"))
{
    //now do what ever initialization is needed
    file = new TFile(file_name.c_str(), "RECREATE");

    tree = new TTree("events", "Tree for scouting data");

    tree->Branch("HT", &Ht, "HT/F");
    tree->Branch("triplet_mass", &triplet_mass);
    tree->Branch("triplet_scalar_pt", &triplet_scalar_pt);
    tree->Branch("triplet_vector_pt", &triplet_vector_pt);
    tree->Branch("triplet_eta", &triplet_eta);
    tree->Branch("triplet_phi", &triplet_phi);
    tree->Branch("triplet_delta", &triplet_delta);
    tree->Branch("triplet_dalitz_high", &triplet_dalitz_high);
    tree->Branch("triplet_dalitz_mid", &triplet_dalitz_mid);
    tree->Branch("triplet_dalitz_low", &triplet_dalitz_low);
    tree->Branch("triplet_lowest_pt", &triplet_lowest_pt);
    tree->Branch("triplet_largest_eta", &triplet_largest_eta);
    tree->Branch("triplet_pairwise_mass", &triplet_pairwise_mass);
    tree->Branch("triplet_jet_csv", &triplet_jet_csv);
    if (is_signal)
        tree->Branch("triplet_is_correct", &triplet_is_correct);
    tree->Branch("jet_num", &jet_num, "jet_num/I");
    tree->Branch("jet_pt", &jet_pt);
    tree->Branch("jet_eta", &jet_eta);
    tree->Branch("vertex_num", &vertex_num, "vertex_num/I");
    //tree->Branch("rho", &rho, "rho/F");
    tree->Branch("Run", &run, "Run/I");
    tree->Branch("Lumi", &lumi, "Lumi/I");
    tree->Branch("Event", &event, "Event/I");
}


ResolvedNtuplizer::~ResolvedNtuplizer()
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
ResolvedNtuplizer::analyze(const edm::Event& iEvent,
                         const edm::EventSetup& iSetup)
{
    ResetVariables();

    run = iEvent.id().run();
    lumi = iEvent.id().luminosityBlock();
    event = iEvent.id().event();

    int getCollectionsResult = GetCollections(iEvent);
    if (getCollectionsResult)
	return;

    jet_num = jet.size();
    if (jet_num < cut_nJets_min)
        return;

    for (int i=0; i<jet_num; ++i) {
        jet_pt.push_back(jet[i].Pt());
        jet_eta.push_back(jet[i].Eta());

        if (is_signal)
            jet_from_triplet.push_back(0);
    }

    if (is_signal)
        GetGenParticles();

    vertex_num = vertex_z->size();
    //rho = *handle_rho;

    MakeTriplets();

    tree->Fill();

    return;
}


// ------- method called once each job just before starting event loop  -------
void ResolvedNtuplizer::beginJob()
{
}

// ------- method called once each job just after ending the event loop  -------
void ResolvedNtuplizer::endJob()
{
}


// -- method fills 'descriptions' with the allowed parameters for the module  --
void ResolvedNtuplizer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}


void ResolvedNtuplizer::ResetVariables()
{
    jet.clear();
    jet_from_triplet.clear();

    Ht = 0.0;

    triplet_mass.clear();
    triplet_scalar_pt.clear();
    triplet_vector_pt.clear();
    triplet_eta.clear();
    triplet_phi.clear();
    triplet_delta.clear();
    triplet_dalitz_high.clear();
    triplet_dalitz_mid.clear();
    triplet_dalitz_low.clear();
    triplet_lowest_pt.clear();
    triplet_largest_eta.clear();
    triplet_pairwise_mass.clear();
    triplet_jet_csv.clear();
    triplet_is_correct.clear();

    jet_num = 0;
    jet_pt.clear();
    jet_eta.clear();

    vertex_num = 0;

    //rho = 0.0;

    run = 0;
    lumi = 0;
    event = 0;

    return;
}


int ResolvedNtuplizer::GetCollections(const edm::Event& iEvent)
{
    // Get collections from ntuple
    // Returns nonzero if there is a problem getting a collection

    // Get jet variables
    iEvent.getByToken(token_jet_pt, jetPt);
    if (!jetPt.isValid()) {
	throw edm::Exception(edm::errors::ProductNotFound)
	    << "Could not find jetPt." << endl;
	return 1;
    }

    iEvent.getByToken(token_jet_eta, jetEta);
    if (!jetEta.isValid()) {
	throw edm::Exception(edm::errors::ProductNotFound)
	    << "Could not find jetEta." << endl;
	return 1;
    }

    iEvent.getByToken(token_jet_phi, jetPhi);
    if (!jetPhi.isValid()) {
	throw edm::Exception(edm::errors::ProductNotFound)
	    << "Could not find jetPhi." << endl;
	return 1;
    }

    iEvent.getByToken(token_jet_E, jetE);
    if (!jetE.isValid()) {
	throw edm::Exception(edm::errors::ProductNotFound)
	    << "Could not find jetE." << endl;
	return 1;
    }

    iEvent.getByToken(token_jet_mass, jetMass);
    if (!jetMass.isValid()) {
	throw edm::Exception(edm::errors::ProductNotFound)
	    << "Could not find jetMass." << endl;
	return 1;
    }

    iEvent.getByToken(token_jet_CSV, jetCSV);
    if (!jetCSV.isValid()) {
	throw edm::Exception(edm::errors::ProductNotFound)
	    << "Could not find jetCSV." << endl;
	return 1;
    }

    // Get vertices
    iEvent.getByToken(token_vertex_z, vertex_z);
    if (!vertex_z.isValid()) {
	throw edm::Exception(edm::errors::ProductNotFound)
	    << "Could not find vertex_z." << endl;
	return 1;
    }

    if (is_signal) {
        // Get gen particles
        iEvent.getByToken(token_genpart_ID, genpart_ID);
        if (!genpart_ID.isValid()) {
            throw edm::Exception(edm::errors::ProductNotFound)
                << "Could not find gen particle ID." << endl;
            return 1;
        }

        iEvent.getByToken(token_genpart_status, genpart_status);
        if (!genpart_status.isValid()) {
            throw edm::Exception(edm::errors::ProductNotFound)
                << "Could not find gen particle status." << endl;
            return 1;
        }

        iEvent.getByToken(token_genpart_momID, genpart_momID);
        if (!genpart_momID.isValid()) {
            throw edm::Exception(edm::errors::ProductNotFound)
                << "Could not find gen particle MomID." << endl;
            return 1;
        }

        iEvent.getByToken(token_genpart_pt, genpart_pt);
        if (!genpart_pt.isValid()) {
            throw edm::Exception(edm::errors::ProductNotFound)
                << "Could not find gen particle pt." << endl;
            return 1;
        }

        iEvent.getByToken(token_genpart_eta, genpart_eta);
        if (!genpart_eta.isValid()) {
            throw edm::Exception(edm::errors::ProductNotFound)
                << "Could not find gen particle eta." << endl;
            return 1;
        }

        iEvent.getByToken(token_genpart_phi, genpart_phi);
        if (!genpart_phi.isValid()) {
            throw edm::Exception(edm::errors::ProductNotFound)
                << "Could not find gen particle phi." << endl;
            return 1;
        }

        iEvent.getByToken(token_genpart_E, genpart_E);
        if (!genpart_E.isValid()) {
            throw edm::Exception(edm::errors::ProductNotFound)
                << "Could not find gen particle E." << endl;
            return 1;
        }
    }

    // Get rho
    /*iEvent.getByToken(token_rho, handle_rho);
    if (!handle_rho.isValid()) {
        throw edm::Exception(edm::errors::ProductNotFound)
	    << "Could not find rho." << endl;
	return 1;
        }*/

    for (unsigned i=0; i<jetPt->size(); ++i) {
        TLorentzVector tmp_vector;
        tmp_vector.SetPtEtaPhiE(jetPt->at(i), jetEta->at(i), jetPhi->at(i),
                                jetE->at(i));
        if (!JetCuts(tmp_vector)) {
            jet.push_back(tmp_vector);
            Ht += jetPt->at(i);
        }
    }

    return 0;
}


void ResolvedNtuplizer::GetGenParticles()
{
    TLorentzVector signal_daughters[6];
    int signal_daughters_matched[6] = {-1, -1, -1, -1, -1, -1};
    int num_to_match = 0;
    for (int unsigned i=0; i<genpart_status->size(); ++i) {
        if (genpart_status->at(i) == 23) {
            int ind = -1;
            if (genpart_momID->at(i) == 6)
                ind = 0;
            else if (genpart_momID->at(i) == 24 && genpart_ID->at(i) > 0)
                ind = 1;
            else if (genpart_momID->at(i) == 24 && genpart_ID->at(i) < 0)
                ind = 2;
            else if (genpart_momID->at(i) == -6)
                ind = 3;
            else if (genpart_momID->at(i) == -24 && genpart_ID->at(i) > 0)
                ind = 4;
            else if (genpart_momID->at(i) == -24 && genpart_ID->at(i) < 0)
                ind = 5;
            else
                continue;

            signal_daughters[ind].SetPtEtaPhiE(genpart_pt->at(i),
                                               genpart_eta->at(i),
                                               genpart_phi->at(i),
                                               genpart_E->at(i));
            signal_daughters_matched[ind] = 0;
            ++num_to_match;
        }
    }

    double match_DeltaR_cut = 0.2;
    double match_pt_cut = 0.25;

    while (num_to_match > 0) {
        double min_DeltaR = 9999.0;
        int min_jet_ind = -1;
        int min_daughter_ind = -1;
        for (int i=0; i<6; ++i) {
            if (signal_daughters_matched[i] != 0)
                continue;

            for (int j=0; j<jet_num; ++j) {
                if (jet_from_triplet[j] != 0)
                    continue;

                double DeltaR = signal_daughters[i].DeltaR(jet[j]);
                if (DeltaR < min_DeltaR) {
                    min_DeltaR = DeltaR;
                    min_daughter_ind = i;
                    min_jet_ind = j;
                }
            }
        }

        signal_daughters_matched[min_daughter_ind] = 1;
        if (min_DeltaR < match_DeltaR_cut
            && fabs(jet[min_jet_ind].Pt()/signal_daughters[min_daughter_ind].Pt()
                    - 1.0) < match_pt_cut) {
            if (min_daughter_ind < 3)
                jet_from_triplet[min_jet_ind] = 1;
            else
                jet_from_triplet[min_jet_ind] = 2;
        }
        --num_to_match;
    }

    return;
}


void ResolvedNtuplizer::MakeTriplets()
{
    for (int i=0; i<jet_num-2; ++i) {
        for (int j=i+1; j<jet_num-1; ++j) {
            for (int k=j+1; k<jet_num; ++k) {
                TLorentzVector triplet_vector = jet[i] + jet[j] + jet[k];
                double mass = triplet_vector.M();
                double scalar_pt = jet[i].Pt() + jet[j].Pt() + jet[k].Pt();
                triplet_mass.push_back(mass);
                triplet_scalar_pt.push_back(scalar_pt);
                triplet_vector_pt.push_back(triplet_vector.Pt());
                triplet_eta.push_back(triplet_vector.Eta());
                triplet_phi.push_back(triplet_vector.Phi());
                triplet_delta.push_back(scalar_pt - mass);
                triplet_lowest_pt.push_back(jet[k].Pt());
                if (fabs(jet[i].Eta()) > fabs(jet[j].Eta())) {
                    if (fabs(jet[i].Eta()) > fabs(jet[k].Eta()))
                        triplet_largest_eta.push_back(jet[i].Eta());
                    else
                        triplet_largest_eta.push_back(jet[k].Eta());
                } else {
                    if (fabs(jet[j].Eta()) > fabs(jet[k].Eta()))
                        triplet_largest_eta.push_back(jet[j].Eta());
                    else
                        triplet_largest_eta.push_back(jet[k].Eta());
                }

                if (is_signal) {
                    if (jet_from_triplet[i] == 1 && jet_from_triplet[j] == 1
                        && jet_from_triplet[k] == 1) {
                        triplet_is_correct.push_back(1);
                    } else if (jet_from_triplet[i] == 2
                               && jet_from_triplet[j] == 2
                               && jet_from_triplet[k] == 2) {
                        triplet_is_correct.push_back(2);
                    } else {
                        triplet_is_correct.push_back(0);
                    }
                }

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

                vector<pair<float, float>> Wb_pairs;
                Wb_pairs.push_back(pair<float, float>((jet[i] + jet[j]).M(),
                                                      jetCSV->at(k)));
                Wb_pairs.push_back(pair<float, float>((jet[i] + jet[k]).M(),
                                                      jetCSV->at(j)));
                Wb_pairs.push_back(pair<float, float>((jet[j] + jet[k]).M(),
                                                      jetCSV->at(i)));
                sort(begin(Wb_pairs), end(Wb_pairs), SortWbPairs);
                vector<float> tmp_pairwise_mass;
                vector<float> tmp_jet_csv;
                for (int l=0; l<3; ++l) {
                    tmp_pairwise_mass.push_back(Wb_pairs[l].first);
                    tmp_jet_csv.push_back(Wb_pairs[l].second);
                }
                triplet_pairwise_mass.push_back(tmp_pairwise_mass);
                triplet_jet_csv.push_back(tmp_jet_csv);
            }
        }
    }

    return;
}


int ResolvedNtuplizer::JetCuts(const TLorentzVector jet_)
{
    // Returns >0 if jet fails cuts
    // Returns  0 is jet passes cuts
    if (fabs(jet_.Eta()) > cut_eta)
        return 0x1;
    if (jet_.Pt() < cut_pt)
        return 2;

    return 0;
}


bool SortWbPairs(const pair<float, float> a, const pair<float, float> b)
{
    return (a.second > b.second);
}


//define this as a plug-in
DEFINE_FWK_MODULE(ResolvedNtuplizer);
