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
    scale(iConfig.getParameter<double>("scale")),
    cut_Ht(iConfig.getParameter<double>("cutHt")),
    cut_JetMaxEta(iConfig.getParameter<double>("cutJetMaxEta")),
    cut_JetMinPt(iConfig.getParameter<double>("cutJetMinPt")),
    cut_JetMinN(iConfig.getParameter<int>("cutJetMinN")),
    cut_JetMaxN(iConfig.getParameter<int>("cutJetMaxN")),
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

    int passSel = Cuts();
    h_PassSel->Fill(passSel, scale);
    if (passSel)
	return;

    h_rawHt->Fill(rawHt, scale);
    h_Ht->Fill(Ht, scale);
    h_nJets->Fill(nJets, scale);
    for (int i=0; i<size_h_jetPt; ++i) {
	if (i + 1 > nJets)
	    break;
	h_jetPt[i]->Fill(jets[0].Pt());
    }

    jets.clear();
    return;
}


// ------- method called once each job just before starting event loop  -------
void ResolvedAnalyzer::beginJob()
{
    edm::Service<TFileService> fs;

    h_PassSel = TH1DInitializer(fs, "h_PassSel", "Event selection failures", 4,
				-0.5, 3.5, "failures", "events");
    h_rawHt = TH1DInitializer(fs, "h_rawHt", "H_{T} of all jets", 200,
			      0.0, 1000.0, "H_{T} [GeV]", "events");
    h_Ht = TH1DInitializer(fs, "h_Ht", "H_{T} of jets that pass cuts", 200,
			   0.0, 1000.0, "H_{T} [GeV]", "events");
    h_nJets = TH1DInitializer(fs, "h_nJets", "Number of jets that make cuts",
			      21, -0.5, 20.5, "number of jets", "events");
    for (int i=0; i<size_h_jetPt; ++i) {
	h_jetPt[i] = TH1DInitializer(fs, "h_jet" + to_string(i+1) + "_Pt",
				     "p_{T} of jet " + to_string(i+1), 200,
				     0.0, 1000.0, "p_{T} [GeV]", "events");
    }
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

    rawHt = 0;
    Ht = 0;
    for (unsigned i=0; i<jetPt->size(); ++i) {
	rawHt += (*jetPt)[i];

	TLorentzVector tmpJet;
	tmpJet.SetPtEtaPhiE((*jetPt)[i], (*jetEta)[i], (*jetPhi)[i],
			    (*jetE)[i]);
	if (!JetCuts(tmpJet)) {
	    jets.push_back(tmpJet);
	    Ht += (*jetPt)[i];
	}
    }
    nJets = jets.size();

    return 0;
}

int ResolvedAnalyzer::JetCuts(const TLorentzVector jet_)
{
    // Returns >0 if jet fails cuts
    // Returns  0 is jet passes cuts
    if (fabs(jet_.Eta()) > cut_JetMaxEta)
	return 1;
    if (jet_.Pt() < jet_.Pt())
	return 2;
    return 0;
}


int ResolvedAnalyzer::Cuts()
{
    // Returns >0 if event fails cuts
    // Returns  0 is event passes cuts
    int passSel_ = 0;

    if (rawHt < cut_Ht)
	passSel_ |= 0x1;
    if (nJets < cut_JetMinN)
	passSel_ |= 0x2;
    if (cut_JetMaxN >= 0 && nJets > cut_JetMaxN)
	passSel_ |= 0x2;

    return passSel_;
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
