// -*- C++ -*-
//
// Package:    ThreeJetAnalysis/MonitorScouting
// Class:      MonitorScouting
//
/**\class MonitorScouting MonitorScouting.cc ThreeJetAnalysis/MonitorScouting/src/MonitorScouting.cc

 Description: Code to monitor scouting streams.

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  David Sheffield
//         Created:  Tue, 06 Oct 2015 23:19:04 GMT
//
//

#include "ThreeJetAnalysis/MonitorScouting/interface/MonitorScouting.h"

using namespace std;
using namespace edm;

//
// constructors and destructor
//
MonitorScouting::MonitorScouting(const edm::ParameterSet& iConfig):
    token_jets(consumes<ScoutingPFJetCollection>(
                   iConfig.getParameter<InputTag>("jet_collection"))),
    token_candidates(consumes<ScoutingParticleCollection>(
                         iConfig.getParameter<InputTag>(
                             "candidate_collection"))),
    token_vertices(consumes<ScoutingVertexCollection>(
                       iConfig.getParameter<InputTag>("vertex_collection"))),
    token_MetPt(consumes<double>(iConfig.getParameter<InputTag>("MetPt"))),
    token_MetPhi(consumes<double>(iConfig.getParameter<InputTag>("MetPhi"))),
    token_rho(consumes<double>(iConfig.getParameter<InputTag>("rho")))
{
    //now do what ever initialization is needed
    edm::Service<TFileService> fs;
    TFileDirectory EventAndJets = fs->mkdir("EventAndJets");
    TFileDirectory JetID = fs->mkdir("JetID");
    TFileDirectory Candidate = fs->mkdir("Caniddate");
    TFileDirectory Vertex = fs->mkdir("Vertex");
    TFileDirectory MET = fs->mkdir("MET");

    // Event and jet histograms
    h_nJets = TH1DInitializer(&EventAndJets, "h_nJets", "PF Scouting jets",
                              50, -0.5, 49.5, "number of jets", "events");
    h_pt = TH1DInitializer(&EventAndJets, "h_pt", "PF Scouting jets",
                           200, 0.0, 1000.0, "p_{T} [GeV]", "jets");
    h_eta = TH1DInitializer(&EventAndJets, "h_eta", "PF Scouting jets",
                            100, -3.0, 3.0, "#eta", "jets");
    h_phi = TH1DInitializer(&EventAndJets, "h_phi", "PF Scouting jets",
                            100, -3.1416, 3.1416, "#phi", "jets");
    h_Ht = TH1DInitializer(&EventAndJets, "h_Ht", "PF Scouting jets",
                           200, 0.0, 1000.0, "H_{T} [GeV]", "events");
    h_mass = TH1DInitializer(&EventAndJets, "h_mass", "PF Scouting jets",
                             200, 0.0, 200.0, "mass [GeV]", "jets");
    h_area = TH1DInitializer(&EventAndJets, "h_area", "PF Scouting jets",
                             100, 0.0, 1.0, "jet area", "jets");
    h_pt_ith_jet = TH2DInitializer(&EventAndJets, "h_pt_ith_jet",
                                   "PF Scouting jets",
                                   200, 0.0, 1000.0, 10, 0.5, 10.5,
                                   "p_{T} [GeV]", "ith jet");
    h_nCandidates_per_jet = TH1DInitializer(&EventAndJets,
                                            "h_nCandidates_per_jet",
                                            "PF Scouting jets",
                                            150, 0.0, 150.0,
                                            "number of candidates", "jets");

    // JetID
    h_chargedHadronEnergy = TH1DInitializer(&JetID, "h_chargedHadronEnergy",
                                            "PF Scouting jets",
                                            200, 0.0, 1000.0,
                                            "energy [GeV]", "jets");
    h_neutralHadronEnergy = TH1DInitializer(&JetID, "h_neutralHadronEnergy",
                                            "PF Scouting jets",
                                            200, 0.0, 1000.0,
                                            "energy [GeV]", "jets");
    h_photonEnergy = TH1DInitializer(&JetID, "h_photonEnergy",
                                     "PF Scouting jets",
                                     200, 0.0, 1000.0, "energy [GeV]", "jets");
    h_electronEnergy = TH1DInitializer(&JetID, "h_electronEnergy",
                                       "PF Scouting jets",
                                       200, 0.0, 1000.0, "energy [GeV]", "jets");
    h_muonEnergy = TH1DInitializer(&JetID, "h_muonEnergy", "PF Scouting jets",
                                   200, 0.0, 1000.0, "energy [GeV]", "jets");
    h_HFHadronEnergy = TH1DInitializer(&JetID, "h_HFHadronEnergy",
                                       "PF Scouting jets",
                                       200, 0.0, 1000.0, "energy [GeV]", "jets");
    h_HFEMEnergy = TH1DInitializer(&JetID, "h_HFEMEnergy", "PF Scouting jets",
                                   200, 0.0, 1000.0, "energy [GeV]", "jets");
    h_chargedHadronMultiplicity = TH1DInitializer(&JetID,
                                                  "h_chargedHadronMultiplicity",
                                                  "PF Scouting jets",
                                                  100, 0.0, 100.0,
                                                  "multiplicity", "jets");
    h_neutralHadronMultiplicity = TH1DInitializer(&JetID,
                                                  "h_neutralHadronMultiplicity",
                                                  "PF Scouting jets",
                                                  100, 0.0, 100.0,
                                                  "multiplicity", "jets");
    h_photonMultiplicity = TH1DInitializer(&JetID, "h_photonMultiplicity",
                                           "PF Scouting jets",
                                           100, 0.0, 100.0,
                                           "multiplicity", "jets");
    h_electronMultiplicity = TH1DInitializer(&JetID, "h_electronMultiplicity",
                                             "PF Scouting jets",
                                             100, 0.0, 100.0,
                                             "multiplicity", "jets");
    h_muonMultiplicity = TH1DInitializer(&JetID, "h_muonMultiplicity",
                                         "PF Scouting jets",
                                         100, 0.0, 100.0,
                                         "multiplicity", "jets");
    h_HFHadronMultiplicity = TH1DInitializer(&JetID, "h_HFHadronMultiplicity",
                                             "PF Scouting jets",
                                             100, 0.0, 100.0,
                                             "multiplicity", "jets");
    h_HFEMMultiplicity = TH1DInitializer(&JetID, "h_HFEMMultiplicity",
                                         "PF Scouting jets",
                                         100, 0.0, 100.0,
                                         "multiplicity", "jets");
    h_HOEnergy = TH1DInitializer(&JetID, "h_HOEnergy", "PF Scouting jets",
                                 100, 0.0, 100.0, "energy [GeV]", "jets");
    h_csv = TH1DInitializer(&JetID, "h_csv", "PF Scouting jets",
                            100, -5.0, 5.0, "csv", "jets");
    h_mvaDiscriminator = TH1DInitializer(&JetID, "h_mvaDiscriminator",
                                         "PF Scouting jets", 100, 0.0, 1000.0,
                                         "mvs discriminator", "jets");

    // Candidate
    h_nCandidates = TH1DInitializer(&Candidate, "h_nCandidates",
                                    "PF Scouting jets", 200, 0.0, 1000.0,
                                    "number of candidates", "events");
    h_cand_pt = TH1DInitializer(&Candidate, "h_cand_pt", "PF Scouting jets",
                                200, 0.0, 1000.0, "p_{T} [GeV]", "candidates");
    h_cand_eta = TH1DInitializer(&Candidate, "h_cand_eta", "PF Scouting jets",
                                100, -5.0, 5.0, "#eta", "candidates");
    h_cand_phi = TH1DInitializer(&Candidate, "h_cand_phi", "PF Scouting jets",
                                100, -3.1416, 3.1416, "#phi", "candidates");
    h_cand_mass = TH1DInitializer(&Candidate, "h_cand_mass", "PF Scouting jets",
                                200, 0.0, 5.0, "mass [GeV]", "candidates");
    h_cand_pdgId = TH1DInitializer(&Candidate, "h_cand_pdgId",
                                   "PF Scouting jets", 500, -0.5, 499.5,
                                   "PDG ID", "candidates");
    h_cand_dR = TH1DInitializer(&Candidate, "h_cand_dR", "PF Scouting jets",
                                100, 0.0, 1.5, "#DeltaR", "candidates");
    h_cand_outofrange = TH1DInitializer(&Candidate, "h_cand_outofrange",
                                        "Index out of range",
                                        1, 0.0, 1.0, "", "candidates");

    // Vertex
    h_nVertices = TH1DInitializer(&Vertex, "h_nVertices", "PF Scouting jets",
                                  150, -0.5, 149.5,
                                  "number of vertices", "events");
    h_vert_x = TH1DInitializer(&Vertex, "h_vert_x", "PF Scouting jets",
                               200, -1.0, 1.0, "x [cm?]", "vertices");
    h_vert_y = TH1DInitializer(&Vertex, "h_vert_y", "PF Scouting jets",
                               200, -1.0, 1.0, "y [cm?]", "vertices");
    h_vert_z = TH1DInitializer(&Vertex, "h_vert_z", "PF Scouting jets",
                               200, -30.0, 30.0, "z [cm?]", "vertices");
    h_vert_zError = TH1DInitializer(&Vertex, "h_vert_zError",
                                    "PF Scouting jets", 200, -10.0, 10.0,
                                    "zError [cm?]", "vertices");

    // MET
    h_MetPt = TH1DInitializer(&MET, "h_MetPt", "PF Scouting jets",
                              200, 0.0, 1000.0, "MET [GeV]", "events");
    h_MetPhi = TH1DInitializer(&MET, "h_MetPhi", "PF Scouting jets",
                              100, -3.1416, 3.1416, "phi", "events");
    h_rho = TH1DInitializer(&MET, "h_rho", "PF Scouting jets",
                              200, 0.0, 30.0, "rho", "events");
}


MonitorScouting::~MonitorScouting()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
MonitorScouting::analyze(const edm::Event& iEvent,
                         const edm::EventSetup& iSetup)
{
    // Get jets
    Handle<ScoutingPFJetCollection> jets;
    iEvent.getByToken(token_jets, jets);
    if (!jets.isValid()) {
        throw edm::Exception(edm::errors::ProductNotFound)
            << "Could not find jet collection." << endl;
        return;
    }

    // Get PF candidates
    Handle<ScoutingParticleCollection> handle_candidates;
    iEvent.getByToken(token_candidates, handle_candidates);
    if (!handle_candidates.isValid()) {
        throw edm::Exception(edm::errors::ProductNotFound)
            << "Could not find candidate collection." << endl;
        return;
    }
    ScoutingParticleCollection candidates = *handle_candidates;

    // Get vertices
    Handle<ScoutingVertexCollection> vertices;
    iEvent.getByToken(token_vertices, vertices);
    if (!vertices.isValid()) {
        throw edm::Exception(edm::errors::ProductNotFound)
            << "Could not find vertices collection." << endl;
        return;
    }

    // Get MET
    Handle<double> MetPt;
    iEvent.getByToken(token_MetPt, MetPt);
    if (!MetPt.isValid()) {
        throw edm::Exception(edm::errors::ProductNotFound)
            << "Could not find MetPt." << endl;
        return;
    }
    Handle<double> MetPhi;
    iEvent.getByToken(token_MetPhi, MetPhi);
    if (!MetPhi.isValid()) {
        throw edm::Exception(edm::errors::ProductNotFound)
            << "Could not find MetPhi." << endl;
        return;
    }
    Handle<double> rho;
    iEvent.getByToken(token_rho, rho);
    if (!rho.isValid()) {
        throw edm::Exception(edm::errors::ProductNotFound)
            << "Could not find rho." << endl;
        return;
    }


    h_nJets->Fill(jets->size());

    double Ht = 0;
    int counter = 0;
    for (auto &jet: *jets) {
        ++counter;
        Ht += jet.pt();

        h_pt->Fill(jet.pt());
        h_eta->Fill(jet.eta());
        h_phi->Fill(jet.phi());
        h_mass->Fill(jet.m());
        h_area->Fill(jet.jetArea());
        if (counter <= 10) {
            h_pt_ith_jet->Fill(jet.pt(), counter);
        }

        h_chargedHadronEnergy->Fill(jet.chargedHadronEnergy());
        h_neutralHadronEnergy->Fill(jet.neutralHadronEnergy());
        h_photonEnergy->Fill(jet.photonEnergy());
        h_electronEnergy->Fill(jet.electronEnergy());
        h_muonEnergy->Fill(jet.muonEnergy());
        h_HFHadronEnergy->Fill(jet.HFHadronEnergy());
        h_HFEMEnergy->Fill(jet.HFEMEnergy());
        h_chargedHadronMultiplicity->Fill(jet.chargedHadronMultiplicity());
        h_neutralHadronMultiplicity->Fill(jet.neutralHadronMultiplicity());
        h_photonMultiplicity->Fill(jet.photonMultiplicity());
        h_electronMultiplicity->Fill(jet.electronMultiplicity());
        h_muonMultiplicity->Fill(jet.muonMultiplicity());
        h_HFHadronMultiplicity->Fill(jet.HFHadronMultiplicity());
        h_HFEMMultiplicity->Fill(jet.HFEMMultiplicity());
        h_HOEnergy->Fill(jet.HOEnergy());
        h_csv->Fill(jet.csv());
        h_mvaDiscriminator->Fill(jet.mvaDiscriminator());

        vector<int> candidate_index = jet.constituents();
        h_nCandidates_per_jet->Fill(candidate_index.size());
        h_nCandidates->Fill(candidates.size());
        TLorentzVector jet_vector;
        jet_vector.SetPtEtaPhiM(jet.pt(), jet.eta(), jet.phi(), jet.m());
        for (unsigned int i=0; i<candidate_index.size(); ++i) {
            if (candidate_index[i] >= static_cast<int>(candidates.size())) {
                h_cand_outofrange->Fill(0);
                continue;
            }
            h_cand_pt->Fill(candidates[candidate_index[i]].pt());
            h_cand_eta->Fill(candidates[candidate_index[i]].eta());
            h_cand_phi->Fill(candidates[candidate_index[i]].phi());
            h_cand_mass->Fill(candidates[candidate_index[i]].m());
            h_cand_pdgId->Fill(abs(candidates[candidate_index[i]].pdgId()));
            TLorentzVector candidate_vector;
            candidate_vector.SetPtEtaPhiM(candidates[candidate_index[i]].pt(),
                                          candidates[candidate_index[i]].eta(),
                                          candidates[candidate_index[i]].phi(),
                                          candidates[candidate_index[i]].m());
            h_cand_dR->Fill(candidate_vector.DeltaR(jet_vector));
        }
    }
    h_Ht->Fill(Ht);

    h_nVertices->Fill(vertices->size());
    for (auto &vertex: *vertices) {
        h_vert_x->Fill(vertex.x());
        h_vert_y->Fill(vertex.y());
        h_vert_z->Fill(vertex.z());
        h_vert_zError->Fill(vertex.zError());
    }

    h_MetPt->Fill(*MetPt);
    h_MetPhi->Fill(*MetPhi);
    h_rho->Fill(*rho);

    return;
}


// ------- method called once each job just before starting event loop  -------
void MonitorScouting::beginJob()
{
}

// ------- method called once each job just after ending the event loop  -------
void MonitorScouting::endJob()
{
}


// -- method fills 'descriptions' with the allowed parameters for the module  --
void MonitorScouting::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MonitorScouting);
