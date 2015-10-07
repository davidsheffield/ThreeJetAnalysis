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

// Root include files
#include "TLorentzVector.h"
#include "TH1D.h"

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

    TH1D *h_nJets;
    TH1D *h_pt;
    TH1D *h_eta;
    TH1D *h_phi;
    TH1D *h_Ht;
};
