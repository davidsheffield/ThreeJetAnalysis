#include "ThreeJetAnalysis/DiPhoton/interface/MakeHistograms.h"

using namespace std;

MakeHistograms::MakeHistograms(TTree *tree) : fChain(0)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
    if (tree == 0) {
        TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/cms/data26/sheffield/ScoutingDiPhotons/ntuples/scouting_diphoton_ntuple.root");
        if (!f || !f->IsOpen()) {
            f = new TFile("/cms/data26/sheffield/ScoutingDiPhotons/ntuples/scouting_diphoton_ntuple.root");
        }
        f->GetObject("events",tree);
    }
    Init(tree);
}

MakeHistograms::~MakeHistograms()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

void MakeHistograms::Loop()
{
//   In a ROOT session, you can do:
//      root> .L MakeHistograms.C
//      root> MakeHistograms t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
    if (fChain == 0) return;

    Long64_t nentries = fChain->GetEntries();
    cout << "Running over " << nentries << " events" << endl;

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        // if (Cut(ientry) < 0) continue;
        if (jentry % 100000 == 0)
            cout << "Processing event " << jentry << endl;

        for (unsigned int i=0; i<diphoton_mass->size(); ++i){
            float mass = (*diphoton_mass)[i];
            h_diphoton_mass->Fill(mass);
            h_diphoton_mass_eta->Fill(mass*1000.0);

            float eta1 = (*photon1_eta)[i];
            float phi1 = (*photon1_phi)[i];
            float eta2 = (*photon2_eta)[i];
            float phi2 = (*photon2_phi)[i];
            h_eta_phi_all_1->Fill(eta1, phi1);
            h_eta_phi_all_2->Fill(eta2, phi2);

            if (mass > 460.0 && mass < 540.0) {
                h_eta_phi_window_1->Fill(eta1, phi1);
                h_eta_phi_window_2->Fill(eta2, phi2);
            } else if (mass > 380.0 && mass < 460.0) {
                h_eta_phi_low_1->Fill(eta1, phi1);
                h_eta_phi_low_2->Fill(eta2, phi2);
            } else if (mass > 540.0 && mass < 620.0) {
                h_eta_phi_up_1->Fill(eta1, phi1);
                h_eta_phi_up_2->Fill(eta2, phi2);
            }
        }
    }
}

Int_t MakeHistograms::GetEntry(Long64_t entry)
{
// Read contents of entry.
    if (!fChain) return 0;
    return fChain->GetEntry(entry);
}
Long64_t MakeHistograms::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
    if (!fChain) return -5;
    Long64_t centry = fChain->LoadTree(entry);
    if (centry < 0) return centry;
    if (fChain->GetTreeNumber() != fCurrent) {
        fCurrent = fChain->GetTreeNumber();
        Notify();
    }
    return centry;
}

