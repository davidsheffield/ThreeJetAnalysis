#include "CMS_lumi.C"

void DalitzPlots()
{
    gStyle->SetOptStat(0);
    gStyle->SetErrorX(0);
    gStyle->SetPalette(55);
    gStyle->SetNumberContours(99);

    TFile *f_ttbar_correct = new TFile("../../../plots/Analysis/2015-11-21/incorrect_histograms_TTJets.root");
    //TFile *f_ttbar_correct = new TFile("../../../plots/Analysis/2015-11-21/histograms_QCD_combined.root");

    TH2D *h_ttbar_correct;
    f_ttbar_correct->GetObject("h_Dalitz", h_ttbar_correct);
    //h_ttbar_correct->SetTitle("QCD MC");

    h_ttbar_correct->GetXaxis()->SetTitleSize(0.045);
    h_ttbar_correct->GetYaxis()->SetTitleSize(0.045);

    TCanvas *c1 = new TCanvas("c1", "c1", 800, 800);
    c1->cd();
    c1->SetTickx();
    c1->SetTicky();
    c1->SetRightMargin(0.11);

    h_ttbar_correct->Draw("colz");

    double W_mass = 80.385;
    double t_mass = 173.21;
    double D_W = W_mass*W_mass/(t_mass*t_mass);

    TLine *l1 = new TLine(D_W, D_W, D_W, 1.0 - 2.0*D_W);
    l1->SetLineWidth(3);
    l1->SetLineColor(1);
    l1->SetLineStyle(1);
    l1->Draw();
    TLine *l2 = new TLine(D_W, 1.0 - 2.0*D_W, (1.0 - D_W)/2.0, (1.0 - D_W)/2.0);
    l2->SetLineWidth(3);
    l2->SetLineColor(1);
    l2->SetLineStyle(1);
    l2->Draw();
    TLine *l3 = new TLine(0.0, D_W, D_W, D_W);
    l3->SetLineWidth(3);
    l3->SetLineColor(1);
    l3->SetLineStyle(9);
    l3->Draw();
    TLine *l4 = new TLine(D_W, 1.0 - 2.0*D_W, D_W, 1.0 - D_W);
    l4->SetLineWidth(3);
    l4->SetLineColor(1);
    l4->SetLineStyle(9);
    l4->Draw();
    TLine *l5 = new TLine(0.0, 1.0 - D_W, D_W, 1.0 - 2.0*D_W);
    l5->SetLineWidth(3);
    l5->SetLineColor(1);
    l5->SetLineStyle(9);
    l5->Draw();

    //CMS_lumi(c1, 4, 33);

    TCanvas *c2 = new TCanvas("c2", "c2", 800, 800);
    c2->cd();
    c2->SetTickx();
    c2->SetTicky();
    c2->SetRightMargin(0.11);

    h_ttbar_correct->Draw("colz");

    double cut_Dalitz = 0.06;

    TLine *l6 = new TLine(cut_Dalitz, cut_Dalitz, cut_Dalitz,
                          1.0 - 2.0*cut_Dalitz);
    l6->SetLineWidth(3);
    l6->SetLineColor(6);
    l6->SetLineStyle(9);
    l6->Draw();
    TLine *l7 = new TLine(cut_Dalitz, 1.0 - 2.0*cut_Dalitz,
                          (1.0 - cut_Dalitz)/2.0, (1.0 - cut_Dalitz)/2.0);
    l7->SetLineWidth(3);
    l7->SetLineColor(6);
    l7->SetLineStyle(9);
    l7->Draw();

    //CMS_lumi(c2, 4, 33);

    TCanvas *c3 = new TCanvas("c3", "c3", 800, 800);
    c3->cd();
    c3->SetTickx();
    c3->SetTicky();
    c3->SetRightMargin(0.11);

    h_ttbar_correct->Draw("colz");

    TLine *l8 = new TLine(0.0, 1.0, 0.33333, 0.33333);
    l8->SetLineWidth(3);
    l8->SetLineColor(1);
    l8->SetLineStyle(1);
    l8->Draw();
    TLine *l9 = new TLine(0.0, 0.5, 0.33333, 0.33333);
    l9->SetLineWidth(3);
    l9->SetLineColor(1);
    l9->SetLineStyle(1);
    l9->Draw();

    //CMS_lumi(c3, 4, 33);

    TCanvas *c4 = new TCanvas("c4", "c4", 800, 800);
    c4->cd();
    c4->SetTickx();
    c4->SetTicky();
    c4->SetRightMargin(0.11);

    TLine *l10 = new TLine(0.0, 0.0, 0.0, 1.0);
    l10->SetLineWidth(3);
    l10->SetLineColor(11);
    l10->SetLineStyle(1);
    TLine *l11 = new TLine(0.0, 0.0, 0.5, 0.5);
    l11->SetLineWidth(3);
    l11->SetLineColor(11);
    l11->SetLineStyle(1);
    TLine *l12 = new TLine(0.0, 1.0, 0.5, 0.5);
    l12->SetLineWidth(3);
    l12->SetLineColor(11);
    l12->SetLineStyle(1);

    l8->SetLineColor(11);
    l9->SetLineColor(11);

    h_ttbar_correct->Draw("colz");
    l8->Draw();
    l9->Draw();
    //l10->Draw();
    //l11->Draw();
    //l12->Draw();
    l1->Draw();
    l2->Draw();
    l3->Draw();
    l4->Draw();
    l5->Draw();
    h_ttbar_correct->Draw("sameaxis");

    //CMS_lumi(c4, 4, 33);

    TCanvas *c5 = new TCanvas("c5", "c5", 800, 800);
    c5->cd();
    c5->SetTickx();
    c5->SetTicky();
    c5->SetRightMargin(0.11);

    TH2D *h_cont = h_ttbar_correct->Clone();
    double root_one_third = 1.0/sqrt(3.0);
    for (int i=1; i<101; ++i) {
        for (int j=1; j<101; ++j) {
            if (h_cont->GetBinContent(i, j) == 0.0)
                continue;
            double x = h_cont->GetXaxis()->GetBinCenter(i);
            double y = h_cont->GetYaxis()->GetBinCenter(j);
            if (1.0 - x - y <= 0) {
                h_cont->SetBinContent(i, j, 0.0);
                continue;
            }
            double d2 = pow(sqrt(x) - root_one_third, 2.0)
                      + pow(sqrt(y) - root_one_third, 2.0)
                      + pow(sqrt(1.0 - x - y) - root_one_third, 2.0);
            h_cont->SetBinContent(i, j, d2);
        }
    }

    h_ttbar_correct->Draw("colz");
    h_cont->Draw("cont1 same");
    h_ttbar_correct->Draw("sameaxis");

    CMS_lumi(c5, 4, 33);

    return;
}
