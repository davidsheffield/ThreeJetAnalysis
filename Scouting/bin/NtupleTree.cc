#include "ThreeJetAnalysis/Scouting/bin/NtupleTree.h"

using namespace std;

NtupleTree::NtupleTree(TTree *tree): fChain(0)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
    if (tree == 0) {

#ifdef SINGLE_TREE
        // The following code should be used if you want this class to access
        // a single tree instead of a chain
        TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(
            "Memory Directory");
        if (!f || !f->IsOpen()) {
            f = new TFile("Memory Directory");
        }
        f->GetObject("events",tree);

#else // SINGLE_TREE

        // The following code should be used if you want this class to access a
        // chain of trees.
        TChain * chain = new TChain("events","");
        chain->Add("/eos/uscms/store/user/dgsheffi/ScoutingPFHT/crab_Scouting_Ntuples_v3/151029_181406/0000/scouting_ntuple_2.root/events");
        chain->Add("/eos/uscms/store/user/dgsheffi/ScoutingPFHT/crab_Scouting_Ntuples_v3/151029_181406/0000/scouting_ntuple_3.root/events");
        chain->Add("/eos/uscms/store/user/dgsheffi/ScoutingPFHT/crab_Scouting_Ntuples_v3/151029_181406/0000/scouting_ntuple_4.root/events");
        tree = chain;
#endif // SINGLE_TREE

    }
    Init(tree);
}

NtupleTree::~NtupleTree()
{
    if (!fChain) return;
    delete fChain->GetCurrentFile();
}

Int_t NtupleTree::GetEntry(Long64_t entry)
{
    // Read contents of entry.
    if (!fChain) return 0;
    return fChain->GetEntry(entry);
}

Long64_t NtupleTree::LoadTree(Long64_t entry)
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

void NtupleTree::Init(TTree *tree)
{
    // The Init() function is called when the selector needs to initialize
    // a new tree or chain. Typically here the branch addresses and branch
    // pointers of the tree will be set.
    // It is normally not necessary to make changes to the generated
    // code, but the routine can be extended by the user if needed.
    // Init() will be called many times when running on PROOF
    // (once per file to be processed).

    // Set object pointer
    triplet_mass = 0;
    triplet_scalar_pt = 0;
    triplet_delta = 0;
    triplet_dalitz_high = 0;
    triplet_dalitz_mid = 0;
    triplet_dalitz_low = 0;
    triplet_lowest_pt = 0;
    jet_pt = 0;
    jet_eta = 0;
    jet_phi = 0;
    jet_m = 0;
    jet_csv = 0;
    // Set branch addresses and branch pointers
    if (!tree) return;
    fChain = tree;
    fCurrent = -1;
    fChain->SetMakeClass(1);

    fChain->SetBranchAddress("HT", &HT, &b_HT);
    fChain->SetBranchAddress("triplet_mass", &triplet_mass, &b_triplet_mass);
    fChain->SetBranchAddress("triplet_scalar_pt", &triplet_scalar_pt,
                             &b_triplet_scalar_pt);
    fChain->SetBranchAddress("triplet_delta", &triplet_delta, &b_triplet_delta);
    fChain->SetBranchAddress("triplet_dalitz_high", &triplet_dalitz_high,
                             &b_triplet_dalitz_high);
    fChain->SetBranchAddress("triplet_dalitz_mid", &triplet_dalitz_mid,
                             &b_triplet_dalitz_mid);
    fChain->SetBranchAddress("triplet_dalitz_low", &triplet_dalitz_low,
                             &b_triplet_dalitz_low);
    fChain->SetBranchAddress("triplet_lowest_pt", &triplet_lowest_pt,
                             &b_triplet_lowest_pt);
    fChain->SetBranchAddress("jet_num", &jet_num, &b_jet_num);
    fChain->SetBranchAddress("jet_pt", &jet_pt, &b_jet_pt);
    fChain->SetBranchAddress("jet_eta", &jet_eta, &b_jet_eta);
    fChain->SetBranchAddress("jet_phi", &jet_phi, &b_jet_phi);
    fChain->SetBranchAddress("jet_m", &jet_m, &b_jet_m);
    fChain->SetBranchAddress("jet_csv", &jet_csv, &b_jet_csv);
    fChain->SetBranchAddress("vertex_num", &vertex_num, &b_vertex_num);
    fChain->SetBranchAddress("rho", &rho, &b_rho);
    fChain->SetBranchAddress("Run", &Run, &b_Run);
    fChain->SetBranchAddress("Lumi", &Lumi, &b_Lumi);
    fChain->SetBranchAddress("Event", &Event, &b_Event);
    Notify();
}

Bool_t NtupleTree::Notify()
{
    // The Notify() function is called when a new file is opened. This
    // can be either for a new TTree in a TChain or when when a new TTree
    // is started when using PROOF. It is normally not necessary to make changes
    // to the generated code, but the routine can be extended by the
    // user if needed. The return value is currently not used.

    return kTRUE;
}

void NtupleTree::Show(Long64_t entry)
{
    // Print contents of entry.
    // If entry is not specified, print current entry
    if (!fChain) return;
    fChain->Show(entry);
}

Int_t NtupleTree::Cut(Long64_t entry)
{
    // This function may be called from Loop.
    // returns  0 if entry is accepted.
    // returns >0 otherwise.
    return 0;
}

void NtupleTree::Loop()
{
//   In a ROOT session, you can do:
//      root> .L NtupleTree.C
//      root> NtupleTree t
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
    if (max_events_ < 0 || max_events_ > nentries) {
        cout << "Running on " << nentries << " events." << endl;
    } else {
        cout << "Running on " << max_events_ << " of " << nentries
             << " events." << endl;
        nentries = max_events_;
    }

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        // if (Cut(ientry)) continue;
        if (jentry%report_every_ == 0)
            cout << "Processing event " << jentry << endl;
   }
}

void NtupleTree::MakeHistograms(TString out_file_name, int max_events,
                                int report_every)
{
    max_events_ = max_events;
    report_every_ = report_every;

    out_file = new TFile(out_file_name, "RECREATE");
    Loop();

    out_file->Close();
    return;
}
