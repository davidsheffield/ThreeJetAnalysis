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
    token_rho(consumes<double>(iConfig.getParameter<InputTag>("rho"))),
    token_muons(consumes<ScoutingMuonCollection>(
                    iConfig.getParameter<InputTag>("muon_collection"))),
    token_electrons(consumes<ScoutingElectronCollection>(
                        iConfig.getParameter<InputTag>("electron_collection"))),
    token_photons(consumes<ScoutingPhotonCollection>(
                      iConfig.getParameter<InputTag>("photon_collection"))),
    dimuon(iConfig.getParameter<bool>("dimuon"))
{
    //now do what ever initialization is needed
    edm::Service<TFileService> fs;
    TFileDirectory EventAndJets = fs->mkdir("EventAndJets");
    TFileDirectory JetID = fs->mkdir("JetID");
    TFileDirectory Candidate = fs->mkdir("Caniddate");
    TFileDirectory Vertex = fs->mkdir("Vertex");
    TFileDirectory MET = fs->mkdir("MET");
    TFileDirectory Muon;
    TFileDirectory Electron;
    TFileDirectory Photon;
    if (dimuon) {
        Muon = fs->mkdir("Muon");
        Electron = fs->mkdir("Electron");
        Photon = fs->mkdir("Photon");
    }

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

    if (dimuon) {
        // Muon
        h_muon_num = TH1DInitializer(&Muon, "h_muon_num", "PF Scouting Muons",
                                     10, -0.5, 9.5, "number of muons",
                                     "events");
        h_muon_pt = TH1DInitializer(&Muon, "h_muon_pt", "PF Scouting Muons",
                                    500, 0.0, 500.0, "p_{T} [GeV]", "muons");
        h_muon_eta = TH1DInitializer(&Muon, "h_muon_eta", "PF Scouting Muons",
                                     100, -2.4, 2.4, "#eta", "muons");
        h_muon_phi = TH1DInitializer(&Muon, "h_muon_phi", "PF Scouting Muons",
                                  100, -3.1416, 3.1416, "#phi", "muons");
        h_muon_mass = TH1DInitializer(&Muon, "h_muon_mass", "PF Scouting Muons",
                                  200, -1.0, 150.0, "mass [MeV]", "muons");
        h_muon_ecalIso = TH1DInitializer(&Muon, "h_muon_ecalIso",
                                         "PF Scouting Muons",
                                         251, -1.0, 250.0, "ECAL Iso",
                                         "muons");
        h_muon_hcalIso = TH1DInitializer(&Muon, "h_muon_hcalIso",
                                         "PF Scouting Muons",
                                         251, -1.0, 250.0, "HCAL Iso",
                                         "muons");
        h_muon_trackIso = TH1DInitializer(&Muon, "h_muon_trackIso",
                                          "PF Scouting Muons", 152, -1, 75.0,
                                          "track Iso", "muons");
        h_muon_chi2 = TH1DInitializer(&Muon, "h_muon_chi2", "PF Scouting Muons",
                                      200, 0.0, 400.0, "#chi^2", "muons");
        h_muon_ndof = TH1DInitializer(&Muon, "h_muon_ndof", "PF Scouting Muons",
                                      200, -0.5, 99.5, "ndof", "muons");
        h_muon_charge = TH1DInitializer(&Muon, "h_muon_charge",
                                        "PF Scouting Muons", 3, -1.5, 1.5,
                                        "charge", "muons");
        h_muon_dxy = TH1DInitializer(&Muon, "h_muon_dxy", "PF Scouting Muons",
                                     200, -30.0, 30.0, "dxy [cm]", "muons");
        h_muon_dz = TH1DInitializer(&Muon, "h_muon_dz", "PF Scouting Muons",
                                    200, -50.0, 50.0, "dz [cm]", "muons");
        h_muon_nValidMuonHits = TH1DInitializer(&Muon, "h_muon_nValidMuonHits",
                                                "PF Scouting Muons",
                                                60, -0.5, 59.5,
                                                "valid muon hits", "muons");
        h_muon_nValidPixelHits = TH1DInitializer(&Muon,
                                                 "h_muon_nValidPixelHits",
                                                 "PF Scouting Muons",
                                                 10, -0.5, 9.5,
                                                 "valid pixel hits", "muons");
        h_muon_nMatchedStations = TH1DInitializer(&Muon,
                                                  "h_muon_nMatchedStations",
                                                  "PF Scouting Muons",
                                                  50, -0.5, 49.5,
                                                  "matched stations", "muons");
        h_muon_nTrackerLayersWithMeasurement = TH1DInitializer(
            &Muon, "h_muon_nTrackerLayersWithMeasurement", "PF Scouting Muons",
            30, -0.5, 29.5, "tracker layers with measurement", "muons");
        h_muon_type = TH1DInitializer(&Muon, "h_muon_type", "PF Scouting Muons",
                                      4, -0.5, 3.5, "type", "muons");
        h_muon_isGlobalMuon = TH1DInitializer(&Muon, "h_muon_isGlobalMuon",
                                              "PF Scouting Muons", 2, -0.5, 1.5,
                                              "isGlobalMuon", "muons");
        h_muon_isTrackerMuon = TH1DInitializer(&Muon, "h_muon_isTrackerMuon",
                                               "PF Scouting Muons",
                                               2, -0.5, 1.5, "isTrackermuon",
                                               "muons");
        h_dimuon_mass = TH1DInitializer(&Muon, "h_dmuon_mass",
                                        "PF Scouting Muons", 300, 0.0, 300.0,
                                        "M_{#mu^{+}#mu^{-}} [GeV]", "events");

        // Electron
        h_electron_num = TH1DInitializer(&Electron, "h_electron_num",
                                         "PF Scouting Muons", 10, -0.5, 9.5,
                                         "number of electrons", "events");
        h_electron_pt = TH1DInitializer(&Electron, "h_electron_pt",
                                        "PF Scouting Muons", 500, 0.0, 500.0,
                                        "p_{T} [GeV]", "electrons");
        h_electron_eta = TH1DInitializer(&Electron, "h_electron_eta",
                                         "PF Scouting Muons", 100, -2.5, 2.5,
                                         "#eta", "electrons");
        h_electron_phi = TH1DInitializer(&Electron, "h_electron_phi",
                                         "PF Scouting Muons",
                                         100, -3.1416, 3.1416, "#phi",
                                         "electrons");
        h_electron_mass = TH1DInitializer(&Electron, "h_electron_mass",
                                          "PF Scouting Muons", 200, -1.0, 1.0,
                                          "mass [MeV]", "electrons");
        h_electron_d0 = TH1DInitializer(&Electron, "h_electron_d0",
                                        "PF Scouting Muons", 200, -30.0, 30.0,
                                        "d0 [cm]", "electrons");
        h_electron_dz = TH1DInitializer(&Electron, "h_electron_dz",
                                        "PF Scouting Muons", 200, -50.0, 50.0,
                                        "dz [cm]", "electrons");
        h_electron_dEtaIn = TH1DInitializer(&Electron, "h_electron_dEtaIn",
                                            "PF Scouting Muons",
                                            200, 0.0, 30.0, "dEtaIn",
                                            "electrons");
        h_electron_dPhiIn = TH1DInitializer(&Electron, "h_electron_dPhiIn",
                                            "PF Scouting Muons",
                                            200, 0.0, 10.0, "dPhiIn",
                                            "electrons");
        h_electron_sigmaIetaIeta = TH1DInitializer(&Electron,
                                                   "h_electron_sigmaIetaIeta",
                                                   "PF Scouting Muons",
                                                   200, -1.0, 1.0,
                                                   "sigmaIetaIeta",
                                                   "electrons");
        h_electron_hOverE = TH1DInitializer(&Electron, "h_electron_hOverE",
                                            "PF Scouting Muons", 200, 0.0, 2.0,
                                            "H/E", "electrons");
        h_electron_ooEMOop = TH1DInitializer(&Electron, "h_electron_ooEMOop",
                                             "PF Scouting Muons",
                                             200, -0.5, 1.5, "1/E - 1/p",
                                             "electrons");
        h_electron_missingHits = TH1DInitializer(&Electron,
                                                 "h_electron_missingHits",
                                                 "PF Scouting Muons",
                                                 15, -0.5, 14.5,
                                                 "missing hits", "electrons");
        h_electron_charge = TH1DInitializer(&Electron, "h_electron_charge",
                                            "PF Scouting Muons", 3, -1.5, 1.5,
                                            "charge", "electrons");
        h_electron_ecalIso = TH1DInitializer(&Electron, "h_electron_ecalIso",
                                             "PF Scouting Muons",
                                             251, -1.0, 250.0, "ECAL Iso",
                                             "electrons");
        h_electron_hcalIso = TH1DInitializer(&Electron, "h_electron_hcalIso",
                                             "PF Scouting Muons",
                                             251, -1.0, 250.0, "HCAL Iso",
                                             "electrons");
        h_electron_trackIso = TH1DInitializer(&Electron, "h_electron_trackIso",
                                              "PF Scouting Muons",
                                              152, -1, 75.0, "track Iso",
                                              "electrons");

        // Photon
        h_photon_num = TH1DInitializer(&Photon, "h_photon_num",
                                       "PF Scouting Muons", 10, -0.5, 9.5,
                                       "number of photons", "events");
        h_photon_pt = TH1DInitializer(&Photon, "h_photon_pt",
                                      "PF Scouting Muons", 500, 0.0, 500.0,
                                      "p_{T} [GeV]", "photons");
        h_photon_eta = TH1DInitializer(&Photon, "h_photon_eta",
                                       "PF Scouting Muons", 100, -2.5, 2.5,
                                       "#eta", "photons");
        h_photon_phi = TH1DInitializer(&Photon, "h_photon_phi",
                                       "PF Scouting Muons",
                                       100, -3.1416, 3.1416, "#phi",
                                       "photons");
        h_photon_mass = TH1DInitializer(&Photon, "h_photon_mass",
                                        "PF Scouting Muons", 200, -1.0, 1.0,
                                        "mass [MeV]", "photons");
        h_photon_sigmaIetaIeta = TH1DInitializer(&Photon,
                                                 "h_photon_sigmaIetaIeta",
                                                 "PF Scouting Muons",
                                                 200, -1.0, 1.0,
                                                 "sigmaIetaIeta",
                                                 "photons");
        h_photon_hOverE = TH1DInitializer(&Photon, "h_photon_hOverE",
                                          "PF Scouting Muons", 200, 0.0, 2.0,
                                          "H/E", "photons");
        h_photon_ecalIso = TH1DInitializer(&Photon, "h_photon_ecalIso",
                                           "PF Scouting Muons",
                                           251, -1.0, 250.0, "ECAL Iso",
                                           "photons");
        h_photon_hcalIso = TH1DInitializer(&Photon, "h_photon_hcalIso",
                                           "PF Scouting Muons",
                                           251, -1.0, 250.0, "HCAL Iso",
                                           "photons");
    }
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

    if (dimuon) {
        // Get muons
        Handle<ScoutingMuonCollection> muons;
        iEvent.getByToken(token_muons, muons);
        if (!muons.isValid()) {
            throw edm::Exception(edm::errors::ProductNotFound)
                << "Could not find muon collection." << endl;
            return;
        }

        // Get electrons
        Handle<ScoutingElectronCollection> electrons;
        iEvent.getByToken(token_electrons, electrons);
        if (!electrons.isValid()) {
            throw edm::Exception(edm::errors::ProductNotFound)
                << "Could not find electron collection." << endl;
            return;
        }

        // Get photons
        Handle<ScoutingPhotonCollection> photons;
        iEvent.getByToken(token_photons, photons);
        if (!photons.isValid()) {
            throw edm::Exception(edm::errors::ProductNotFound)
                << "Could not find photon collection." << endl;
            return;
        }

        h_muon_num->Fill(muons->size());
        for (auto &muon: *muons) {
            h_muon_pt->Fill(muon.pt());
            h_muon_eta->Fill(muon.eta());
            h_muon_phi->Fill(muon.phi());
            h_muon_mass->Fill(muon.m()*1000.0);
            h_muon_ecalIso->Fill(muon.ecalIso());
            h_muon_hcalIso->Fill(muon.hcalIso());
            h_muon_trackIso->Fill(muon.trackIso());
            h_muon_chi2->Fill(muon.chi2());
            h_muon_ndof->Fill(muon.ndof());
            h_muon_charge->Fill(muon.charge());
            h_muon_dxy->Fill(muon.dxy());
            h_muon_dz->Fill(muon.dz());
            h_muon_nValidMuonHits->Fill(muon.nValidMuonHits());
            h_muon_nValidPixelHits->Fill(muon.nValidPixelHits());
            h_muon_nMatchedStations->Fill(muon.nMatchedStations());
            h_muon_nTrackerLayersWithMeasurement->Fill(
                muon.nTrackerLayersWithMeasurement());
            h_muon_type->Fill(muon.type());
            h_muon_isGlobalMuon->Fill(muon.isGlobalMuon());
            h_muon_isTrackerMuon->Fill(muon.isTrackerMuon());
        }

        if (muons->size() == 2) {
            int charge_product = 1.0;
            TLorentzVector dimuon_vector;
            for (auto &muon: *muons) {
                charge_product *= muon.charge();
                TLorentzVector tmp_vector;
                tmp_vector.SetPtEtaPhiM(muon.pt(), muon.eta(), muon.phi(),
                                        muon.m());
                dimuon_vector += tmp_vector;
            }
            if (charge_product < 0)
                h_dimuon_mass->Fill(dimuon_vector.M());
        }

        h_electron_num->Fill(electrons->size());
        for (auto &electron: *electrons) {
            h_electron_pt->Fill(electron.pt());
            h_electron_eta->Fill(electron.eta());
            h_electron_phi->Fill(electron.phi());
            h_electron_mass->Fill(electron.m()*1000.0);
            h_electron_d0->Fill(electron.d0());
            h_electron_dz->Fill(electron.dz());
            h_electron_dEtaIn->Fill(electron.dEtaIn());
            h_electron_dPhiIn->Fill(electron.dPhiIn());
            h_electron_sigmaIetaIeta->Fill(electron.sigmaIetaIeta());
            h_electron_hOverE->Fill(electron.hOverE());
            h_electron_ooEMOop->Fill(electron.ooEMOop());
            h_electron_missingHits->Fill(electron.missingHits());
            h_electron_charge->Fill(electron.charge());
            h_electron_ecalIso->Fill(electron.ecalIso());
            h_electron_hcalIso->Fill(electron.hcalIso());
            h_electron_trackIso->Fill(electron.trackIso());
        }

        h_photon_num->Fill(photons->size());
        for (auto &photon: *photons) {
            h_photon_pt->Fill(photon.pt());
            h_photon_eta->Fill(photon.eta());
            h_photon_phi->Fill(photon.phi());
            h_photon_mass->Fill(photon.m()*1000.0);
            h_photon_sigmaIetaIeta->Fill(photon.sigmaIetaIeta());
            h_photon_hOverE->Fill(photon.hOverE());
            h_photon_ecalIso->Fill(photon.ecalIso());
            h_photon_hcalIso->Fill(photon.hcalIso());
        }
    }

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
