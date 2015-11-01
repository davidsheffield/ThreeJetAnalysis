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
        chain->Add("/cms/data26/sheffield/Scouting/ntuples/v4/scouting_ntuple_*.root/events");
        /*chain->Add("/eos/uscms/store/user/dgsheffi/ScoutingPFHT/crab_Scouting_Ntuples_v3/151029_181406/0000/scouting_ntuple_2.root/events");
        chain->Add("/eos/uscms/store/user/dgsheffi/ScoutingPFHT/crab_Scouting_Ntuples_v3/151029_181406/0000/scouting_ntuple_3.root/events");
        chain->Add("/eos/uscms/store/user/dgsheffi/ScoutingPFHT/crab_Scouting_Ntuples_v3/151029_181406/0000/scouting_ntuple_4.root/events");*/
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

void NtupleTree::Cut(Long64_t entry)
{
    // This function may be called from Loop.
    // returns  0 if entry is accepted.
    // returns >0 otherwise.
    passSel_ = 0;

    if (jet_num < cut_nJets_min_)
        passSel_ |= 0x1;
    else if (cut_nJets_max_ > -1 && jet_num > cut_nJets_max_)
        passSel_ |= 0x1;

    if (vertex_num < cut_NPV_min_)
        passSel_ |= 0x2;
    else if (cut_NPV_max_ > -1 && vertex_num > cut_NPV_max_)
        passSel_ |= 0x2;

    return;
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

        if (jentry%report_every_ == 0)
            cout << "Processing event " << jentry << endl;

        Cut(ientry);
        h_passSel->Fill(passSel_);
        if (passSel_)
            continue;

        h_HT->Fill(HT);
        h_nJets->Fill(jet_num);
        for (int i=0; i<jet_num; ++i) {
            h_jet_pt->Fill(jet_pt->at(i));
        }

        for (unsigned int i=0; i<triplet_mass->size(); ++i) {
            h_M_vs_pt->Fill(triplet_scalar_pt->at(i), triplet_mass->at(i));
            h_mass->Fill(triplet_mass->at(i));
            for(int j=0; j<size_h_M_DeltaCut; ++j){
                double delta = 10.0*static_cast<double>(j);
                if (triplet_delta->at(i) > delta)
                    h_M_DeltaCut[j]->Fill(triplet_mass->at(i));
            }
            h_Dalitz->Fill(triplet_dalitz_mid->at(i),
                           triplet_dalitz_high->at(i));
            h_Dalitz->Fill(triplet_dalitz_low->at(i),
                           triplet_dalitz_high->at(i));
            h_Dalitz->Fill(triplet_dalitz_low->at(i),
                           triplet_dalitz_mid->at(i));
        }

        h_vertex_num->Fill(vertex_num);
        h_rho->Fill(rho);
   }
}

void NtupleTree::MakeHistograms(TString out_file_name, int max_events,
                                int report_every)
{
    out_file_name_ = out_file_name;
    max_events_ = max_events;
    report_every_ = report_every;

    cut_nJets_min_ = 6;
    cut_nJets_max_ = -1;
    cut_NPV_min_ = 0;
    cut_NPV_max_ = -1;

    InitializeHistograms();
    Loop();
    WriteHistograms();

    return;
}

void NtupleTree::InitializeHistograms()
{
    h_passSel = TH1DInitializer("h_passSel", "Scouting selection",
                                32, -0.5, 31.5, "", "events");
    h_nJets = TH1DInitializer("h_nJets", "Scouting", 100, -0.5, 99.5,
                              "number of jets", "events");
    h_HT = TH1DInitializer("h_HT", "Scouting", 200, 0.0, 2000.0,
                           "H_{T} [GeV]", "events");
    h_jet_pt = TH1DInitializer("h_jet_pt", "Scouting", 200, 0.0, 2000.0,
                               "p_{T} [GeV]", "jets");
    h_M_vs_pt = TH2DInitializer("h_M_vs_pt", "Scouting", 400, 0.0, 4000.0,
                                400, 0.0, 4000.0, "#Sigma_{jjj} p_{T} [GeV]",
                                "M_{jjj} [GeV]");
    h_mass = TH1DInitializer("h_mass", "Scouting", 500, 0.0, 5000.0,
                             "M_{jjj} [GeV]", "triplets");
    h_vertex_num = TH1DInitializer("h_vertex_num", "Scouting", 100, -0.5, 99.5,
                                   "number of vertices", "events");
    h_rho = TH1DInitializer("h_rho", "Scouting", 200, 0.0, 30.0,
                            "#rho", "events");
    h_Dalitz = TH2DInitializer("h_Dalitz", "Scouting, Dalitz", 100, 0.0, 0.5,
                               100, 0.0, 1.0, "mid, low, low",
                               "high, high, mid");
    for (int i=0; i<size_h_M_DeltaCut; ++i) {
	int delta = 10*i;
	h_M_DeltaCut[i] = TH1DInitializer("h_M_DeltaCut_" + to_string(delta),
					  "Scouting, #Delta = "
					  + to_string(delta),
					  200, 0.0, 1000.0,
					  "M_{jjj} [GeV]", "triplets");
    }

    return;
}

void NtupleTree::WriteHistograms()
{
    out_file = new TFile(out_file_name_, "RECREATE");
    out_file->cd();

    h_passSel->Write();
    h_nJets->Write();
    h_HT->Write();
    h_jet_pt->Write();
    h_M_vs_pt->Write();
    h_mass->Write();
    h_vertex_num->Write();
    h_rho->Write();
    h_Dalitz->Write();

    TDirectory *dir_DeltaCuts = out_file->mkdir("Delta_Cuts");
    dir_DeltaCuts->cd();
    for (int i=0; i<size_h_M_DeltaCut; ++i) {
        h_M_DeltaCut[i]->Write();
    }

    out_file->Close();

    return;
}
