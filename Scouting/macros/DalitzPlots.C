void DalitzPlots()
{
    gStyle->SetOptStat(0);
    gStyle->SetErrorX(0);

    TFile *f_ttbar_correct = new TFile("correct_histograms_TTJets.root");

    TH2D *h_ttbar_correct;
    f_ttbar_correct->GetObject("h_Dalitz", h_ttbar_correct);

    TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
    c1->cd();

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

    TCanvas *c2 = new TCanvas("c2", "c2", 800, 600);
    c2->cd();

    h_ttbar_correct->Draw("colz");

    double cut_Dalitz = 0.06;

    TLine *l6 = new TLine(cut_Dalitz, cut_Dalitz, cut_Dalitz,
                          1.0 - 2.0*cut_Dalitz);
    l6->SetLineWidth(3);
    l6->SetLineColor(1);
    l6->SetLineStyle(1);
    l6->Draw();
    TLine *l7 = new TLine(cut_Dalitz, 1.0 - 2.0*cut_Dalitz,
                          (1.0 - cut_Dalitz)/2.0, (1.0 - cut_Dalitz)/2.0);
    l7->SetLineWidth(3);
    l7->SetLineColor(1);
    l7->SetLineStyle(1);
    l7->Draw();

    return;
}