void MakeHistograms::Init(TTree *tree)
{
    // The Init() function is called when the selector needs to initialize
    // a new tree or chain. Typically here the branch addresses and branch
    // pointers of the tree will be set.
    // It is normally not necessary to make changes to the generated
    // code, but the routine can be extended by the user if needed.
    // Init() will be called many times when running on PROOF
    // (once per file to be processed).

    // Set object pointer
    diphoton_mass = 0;
    photon1_pt = 0;
    photon1_eta = 0;
    photon1_phi = 0;
    photon1_m = 0;
    photon1_sigmaIetaIeta = 0;
    photon1_hOverE = 0;
    photon1_ecalIso = 0;
    photon1_hcalIso = 0;
    photon2_pt = 0;
    photon2_eta = 0;
    photon2_phi = 0;
    photon2_m = 0;
    photon2_sigmaIetaIeta = 0;
    photon2_hOverE = 0;
    photon2_ecalIso = 0;
    photon2_hcalIso = 0;
    dielectron_mass = 0;
    electron1_pt = 0;
    electron1_eta = 0;
    electron1_phi = 0;
    electron1_m = 0;
    electron1_d0 = 0;
    electron1_dz = 0;
    electron1_dEtaIn = 0;
    electron1_sigmaIetaIeta = 0;
    electron1_hOverE = 0;
    electron1_ooEMOop = 0;
    electron1_missingHits = 0;
    electron1_charge = 0;
    electron1_ecalIso = 0;
    electron1_hcalIso = 0;
    electron1_trackIso = 0;
    electron2_pt = 0;
    electron2_eta = 0;
    electron2_phi = 0;
    electron2_m = 0;
    electron2_d0 = 0;
    electron2_dz = 0;
    electron2_dEtaIn = 0;
    electron2_sigmaIetaIeta = 0;
    electron2_hOverE = 0;
    electron2_ooEMOop = 0;
    electron2_missingHits = 0;
    electron2_charge = 0;
    electron2_ecalIso = 0;
    electron2_hcalIso = 0;
    electron2_trackIso = 0;
    muon_pt = 0;
    muon_eta = 0;
    muon_phi = 0;
    muon_m = 0;
    jet_pt = 0;
    jet_eta = 0;
    jet_phi = 0;
    jet_m = 0;
    jet_csv = 0;
    vertex_x = 0;
    vertex_y = 0;
    vertex_z = 0;
    vertex_zError = 0;
    // Set branch addresses and branch pointers
    if (!tree) return;
    fChain = tree;
    fCurrent = -1;
    fChain->SetMakeClass(1);

    fChain->SetBranchAddress("photon_num", &photon_num, &b_photon_num);
    fChain->SetBranchAddress("diphoton_mass", &diphoton_mass, &b_diphoton_mass);
    fChain->SetBranchAddress("photon1_pt", &photon1_pt, &b_photon1_pt);
    fChain->SetBranchAddress("photon1_eta", &photon1_eta, &b_photon1_eta);
    fChain->SetBranchAddress("photon1_phi", &photon1_phi, &b_photon1_phi);
    fChain->SetBranchAddress("photon1_m", &photon1_m, &b_photon1_m);
    fChain->SetBranchAddress("photon1_sigmaIetaIeta", &photon1_sigmaIetaIeta, &b_photon1_sigmaIetaIeta);
    fChain->SetBranchAddress("photon1_hOverE", &photon1_hOverE, &b_photon1_hOverE);
    fChain->SetBranchAddress("photon1_ecalIso", &photon1_ecalIso, &b_photon1_ecalIso);
    fChain->SetBranchAddress("photon1_hcalIso", &photon1_hcalIso, &b_photon1_hcalIso);
    fChain->SetBranchAddress("photon2_pt", &photon2_pt, &b_photon2_pt);
    fChain->SetBranchAddress("photon2_eta", &photon2_eta, &b_photon2_eta);
    fChain->SetBranchAddress("photon2_phi", &photon2_phi, &b_photon2_phi);
    fChain->SetBranchAddress("photon2_m", &photon2_m, &b_photon2_m);
    fChain->SetBranchAddress("photon2_sigmaIetaIeta", &photon2_sigmaIetaIeta, &b_photon2_sigmaIetaIeta);
    fChain->SetBranchAddress("photon2_hOverE", &photon2_hOverE, &b_photon2_hOverE);
    fChain->SetBranchAddress("photon2_ecalIso", &photon2_ecalIso, &b_photon2_ecalIso);
    fChain->SetBranchAddress("photon2_hcalIso", &photon2_hcalIso, &b_photon2_hcalIso);
    fChain->SetBranchAddress("electron_num", &electron_num, &b_electron_num);
    fChain->SetBranchAddress("dielectron_mass", &dielectron_mass, &b_dielectron_mass);
    fChain->SetBranchAddress("electron1_pt", &electron1_pt, &b_electron1_pt);
    fChain->SetBranchAddress("electron1_eta", &electron1_eta, &b_electron1_eta);
    fChain->SetBranchAddress("electron1_phi", &electron1_phi, &b_electron1_phi);
    fChain->SetBranchAddress("electron1_m", &electron1_m, &b_electron1_m);
    fChain->SetBranchAddress("electron1_d0", &electron1_d0, &b_electron1_d0);
    fChain->SetBranchAddress("electron1_dz", &electron1_dz, &b_electron1_dz);
    fChain->SetBranchAddress("electron1_dEtaIn", &electron1_dEtaIn, &b_electron1_dEtaIn);
    fChain->SetBranchAddress("electron1_sigmaIetaIeta", &electron1_sigmaIetaIeta, &b_electron1_sigmaIetaIeta);
    fChain->SetBranchAddress("electron1_hOverE", &electron1_hOverE, &b_electron1_hOverE);
    fChain->SetBranchAddress("electron1_ooEMOop", &electron1_ooEMOop, &b_electron1_ooEMOop);
    fChain->SetBranchAddress("electron1_missingHits", &electron1_missingHits, &b_electron1_missingHits);
    fChain->SetBranchAddress("electron1_charge", &electron1_charge, &b_electron1_charge);
    fChain->SetBranchAddress("electron1_ecalIso", &electron1_ecalIso, &b_electron1_ecalIso);
    fChain->SetBranchAddress("electron1_hcalIso", &electron1_hcalIso, &b_electron1_hcalIso);
    fChain->SetBranchAddress("electron1_trackIso", &electron1_trackIso, &b_electron1_trackIso);
    fChain->SetBranchAddress("electron2_pt", &electron2_pt, &b_electron2_pt);
    fChain->SetBranchAddress("electron2_eta", &electron2_eta, &b_electron2_eta);
    fChain->SetBranchAddress("electron2_phi", &electron2_phi, &b_electron2_phi);
    fChain->SetBranchAddress("electron2_m", &electron2_m, &b_electron2_m);
    fChain->SetBranchAddress("electron2_d0", &electron2_d0, &b_electron2_d0);
    fChain->SetBranchAddress("electron2_dz", &electron2_dz, &b_electron2_dz);
    fChain->SetBranchAddress("electron2_dEtaIn", &electron2_dEtaIn, &b_electron2_dEtaIn);
    fChain->SetBranchAddress("electron2_sigmaIetaIeta", &electron2_sigmaIetaIeta, &b_electron2_sigmaIetaIeta);
    fChain->SetBranchAddress("electron2_hOverE", &electron2_hOverE, &b_electron2_hOverE);
    fChain->SetBranchAddress("electron2_ooEMOop", &electron2_ooEMOop, &b_electron2_ooEMOop);
    fChain->SetBranchAddress("electron2_missingHits", &electron2_missingHits, &b_electron2_missingHits);
    fChain->SetBranchAddress("electron2_charge", &electron2_charge, &b_electron2_charge);
    fChain->SetBranchAddress("electron2_ecalIso", &electron2_ecalIso, &b_electron2_ecalIso);
    fChain->SetBranchAddress("electron2_hcalIso", &electron2_hcalIso, &b_electron2_hcalIso);
    fChain->SetBranchAddress("electron2_trackIso", &electron2_trackIso, &b_electron2_trackIso);
    fChain->SetBranchAddress("muon_num", &muon_num, &b_muon_num);
    fChain->SetBranchAddress("muon_pt", &muon_pt, &b_muon_pt);
    fChain->SetBranchAddress("muon_eta", &muon_eta, &b_muon_eta);
    fChain->SetBranchAddress("muon_phi", &muon_phi, &b_muon_phi);
    fChain->SetBranchAddress("muon_m", &muon_m, &b_muon_m);
    fChain->SetBranchAddress("HT", &HT, &b_HT);
    fChain->SetBranchAddress("jet_num", &jet_num, &b_jet_num);
    fChain->SetBranchAddress("jet_pt", &jet_pt, &b_jet_pt);
    fChain->SetBranchAddress("jet_eta", &jet_eta, &b_jet_eta);
    fChain->SetBranchAddress("jet_phi", &jet_phi, &b_jet_phi);
    fChain->SetBranchAddress("jet_m", &jet_m, &b_jet_m);
    fChain->SetBranchAddress("jet_csv", &jet_csv, &b_jet_csv);
    fChain->SetBranchAddress("vertex_num", &vertex_num, &b_vertex_num);
    fChain->SetBranchAddress("vertex_x", &vertex_x, &b_vertex_x);
    fChain->SetBranchAddress("vertex_y", &vertex_y, &b_vertex_y);
    fChain->SetBranchAddress("vertex_z", &vertex_z, &b_vertex_z);
    fChain->SetBranchAddress("vertex_zError", &vertex_zError, &b_vertex_zError);
    fChain->SetBranchAddress("MET_pt", &MET_pt, &b_MET_pt);
    fChain->SetBranchAddress("MET_phi", &MET_phi, &b_MET_phi);
    fChain->SetBranchAddress("Run", &Run, &b_Run);
    fChain->SetBranchAddress("Lumi", &Lumi, &b_Lumi);
    fChain->SetBranchAddress("Event", &Event, &b_Event);
    Notify();
}

