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

#include "ThreeJetAnalysis/Resolved/interface/ResolvedAnalyzer.h"

ResolvedAnalyzer::ResolvedAnalyzer(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed

}


ResolvedAnalyzer::~ResolvedAnalyzer()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


// ------------ method called for each event  ------------
void
ResolvedAnalyzer::analyze(const edm::Event& iEvent,
			  const edm::EventSetup& iSetup)
{
    using namespace edm;



#ifdef THIS_IS_AN_EVENT_EXAMPLE
    Handle<ExampleData> pIn;
    iEvent.getByLabel("example",pIn);
#endif

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
    ESHandle<SetupData> pSetup;
    iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------- method called once each job just before starting event loop  -------
void ResolvedAnalyzer::beginJob()
{
}

// ------- method called once each job just after ending the event loop  ------
void ResolvedAnalyzer::endJob()
{
}

// ------------ method called when starting to processes a run  ------------
/*
void ResolvedAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void ResolvedAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------- method called when starting to processes a luminosity block  -------
/*
void ResolvedAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&,
					    edm::EventSetup const&)
{
}
*/

// ----- method called when ending the processing of a luminosity block  -----
/*
void ResolvedAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&,
					  edm::EventSetup const&)
{
}
*/

// -- method fills 'descriptions' with the allowed parameters for the module  --
void ResolvedAnalyzer::fillDescriptions(edm::ConfigurationDescriptions&
					descriptions)
{
    // The following says we do not know what parameters are allowed
    // so do no validation
    // Please change this to state exactly what you do use, even if it
    // is no parameters
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(ResolvedAnalyzer);
