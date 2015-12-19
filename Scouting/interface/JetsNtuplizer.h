// -*- C++ -*-
//
// Package:    ThreeJetAnalysis/Scouting
// Class:      JetsNtuplizer
//
/**\class JetsNtuplizer JetsNtuplizer.h ThreeJetAnalysis/Scouting/interface/JetsNtuplizer.h

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
#include <utility>

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

class JetsNtuplizer : public edm::EDAnalyzer {
public:
    explicit JetsNtuplizer(const edm::ParameterSet&);
    ~JetsNtuplizer();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
    virtual void beginJob() override;
    virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;
    virtual void ResetVariables();
    virtual int GetCollections(const edm::Event&);

    // ----------member data ---------------------------
    edm::EDGetTokenT<ScoutingPFJetCollection> token_jets;
    edm::EDGetTokenT<ScoutingParticleCollection> token_candidates;
    edm::EDGetTokenT<ScoutingVertexCollection> token_vertices;
    edm::EDGetTokenT<double> token_rho;

    edm::Handle<ScoutingPFJetCollection> jets;
    edm::Handle<ScoutingParticleCollection> candidates;
    edm::Handle<ScoutingVertexCollection> vertices;
    edm::Handle<double> handle_rho;

    std::string file_name;
    TFile *file;
    TTree *tree;

    int jet_num;
    std::vector<float> jet_pt;
    std::vector<float> jet_eta;
    std::vector<float> jet_phi;
    std::vector<float> jet_mass;
    std::vector<float> jet_csv;
    std::vector<int>   jet_vertex_index;

    int vertex_num;

    float rho;

    int run;
    int lumi;
    int event;
};

bool SortVertexIndices(const std::pair<int, double>,
                       const std::pair<int, double>);
