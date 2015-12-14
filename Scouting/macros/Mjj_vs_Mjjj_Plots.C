#include "CMS_lumi.C"

void Mjj_vs_Mjjj_Plots()
{
    TFile *file_data = new TFile("../../../plots/Analysis/2015-11-21/histograms_data.root");
    TFile *file_correct_signal = new TFile("../../../plots/Analysis/2015-11-21/correct_histograms_TTJets.root");
    TFile *file_incorrect_signal = new TFile("../../../plots/Analysis/2015-11-21/incorrect_histograms_TTJets.root");

    TH2D *h_data, *h_correct_signal, *h_incorrect_signal;
    TString name = "Dalitz_Cuts/DalitzCut_0.06/Wb/h_MW_vs_M_DalitzCut_0.06_DeltaCut_110";
    //TString name = "Delta_Cuts/Wb/h_MW_vs_M_DeltaCut_110";

    file_data->GetObject(name, h_data);
    file_correct_signal->GetObject(name, h_correct_signal);
    file_incorrect_signal->GetObject(name, h_incorrect_signal);

    gStyle->SetOptStat(0);

    TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
    c1->cd();
    c1->SetLogz();

    h_data->GetXaxis()->SetRangeUser(0.0, 300.0);
    h_data->GetYaxis()->SetRangeUser(0.0, 200.0);

    h_data->Draw("colz");

    CMS_lumi(c1, 4, 11);

    TCanvas *c2 = new TCanvas("c2", "c2", 800, 600);
    c2->cd();
    c2->SetLogz();

    h_incorrect_signal->GetXaxis()->SetRangeUser(0.0, 300.0);
    h_incorrect_signal->GetYaxis()->SetRangeUser(0.0, 200.0);

    h_incorrect_signal->Draw("cont1");
    h_correct_signal->Draw("colz same");

    return;
}
