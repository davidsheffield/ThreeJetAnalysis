// -*- C++ -*-
//
// Package:    ThreeJetAnalysis/Scouting
// Class:      ScoutingNtuplizer
//
/**\class ScoutingNtuplizer ScoutingNtuplizer.h ThreeJetAnalysis/Scouting/interface/ScoutingNtuplizer.h

 Description: Code to monitor scouting streams.

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  David Sheffield
//         Created:  Wed, 28 Oct 2015
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

class ScoutingNtuplizer : public edm::EDAnalyzer {
public:
    explicit ScoutingNtuplizer(const edm::ParameterSet&);
    ~ScoutingNtuplizer();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
    virtual void beginJob() override;
    virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;
    virtual void ResetVariables();
    virtual int GetCollections(const edm::Event&);
    virtual void MakeTriplets();

    // ----------member data ---------------------------
    edm::EDGetTokenT<ScoutingPFJetCollection> token_jets;
    edm::EDGetTokenT<ScoutingParticleCollection> token_candidates;
    edm::EDGetTokenT<ScoutingVertexCollection> token_vertices;
    edm::EDGetTokenT<double> token_rho;

    edm::Handle<ScoutingPFJetCollection> jets;
    edm::Handle<ScoutingVertexCollection> vertices;
    edm::Handle<double> handle_rho;
    std::vector<TLorentzVector> jet;

    int cut_nJets_min;

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
    std::vector<float> triplet_largest_eta;

    int jet_num;
    std::vector<float> jet_pt;

    int vertex_num;

    float rho;

    int run;
    int lumi;
    int event;
};

void normalizeHistogram(TH1D*);
