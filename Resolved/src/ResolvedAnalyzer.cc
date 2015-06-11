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

using namespace std;
using namespace edm;

ResolvedAnalyzer::ResolvedAnalyzer(const edm::ParameterSet& iConfig):
    token_jetPt(consumes<vector<float>>(
		    iConfig.getParameter<InputTag>("jetPt"))),
    token_jetEta(consumes<vector<float>>(
		     iConfig.getParameter<InputTag>("jetEta"))),
    token_jetPhi(consumes<vector<float>>(
		     iConfig.getParameter<InputTag>("jetPhi"))),
    token_jetE(consumes<vector<float>>(
		   iConfig.getParameter<InputTag>("jetE"))),
    token_jetMass(consumes<vector<float>>(
		      iConfig.getParameter<InputTag>("jetMass")))
{
    //now do what ever initialization is needed
    edm::Service<TFileService> fs;
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

    int getCollectionsResult = GetCollections(iEvent);
    if (getCollectionsResult)
	return;

    jets.clear();
    return;
}


// ------- method called once each job just before starting event loop  -------
void ResolvedAnalyzer::beginJob()
{
}

// ------- method called once each job just after ending the event loop  ------
void ResolvedAnalyzer::endJob()
{
}


int ResolvedAnalyzer::GetCollections(const edm::Event& iEvent)
{
    // Get collections from ntuple
    // Returns nonzero if there is a problem getting a collection

    // Get jet variables
    Handle<std::vector<float>> jetPt;
    iEvent.getByToken(token_jetPt, jetPt);
    if (!jetPt.isValid()) {
	throw edm::Exception(edm::errors::ProductNotFound)
	    << "Could not find jetPt." << endl;
	return 1;
    }

    Handle<std::vector<float>> jetEta;
    iEvent.getByToken(token_jetEta, jetEta);
    if (!jetEta.isValid()) {
	throw edm::Exception(edm::errors::ProductNotFound)
	    << "Could not find jetEta." << endl;
	return 1;
    }

    Handle<std::vector<float>> jetPhi;
    iEvent.getByToken(token_jetPhi, jetPhi);
    if (!jetPhi.isValid()) {
	throw edm::Exception(edm::errors::ProductNotFound)
	    << "Could not find jetPhi." << endl;
	return 1;
    }

    Handle<std::vector<float>> jetE;
    iEvent.getByToken(token_jetE, jetE);
    if (!jetE.isValid()) {
	throw edm::Exception(edm::errors::ProductNotFound)
	    << "Could not find jetE." << endl;
	return 1;
    }

    Handle<std::vector<float>> jetMass;
    iEvent.getByToken(token_jetMass, jetMass);
    if (!jetMass.isValid()) {
	throw edm::Exception(edm::errors::ProductNotFound)
	    << "Could not find jetMass." << endl;
	return 1;
    }

    for (unsigned i=0; i<jetPt->size(); ++i) {
	TLorentzVector tmpJet;
	tmpJet.SetPtEtaPhiE((*jetPt)[i], (*jetEta)[i], (*jetPhi)[i],
			    (*jetE)[i]);
	if(!JetCuts(tmpJet))
	    jets.push_back(tmpJet);
    }

    return 0;
}

int ResolvedAnalyzer::JetCuts(const TLorentzVector jet_)
{
    // Returns >0 if jet fails cuts
    // Returns  0 is jet passes cuts
    return false;
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
