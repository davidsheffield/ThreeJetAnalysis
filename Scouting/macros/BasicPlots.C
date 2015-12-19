#include "CMS_lumi.C"

void BasicPlots()
{
    TFile *f_data = new TFile("../../../plots/Analysis/2015-11-21/histograms_data.root");
    TFile *f_correct = new TFile("../../../plots/Analysis/2015-11-21/correct_histograms_TTJets.root");
    TFile *f_incorrect = new TFile("../../../plots/Analysis/2015-11-21/incorrect_histograms_TTJets.root");
    TFile *f_qcd = new TFile("../../../plots/Analysis/2015-11-21/histograms_qcd_combined.root");

    TH1D *h_data_Ht;
    f_data->GetObject("h_HT", h_data_Ht);

    h_data_Ht->Rebin(10);
    h_data_Ht->SetLineColor(1);
    h_data_Ht->SetMarkerStyle(20);
    h_data_Ht->SetMarkerSize(0.25);
    //h_data_Ht->GetXaxis()->SetRangeUser(0.0, 2000.0);
    h_data_Ht->SetTitle();
    h_data_Ht->SetMaximum(1.0e6);
    h_data_Ht->GetXaxis()->SetTitleSize(0.045);
    h_data_Ht->GetYaxis()->SetTitleSize(0.045);

    //h_correct->SetLineColor(3);
    //h_incorrect->SetLineColor(2);
    //h_qcd->SetLineColor(4);

    TLine *cut1 = new TLine(450.0, 0.0, 450.0, 1.0e6);
    cut1->SetLineColor(6);
    cut1->SetLineStyle(2);
    cut1->SetLineWidth(2);
    TBox *hash1 = new TBox(450.0, 0.0, 350.0, 1.0e6);
    hash1->SetFillColor(6);
    hash1->SetFillStyle(3004);

    gStyle->SetOptStat(0);

    TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
    c1->cd();
    c1->SetLogy();
    c1->SetTickx();
    c1->SetTicky();

    h_data_Ht->Draw();
    //h_correct->Draw("hist same");
    //h_incorrect->Draw("hist same");
    //h_qcd->Draw("hist same");
    hash1->Draw();
    cut1->Draw();

    // TLegend *leg = new TLegend(0.4, 0.25, 0.75, 0.4);
    // leg->SetLineColor(0);
    // leg->SetFillColor(0);
    // leg->AddEntry(h_data_Ht, "data", "lp");
    // leg->AddEntry(h_correct, "t#bar{t}, normalized to data area", "l");
    // leg->Draw();

    //h_data_Ht->Draw("sameaxis");

    CMS_lumi(c1, 4, 33);

    TH1D *h_data_pt;
    f_data->GetObject("h_jet_pt", h_data_pt);

    //h_data_pt->Rebin(1);
    h_data_pt->SetLineColor(1);
    h_data_pt->SetMarkerStyle(20);
    h_data_pt->SetMarkerSize(0.25);
    //h_data_pt->GetXaxis()->SetRangeUser(0.0, 2000.0);
    h_data_pt->SetTitle();
    //h_data_pt->SetMaximum(1.0e6);
    h_data_pt->GetXaxis()->SetTitleSize(0.045);
    h_data_pt->GetYaxis()->SetTitleSize(0.045);

    //h_correct->SetLineColor(3);
    //h_incorrect->SetLineColor(2);
    //h_qcd->SetLineColor(4);

    gStyle->SetOptStat(0);

    TCanvas *c2 = new TCanvas("c2", "c2", 800, 600);
    c2->cd();
    c2->SetLogy();
    c2->SetTickx();
    c2->SetTicky();

    h_data_pt->Draw();

    CMS_lumi(c2, 4, 33);

    return;
}
