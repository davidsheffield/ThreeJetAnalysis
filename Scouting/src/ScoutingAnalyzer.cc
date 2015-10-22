//
// ScoutingAnalyzer.cc
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

#include "ThreeJetAnalysis/Scouting/interface/ScoutingAnalyzer.h"

using namespace std;
using namespace edm;

ScoutingAnalyzer::ScoutingAnalyzer(const edm::ParameterSet& iConfig):
    scale(iConfig.getParameter<double>("scale")),
    cut_Ht(iConfig.getParameter<double>("cutHt")),
    cut_JetMaxEta(iConfig.getParameter<double>("cutJetMaxEta")),
    cut_JetMinPt(iConfig.getParameter<double>("cutJetMinPt")),
    cut_JetMinN(iConfig.getParameter<int>("cutJetMinN")),
    cut_JetMaxN(iConfig.getParameter<int>("cutJetMaxN")),
    token_jets(consumes<ScoutingPFJetCollection>(
                   iConfig.getParameter<InputTag>("jet_collection"))),
    token_candidates(consumes<ScoutingParticleCollection>(
                         iConfig.getParameter<InputTag>(
                             "candidate_collection"))),
    token_vertices(consumes<ScoutingVertexCollection>(
                       iConfig.getParameter<InputTag>("vertex_collection")))
{
    //now do what ever initialization is needed
    edm::Service<TFileService> fs;

    h_PassSel = TH1DInitializer(fs, "h_PassSel", "Event selection failures",
				4, -0.5, 3.5, "failures", "events");
    h_rawHt = TH1DInitializer(fs, "h_rawHt", "H_{T} of all jets",
			      200, 0.0, 1000.0, "H_{T} [GeV]", "events");
    h_Ht = TH1DInitializer(fs, "h_Ht", "H_{T} of jets that pass cuts",
			   200, 0.0, 1000.0, "H_{T} [GeV]", "events");
    h_nJets = TH1DInitializer(fs, "h_nJets", "Number of jets that make cuts",
			      26, -0.5, 25.5, "number of jets", "events");
    TFileDirectory dir_jetPts = fs->mkdir("jetPts");
    for (int i=0; i<size_h_jetPt; ++i) {
	h_jetPt[i] = TH1DInitializer(&dir_jetPts,
				     "h_jet" + to_string(i+1) + "_Pt",
				     "p_{T} of jet " + to_string(i+1),
				     200, 0.0, 1000.0, "p_{T} [GeV]", "events");
    }

    h_Mass = TH1DInitializer(fs, "h_Mass", "Mass spectrum of triplets",
			     200, 0.0, 1000.0,
			     "#Sigma|p_{T}| [GeV]", "triplets");
    h_M_vs_Pt = TH2DInitializer(fs, "h_M_vs_Pt",
				"Mass vs. #Sigma|p_{T}| of triplets",
				200, 0.0, 1000.0, 200, 0.0, 1000.0,
				"#Sigma|p_{T}| [GeV]", "M_{jjj} [GeV]");
    TFileDirectory dir_deltaCuts = fs->mkdir("Delta_Cuts");
    for (int i=0; i<size_h_M_DeltaCut; ++i) {
	int delta = 10*i;
	h_M_DeltaCut[i] = TH1DInitializer(&dir_deltaCuts,
					  "h_M_DeltaCut_" + to_string(delta),
					  "Mass for #Delta = "
					  + to_string(delta),
					  200, 0.0, 1000.0,
					  "M_{jjj} [GeV]", "triplets");
    }

    h_jet_vertices = TH1DInitializer(fs, "h_jet_vertices",
                                     "Primary vertex of jets",
                                     51, -1.5, 49.5,
                                     "primary vertex index", "jets");
    h_candidate_vertices = TH1DInitializer(fs, "h_candidate_vertices",
                                           "Primary vertex of PF candidates",
                                           51, -1.5, 49.5,
                                           "primary vertex index",
                                           "candidates");
}


ScoutingAnalyzer::~ScoutingAnalyzer()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


