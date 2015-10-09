//
// ScoutingAnalyzer.h
//
//     Package:  ThreeJetAnalysis/Scouting
//       Class:  ScoutingAnalyzer
//
// Description:  Analyzer for three jet analysis of low mass gluinos with a
//               resolved three jet final state in scouting data.
//
//      Author:  David G. Sheffield (Rutgers)
//     Created:  Fri, 9 October 2015
//

// System include files
#include <memory>
#include <iostream>
#include <vector>

// CMSSW include files
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/Scouting/interface/ScoutingPFJet.h"
#include "DataFormats/Scouting/interface/ScoutingParticle.h"
#include "DataFormats/Scouting/interface/ScoutingVertex.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

// Root include files
#include "TLorentzVector.h"

// User include files
#include "ThreeJetAnalysis/Utilities/interface/TH1DInitializer.h"
#include "ThreeJetAnalysis/Utilities/interface/TH2DInitializer.h"

class ScoutingAnalyzer : public edm::EDAnalyzer {
public:
    explicit ScoutingAnalyzer(const edm::ParameterSet&);
    ~ScoutingAnalyzer();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
    virtual void beginJob() override;
    virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;
    int GetCollections(const edm::Event&);
    int JetCuts(const TLorentzVector);
    int Cuts();

    //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
    //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
    /*virtual void beginLuminosityBlock(edm::LuminosityBlock const&,
     *			                edm::EventSetup const&) override;*/
    /*virtual void endLuminosityBlock(edm::LuminosityBlock const&,
     *			              edm::EventSetup const&) override;*/

    // ----------member data ---------------------------
    double scale;
    double cut_Ht;
    double cut_JetMaxEta;
    double cut_JetMinPt;
    int cut_JetMinN;
    int cut_JetMaxN;
    edm::EDGetTokenT<ScoutingPFJetCollection> token_jets;

    double rawHt;
    double Ht;
    int nJets;
    std::vector<TLorentzVector> jets;

    TH1D *h_PassSel;
    TH1D *h_rawHt;
    TH1D *h_Ht;
    TH1D *h_nJets;
    static const int size_h_jetPt = 10;
    TH1D *h_jetPt[size_h_jetPt];
    TH1D *h_Mass;
    TH2D *h_M_vs_Pt;
    static const int size_h_M_DeltaCut = 31;
    TH1D *h_M_DeltaCut[size_h_M_DeltaCut];
};
