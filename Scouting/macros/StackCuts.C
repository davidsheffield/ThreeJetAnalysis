#include "CMS_lumi.C"

void StackCuts()
{
    TString version = "";//noBtag_";
    TFile *file_data = new TFile("../../../plots/Analysis/2015-11-21/histograms_"
                                 + version + "data.root");

    TString delta_name = "Dalitz_Cuts/DalitzCut_0.06/h_M_DalitzCut_0.06_DeltaCut_";
    const int num_delta_cuts = 9;
    // TString cuts[num_delta_cuts] = {"70", "90", "110", "130", "150"};
    TString delta_cuts[num_delta_cuts] = {"70", "80", "90", "100", "110", "120", "130",
                              "140", "150"};
    TH1D *h_data_delta[num_delta_cuts];

    int rebin = 2;
    for (int i=0; i<num_delta_cuts; ++i) {
        file_data->GetObject(delta_name + delta_cuts[i], h_data_delta[i]);
        h_data_delta[i]->Rebin(rebin);
        h_data_delta[i]->GetYaxis()->SetTitle("triplets / 4 GeV");
    }

    gStyle->SetOptStat(0);

    TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
    c1->cd();
    c1->SetLeftMargin(0.11);

    int offset = 2;
    for (int i=0; i<num_delta_cuts; ++i) {
        if (i == 8)
            offset += 2;
        h_data_delta[i]->SetLineColor(i+offset);
        h_data_delta[i]->SetMarkerColor(i+offset);
        h_data_delta[i]->SetMarkerStyle(20);
        h_data_delta[i]->SetMarkerSize(0.5);
    }

    h_data_delta[0]->GetXaxis()->SetRangeUser(0.0, 500.0);
    h_data_delta[0]->SetTitle("D_{low} > 0.06");
    h_data_delta[0]->GetYaxis()->SetTitleSize(0.045);
    h_data_delta[0]->GetXaxis()->SetTitleSize(0.045);
    h_data_delta[0]->GetYaxis()->SetTitleOffset(1.2);

    h_data_delta[0]->Draw();
    for (int i=1; i<num_delta_cuts; ++i) {
        h_data_delta[i]->Draw("same");
    }

    TLegend *leg1 = new TLegend(0.65, 0.3, 0.89, 0.7);
    leg1->SetLineColor(0);
    leg1->SetFillColor(0);
    for (int i=0; i<num_delta_cuts; ++i) {
        leg1->AddEntry(h_data_delta[i], "#Delta = " + delta_cuts[i] + " GeV",
                       "lp");
    }
    leg1->Draw();

    CMS_lumi(c1, 4, 33);

    const int num_dalitz_cuts = 10;
    TString dalitz_cuts[num_dalitz_cuts] = {"0.01", "0.02", "0.03", "0.04",
                                            "0.05", "0.06", "0.07", "0.08",
                                            "0.09", "0.10"};
    TH1D *h_data_dalitz[num_dalitz_cuts];

    int rebin = 2;
    for (int i=0; i<num_dalitz_cuts; ++i) {
        TString dalitz_name = "Dalitz_Cuts/DalitzCut_" + dalitz_cuts[i]
                            + "/h_M_DalitzCut_" + dalitz_cuts[i]
                            + "_DeltaCut_110";
        cout << dalitz_name << endl;
        file_data->GetObject(dalitz_name, h_data_dalitz[i]);
        if (i == 5)
            continue;

        h_data_dalitz[i]->Rebin(rebin);
        h_data_dalitz[i]->GetYaxis()->SetTitle("triplets / 4 GeV");
    }

    gStyle->SetOptStat(0);

    TCanvas *c2 = new TCanvas("c2", "c2", 800, 600);
    c2->cd();
    c2->SetLeftMargin(0.11);

    int offset = 2;
    for (int i=0; i<num_dalitz_cuts; ++i) {
        if (i == 8)
            offset += 2;
        h_data_dalitz[i]->SetLineColor(i+offset);
        h_data_dalitz[i]->SetMarkerColor(i+offset);
        h_data_dalitz[i]->SetMarkerStyle(20);
        h_data_dalitz[i]->SetMarkerSize(0.5);
    }

    h_data_dalitz[0]->GetXaxis()->SetRangeUser(0.0, 500.0);
    h_data_dalitz[0]->SetTitle("#Delta = 110 GeV");
    h_data_dalitz[0]->GetYaxis()->SetTitleSize(0.045);
    h_data_dalitz[0]->GetXaxis()->SetTitleSize(0.045);
    h_data_dalitz[0]->GetYaxis()->SetTitleOffset(1.2);

    h_data_dalitz[0]->Draw();
    for (int i=1; i<num_dalitz_cuts; ++i) {
        h_data_dalitz[i]->Draw("same");
    }

    TLegend *leg2 = new TLegend(0.65, 0.3, 0.89, 0.7);
    leg2->SetLineColor(0);
    leg2->SetFillColor(0);
    for (int i=0; i<num_dalitz_cuts; ++i) {
        leg2->AddEntry(h_data_dalitz[i],
                       "D_{low} > " + dalitz_cuts[i] + " GeV", "lp");
    }
    leg2->Draw();

    CMS_lumi(c2, 4, 33);

    return;
}