// ------------ method called for each event  ------------
void
ScoutingAnalyzer::analyze(const edm::Event& iEvent,
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
	h_jetPt[i]->Fill(jets[i].Pt());
    }

    for (int i=0; i<nJets-2; ++i) {
	for (int j=i+1; j<nJets-1; ++j) {
	    for (int k=j+1; k<nJets; ++k){
		TLorentzVector tripletVec = jets[i] + jets[j] + jets[k];
		double mass = tripletVec.M();
		double scalarPt = jets[i].Pt() + jets[j].Pt() + jets[k].Pt();

		h_Mass->Fill(mass, scale);
		h_M_vs_Pt->Fill(scalarPt, mass, scale);

		for(int l=0; l<size_h_M_DeltaCut; ++l){
		    double delta = 10.0*static_cast<double>(l);
		    if (mass < scalarPt - delta)
			h_M_DeltaCut[l]->Fill(mass, scale);
		}

	    }
	}
    }

    jets.clear();
    return;
}


// ------- method called once each job just before starting event loop  -------
void ScoutingAnalyzer::beginJob()
{
}

// ------- method called once each job just after ending the event loop  ------
void ScoutingAnalyzer::endJob()
{
}


int ScoutingAnalyzer::GetCollections(const edm::Event& iEvent)
{
    // Get collections from ntuple
    // Returns nonzero if there is a problem getting a collection

    // Get jet collection
    Handle<ScoutingPFJetCollection> handle_jets;
    iEvent.getByToken(token_jets, handle_jets);
    if (!handle_jets.isValid()) {
	throw edm::Exception(edm::errors::ProductNotFound)
	    << "Could not find scouting jet collection." << endl;
	return 1;
    }

    // Get candidate collection
    Handle<ScoutingParticleCollection> handle_candidates;
    iEvent.getByToken(token_candidates, handle_candidates);
    if (!handle_candidates.isValid()) {
	throw edm::Exception(edm::errors::ProductNotFound)
	    << "Could not find scouting candidate collection." << endl;
	return 1;
    }
    ScoutingParticleCollection candidates = *handle_candidates;

    // Get jet collection
    Handle<ScoutingVertexCollection> handle_vertices;
    iEvent.getByToken(token_vertices, handle_vertices);
    if (!handle_vertices.isValid()) {
	throw edm::Exception(edm::errors::ProductNotFound)
	    << "Could not find scouting vertex collection." << endl;
	return 1;
    }
    ScoutingVertexCollection vertices = *handle_vertices;

    /*cout << candidates.size() << " " << vertices.size() << " "
         << vertices[0].x() << " " << vertices[0].y() << " " << vertices[0].z()
         << endl;*/

    rawHt = 0;
    Ht = 0;
    for (auto &jet: *handle_jets) {
	rawHt += jet.pt();

	TLorentzVector tmpJet;
	tmpJet.SetPtEtaPhiM(jet.pt(), jet.eta(), jet.phi(), jet.m());

        vector<int> index_vector;
        for (auto index: jet.constituents()) {
            index_vector.push_back(candidates[index].vertex());
        }
        sort(index_vector.begin(), index_vector.end());
        int mode = -1;
        int count_mode = 0;
        int count_current = 0;
        int last = -1;
        for (auto i: index_vector) {
            h_candidate_vertices->Fill(i);
            if (i == -1)
                continue;
            if (i != last)
                count_current = 0;
            ++count_current;
            if (count_current > count_mode) {
                mode = i;
                count_mode = count_current;
            }
            last = i;
        }
        h_jet_vertices->Fill(mode);

	if (!JetCuts(tmpJet) && mode == 0) {
	    jets.push_back(tmpJet);
	    Ht += jet.pt();
	}
    }
    nJets = jets.size();

    return 0;
}

int ScoutingAnalyzer::JetCuts(const TLorentzVector jet_)
{
    // Returns >0 if jet fails cuts
    // Returns  0 is jet passes cuts
    if (fabs(jet_.Eta()) > cut_JetMaxEta)
	return 1;
    if (jet_.Pt() < cut_JetMinPt)
	return 2;
    return 0;
}


int ScoutingAnalyzer::Cuts()
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
void ScoutingAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void ScoutingAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------- method called when starting to processes a luminosity block  -------
/*
void ScoutingAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&,
					    edm::EventSetup const&)
{
}
*/

// ----- method called when ending the processing of a luminosity block  -----
/*
void ScoutingAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&,
					  edm::EventSetup const&)
{
}
*/

// -- method fills 'descriptions' with the allowed parameters for the module  --
void ScoutingAnalyzer::fillDescriptions(edm::ConfigurationDescriptions&
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
DEFINE_FWK_MODULE(ScoutingAnalyzer);
