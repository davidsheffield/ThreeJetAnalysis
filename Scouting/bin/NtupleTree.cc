#include "ThreeJetAnalysis/Scouting/bin/NtupleTree.h"

using namespace std;

NtupleTree::NtupleTree(TTree *tree, int isMC): fChain(0), isMC_(isMC),
                                               scale_triplets(false)
{
    // if parameter tree is not specified (or zero), connect the file
    // used to generate this class and read the Tree.
    if (tree == 0) {
        TChain * chain = new TChain("events","");
        chain->Add("/cms/data26/sheffield/Scouting/ntuples/v4/scouting_ntuple_*.root/events");
        tree = chain;
    }
    Init(tree);

    for (int i=0; i< number_of_Dalitz_cuts; ++i) {
        cut_Dalitz_low[i] = 0.01*static_cast<double>(i) + 0.01;
        char str[10];
        sprintf(str, "DalitzCut_%.2f", cut_Dalitz_low[i]);
        Dalitz_cut_name[i] = str;
    }
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
    triplet_vector_pt = 0;
    triplet_eta = 0;
    triplet_phi = 0;
    triplet_delta = 0;
    triplet_dalitz_high = 0;
    triplet_dalitz_mid = 0;
    triplet_dalitz_low = 0;
    triplet_lowest_pt = 0;
    triplet_largest_eta = 0;
    triplet_is_correct = 0;
    triplet_pairwise_mass = 0;
    triplet_jet_csv = 0;
    jet_pt = 0;
    jet_eta = 0;
    // Set branch addresses and branch pointers
    if (!tree) return;
    fChain = tree;
    fCurrent = -1;
    fChain->SetMakeClass(1);

    fChain->SetBranchAddress("HT", &HT, &b_HT);
    fChain->SetBranchAddress("triplet_mass", &triplet_mass, &b_triplet_mass);
    fChain->SetBranchAddress("triplet_scalar_pt", &triplet_scalar_pt,
                             &b_triplet_scalar_pt);
    fChain->SetBranchAddress("triplet_vector_pt", &triplet_vector_pt,
                             &b_triplet_vector_pt);
    fChain->SetBranchAddress("triplet_eta", &triplet_eta, &b_triplet_eta);
    fChain->SetBranchAddress("triplet_phi", &triplet_phi, &b_triplet_phi);
    fChain->SetBranchAddress("triplet_delta", &triplet_delta, &b_triplet_delta);
    fChain->SetBranchAddress("triplet_dalitz_high", &triplet_dalitz_high,
                             &b_triplet_dalitz_high);
    fChain->SetBranchAddress("triplet_dalitz_mid", &triplet_dalitz_mid,
                             &b_triplet_dalitz_mid);
    fChain->SetBranchAddress("triplet_dalitz_low", &triplet_dalitz_low,
                             &b_triplet_dalitz_low);
    fChain->SetBranchAddress("triplet_lowest_pt", &triplet_lowest_pt,
                             &b_triplet_lowest_pt);
    fChain->SetBranchAddress("triplet_largest_eta", &triplet_largest_eta,
                             &b_triplet_largest_eta);
    if (abs(isMC_) == 2) {
        fChain->SetBranchAddress("triplet_is_correct", &triplet_is_correct,
                                 &b_triplet_is_correct);
    }
    fChain->SetBranchAddress("triplet_pairwise_mass", &triplet_pairwise_mass,
                             &b_triplet_pairwise_mass);
    fChain->SetBranchAddress("triplet_jet_csv", &triplet_jet_csv,
                             &b_triplet_jet_csv);
    fChain->SetBranchAddress("jet_num", &jet_num, &b_jet_num);
    fChain->SetBranchAddress("jet_pt", &jet_pt, &b_jet_pt);
    fChain->SetBranchAddress("jet_eta", &jet_eta, &b_jet_eta);
    fChain->SetBranchAddress("vertex_num", &vertex_num, &b_vertex_num);
    if (isMC_ == 0)
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

    if (HT < cut_Ht_)
        passSel_ |= 0x4;

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
        h_passSel->Fill(passSel_, scale_);
        if (passSel_)
            continue;

        HT = 0.0;
        int new_jet_num = 0;
        vector<double> jet_pts;
        for (int i=0; i<jet_num; ++i) {
            if (jet_pt->at(i) < cut_pt_)
                continue;
            if (fabs(jet_eta->at(i)) > cut_eta_)
                continue;

            jet_pts.push_back(jet_pt->at(i));
            HT += jet_pt->at(i);
            ++new_jet_num;
        }
        jet_num = new_jet_num;
        if (jet_num < cut_nJets_min_)
            continue;
        h_HT->Fill(HT, scale_);
        h_nJets->Fill(jet_num, scale_);
        for (int i=0; i<jet_num; ++i) {
            h_jet_pt->Fill(jet_pts[i], scale_);
        }
        h_leading_jet_pt->Fill(jet_pts[0], scale_);

        double comb_factor = new_jet_num/(TMath::Binomial(new_jet_num, 3)*3.0);
        for (unsigned int i=0; i<triplet_mass->size(); ++i) {
            if (triplet_lowest_pt->at(i) < cut_pt_)
                continue;
            if (fabs(triplet_largest_eta->at(i)) > cut_eta_)
                continue;
            h_csv->Fill(triplet_jet_csv->at(i)[0], comb_factor);
            if (triplet_jet_csv->at(i)[0] < 0.95)
                continue;
            if (isMC_ == 2 && triplet_is_correct->at(i) == 0)
                continue;
            if (isMC_ == -2 && triplet_is_correct->at(i) > 0)
                continue;

            double scale_factor = scale_;
            if (scale_triplets) {
                int bin = static_cast<int>(triplet_scalar_pt->at(i)) + 1;
                scale_factor *= h_scales->GetBinContent(bin);
            }

            h_M_vs_pt->Fill(triplet_scalar_pt->at(i), triplet_mass->at(i),
                            scale_factor);
            h_mass->Fill(triplet_mass->at(i), scale_factor);
            h_triplet_scalar_pt->Fill(triplet_scalar_pt->at(i));
            for (int j=0; j<size_h_M_DeltaCut; ++j) {
                double delta = 10.0*static_cast<double>(j);
                if (triplet_delta->at(i) > delta) {
                    h_M_DeltaCut[j]->Fill(triplet_mass->at(i), scale_factor);
                    if (fabs(triplet_mass->at(i) - 173.21) < 30.0) {
                        h_MW_DeltaCut[j]->Fill(triplet_pairwise_mass->at(i)[0],
                                               scale_factor);
                    }
                    h_CSV_vs_M_DeltaCut[j]->Fill(triplet_mass->at(i),
                                                 triplet_jet_csv->at(i)[0],
                                                 scale_factor);
                    h_MW_vs_M_DeltaCut[j]->Fill(triplet_mass->at(i),
                                                triplet_pairwise_mass->at(i)[0],
                                                scale_factor);
                    h_Dalitz_after_DeltaCut[j]->Fill(triplet_dalitz_mid->at(i),
                                                     triplet_dalitz_high->at(i),
                                                     scale_factor);
                    h_Dalitz_after_DeltaCut[j]->Fill(triplet_dalitz_low->at(i),
                                                     triplet_dalitz_high->at(i),
                                                     scale_factor);
                    h_Dalitz_after_DeltaCut[j]->Fill(triplet_dalitz_low->at(i),
                                                     triplet_dalitz_mid->at(i),
                                                     scale_factor);
                    for (int k=0; k<number_of_Dalitz_cuts; ++k) {
                        if (triplet_dalitz_low->at(i) > cut_Dalitz_low[k]) {
                            h_M_DeltaDalitzCut[k][j]->Fill(triplet_mass->at(i),
                                                           scale_factor);
                            h_MW_vs_M_DeltaDalitzCut[k][j]->Fill(
                                triplet_mass->at(i),
                                triplet_pairwise_mass->at(i)[0], scale_factor);
                        }
                    }
                }
            }
            h_Dalitz->Fill(triplet_dalitz_mid->at(i),
                           triplet_dalitz_high->at(i), scale_factor);
            h_Dalitz->Fill(triplet_dalitz_low->at(i),
                           triplet_dalitz_high->at(i), scale_factor);
            h_Dalitz->Fill(triplet_dalitz_low->at(i),
                           triplet_dalitz_mid->at(i), scale_factor);
            double norm_m_low = sqrt(triplet_dalitz_low->at(i));
            double norm_m_mid = sqrt(triplet_dalitz_mid->at(i));
            double norm_m_high = sqrt(triplet_dalitz_high->at(i));
            h_NormalizedMass_midhigh->Fill(norm_m_mid, norm_m_high, scale_factor);
            h_NormalizedMass_lowhigh->Fill(norm_m_low, norm_m_high, scale_factor);
            h_NormalizedMass_lowmid->Fill(norm_m_low, norm_m_mid, scale_factor);
            double one_third = 1.0/3.0;
            double root_one_third = 1.0/sqrt(3.0);
            double dalitz_distance_squared = pow(triplet_dalitz_low->at(i)
                                                 - one_third, 2.0)
                                           + pow(triplet_dalitz_mid->at(i)
                                                 - one_third, 2.0)
                                           + pow(triplet_dalitz_high->at(i)
                                                 - one_third, 2.0);
            double normmass_distance_squared = pow(norm_m_low - root_one_third, 2.0)
                                             + pow(norm_m_mid - root_one_third, 2.0)
                                             + pow(norm_m_high - root_one_third, 2.0);
            h_DalitzDistance->Fill(sqrt(dalitz_distance_squared), scale_factor);
            h_DalitzDistanceSquared->Fill(dalitz_distance_squared, scale_factor);
            h_NormalizedMassDistance->Fill(sqrt(normmass_distance_squared),
                                           scale_factor);
            h_NormalizedMassDistanceSquared->Fill(normmass_distance_squared,
                                                  scale_factor);
            for (int j=0; j<number_of_Dalitz_cuts; ++j) {
                if (triplet_dalitz_low->at(i) > cut_Dalitz_low[j]) {
                    h_Dalitz_after_cut[j]->Fill(triplet_dalitz_mid->at(i),
                                                triplet_dalitz_high->at(i),
                                                scale_factor);
                    h_Dalitz_after_cut[j]->Fill(triplet_dalitz_low->at(i),
                                                triplet_dalitz_high->at(i),
                                                scale_factor);
                    h_Dalitz_after_cut[j]->Fill(triplet_dalitz_low->at(i),
                                                triplet_dalitz_mid->at(i),
                                                scale_factor);
                    h_M_vs_pt_after_Dalitz[j]->Fill(triplet_scalar_pt->at(i),
                                                    triplet_mass->at(i),
                                                    scale_factor);
                }
            }
        }

        h_vertex_num->Fill(vertex_num, scale_);
        if (isMC_ == 0)
            h_rho->Fill(rho, scale_);
   }
}

