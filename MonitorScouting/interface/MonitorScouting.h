// -*- C++ -*-
//
// Package:    ThreeJetAnalysis/MonitorScouting
// Class:      MonitorScouting
//
/**\class MonitorScouting MonitorScouting.h ThreeJetAnalysis/MonitorScouting/interface/MonitorScouting.h

 Description: Code to monitor scouting streams.

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  David Sheffield
//         Created:  Tue, 06 Oct 2015 23:19:04 GMT
//
//


// System include files
#include <memory>
#include <iostream>
#include <vector>

// CMSSW include files
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/Scouting/interface/ScoutingPFJet.h"
#include "DataFormats/Scouting/interface/ScoutingParticle.h"
#include "DataFormats/Scouting/interface/ScoutingVertex.h"
#include "DataFormats/Scouting/interface/ScoutingMuon.h"
#include "DataFormats/Scouting/interface/ScoutingElectron.h"
#include "DataFormats/Scouting/interface/ScoutingPhoton.h"

// Root include files
#include "TLorentzVector.h"

// User include files
#include "ThreeJetAnalysis/Utilities/interface/TH1DInitializer.h"
#include "ThreeJetAnalysis/Utilities/interface/TH2DInitializer.h"

//
// class declaration
//

class MonitorScouting : public edm::EDAnalyzer {
public:
    explicit MonitorScouting(const edm::ParameterSet&);
    ~MonitorScouting();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
    virtual void beginJob() override;
    virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;

    // ----------member data ---------------------------
    edm::EDGetTokenT<ScoutingPFJetCollection> token_jets;
    edm::EDGetTokenT<ScoutingParticleCollection> token_candidates;
    edm::EDGetTokenT<ScoutingVertexCollection> token_vertices;
    edm::EDGetTokenT<double> token_MetPt;
    edm::EDGetTokenT<double> token_MetPhi;
    edm::EDGetTokenT<double> token_rho;
    edm::EDGetTokenT<ScoutingMuonCollection> token_muons;
    edm::EDGetTokenT<ScoutingElectronCollection> token_electrons;
    edm::EDGetTokenT<ScoutingPhotonCollection> token_photons;

    bool dimuon;

    TH1D *h_nJets;
    TH1D *h_pt;
    TH1D *h_eta;
    TH1D *h_phi;
    TH1D *h_Ht;
    TH1D *h_mass;
    TH1D *h_area;
    TH2D *h_pt_ith_jet;
    TH1D *h_nCandidates_per_jet;

    TH1D *h_chargedHadronEnergy;
    TH1D *h_neutralHadronEnergy;
    TH1D *h_photonEnergy;
    TH1D *h_electronEnergy;
    TH1D *h_muonEnergy;
    TH1D *h_HFHadronEnergy;
    TH1D *h_HFEMEnergy;
    TH1D *h_chargedHadronMultiplicity;
    TH1D *h_neutralHadronMultiplicity;
    TH1D *h_photonMultiplicity;
    TH1D *h_electronMultiplicity;
    TH1D *h_muonMultiplicity;
    TH1D *h_HFHadronMultiplicity;
    TH1D *h_HFEMMultiplicity;
    TH1D *h_HOEnergy;
    TH1D *h_csv;
    TH1D *h_mvaDiscriminator;

    TH1D *h_nCandidates;
    TH1D *h_cand_pt;
    TH1D *h_cand_eta;
    TH1D *h_cand_phi;
    TH1D *h_cand_mass;
    TH1D *h_cand_pdgId;
    TH1D *h_cand_dR;
    TH1D *h_cand_outofrange;

    TH1D *h_nVertices;
    TH1D *h_vert_x;
    TH1D *h_vert_y;
    TH1D *h_vert_z;
    TH1D *h_vert_zError;

    TH1D *h_MetPt;
    TH1D *h_MetPhi;
    TH1D *h_rho;

    TH1D *h_muon_num;
    TH1D *h_muon_pt;
    TH1D *h_muon_eta;
    TH1D *h_muon_phi;
    TH1D *h_muon_mass;
    TH1D *h_muon_ecalIso;
    TH1D *h_muon_hcalIso;
    TH1D *h_muon_trackIso;
    TH1D *h_muon_chi2;
    TH1D *h_muon_ndof;
    TH1D *h_muon_charge;
    TH1D *h_muon_dxy;
    TH1D *h_muon_dz;
    TH1D *h_muon_nValidMuonHits;
    TH1D *h_muon_nValidPixelHits;
    TH1D *h_muon_nMatchedStations;
    TH1D *h_muon_nTrackerLayersWithMeasurement;
    TH1D *h_muon_type;
    TH1D *h_muon_isGlobalMuon;
    TH1D *h_muon_isTrackerMuon;
    TH1D *h_dimuon_mass;

    TH1D *h_electron_num;
    TH1D *h_electron_pt;
    TH1D *h_electron_eta;
    TH1D *h_electron_phi;
    TH1D *h_electron_mass;
    TH1D *h_electron_d0;
    TH1D *h_electron_dz;
    TH1D *h_electron_dEtaIn;
    TH1D *h_electron_dPhiIn;
    TH1D *h_electron_sigmaIetaIeta;
    TH1D *h_electron_hOverE;
    TH1D *h_electron_ooEMOop;
    TH1D *h_electron_missingHits;
    TH1D *h_electron_charge;
    TH1D *h_electron_ecalIso;
    TH1D *h_electron_hcalIso;
    TH1D *h_electron_trackIso;

    TH1D *h_photon_num;
    TH1D *h_photon_pt;
    TH1D *h_photon_eta;
    TH1D *h_photon_phi;
    TH1D *h_photon_mass;
    TH1D *h_photon_sigmaIetaIeta;
    TH1D *h_photon_hOverE;
    TH1D *h_photon_ecalIso;
    TH1D *h_photon_hcalIso;
};
