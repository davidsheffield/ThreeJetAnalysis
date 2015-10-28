// -*- C++ -*-
//
// Package:    ThreeJetAnalysis/DiPhoton
// Class:      DiPhotonNtuplizer
//
/**\class DiPhotonNtuplizer DiPhotonNtuplizer.h ThreeJetAnalysis/DiPhoton/interface/DiPhotonNtuplizer.h

 Description: Code to monitor scouting streams.

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  David Sheffield
//         Created:  Mon, 26 Oct 2015
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
#include "TFile.h"
#include "TTree.h"

// User include files
#include "ThreeJetAnalysis/Utilities/interface/TH1DInitializer.h"
#include "ThreeJetAnalysis/Utilities/interface/TH2DInitializer.h"

//
// class declaration
//

class DiPhotonNtuplizer : public edm::EDAnalyzer {
public:
    explicit DiPhotonNtuplizer(const edm::ParameterSet&);
    ~DiPhotonNtuplizer();

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

    std::string file_name;
    TFile *file;
    TTree *tree;

    int photon_num;
    std::vector<float> diphoton_mass;
    std::vector<float> photon1_pt;
    std::vector<float> photon1_eta;
    std::vector<float> photon1_phi;
    std::vector<float> photon1_m;
    std::vector<float> photon1_sigmaIetaIeta;
    std::vector<float> photon1_hOverE;
    std::vector<float> photon1_ecalIso;
    std::vector<float> photon1_hcalIso;
    std::vector<float> photon2_pt;
    std::vector<float> photon2_eta;
    std::vector<float> photon2_phi;
    std::vector<float> photon2_m;
    std::vector<float> photon2_sigmaIetaIeta;
    std::vector<float> photon2_hOverE;
    std::vector<float> photon2_ecalIso;
    std::vector<float> photon2_hcalIso;

    int electron_num;
    std::vector<float> dielectron_mass;
    std::vector<float> electron1_pt;
    std::vector<float> electron1_eta;
    std::vector<float> electron1_phi;
    std::vector<float> electron1_m;
    std::vector<float> electron1_d0;
    std::vector<float> electron1_dz;
    std::vector<float> electron1_dEtaIn;
    std::vector<float> electron1_dPhiIn;
    std::vector<float> electron1_sigmaIetaIeta;
    std::vector<float> electron1_hOverE;
    std::vector<float> electron1_ooEMOop;
    std::vector<int> electron1_missingHits;
    std::vector<int> electron1_charge;
    std::vector<float> electron1_ecalIso;
    std::vector<float> electron1_hcalIso;
    std::vector<float> electron1_trackIso;
    std::vector<float> electron2_pt;
    std::vector<float> electron2_eta;
    std::vector<float> electron2_phi;
    std::vector<float> electron2_m;
    std::vector<float> electron2_d0;
    std::vector<float> electron2_dz;
    std::vector<float> electron2_dEtaIn;
    std::vector<float> electron2_dPhiIn;
    std::vector<float> electron2_sigmaIetaIeta;
    std::vector<float> electron2_hOverE;
    std::vector<float> electron2_ooEMOop;
    std::vector<int> electron2_missingHits;
    std::vector<int> electron2_charge;
    std::vector<float> electron2_ecalIso;
    std::vector<float> electron2_hcalIso;
    std::vector<float> electron2_trackIso;

    int muon_num;
    std::vector<float> dimuon_mass;
    std::vector<float> muon_pt;
    std::vector<float> muon_eta;
    std::vector<float> muon_phi;
    std::vector<float> muon_m;
    std::vector<int> muon_charge;

    float Ht;
    int jet_num;
    std::vector<float> jet_pt;
    std::vector<float> jet_eta;
    std::vector<float> jet_phi;
    std::vector<float> jet_m;
    std::vector<float> jet_csv;

    int vertex_num;
    std::vector<float> vertex_x;
    std::vector<float> vertex_y;
    std::vector<float> vertex_z;
    std::vector<float> vertex_zError;

    float MET_pt;
    float MET_phi;

    int run;
    int lumi;
    int event;
};

void normalizeHistogram(TH1D*);
