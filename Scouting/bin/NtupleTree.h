//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Oct 29 15:26:49 2015 by ROOT version 6.02/05
// from TChain events/
//////////////////////////////////////////////////////////

#ifndef THREEJETANALYSIS_SCOUTING_NTUPLETREE_H
#define THREEJETANALYSIS_SCOUTING_NTUPLETREE_H

#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"

// Header file for the classes stored in the TTree if any.
#include <iostream>
#include <vector>

class NtupleTree {
public :
    NtupleTree(TTree *tree=0);
    virtual ~NtupleTree();
    virtual void MakeHistograms(TString out_file_name="histograms.root",
                                int max_events=-1, int report_every=100000);

private:
    TTree *fChain;   //!pointer to the analyzed TTree or TChain
    Int_t fCurrent; //!current Tree number in a TChain

    int max_events_;
    int report_every_;
    TFile *out_file;

// Fixed size dimensions of array or collections stored in the TTree if any.

    // Declaration of leaf types
    Float_t              HT;
    std::vector<float>   *triplet_mass;
    std::vector<float>   *triplet_scalar_pt;
    std::vector<float>   *triplet_delta;
    std::vector<float>   *triplet_dalitz_high;
    std::vector<float>   *triplet_dalitz_mid;
    std::vector<float>   *triplet_dalitz_low;
    std::vector<float>   *triplet_lowest_pt;
    Int_t                jet_num;
    std::vector<float>   *jet_pt;
    std::vector<float>   *jet_eta;
    std::vector<float>   *jet_phi;
    std::vector<float>   *jet_m;
    std::vector<float>   *jet_csv;
    Int_t                vertex_num;
    Float_t              rho;
    Int_t                Run;
    Int_t                Lumi;
    Int_t                Event;

    // List of branches
    TBranch *b_HT;
    TBranch *b_triplet_mass;
    TBranch *b_triplet_scalar_pt;
    TBranch *b_triplet_delta;
    TBranch *b_triplet_dalitz_high;
    TBranch *b_triplet_dalitz_mid;
    TBranch *b_triplet_dalitz_low;
    TBranch *b_triplet_lowest_pt;
    TBranch *b_jet_num;
    TBranch *b_jet_pt;
    TBranch *b_jet_eta;
    TBranch *b_jet_phi;
    TBranch *b_jet_m;
    TBranch *b_jet_csv;
    TBranch *b_vertex_num;
    TBranch *b_rho;
    TBranch *b_Run;
    TBranch *b_Lumi;
    TBranch *b_Event;

    virtual Int_t    Cut(Long64_t entry);
    virtual Int_t    GetEntry(Long64_t entry);
    virtual Long64_t LoadTree(Long64_t entry);
    virtual void     Init(TTree *tree);
    virtual void     Loop();
    virtual Bool_t   Notify();
    virtual void     Show(Long64_t entry = -1);
};
#endif
