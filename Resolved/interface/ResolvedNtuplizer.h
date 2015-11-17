// -*- C++ -*-
//
// Package:    ThreeJetAnalysis/Resolved
// Class:      ResolvedNtuplizer
//
/**\class ResolvedNtuplizer ResolvedNtuplizer.h ThreeJetAnalysis/Resolved/interface/ResolvedNtuplizer.h

 Description: Code to monitor scouting streams.

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  David Sheffield
//         Created:  Sat, 14 Nov 2015
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

class ResolvedNtuplizer : public edm::EDAnalyzer {
public:
    explicit ResolvedNtuplizer(const edm::ParameterSet&);
    ~ResolvedNtuplizer();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
    virtual void beginJob() override;
    virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;
    virtual void ResetVariables();
    virtual int GetCollections(const edm::Event&);
    virtual void GetGenParticles();
    virtual void MakeTriplets();

    // ----------member data ---------------------------
    edm::EDGetTokenT<std::vector<float>> token_jet_pt;
    edm::EDGetTokenT<std::vector<float>> token_jet_eta;
    edm::EDGetTokenT<std::vector<float>> token_jet_phi;
    edm::EDGetTokenT<std::vector<float>> token_jet_E;
    edm::EDGetTokenT<std::vector<float>> token_jet_mass;
    edm::EDGetTokenT<std::vector<float>> token_jet_CSV;
    edm::EDGetTokenT<std::vector<float>> token_vertex_z;
    edm::EDGetTokenT<std::vector<float>> token_genpart_ID;
    edm::EDGetTokenT<std::vector<float>> token_genpart_status;
    edm::EDGetTokenT<std::vector<float>> token_genpart_momID;
    edm::EDGetTokenT<std::vector<float>> token_genpart_pt;
    edm::EDGetTokenT<std::vector<float>> token_genpart_eta;
    edm::EDGetTokenT<std::vector<float>> token_genpart_phi;
    edm::EDGetTokenT<std::vector<float>> token_genpart_E;

    edm::Handle<std::vector<float>> jetPt;
    edm::Handle<std::vector<float>> jetEta;
    edm::Handle<std::vector<float>> jetPhi;
    edm::Handle<std::vector<float>> jetE;
    edm::Handle<std::vector<float>> jetMass;
    edm::Handle<std::vector<float>> jetCSV;
    edm::Handle<std::vector<float>> vertex_z;
    edm::Handle<std::vector<float>> genpart_ID;
    edm::Handle<std::vector<float>> genpart_status;
    edm::Handle<std::vector<float>> genpart_momID;
    edm::Handle<std::vector<float>> genpart_pt;
    edm::Handle<std::vector<float>> genpart_eta;
    edm::Handle<std::vector<float>> genpart_phi;
    edm::Handle<std::vector<float>> genpart_E;
    //edm::Handle<double> handle_rho;
    std::vector<TLorentzVector> jet;

    int cut_nJets_min;
    bool is_signal;

    std::string file_name;
    TFile *file;
    TTree *tree;

    float Ht;

    std::vector<float> triplet_mass;
    std::vector<float> triplet_scalar_pt;
    std::vector<float> triplet_delta;
    std::vector<float> triplet_dalitz_high;
    std::vector<float> triplet_dalitz_mid;
    std::vector<float> triplet_dalitz_low;
    std::vector<float> triplet_lowest_pt;
    std::vector<int> triplet_is_correct;

    int jet_num;
    std::vector<float> jet_pt;
    std::vector<float> jet_eta;
    std::vector<float> jet_phi;
    std::vector<float> jet_m;
    std::vector<float> jet_csv;

    int vertex_num;

    std::vector<int> jet_from_triplet;

    //float rho;

    int run;
    int lumi;
    int event;
};