// -*- C++ -*-
//
// Package:    ThreeJetAnalysis/MonitorScouting
// Class:      MonitorScouting
//
/**\class MonitorScouting MonitorScouting.cc ThreeJetAnalysis/MonitorScouting/src/MonitorScouting.cc

 Description: Code to monitor scouting streams.

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  David Sheffield
//         Created:  Tue, 06 Oct 2015 23:19:04 GMT
//
//

#include "ThreeJetAnalysis/MonitorScouting/interface/MonitorScouting.h"

using namespace std;
using namespace edm;

//
// constructors and destructor
//
MonitorScouting::MonitorScouting(const edm::ParameterSet& iConfig):
    token_jets(consumes<ScoutingPFJetCollection>(
                  iConfig.getParameter<InputTag>("jet_collection")))
{
    //now do what ever initialization is needed
    edm::Service<TFileService> fs;

    //h_nJets = fs->make<TH1D>("h_nJets", "PF Scouting jets", 100, -0.5, 99.5);
    h_nJets = TH1DInitializer(fs, "h_nJets", "PF Scouting jets",
                              50, -0.5, 49.5, "number of jets", "events");
    h_pt = TH1DInitializer(fs, "h_pt", "PF Scouting jets", 200, 0.0, 1000.0,
                           "p_{T} [GeV]", "jets");
    h_eta = TH1DInitializer(fs, "h_eta", "PF Scouting jets", 100, -3.0, 3.0,
                           "#eta", "jets");
    h_phi = TH1DInitializer(fs, "h_phi", "PF Scouting jets",
                            100, -3.1416, 3.1416, "#phi", "jets");
    h_Ht = TH1DInitializer(fs, "h_Ht", "PF Scouting jets", 200, 0.0, 1000.0,
                           "H_{T} [GeV]", "events");
}


MonitorScouting::~MonitorScouting()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
MonitorScouting::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    Handle<ScoutingPFJetCollection> jets;
    iEvent.getByToken(token_jets, jets);
    if (!jets.isValid()) {
        throw edm::Exception(edm::errors::ProductNotFound)
            << "Could not find jet collection." << endl;
        return;
    }

    h_nJets->Fill(jets->size());

    double Ht = 0;
    for (auto &jet: *jets) {
        Ht += jet.pt();
        h_pt->Fill(jet.pt());
        h_eta->Fill(jet.eta());
        h_phi->Fill(jet.phi());
    }
    h_Ht->Fill(Ht);

    return;
}


// ------- method called once each job just before starting event loop  -------
void MonitorScouting::beginJob()
{
}

// ------- method called once each job just after ending the event loop  -------
void MonitorScouting::endJob()
{
}


// -- method fills 'descriptions' with the allowed parameters for the module  --
void MonitorScouting::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MonitorScouting);