void NtupleTree::MakeHistograms(TString out_file_name, double scale,
                                int max_events, int report_every,
                                int cut_nJets_min, int cut_nJets_max,
                                int cut_NPV_min, int cut_NPV_max, double cut_Ht,
                                double cut_pt, double cut_eta)
{
    out_file_name_ = out_file_name;
    max_events_ = max_events;
    report_every_ = report_every;

    scale_ = scale;

    cut_nJets_min_ = cut_nJets_min;
    cut_nJets_max_ = cut_nJets_max;
    cut_NPV_min_ = cut_NPV_min;
    cut_NPV_max_ = cut_NPV_max;
    cut_Ht_ = cut_Ht;
    cut_pt_ = cut_pt;
    cut_eta_ = cut_eta;

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
    h_HT = TH1DInitializer("h_HT", "Scouting", 5000, 0.0, 5000.0,
                           "H_{T} [GeV]", "events");
    h_jet_pt = TH1DInitializer("h_jet_pt", "Scouting", 200, 0.0, 2000.0,
                               "p_{T} [GeV]", "jets");
    h_leading_jet_pt = TH1DInitializer("h_leading_jet_pt", "Scouting",
                                       300, 0.0, 3000.0, "leading p_{T} [GeV]",
                                       "events");
    h_M_vs_pt = TH2DInitializer("h_M_vs_pt", "Scouting", 400, 0.0, 4000.0,
                                400, 0.0, 4000.0, "#Sigma_{jjj} |p_{T}| [GeV]",
                                "M_{jjj} [GeV]");
    h_mass = TH1DInitializer("h_mass", "Scouting", 500, 0.0, 5000.0,
                             "M_{jjj} [GeV]", "triplets");
    h_triplet_scalar_pt = TH1DInitializer("h_triplet_scalar_pt", "Scouting",
                                          5000, 0.0, 5000.0,
                                          "#Sigma |p_{T}| [GeV]", "triplets");
    h_vertex_num = TH1DInitializer("h_vertex_num", "Scouting", 100, -0.5, 99.5,
                                   "number of vertices", "events");
    h_rho = TH1DInitializer("h_rho", "Scouting", 200, 0.0, 30.0,
                            "#rho", "events");
    h_Dalitz = TH2DInitializer("h_Dalitz", "Scouting, Dalitz", 100, 0.0, 0.5,
                               100, 0.0, 1.0, "mid, low, low",
                               "high, high, mid");
    h_NormalizedMass_lowmid = TH2DInitializer("h_NormalizedMass_lowmid",
                                              "Scouting",
                                              100, 0.0, 1.0, 100, 0.0, 1.0,
                                              "normalized m_{low}",
                                              "normalized m_{mid}");
    h_NormalizedMass_lowhigh = TH2DInitializer("h_NormalizedMass_lowhigh",
                                               "Scouting",
                                               100, 0.0, 1.0, 100, 0.0, 1.0,
                                               "normalized m_{low}",
                                               "normalized m_{high}");
    h_NormalizedMass_midhigh = TH2DInitializer("h_NormalizedMass_midhigh",
                                               "Scouting",
                                               100, 0.0, 1.0, 100, 0.0, 1.0,
                                               "normalized m_{mid}",
                                               "normalized m_{high}");
    h_DalitzDistance = TH1DInitializer("h_DalitzDistance", "Scouting",
                                       200, 0.0, 1.0, "Dalitz distance",
                                       "triplets");
    h_DalitzDistanceSquared = TH1DInitializer("h_DalitzDistanceSquared",
                                              "Scouting", 200, 0.0, 1.0,
                                              "(Dalitz distance)^{2}",
                                              "triplets");
    h_NormalizedMassDistance = TH1DInitializer("h_NormalizedMassDistance",
                                               "Scouting", 200, 0.0, 1.0,
                                               "Normalized mass distance",
                                               "triplets");
    h_NormalizedMassDistanceSquared = TH1DInitializer("h_NormalizedMassDistanceSquared",
                                                      "Scouting", 200, 0.0, 1.0,
                                                      "(Normalized mass distance)^{2}",
                                                      "triplets");
    h_csv = TH1DInitializer("h_csv", "Scouting", 200, 0.0, 2.0, "CSV", "jets");
    for (int i=0; i<size_h_M_DeltaCut; ++i) {
	int delta = 10*i;
	h_M_DeltaCut[i] = TH1DInitializer("h_M_DeltaCut_" + to_string(delta),
					  "Scouting, #Delta = "
					  + to_string(delta),
					  500, 0.0, 1000.0,
					  "M_{jjj} [GeV]", "triplets");
        h_MW_DeltaCut[i] = TH1DInitializer("h_MW_DeltaCut_" + to_string(delta),
					  "Scouting, #Delta = "
					  + to_string(delta),
					  500, 0.0, 1000.0,
					  "M_{jj} [GeV]", "triplets");
        h_CSV_vs_M_DeltaCut[i] = TH2DInitializer("h_CSV_vs_M_DeltaCut_"
                                                 + to_string(delta),
                                                 "Scouting, #Delta = "
                                                 + to_string(delta),
                                                 500, 0.0, 1000.0,
                                                 100, 0.0, 1.0, "M_{jj} [GeV]",
                                                 "CSV");
        h_MW_vs_M_DeltaCut[i] = TH2DInitializer("h_MW_vs_M_DeltaCut_"
                                                 + to_string(delta),
                                                 "Scouting, #Delta = "
                                                 + to_string(delta),
                                                 500, 0.0, 1000.0,
                                                 250, 0.0, 500.0,
                                                "M_{jjj} [GeV]", "M_{jj} [GeV]");
        h_Dalitz_after_DeltaCut[i] = TH2DInitializer("h_Dalitz_after_DeltaCut_"
                                                     + to_string(delta),
                                                     "Scouting, Delta = "
                                                     + to_string(delta),
                                                     100, 0.0, 0.5,
                                                     100, 0.0, 1.0,
                                                     "mid, low, low",
                                                     "high, high, mid");
    }
    for (int i=0; i<number_of_Dalitz_cuts; ++i) {
        for (int j=0; j<size_h_M_DeltaCut; ++j) {
            int delta = 10*j;
            h_M_DeltaDalitzCut[i][j] = TH1DInitializer(
                "h_M_" + Dalitz_cut_name[i] + "_DeltaCut_" + to_string(delta),
                "Scouting, " + Dalitz_cut_name[i] + " #Delta = "
                + to_string(delta), 500, 0.0, 1000.0, "M_{jjj} [GeV]",
                "triplets");
            h_MW_vs_M_DeltaDalitzCut[i][j] = TH2DInitializer(
                "h_MW_vs_M_" + Dalitz_cut_name[i] + "_DeltaCut_"
                + to_string(delta), "Scouting, " + Dalitz_cut_name[i]
                + " #Delta = " + to_string(delta), 500, 0.0, 1000.0,
                250, 0.0, 500.0, "M_{jjj} [GeV]", "M_{jj} [GeV]");
        }
        h_Dalitz_after_cut[i] = TH2DInitializer("h_Dalitz_cut_"
                                                + Dalitz_cut_name[i],
                                                "Scouting, "
                                                + Dalitz_cut_name[i]
                                                + " Dalitz", 100, 0.0, 0.5,
                                                100, 0.0, 1.0, "mid, low, low",
                                                "high, high, mid");
        h_M_vs_pt_after_Dalitz[i] = TH2DInitializer("h_M_vs_pt_"
                                                    + Dalitz_cut_name[i],
                                                    "Scouting, "
                                                    + Dalitz_cut_name[i]
                                                    + " Dalitz",
                                                    400, 0.0, 4000.0,
                                                    400, 0.0, 4000.0,
                                                    "#Sigma_{jjj} |p_{T}| [GeV]",
                                                    "M_{jjj} [GeV]");
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
    h_leading_jet_pt->Write();
    h_M_vs_pt->Write();
    h_mass->Write();
    h_triplet_scalar_pt->Write();
    h_vertex_num->Write();
    h_rho->Write();
    h_Dalitz->Write();
    h_NormalizedMass_lowmid->Write();
    h_NormalizedMass_lowhigh->Write();
    h_NormalizedMass_midhigh->Write();
    h_DalitzDistance->Write();
    h_DalitzDistanceSquared->Write();
    h_NormalizedMassDistance->Write();
    h_NormalizedMassDistanceSquared->Write();
    h_csv->Write();

    TDirectory *dir_DeltaCuts = out_file->mkdir("Delta_Cuts");
    dir_DeltaCuts->cd();
    for (int i=0; i<size_h_M_DeltaCut; ++i) {
        h_M_DeltaCut[i]->Write();
    }
    TDirectory *dir_DeltaCuts_Wb = dir_DeltaCuts->mkdir("Wb");
    dir_DeltaCuts_Wb->cd();
    for (int i=0; i<size_h_M_DeltaCut; ++i) {
        h_MW_DeltaCut[i]->Write();
    }
    for (int i=0; i<size_h_M_DeltaCut; ++i) {
        h_CSV_vs_M_DeltaCut[i]->Write();
    }
    for (int i=0; i<size_h_M_DeltaCut; ++i) {
        h_MW_vs_M_DeltaCut[i]->Write();
    }
    TDirectory *dir_Dalitz_after_DeltaCut
        = dir_DeltaCuts->mkdir("Dalitz_after_DeltaCut");
    dir_Dalitz_after_DeltaCut->cd();
    for (int i=0; i<size_h_M_DeltaCut; ++i) {
        h_Dalitz_after_DeltaCut[i]->Write();
    }

    TDirectory *dir_Dalitz = out_file->mkdir("Dalitz_Cuts");
    TDirectory *dirs_Dalitz[number_of_Dalitz_cuts];
    TDirectory *dirs_Dalitz_Wb[number_of_Dalitz_cuts];
    for (int i=0; i<number_of_Dalitz_cuts; ++i) {
        dirs_Dalitz[i] = dir_Dalitz->mkdir(Dalitz_cut_name[i]);
        dirs_Dalitz[i]->cd();
        h_Dalitz_after_cut[i]->Write();
        h_M_vs_pt_after_Dalitz[i]->Write();
        for (int j=0; j<size_h_M_DeltaCut; ++j) {
            h_M_DeltaDalitzCut[i][j]->Write();
        }

        dirs_Dalitz_Wb[i] = dirs_Dalitz[i]->mkdir("Wb");
        dirs_Dalitz_Wb[i]->cd();
        for (int j=0; j<size_h_M_DeltaCut; ++j) {
            h_MW_vs_M_DeltaDalitzCut[i][j]->Write();
        }
    }

    out_file->Close();

    return;
}


void NtupleTree::ScaleTriplets(TString scale_file_name)
{
    TFile *f_scales = new TFile(scale_file_name);
    f_scales->GetObject("h_scales", h_scales);
    scale_triplets = true;

    return;
}
