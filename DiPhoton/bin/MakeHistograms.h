//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Oct 26 16:56:19 2015 by ROOT version 6.02/05
// from TTree events/Tree for scouting diphoton
// found on file: /cms/data26/sheffield/ScoutingDiPhotons/ntuples/scouting_diphoton_ntuple.root
//////////////////////////////////////////////////////////

#ifndef THREEJETANALYSIS_DIPHOTON_MAKEHISTOGRAM_H
#define THREEJETANALYSIS_DIPHOTON_MAKEHISTOGRAM_H

#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLorentzVector.h"

// Header file for the classes stored in the TTree if any.
#include <iostream>
#include <vector>

class MakeHistograms {
public :
    TTree          *fChain;   //!pointer to the analyzed TTree or TChain
    Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

    // Declaration of leaf types
    Int_t           photon_num;
    std::vector<float>   *diphoton_mass;
    std::vector<float>   *photon1_pt;
    std::vector<float>   *photon1_eta;
    std::vector<float>   *photon1_phi;
    std::vector<float>   *photon1_m;
    std::vector<float>   *photon1_sigmaIetaIeta;
    std::vector<float>   *photon1_hOverE;
    std::vector<float>   *photon1_ecalIso;
    std::vector<float>   *photon1_hcalIso;
    std::vector<float>   *photon2_pt;
    std::vector<float>   *photon2_eta;
    std::vector<float>   *photon2_phi;
    std::vector<float>   *photon2_m;
    std::vector<float>   *photon2_sigmaIetaIeta;
    std::vector<float>   *photon2_hOverE;
    std::vector<float>   *photon2_ecalIso;
    std::vector<float>   *photon2_hcalIso;
    Int_t           electron_num;
    std::vector<float>   *dielectron_mass;
    std::vector<float>   *electron1_pt;
    std::vector<float>   *electron1_eta;
    std::vector<float>   *electron1_phi;
    std::vector<float>   *electron1_m;
    std::vector<float>   *electron1_d0;
    std::vector<float>   *electron1_dz;
    std::vector<float>   *electron1_dEtaIn;
    std::vector<float>   *electron1_sigmaIetaIeta;
    std::vector<float>   *electron1_hOverE;
    std::vector<float>   *electron1_ooEMOop;
    std::vector<int>     *electron1_missingHits;
    std::vector<int>     *electron1_charge;
    std::vector<float>   *electron1_ecalIso;
    std::vector<float>   *electron1_hcalIso;
    std::vector<float>   *electron1_trackIso;
    std::vector<float>   *electron2_pt;
    std::vector<float>   *electron2_eta;
    std::vector<float>   *electron2_phi;
    std::vector<float>   *electron2_m;
    std::vector<float>   *electron2_d0;
    std::vector<float>   *electron2_dz;
    std::vector<float>   *electron2_dEtaIn;
    std::vector<float>   *electron2_sigmaIetaIeta;
    std::vector<float>   *electron2_hOverE;
    std::vector<float>   *electron2_ooEMOop;
    std::vector<int>     *electron2_missingHits;
    std::vector<int>     *electron2_charge;
    std::vector<float>   *electron2_ecalIso;
    std::vector<float>   *electron2_hcalIso;
    std::vector<float>   *electron2_trackIso;
    Int_t           muon_num;
    std::vector<float>   *dimuon_mass;
    std::vector<float>   *muon_pt;
    std::vector<float>   *muon_eta;
    std::vector<float>   *muon_phi;
    std::vector<float>   *muon_m;
    std::vector<float>   *muon_charge;
    Float_t         HT;
    Int_t           jet_num;
    std::vector<float>   *jet_pt;
    std::vector<float>   *jet_eta;
    std::vector<float>   *jet_phi;
    std::vector<float>   *jet_m;
    std::vector<float>   *jet_csv;
    Int_t           vertex_num;
    std::vector<float>   *vertex_x;
    std::vector<float>   *vertex_y;
    std::vector<float>   *vertex_z;
    std::vector<float>   *vertex_zError;
    Float_t         MET_pt;
    Float_t         MET_phi;
    Int_t           Run;
    Int_t           Lumi;
    Int_t           Event;

