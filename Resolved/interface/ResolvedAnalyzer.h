//
// ResolvedAnalyzer.cc
//
//     Package:  ThreeJetAnalysis/Resolved
//       Class:  ResolvedAnalyzer
//
// Description:  Analyzer for three jet analysis of high mass gluinos with a
//               resolved three jet final state.
//
//      Author:  David G. Sheffield (Rutgers)
//     Created:  Thu, 11 Jun 2015 16:09:19 GMT
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

// User include files
#include "ThreeJetAnalysis/Utilities/interface/TH1DInitializer.h"

class ResolvedAnalyzer : public edm::EDAnalyzer {
public:
    explicit ResolvedAnalyzer(const edm::ParameterSet&);
    ~ResolvedAnalyzer();

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
    edm::EDGetTokenT<std::vector<float>> token_jetPt;
    edm::EDGetTokenT<std::vector<float>> token_jetEta;
    edm::EDGetTokenT<std::vector<float>> token_jetPhi;
    edm::EDGetTokenT<std::vector<float>> token_jetE;
    edm::EDGetTokenT<std::vector<float>> token_jetMass;

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
};
