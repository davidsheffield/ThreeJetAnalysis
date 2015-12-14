#include "CMS_lumi.C"

void Mjj_vs_Mjjj_Projections()
{
    TFile *file_data = new TFile("../../../plots/Analysis/2015-11-21/histograms_data.root");
    TFile *file_correct_signal = new TFile("../../../plots/Analysis/2015-11-21/correct_histograms_TTJets.root");
    TFile *file_incorrect_signal = new TFile("../../../plots/Analysis/2015-11-21/incorrect_histograms_TTJets.root");

    TH2D *h_data, *h_correct_signal, *h_incorrect_signal;
    TString name = "Dalitz_Cuts/DalitzCut_0.06/Wb/h_MW_vs_M_DalitzCut_0.06_DeltaCut_110";
    //TString name = "Dalitz_Cuts/DalitzCut_0.06/h_M_DalitzCut_0.06_DeltaCut_110";
    file_data->GetObject(name, h_data);
    file_correct_signal->GetObject(name, h_correct_signal);
    file_incorrect_signal->GetObject(name, h_incorrect_signal);

    // W cuts
    int W_low = 99999;
    int W_up = -1;
    for (int i=1; i<501; ++i) {
        if (h_data->GetYaxis()->GetBinUpEdge(i) > 60.0 && i < W_low) {
            W_low = i;
        }
        if (h_data->GetYaxis()->GetBinLowEdge(i) < 100.0 && i > W_up) {
            W_up = i;
        }
    }
    cout << "W: " << W_low << " " << h_data->GetYaxis()->GetBinLowEdge(W_low)
         << " " << h_data->GetYaxis()->GetBinUpEdge(W_low) << endl;
    cout << "W: " << W_up << " " << h_data->GetYaxis()->GetBinLowEdge(W_up)
         << " " << h_data->GetYaxis()->GetBinUpEdge(W_up) << endl;

    TH1D *h_data_Wcut = h_data->ProjectionX("h_data_Wcut", W_low, -1);
    TH1D *h_data_Wwindow = h_data->ProjectionX("h_data_Wwindow", W_low, W_up);

    // Top cuts
    int top_low = 99999;
    int top_up = -1;
    for (int i=1; i<251; ++i) {
        if (h_data->GetYaxis()->GetBinUpEdge(i) > 150.0 && i < top_low) {
            top_low = i;
        }
        if (h_data->GetYaxis()->GetBinLowEdge(i) < 190.0 && i > top_up) {
            top_up = i;
        }
    }
    cout << "t: " << top_low << " " << h_data->GetYaxis()->GetBinLowEdge(top_low)
         << " " << h_data->GetYaxis()->GetBinUpEdge(top_low) << endl;
    cout << "t: " << top_up << " " << h_data->GetYaxis()->GetBinLowEdge(top_up)
         << " " << h_data->GetYaxis()->GetBinUpEdge(top_up) << endl;

    TH1D *h_data_Topcut = h_data->ProjectionY("h_data_Topcut", top_low, -1);
    TH1D *h_data_Topwindow = h_data->ProjectionY("h_data_Topwindow",
                                                 top_low, top_up);

    gStyle->SetOptStat(0);

    TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
    c1->cd();

    h_data_Wcut->Rebin(2);
    h_data_Wcut->SetLineColor(1);
    h_data_Wcut->SetMarkerStyle(20);
    h_data_Wcut->SetMarkerSize(0.25);
    h_data_Wcut->GetXaxis()->SetRangeUser(0.0, 500.0);
    h_data_Wcut->GetYaxis()->SetTitle("triplets / 4 GeV");
    h_data_Wcut->GetYaxis()->SetTitleOffset(1.4);
    h_data_Wcut->SetTitle("M_{jj} > 60 GeV");

    h_data_Wcut->Draw();

    CMS_lumi(c1, 4, 33);

    TCanvas *c2 = new TCanvas("c2", "c2", 800, 600);
    c2->cd();

    h_data_Wwindow->Rebin(2);
    h_data_Wwindow->SetLineColor(1);
    h_data_Wwindow->SetMarkerStyle(20);
    h_data_Wwindow->SetMarkerSize(0.25);
    h_data_Wwindow->GetXaxis()->SetRangeUser(0.0, 500.0);
    h_data_Wwindow->GetYaxis()->SetTitle("triplets / 4 GeV");
    h_data_Wwindow->GetYaxis()->SetTitleOffset(1.4);
    h_data_Wwindow->SetTitle("60 GeV < M_{jj} < 100 GeV");

    h_data_Wwindow->Draw();

    CMS_lumi(c2, 4, 33);

    TCanvas *c3 = new TCanvas("c3", "c3", 800, 600);
    c3->cd();

    h_data_Topcut->Rebin(2);
    h_data_Topcut->SetLineColor(1);
    h_data_Topcut->SetMarkerStyle(20);
    h_data_Topcut->SetMarkerSize(0.25);
    h_data_Topcut->GetXaxis()->SetRangeUser(0.0, 250.0);
    h_data_Topcut->GetYaxis()->SetTitle("triplets / 4 GeV");
    h_data_Topcut->GetYaxis()->SetTitleOffset(1.4);
    h_data_Topcut->SetTitle("M_{jjj} > 150 GeV");

    h_data_Topcut->Draw();

    CMS_lumi(c3, 4, 33);

    TCanvas *c4 = new TCanvas("c4", "c4", 800, 600);
    c4->cd();

    h_data_Topwindow->Rebin(2);
    h_data_Topwindow->SetLineColor(1);
    h_data_Topwindow->SetMarkerStyle(20);
    h_data_Topwindow->SetMarkerSize(0.25);
    h_data_Topwindow->GetXaxis()->SetRangeUser(0.0, 250.0);
    h_data_Topwindow->GetYaxis()->SetTitle("triplets / 4 GeV");
    h_data_Topwindow->GetYaxis()->SetTitleOffset(1.4);
    h_data_Topwindow->SetTitle("150 GeV < M_{jjj} < 190 GeV");

    h_data_Topwindow->Draw();

    CMS_lumi(c4, 4, 33);

    return;
}