    // List of branches
    TBranch        *b_photon_num;   //!
    TBranch        *b_diphoton_mass;   //!
    TBranch        *b_photon1_pt;   //!
    TBranch        *b_photon1_eta;   //!
    TBranch        *b_photon1_phi;   //!
    TBranch        *b_photon1_m;   //!
    TBranch        *b_photon1_sigmaIetaIeta;   //!
    TBranch        *b_photon1_hOverE;   //!
    TBranch        *b_photon1_ecalIso;   //!
    TBranch        *b_photon1_hcalIso;   //!
    TBranch        *b_photon2_pt;   //!
    TBranch        *b_photon2_eta;   //!
    TBranch        *b_photon2_phi;   //!
    TBranch        *b_photon2_m;   //!
    TBranch        *b_photon2_sigmaIetaIeta;   //!
    TBranch        *b_photon2_hOverE;   //!
    TBranch        *b_photon2_ecalIso;   //!
    TBranch        *b_photon2_hcalIso;   //!
    TBranch        *b_electron_num;   //!
    TBranch        *b_dielectron_mass;   //!
    TBranch        *b_electron1_pt;   //!
    TBranch        *b_electron1_eta;   //!
    TBranch        *b_electron1_phi;   //!
    TBranch        *b_electron1_m;   //!
    TBranch        *b_electron1_d0;   //!
    TBranch        *b_electron1_dz;   //!
    TBranch        *b_electron1_dEtaIn;   //!
    TBranch        *b_electron1_sigmaIetaIeta;   //!
    TBranch        *b_electron1_hOverE;   //!
    TBranch        *b_electron1_ooEMOop;   //!
    TBranch        *b_electron1_missingHits;   //!
    TBranch        *b_electron1_charge;   //!
    TBranch        *b_electron1_ecalIso;   //!
    TBranch        *b_electron1_hcalIso;   //!
    TBranch        *b_electron1_trackIso;   //!
    TBranch        *b_electron2_pt;   //!
    TBranch        *b_electron2_eta;   //!
    TBranch        *b_electron2_phi;   //!
    TBranch        *b_electron2_m;   //!
    TBranch        *b_electron2_d0;   //!
    TBranch        *b_electron2_dz;   //!
    TBranch        *b_electron2_dEtaIn;   //!
    TBranch        *b_electron2_sigmaIetaIeta;   //!
    TBranch        *b_electron2_hOverE;   //!
    TBranch        *b_electron2_ooEMOop;   //!
    TBranch        *b_electron2_missingHits;   //!
    TBranch        *b_electron2_charge;   //!
    TBranch        *b_electron2_ecalIso;   //!
    TBranch        *b_electron2_hcalIso;   //!
    TBranch        *b_electron2_trackIso;   //!
    TBranch        *b_muon_num;   //!
    TBranch        *b_dimuon_mass;   //!
    TBranch        *b_muon_pt;   //!
    TBranch        *b_muon_eta;   //!
    TBranch        *b_muon_phi;   //!
    TBranch        *b_muon_m;   //!
    TBranch        *b_muon_charge;   //!
    TBranch        *b_HT;   //!
    TBranch        *b_jet_num;   //!
    TBranch        *b_jet_pt;   //!
    TBranch        *b_jet_eta;   //!
    TBranch        *b_jet_phi;   //!
    TBranch        *b_jet_m;   //!
    TBranch        *b_jet_csv;   //!
    TBranch        *b_vertex_num;   //!
    TBranch        *b_vertex_x;   //!
    TBranch        *b_vertex_y;   //!
    TBranch        *b_vertex_z;   //!
    TBranch        *b_vertex_zError;   //!
    TBranch        *b_MET_pt;   //!
    TBranch        *b_MET_phi;   //!
    TBranch        *b_Run;   //!
    TBranch        *b_Lumi;   //!
    TBranch        *b_Event;   //!

    MakeHistograms(TTree *tree=0);
    virtual ~MakeHistograms();
    virtual Int_t    Cut(Long64_t entry);
    virtual Int_t    GetEntry(Long64_t entry);
    virtual Long64_t LoadTree(Long64_t entry);
    virtual void     Init(TTree *tree);
    virtual void     Loop();
    virtual Bool_t   Notify();
    virtual void     Show(Long64_t entry = -1);
    virtual void     Make(TString);
    virtual void     InitializeHistograms();

    TFile *file;
    TH1D *h_diphoton_mass;
    TH1D *h_diphoton_mass_eta;
    TH1D *h_diphoton_mass_barrel;
    TH1D *h_diphoton_mass_barrel_eta;
    TH2D *h_eta_phi_all_1;
    TH2D *h_eta_phi_window_1;
    TH2D *h_eta_phi_low_1;
    TH2D *h_eta_phi_up_1;
    TH2D *h_eta_phi_all_2;
    TH2D *h_eta_phi_window_2;
    TH2D *h_eta_phi_low_2;
    TH2D *h_eta_phi_up_2;
    TH1D *h_dR_window;
    TH1D *h_pt_all_1;
    TH1D *h_pt_window_1;
    TH1D *h_pt_low_1;
    TH1D *h_pt_up_1;
    TH1D *h_pt_all_2;
    TH1D *h_pt_window_2;
    TH1D *h_pt_low_2;
    TH1D *h_pt_up_2;
    TH1D *h_dimuon_mass_low;
    TH1D *h_dimuon_mass_high;

    int last_Run;
    int last_Lumi;
};

TH1D* TH1DInitialize(const TString, const TString, const Int_t, const Double_t,
                     const Double_t, const TString, const TString);
TH2D* TH2DInitialize(const TString, const TString, const Int_t, const Double_t,
                     const Double_t, const Int_t, const Double_t,
                     const Double_t, const TString, const TString);
#endif
