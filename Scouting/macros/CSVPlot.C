#include "CMS_lumi.C"

void CSVPlot()
{
    TFile *f_data = new TFile("../../../plots/Analysis/2015-11-21/histograms_data.root");
    TFile *f_correct = new TFile("../../../plots/Analysis/2015-11-21/correct_histograms_TTJets.root");
    TFile *f_incorrect = new TFile("../../../plots/Analysis/2015-11-21/incorrect_histograms_TTJets.root");
    TFile *f_qcd = new TFile("../../../plots/Analysis/2015-11-21/histograms_qcd_combined.root");

    TH1D *h_data, *h_correct, *h_incorrect, *h_qcd;
    TString name = "h_csv";
    f_data->GetObject(name, h_data);
    f_correct->GetObject(name, h_correct);
    f_incorrect->GetObject(name, h_incorrect);
    f_qcd->GetObject(name, h_qcd);

    double factor = h_data->Integral(1, 10000)/h_correct->Integral(1, 10000);
    h_correct->Scale(factor);

    h_data->SetLineColor(1);
    h_data->SetMarkerStyle(20);
    h_data->SetMarkerSize(0.5);
    h_data->GetXaxis()->SetRangeUser(0.0, 1.05);
    h_data->SetTitle();
    h_data->SetMaximum(7.0e6);
    h_data->GetXaxis()->SetTitleSize(0.045);
    h_data->GetYaxis()->SetTitleSize(0.045);

    h_correct->SetLineColor(3);
    h_incorrect->SetLineColor(2);
    //h_qcd->SetLineColor(4);

    TLine *cut = new TLine(0.95, 0.0, 0.95, 7.0e6);
    cut->SetLineColor(6);
    cut->SetLineStyle(2);
    cut->SetLineWidth(3);
    TBox *hash = new TBox(0.92, 0.0, 0.95, 7.0e6);
    hash->SetFillColor(6);
    hash->SetFillStyle(3004);

    gStyle->SetOptStat(0);

    TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
    c1->cd();
    c1->SetLogy();
    c1->SetTickx();
    c1->SetTicky();

    h_data->Draw();
    h_correct->Draw("hist same");
    //h_incorrect->Draw("hist same");
    //h_qcd->Draw("hist same");
    hash->Draw();
    cut->Draw();

    TLegend *leg = new TLegend(0.4, 0.25, 0.75, 0.4);
    leg->SetLineColor(0);
    leg->SetFillColor(0);
    leg->AddEntry(h_data, "data", "lp");
    leg->AddEntry(h_correct, "t#bar{t}, normalized to data area", "l");
    leg->Draw();

    h_data->Draw("sameaxis");

    CMS_lumi(c1, 4, 1);

    return;
}
