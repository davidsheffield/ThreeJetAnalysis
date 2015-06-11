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

// CMSSW include files
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

// User include files

class ResolvedAnalyzer : public edm::EDAnalyzer {
public:
    explicit ResolvedAnalyzer(const edm::ParameterSet&);
    ~ResolvedAnalyzer();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
    virtual void beginJob() override;
    virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;

    //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
    //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
    /*virtual void beginLuminosityBlock(edm::LuminosityBlock const&,
     *			                edm::EventSetup const&) override;*/
    /*virtual void endLuminosityBlock(edm::LuminosityBlock const&,
     *			              edm::EventSetup const&) override;*/

    // ----------member data ---------------------------
};
