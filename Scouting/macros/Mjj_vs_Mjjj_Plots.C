#include "CMS_lumi.C"

void Mjj_vs_Mjjj_Plots()
{
    TFile *file_data = new TFile("../../../plots/Analysis/2015-11-21/histograms_data.root");
    TFile *file_correct_signal = new TFile("../../../plots/Analysis/2015-11-21/correct_histograms_TTJets.root");
    TFile *file_incorrect_signal = new TFile("../../../plots/Analysis/2015-11-21/incorrect_histograms_TTJets.root");
    TFile *file_qcd = new TFile("../../../plots/Analysis/2015-11-21/histograms_QCD_combined.root");

    TH2D *h_data, *h_correct_signal, *h_incorrect_signal, *h_qcd;
    TString name = "Dalitz_Cuts/DalitzCut_0.06/Wb/h_MW_vs_M_DalitzCut_0.06_DeltaCut_110";
    //TString name = "Delta_Cuts/Wb/h_MW_vs_M_DeltaCut_110";

    file_data->GetObject(name, h_data);
    file_correct_signal->GetObject(name, h_correct_signal);
    file_incorrect_signal->GetObject(name, h_incorrect_signal);
    file_qcd->GetObject(name, h_qcd);

    gStyle->SetOptStat(0);
    gStyle->SetPalette(55);
    gStyle->SetNumberContours(99);

    TLatex *text = new TLatex(35.0, 160.0, "#splitline{#Delta = 110 GeV}{D_{low} > 0.06}");
    //TLatex *text = new TLatex(35.0, 160.0, "#Delta = 110 GeV");
    text.SetTextFont(43);
    text.SetTextSize(40);

    TCanvas *c1 = new TCanvas("c1", "c1", 800, 800);
    c1->cd();
    c1->SetLogz();
    c1->SetTickx();
    c1->SetTicky();
    c1->SetLeftMargin(0.11);
    c1->SetRightMargin(0.11);

    h_data->GetXaxis()->SetRangeUser(0.0, 300.0);
    h_data->GetYaxis()->SetRangeUser(0.0, 300.0);
    h_data->GetXaxis()->SetTitleSize(0.045);
    h_data->GetYaxis()->SetTitleSize(0.045);
    h_data->GetYaxis()->SetTitleOffset(1.13);
    h_data->SetTitle();

    h_data->Draw("colz");
    text->Draw();

    CMS_lumi(c1, 4, 11);

    TCanvas *c2 = new TCanvas("c2", "c2", 800, 800);
    c2->cd();
    c2->SetLogz();
    c2->SetTickx();
    c2->SetTicky();
    c2->SetLeftMargin(0.11);
    c2->SetRightMargin(0.11);

    h_incorrect_signal->GetXaxis()->SetRangeUser(0.0, 300.0);
    h_incorrect_signal->GetYaxis()->SetRangeUser(0.0, 300.0);
    h_incorrect_signal->GetYaxis()->SetRangeUser(0.0, 300.0);
    h_incorrect_signal->GetXaxis()->SetTitleSize(0.045);
    h_incorrect_signal->GetYaxis()->SetTitleSize(0.045);
    h_incorrect_signal->GetYaxis()->SetTitleOffset(1.13);
    h_incorrect_signal->SetTitle("t#bar{t} MC");

    h_incorrect_signal->Draw("cont1");
    h_correct_signal->Draw("colz same");
    text->Draw();

    TCanvas *c3 = new TCanvas("c3", "c3", 800, 800);
    c3->cd();
    c3->SetLogz();
    c3->SetTickx();
    c3->SetTicky();
    c3->SetLeftMargin(0.11);
    c3->SetRightMargin(0.11);

    TH2D *combined = h_incorrect_signal->Clone();
    combined->Add(h_correct_signal);
    combined->GetXaxis()->SetRangeUser(0.0, 300.0);
    combined->GetYaxis()->SetRangeUser(0.0, 300.0);
    combined->GetXaxis()->SetTitleSize(0.045);
    combined->GetYaxis()->SetTitleSize(0.045);
    combined->GetYaxis()->SetTitleOffset(1.13);
    combined->SetTitle("t#bar{t} MC");

    combined->Draw("colz");
    text->Draw();

    TCanvas *c4 = new TCanvas("c4", "c4", 800, 800);
    c4->cd();
    c4->SetLogz();
    c4->SetTickx();
    c4->SetTicky();
    c4->SetLeftMargin(0.11);
    c4->SetRightMargin(0.11);

    h_qcd->GetXaxis()->SetRangeUser(0.0, 300.0);
    h_qcd->GetYaxis()->SetRangeUser(0.0, 300.0);
    h_qcd->GetXaxis()->SetTitleSize(0.045);
    h_qcd->GetYaxis()->SetTitleSize(0.045);
    h_qcd->GetYaxis()->SetTitleOffset(1.13);
    h_qcd->SetTitle("QCD MC");

    h_qcd->Draw("colz");
    text->Draw();

    return;
}
