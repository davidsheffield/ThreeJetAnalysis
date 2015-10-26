// -*- C++ -*-
//
// Package:    ThreeJetAnalysis/DiPhoton
// Class:      DiPhotonNtuplizer
//
/**\class DiPhotonNtuplizer DiPhotonNtuplizer.cc ThreeJetAnalysis/DiPhoton/src/DiPhotonNtuplizer.cc

 Description: Code to monitor scouting streams.

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  David Sheffield
//         Created:  Mon, 26 Oct 2015
//
//

#include "ThreeJetAnalysis/DiPhoton/interface/DiPhotonNtuplizer.h"

using namespace std;
using namespace edm;

//
// constructors and destructor
//
DiPhotonNtuplizer::DiPhotonNtuplizer(const edm::ParameterSet& iConfig):
    token_jets(consumes<ScoutingPFJetCollection>(
                   iConfig.getParameter<InputTag>("jet_collection"))),
    token_candidates(consumes<ScoutingParticleCollection>(
                         iConfig.getParameter<InputTag>(
                             "candidate_collection"))),
    token_vertices(consumes<ScoutingVertexCollection>(
                       iConfig.getParameter<InputTag>("vertex_collection"))),
    token_MetPt(consumes<double>(iConfig.getParameter<InputTag>("MetPt"))),
    token_MetPhi(consumes<double>(iConfig.getParameter<InputTag>("MetPhi"))),
    token_rho(consumes<double>(iConfig.getParameter<InputTag>("rho"))),
    token_muons(consumes<ScoutingMuonCollection>(
                    iConfig.getParameter<InputTag>("muon_collection"))),
    token_electrons(consumes<ScoutingElectronCollection>(
                        iConfig.getParameter<InputTag>("electron_collection"))),
    token_photons(consumes<ScoutingPhotonCollection>(
                      iConfig.getParameter<InputTag>("photon_collection"))),
    file_name(iConfig.getParameter<string>("output_file_name"))
{
    //now do what ever initialization is needed
    file = new TFile(file_name.c_str(), "RECREATE");

    tree = new TTree("events", "Tree for scouting diphoton");

    tree->Branch("photon_num", &photon_num, "photon_num/I");
    tree->Branch("diphoton_mass", &diphoton_mass);
    tree->Branch("photon1_pt", &photon1_pt);
    tree->Branch("photon1_eta", &photon1_eta);
    tree->Branch("photon1_phi", &photon1_phi);
    tree->Branch("photon1_m", &photon1_m);
    tree->Branch("photon1_sigmaIetaIeta", &photon1_sigmaIetaIeta);
    tree->Branch("photon1_hOverE", &photon1_hOverE);
    tree->Branch("photon1_ecalIso", &photon1_ecalIso);
    tree->Branch("photon1_hcalIso", &photon1_hcalIso);
    tree->Branch("photon2_pt", &photon2_pt);
    tree->Branch("photon2_eta", &photon2_eta);
    tree->Branch("photon2_phi", &photon2_phi);
    tree->Branch("photon2_m", &photon2_m);
    tree->Branch("photon2_sigmaIetaIeta", &photon2_sigmaIetaIeta);
    tree->Branch("photon2_hOverE", &photon2_hOverE);
    tree->Branch("photon2_ecalIso", &photon2_ecalIso);
    tree->Branch("photon2_hcalIso", &photon2_hcalIso);

    tree->Branch("electron_num", &electron_num, "electron_num/I");
    tree->Branch("dielectron_mass", &dielectron_mass);
    tree->Branch("electron1_pt", &electron1_pt);
    tree->Branch("electron1_eta", &electron1_eta);
    tree->Branch("electron1_phi", &electron1_phi);
    tree->Branch("electron1_m", &electron1_m);
    tree->Branch("electron1_d0", &electron1_d0);
    tree->Branch("electron1_dz", &electron1_dz);
    tree->Branch("electron1_dEtaIn", &electron1_dEtaIn);
    tree->Branch("electron1_sigmaIetaIeta", &electron1_sigmaIetaIeta);
    tree->Branch("electron1_hOverE", &electron1_hOverE);
    tree->Branch("electron1_ooEMOop", &electron1_ooEMOop);
    tree->Branch("electron1_missingHits", &electron1_missingHits);
    tree->Branch("electron1_charge", &electron1_charge);
    tree->Branch("electron1_ecalIso", &electron1_ecalIso);
    tree->Branch("electron1_hcalIso", &electron1_hcalIso);
    tree->Branch("electron1_trackIso", &electron1_trackIso);
    tree->Branch("electron2_pt", &electron2_pt);
    tree->Branch("electron2_eta", &electron2_eta);
    tree->Branch("electron2_phi", &electron2_phi);
    tree->Branch("electron2_m", &electron2_m);
    tree->Branch("electron2_d0", &electron2_d0);
    tree->Branch("electron2_dz", &electron2_dz);
    tree->Branch("electron2_dEtaIn", &electron2_dEtaIn);
    tree->Branch("electron2_sigmaIetaIeta", &electron2_sigmaIetaIeta);
    tree->Branch("electron2_hOverE", &electron2_hOverE);
    tree->Branch("electron2_ooEMOop", &electron2_ooEMOop);
    tree->Branch("electron2_missingHits", &electron2_missingHits);
    tree->Branch("electron2_charge", &electron2_charge);
    tree->Branch("electron2_ecalIso", &electron2_ecalIso);
    tree->Branch("electron2_hcalIso", &electron2_hcalIso);
    tree->Branch("electron2_trackIso", &electron2_trackIso);

    tree->Branch("muon_num", &muon_num, "muon_num/I");
    tree->Branch("muon_pt", &muon_pt);
    tree->Branch("muon_eta", &muon_eta);
    tree->Branch("muon_phi", &muon_phi);
    tree->Branch("muon_m", &muon_m);

    tree->Branch("HT", &Ht, "HT/F");
    tree->Branch("jet_num", &jet_num, "jet_num/I");
    tree->Branch("jet_pt", &jet_pt);
    tree->Branch("jet_eta", &jet_eta);
    tree->Branch("jet_phi", &jet_phi);
    tree->Branch("jet_m", &jet_m);
    tree->Branch("jet_csv", &jet_csv);

    tree->Branch("vertex_num", &vertex_num, "vertex_num/I");
    tree->Branch("vertex_x", &vertex_x);
    tree->Branch("vertex_y", &vertex_y);
    tree->Branch("vertex_z", &vertex_z);
    tree->Branch("vertex_zError", &vertex_zError);

    tree->Branch("MET_pt", &MET_pt, "MET_pt/F");
    tree->Branch("MET_phi", &MET_phi, "MET_phi/F");

    tree->Branch("Run", &run, "Run/I");
    tree->Branch("Lumi", &lumi, "Lumi/I");
    tree->Branch("Event", &event, "Event/I");
}


DiPhotonNtuplizer::~DiPhotonNtuplizer()
{

    // do anything here that needs to be done at desctruction time
    // (e.g. close files, deallocate resources etc.)
    file->cd();
    tree->Write();
    file->Close();

}


//
// member functions
//

// ------------ method called for each event  ------------
void
DiPhotonNtuplizer::analyze(const edm::Event& iEvent,
                         const edm::EventSetup& iSetup)
{
    photon_num = 0;
    diphoton_mass.clear();
    photon1_pt.clear();
    photon1_eta.clear();
    photon1_phi.clear();
    photon1_m.clear();
    photon1_sigmaIetaIeta.clear();
    photon1_hOverE.clear();
    photon1_ecalIso.clear();
    photon1_hcalIso.clear();
    photon2_pt.clear();
    photon2_eta.clear();
    photon2_phi.clear();
    photon2_m.clear();
    photon2_sigmaIetaIeta.clear();
    photon2_hOverE.clear();
    photon2_ecalIso.clear();
    photon2_hcalIso.clear();

    electron_num = 0;
    dielectron_mass.clear();
    electron1_pt.clear();
    electron1_eta.clear();
    electron1_phi.clear();
    electron1_m.clear();
    electron1_d0.clear();
    electron1_dz.clear();
    electron1_dEtaIn.clear();
    electron1_dPhiIn.clear();
    electron1_sigmaIetaIeta.clear();
    electron1_hOverE.clear();
    electron1_ooEMOop.clear();
    electron1_missingHits.clear();
    electron1_charge.clear();
    electron1_ecalIso.clear();
    electron1_hcalIso.clear();
    electron1_trackIso.clear();
    electron2_pt.clear();
    electron2_eta.clear();
    electron2_phi.clear();
    electron2_m.clear();
    electron2_d0.clear();
    electron2_dz.clear();
    electron2_dEtaIn.clear();
    electron2_dPhiIn.clear();
    electron2_sigmaIetaIeta.clear();
    electron2_hOverE.clear();
    electron2_ooEMOop.clear();
    electron2_missingHits.clear();
    electron2_charge.clear();
    electron2_ecalIso.clear();
    electron2_hcalIso.clear();
    electron2_trackIso.clear();

    muon_num = 0;
    muon_pt.clear();
    muon_eta.clear();
    muon_phi.clear();
    muon_m.clear();

    Ht = 0.0;
    jet_num = 0;
    jet_pt.clear();
    jet_eta.clear();
    jet_phi.clear();
    jet_m.clear();
    jet_csv.clear();

    vertex_num = 0;
    vertex_x.clear();
    vertex_y.clear();
    vertex_z.clear();
    vertex_zError.clear();

    MET_pt = 0.0;
    MET_phi = 0.0;

    run = iEvent.id().run();
    lumi = iEvent.id().luminosityBlock();
    event = iEvent.id().event();

    // Get photons
    Handle<ScoutingPhotonCollection> photons;
    iEvent.getByToken(token_photons, photons);
    if (!photons.isValid()) {
        return;
    }
    ScoutingPhotonCollection photon = *photons;

    // Get electrons
    Handle<ScoutingElectronCollection> electrons;
    iEvent.getByToken(token_electrons, electrons);
    if (!electrons.isValid()) {
        return;
    }
    ScoutingElectronCollection electron = *electrons;

    // Get muons
    Handle<ScoutingMuonCollection> muons;
    iEvent.getByToken(token_muons, muons);
    if (!muons.isValid()) {
        return;
    }

    // Get jets
    Handle<ScoutingPFJetCollection> jets;
    iEvent.getByToken(token_jets, jets);
    if (!jets.isValid()) {
        return;
    }

    // Get vertices
    Handle<ScoutingVertexCollection> vertices;
    iEvent.getByToken(token_vertices, vertices);
    if (!vertices.isValid()) {
        return;
    }

    // Get met
    Handle<double> MetPt;
    iEvent.getByToken(token_MetPt, MetPt);
    if (!MetPt.isValid()) {
        return;
    }
    Handle<double> MetPhi;
    iEvent.getByToken(token_MetPhi, MetPhi);
    if (!MetPhi.isValid()) {
        return;
    }
    MET_pt = *MetPt;
    MET_phi = *MetPhi;

    photon_num = photon.size();
    if (photon_num > 1) {
        for (int i=0; i<photon_num-1; ++i) {
            for (int j=i+1; j<photon_num; ++j) {
                TLorentzVector photon1;
                TLorentzVector photon2;
                photon1.SetPtEtaPhiM(photon[i].pt(), photon[i].eta(),
                                     photon[i].phi(), photon[i].m());
                photon2.SetPtEtaPhiM(photon[j].pt(), photon[j].eta(),
                                     photon[j].phi(), photon[j].m());
                TLorentzVector diphoton_vector = photon1 + photon2;

                diphoton_mass.push_back(diphoton_vector.M());
                photon1_pt.push_back(photon[i].pt());
                photon1_eta.push_back(photon[i].eta());
                photon1_phi.push_back(photon[i].phi());
                photon1_m.push_back(photon[i].m());
                photon1_sigmaIetaIeta.push_back(photon[i].sigmaIetaIeta());
                photon1_hOverE.push_back(photon[i].hOverE());
                photon1_ecalIso.push_back(photon[i].ecalIso());
                photon1_hcalIso.push_back(photon[i].hcalIso());
                photon2_pt.push_back(photon[j].pt());
                photon2_eta.push_back(photon[j].eta());
                photon2_phi.push_back(photon[j].phi());
                photon2_m.push_back(photon[j].m());
                photon2_sigmaIetaIeta.push_back(photon[j].sigmaIetaIeta());
                photon2_hOverE.push_back(photon[j].hOverE());
                photon2_ecalIso.push_back(photon[j].ecalIso());
                photon2_hcalIso.push_back(photon[j].hcalIso());
            }
        }
    }

    electron_num = electron.size();
    if (electron_num > 1) {
        for (int i=0; i<electron_num-1; ++i) {
            for (int j=i+1; j<electron_num; ++j) {
                TLorentzVector electron1;
                TLorentzVector electron2;
                electron1.SetPtEtaPhiM(electron[i].pt(), electron[i].eta(),
                                       electron[i].phi(), electron[i].m());
                electron2.SetPtEtaPhiM(electron[j].pt(), electron[j].eta(),
                                       electron[j].phi(), electron[j].m());
                TLorentzVector dielectron_vector = electron1 + electron2;

                dielectron_mass.push_back(dielectron_vector.M());
                electron1_pt.push_back(electron[i].pt());
                electron1_eta.push_back(electron[i].eta());
                electron1_phi.push_back(electron[i].phi());
                electron1_m.push_back(electron[i].m());
                electron1_d0.push_back(electron[i].d0());
                electron1_dz.push_back(electron[i].dz());
                electron1_dEtaIn.push_back(electron[i].dEtaIn());
                electron1_dPhiIn.push_back(electron[i].dPhiIn());
                electron1_sigmaIetaIeta.push_back(electron[i].sigmaIetaIeta());
                electron1_hOverE.push_back(electron[i].hOverE());
                electron1_ooEMOop.push_back(electron[i].ooEMOop());
                electron1_missingHits.push_back(electron[i].missingHits());
                electron1_charge.push_back(electron[i].charge());
                electron1_ecalIso.push_back(electron[i].ecalIso());
                electron1_hcalIso.push_back(electron[i].hcalIso());
                electron1_trackIso.push_back(electron[i].trackIso());
                electron2_pt.push_back(electron[j].pt());
                electron2_eta.push_back(electron[j].eta());
                electron2_phi.push_back(electron[j].phi());
                electron2_m.push_back(electron[j].m());
                electron2_d0.push_back(electron[j].d0());
                electron2_dz.push_back(electron[j].dz());
                electron2_dEtaIn.push_back(electron[j].dEtaIn());
                electron2_dPhiIn.push_back(electron[j].dPhiIn());
                electron2_sigmaIetaIeta.push_back(electron[j].sigmaIetaIeta());
                electron2_hOverE.push_back(electron[j].hOverE());
                electron2_ooEMOop.push_back(electron[j].ooEMOop());
                electron2_missingHits.push_back(electron[j].missingHits());
                electron2_charge.push_back(electron[j].charge());
                electron2_ecalIso.push_back(electron[j].ecalIso());
                electron2_hcalIso.push_back(electron[j].hcalIso());
                electron2_trackIso.push_back(electron[j].trackIso());
            }
        }
    }

    muon_num = muons->size();
    for (auto &muon: *muons) {
        muon_pt.push_back(muon.pt());
        muon_eta.push_back(muon.eta());
        muon_phi.push_back(muon.phi());
        muon_m.push_back(muon.m());
    }

    jet_num = jets->size();
    for (auto &jet: *jets) {
        Ht += jet.pt();

        jet_pt.push_back(jet.pt());
        jet_eta.push_back(jet.eta());
        jet_phi.push_back(jet.phi());
        jet_m.push_back(jet.m());
        jet_csv.push_back(jet.csv());
    }

    vertex_num = vertices->size();
    for (auto &vertex: *vertices) {
        vertex_x.push_back(vertex.x());
        vertex_y.push_back(vertex.y());
        vertex_z.push_back(vertex.z());
        vertex_zError.push_back(vertex.zError());
    }

    tree->Fill();

    return;
}


// ------- method called once each job just before starting event loop  -------
void DiPhotonNtuplizer::beginJob()
{
}

// ------- method called once each job just after ending the event loop  -------
void DiPhotonNtuplizer::endJob()
{
}


// -- method fills 'descriptions' with the allowed parameters for the module  --
void DiPhotonNtuplizer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

void normalizeHistogram(TH1D *hist)
{
    int nbins = hist->GetNbinsX();
    for (int i=1; i<nbins+1; ++i) {
        double content = hist->GetBinContent(i);
        double error = hist->GetBinError(i);
        double width = hist->GetXaxis()->GetBinWidth(i);
        hist->SetBinContent(i, content/width);
        hist->SetBinError(i, error/width);
    }
    return;
}

//define this as a plug-in
DEFINE_FWK_MODULE(DiPhotonNtuplizer);