Bool_t MakeHistograms::Notify()
{
    // The Notify() function is called when a new file is opened. This
    // can be either for a new TTree in a TChain or when when a new TTree
    // is started when using PROOF. It is normally not necessary to make changes
    // to the generated code, but the routine can be extended by the
    // user if needed. The return value is currently not used.

    return kTRUE;
}

void MakeHistograms::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
    if (!fChain) return;
    fChain->Show(entry);
}
Int_t MakeHistograms::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
    return 1;
}

void MakeHistograms::Make(TString file_name)
{
    file = new TFile(file_name, "RECREATE");

    InitializeHistograms();
    Loop();

    cout << "Saving histograms to " << file_name << endl;

    file->cd();
    h_diphoton_mass->Write();
    h_diphoton_mass_eta->Write();
    h_eta_phi_all_1->Write();
    h_eta_phi_all_2->Write();
    h_eta_phi_window_1->Write();
    h_eta_phi_window_2->Write();
    h_eta_phi_low_1->Write();
    h_eta_phi_low_2->Write();
    h_eta_phi_up_1->Write();
    h_eta_phi_up_2->Write();
    file->Close();

    return;
}

void MakeHistograms::InitializeHistograms()
{
    // h_diphoton_mass = new TH1D("h_diphoton_mass", "Scouting PF HT",
    //                            1000, 0.0, 1000.0);
    // h_diphoton_mass->GetXaxis()->SetTitle("M_{#gamma#gamma} [GeV]");
    // h_diphoton_mass->GetYaxis()->SetTitle("events");
    h_diphoton_mass = TH1DInitialize("h_diphoton_mass", "Scouting PF HT",
                                     200, 0.0, 1000.0,
                                     "M_{#gamma#gamma} [GeV]", "events");
    h_diphoton_mass_eta = TH1DInitialize("h_diphoton_mass_eta",
                                         "Scouting PF HT", 200, 0.0, 1000.0,
                                         "M_{#gamma#gamma} [MeV]", "events");
    h_eta_phi_all_1 = TH2DInitialize("h_eta_phi_all_1", "Scouting PF HT",
                                     200, -2.5, 2.5, 200, -3.1416, 3.1416,
                                     "#eta", "#phi");
    h_eta_phi_window_1 = TH2DInitialize("h_eta_phi_window_1", "Scouting PF HT",
                                        200, -2.5, 2.5, 200, -3.1416, 3.1416,
                                        "#eta", "#phi");
    h_eta_phi_low_1 = TH2DInitialize("h_eta_phi_low_1", "Scouting PF HT",
                                     200, -2.5, 2.5, 200, -3.1416, 3.1416,
                                     "#eta", "#phi");
    h_eta_phi_up_1 = TH2DInitialize("h_eta_phi_up_1", "Scouting PF HT",
                                    200, -2.5, 2.5, 200, -3.1416, 3.1416,
                                    "#eta", "#phi");
    h_eta_phi_all_2 = TH2DInitialize("h_eta_phi_all_2", "Scouting PF HT",
                                     200, -2.5, 2.5, 200, -3.1416, 3.1416,
                                     "#eta", "#phi");
    h_eta_phi_window_2 = TH2DInitialize("h_eta_phi_window_2", "Scouting PF HT",
                                        200, -2.5, 2.5, 200, -3.1416, 3.1416,
                                        "#eta", "#phi");
    h_eta_phi_low_2 = TH2DInitialize("h_eta_phi_low_2", "Scouting PF HT",
                                     200, -2.5, 2.5, 200, -3.1416, 3.1416,
                                     "#eta", "#phi");
    h_eta_phi_up_2 = TH2DInitialize("h_eta_phi_up_2", "Scouting PF HT",
                                    200, -2.5, 2.5, 200, -3.1416, 3.1416,
                                    "#eta", "#phi");

    return;
}

TH1D* TH1DInitialize(const TString name, const TString title,
                     const Int_t nbinsx, const Double_t xlow,
                     const Double_t xup, const TString xaxis_title,
                     const TString yaxis_title)
{
    TH1D *histogram = new TH1D(name, title, nbinsx, xlow, xup);
    histogram->GetXaxis()->SetTitle(xaxis_title);
    histogram->GetYaxis()->SetTitle(yaxis_title);
    return histogram;
}

TH2D* TH2DInitialize(const TString name, const TString title,
                     const Int_t nbinsx, const Double_t xlow,
                     const Double_t xup, const Int_t nbinsy,
                     const Double_t ylow, const Double_t yup,
                     const TString xaxis_title, const TString yaxis_title)
{
    TH2D *histogram = new TH2D(name, title, nbinsx, xlow, xup,
                               nbinsy, ylow, yup);
    histogram->GetXaxis()->SetTitle(xaxis_title);
    histogram->GetYaxis()->SetTitle(yaxis_title);
    return histogram;
}
