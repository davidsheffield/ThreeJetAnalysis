#include "CMS_lumi.C"

void MvsPtPlots()
{
    TFile *f_data = new TFile("../../../plots/Analysis/2015-11-21/histograms_data.root");
    TFile *f_correct = new TFile("../../../plots/Analysis/2015-11-21/correct_histograms_TTJets.root");
    TFile *f_incorrect = new TFile("../../../plots/Analysis/2015-11-21/incorrect_histograms_TTJets.root");
    TFile *f_qcd = new TFile("../../../plots/Analysis/2015-11-21/histograms_qcd_combined.root");

    TH2D *h_data, *h_correct, *h_incorrect, *h_qcd;
    TString name = "h_M_vs_pt";
    f_data->GetObject(name, h_data);
    f_correct->GetObject(name, h_correct);
    f_incorrect->GetObject(name, h_incorrect);
    f_qcd->GetObject(name, h_qcd);

    h_data->GetXaxis()->SetRangeUser(0.0, 3000.0);
    h_data->GetYaxis()->SetRangeUser(0.0, 3000.0);
    h_correct->GetXaxis()->SetRangeUser(0.0, 3000.0);
    h_correct->GetYaxis()->SetRangeUser(0.0, 3000.0);
    h_incorrect->GetXaxis()->SetRangeUser(0.0, 3000.0);
    h_incorrect->GetYaxis()->SetRangeUser(0.0, 3000.0);
    h_qcd->GetXaxis()->SetRangeUser(0.0, 3000.0);
    h_qcd->GetYaxis()->SetRangeUser(0.0, 3000.0);

    h_data->GetXaxis()->SetTitle("#Sigma_{j} |p_{Tj}| [GeV]");
    h_correct->GetXaxis()->SetTitle("#Sigma_{j} |p_{Tj}| [GeV]");
    h_incorrect->GetXaxis()->SetTitle("#Sigma_{j} |p_{Tj}| [GeV]");
    h_qcd->GetXaxis()->SetTitle("#Sigma_{j} |p_{Tj}| [GeV]");

    h_data->GetXaxis()->SetTitleSize(0.045);
    h_correct->GetXaxis()->SetTitleSize(0.045);
    h_incorrect->GetXaxis()->SetTitleSize(0.045);
    h_qcd->GetXaxis()->SetTitleSize(0.045);
    h_data->GetYaxis()->SetTitleSize(0.045);
    h_correct->GetYaxis()->SetTitleSize(0.045);
    h_incorrect->GetYaxis()->SetTitleSize(0.045);
    h_qcd->GetYaxis()->SetTitleSize(0.045);

    h_data->GetYaxis()->SetTitleOffset(1.4);
    h_correct->GetYaxis()->SetTitleOffset(1.4);
    h_incorrect->GetYaxis()->SetTitleOffset(1.4);
    h_qcd->GetYaxis()->SetTitleOffset(1.4);

    h_data->SetTitle();
    h_incorrect->SetTitle("t#bar{t} MC");
    h_qcd->SetTitle("QCD MC");

    TLine *cut = new TLine(110.0, 0.0, 3000.0, 2890.0);
    //TLine *cut = new TLine(110.0, 0.0, 1500.0, 1390.0);
    cut->SetLineColor(6);
    cut->SetLineStyle(9);
    cut->SetLineWidth(3);

    gStyle->SetOptStat(0);
    gStyle->SetPalette(55);
    gStyle->SetNumberContours(99);

    TCanvas *c1 = new TCanvas("c1", "c1", 800, 790);
    c1->cd();
    c1->SetLogz();
    c1->SetTickx();
    c1->SetTicky();
    c1->SetLeftMargin(0.13);
    c1->SetRightMargin(0.11);

    h_data->Draw("colz");
    cut->Draw();

    CMS_lumi(c1, 4, 33);
    //CMS_lumi(c1, 4, 1);

    TCanvas *c2 = new TCanvas("c2", "c2", 800, 790);
    c2->cd();
    c2->SetLogz();
    c2->SetTickx();
    c2->SetTicky();
    c2->SetLeftMargin(0.13);
    c2->SetRightMargin(0.11);

    h_incorrect->Draw("cont1");
    h_correct->Draw("colz same");
    cut->Draw();

    TCanvas *c3 = new TCanvas("c3", "c3", 800, 790);
    c3->cd();
    c3->SetLogz();
    c3->SetTickx();
    c3->SetTicky();
    c3->SetLeftMargin(0.13);
    c3->SetRightMargin(0.11);

    h_qcd->Draw("colz");
    cut->Draw();

    return;
}
