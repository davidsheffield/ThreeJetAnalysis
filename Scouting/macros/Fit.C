#include "ScoutingFitter.cc"
#include "CMS_lumi.C"

void Fit()
{
    TFile *file_data = new TFile("../../../plots/Analysis/2015-11-21/histograms_data.root");
    TFile *file_correct_signal = new TFile("../../../plots/Analysis/2015-11-21/correct_histograms_TTJets.root");
    TFile *file_incorrect_signal = new TFile("../../../plots/Analysis/2015-11-21/incorrect_histograms_TTJets.root");

    TH1D *h_data, *h_correct_signal, *h_incorrect_signal;

    TString name = "Dalitz_Cuts/DalitzCut_0.06/h_M_DalitzCut_0.06_DeltaCut_130";
    file_data->GetObject(name, h_data);
    file_correct_signal->GetObject(name, h_correct_signal);
    file_incorrect_signal->GetObject(name, h_incorrect_signal);
    TH1D *h_signal = h_correct_signal->Clone();
    h_signal->Add(h_incorrect_signal);

    int rebin = 2;
    h_data->Rebin(rebin);
    h_signal->Rebin(rebin);

    for (int i=1; i<h_data->GetSize()-1; ++i) {
        double x = h_data->GetBinContent(i)/h_data->GetXaxis()->GetBinWidth(i);
        double err = h_data->GetBinError(i)/h_data->GetXaxis()->GetBinWidth(i);
        h_data->SetBinContent(i, x);
        h_data->SetBinError(i, err);

        x = h_signal->GetBinContent(i)/h_signal->GetXaxis()->GetBinWidth(i);
        err = h_signal->GetBinError(i)/h_signal->GetXaxis()->GetBinWidth(i);
        h_signal->SetBinContent(i, x);
        h_signal->SetBinError(i, err);

        x = h_correct_signal->GetBinContent(i)
           /h_correct_signal->GetXaxis()->GetBinWidth(i);
        err = h_correct_signal->GetBinError(i)
             /h_correct_signal->GetXaxis()->GetBinWidth(i);
        h_correct_signal->SetBinContent(i, x);
        h_correct_signal->SetBinError(i, err);

        x = h_incorrect_signal->GetBinContent(i)
           /h_incorrect_signal->GetXaxis()->GetBinWidth(i);
        err = h_incorrect_signal->GetBinError(i)
             /h_incorrect_signal->GetXaxis()->GetBinWidth(i);
        h_incorrect_signal->SetBinContent(i, x);
        h_incorrect_signal->SetBinError(i, err);
    }
    h_data->GetYaxis()->SetTitle("dN/dm");
    h_signal->GetYaxis()->SetTitle("dN/dm");
    h_correct_signal->GetYaxis()->SetTitle("dN/dm");
    h_incorrect_signal->GetYaxis()->SetTitle("dN/dm");

    double min = 120.0; // 120
    double max = 300.0; // 300

    // Do fit
    ScoutingFitter fit(h_data, min, max);
    TF1 *f1 = fit.FitP4(160.0, 188.0);  // Fit P4
    TF1 *f2 = fit.FitP4PlusGauss(0xf);  // Fit fixed P4 + gauss
    TF1 *f3 = fit.FitP4PlusGauss(0x70); // Fit P4 + fixed gauss
    TF1 *f4 = fit.FitP4PlusGauss();     // Fit P4 + gauss
    TF1 *f5 = fit.GetP4();              // Get P4 for display

    ScoutingFitter fit_signal(h_signal, min, max);
    TF1 *sf1 = fit_signal.FitP4(165.0, 188.0);  // Fit P4
    TF1 *sf2 = fit_signal.FitP4PlusGauss(0xf);  // Fit fixed P4+gauss
    TF1 *sf3 = fit_signal.FitP4PlusGauss(0x70); // Fit P4+fixed gauss
    TF1 *sf4 = fit_signal.FitP4PlusGauss();     // Fit P4 + gauss
    TF1 *sf5 = fit_signal.GetP4();              // Get P4 for display

    //combined->SetParLimits(5, 150.0, 190.0);

    gStyle->SetOptStat(0);

    TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
    c1->cd();

    h_data->SetLineColor(1);
    h_data->SetMarkerStyle(20);
    h_data->SetMarkerSize(0.25);
    h_data->GetXaxis()->SetRangeUser(100.0, 400.0);
    h_data->SetMinimum(0);

    f4->SetLineColor(2);
    f5->SetLineColor(4);
    h_correct_signal->SetLineColor(1);
    h_incorrect_signal->SetLineColor(1);
    h_correct_signal->SetFillColor(3);
    h_incorrect_signal->SetFillColor(5);
    sf4->SetLineColor(2);
    sf5->SetLineColor(4);
    sf4->SetLineStyle(2);
    sf5->SetLineStyle(2);

    h_data->SetTitle();
    h_data->GetYaxis()->SetTitleOffset(1.4);

    THStack *h_signal_stack = new THStack("h_signal_stack", "signal stack");
    h_signal_stack->Add(h_incorrect_signal);
    h_signal_stack->Add(h_correct_signal);

    h_data->Draw();
    f4->Draw("same");
    f5->Draw("same");
    h_signal_stack->Draw("hist same");
    sf4->Draw("same");
    sf5->Draw("same");

    TLegend *leg1 = new TLegend(0.6, 0.4, 0.89, 0.6);
    leg1->SetLineColor(0);
    leg1->SetFillColor(0);
    leg1->AddEntry(h_data, "data", "lp");
    leg1->AddEntry(f4, "P4 + Gaussian", "l");
    leg1->AddEntry(f5, "P4", "l");
    leg1->AddEntry(h_correct_signal, "t#bar{t}, correct", "f");
    leg1->AddEntry(h_incorrect_signal, "t#bar{t}, incorrect", "f");
    leg1->Draw();

    CMS_lumi(c1, 4, 33);

    cout << "Data integral " << f4->Integral(min, max) - f5->Integral(min, max)
         << endl;
    cout << "Signal integral " << sf4->Integral(min, max) - sf5->Integral(min, max)
         << " " << sf4->Integral(min, max) << endl;
    // double signal_area = signal_fit->GetParameter(0)
    //     *sqrt(2.0*TMath::Pi()*pow(signal_fit->GetParameter(2), 2))
    //     /h_data->GetXaxis()->GetBinWidth(1);
    // double fit_area = combined->GetParameter(4)
    //     *sqrt(2.0*TMath::Pi()*pow(combined->GetParameter(6), 2))
    //     /h_correct_signal->GetXaxis()->GetBinWidth(1);
    // double signal_cross_section = 831.76;
    // double fit_cross_section = signal_cross_section*fit_area/signal_area;

    // cout << "Signal area " << signal_area << "    Integral "
    //      << h_correct_signal->Integral(1, 1000) << endl;
    // cout << "Fit area    " << fit_area << endl;
    // cout << "Cross section " << fit_cross_section << " pb" << endl;

    // LandGauss
    ScoutingFitter fit2(h_data, min, max);
    TF1 *g1 = fit2.FitLandGauss(160.0, 188.0);  // Fit LandGauss
    TF1 *g2 = fit2.FitLandGaussPlusGauss(0xf);  // Fit fixed LandGauss + Gauss
    TF1 *g3 = fit2.FitLandGaussPlusGauss(0x70); // Fit LandGauss + fixed gauss
    TF1 *g4 = fit2.FitLandGaussPlusGauss();     // Fit LandGauss + gauss
    TF1 *g5 = fit2.GetLandGauss();              // Get P4 for display

    ScoutingFitter fit2_signal(h_signal, min, max);
    TF1 *sg1 = fit2_signal.FitLandGauss(160.0, 188.0);  // Fit LandGauss
    TF1 *sg2 = fit2_signal.FitLandGaussPlusGauss(0xf);  // Fit fixed LandGauss + Gauss
    TF1 *sg3 = fit2_signal.FitLandGaussPlusGauss(0x70); // Fit LandGauss + fixed gauss
    TF1 *sg4 = fit2_signal.FitLandGaussPlusGauss();     // Fit LandGauss + gauss
    TF1 *sg5 = fit2_signal.GetLandGauss();              // Get P4 for display

    TCanvas *c2 = new TCanvas("c2", "c2", 800, 600);
    c2->cd();

    g4->SetLineColor(2);
    g5->SetLineColor(4);
    sg4->SetLineColor(2);
    sg5->SetLineColor(4);
    sg4->SetLineStyle(2);
    sg5->SetLineStyle(2);

    h_data->Draw();
    g4->Draw("same");
    g5->Draw("same");
    h_signal_stack->Draw("hist same");
    sg4->Draw("same");
    sg5->Draw("same");

    TLegend *leg2 = new TLegend(0.6, 0.4, 0.89, 0.6);
    leg2->SetLineColor(0);
    leg2->SetFillColor(0);
    leg2->AddEntry(h_data, "data", "lp");
    leg2->AddEntry(g4, "LandGauss + Gauss", "l");
    leg2->AddEntry(g5, "LandGauss", "l");
    leg2->AddEntry(h_correct_signal, "t#bar{t}, correct", "f");
    leg2->AddEntry(h_incorrect_signal, "t#bar{t}, incorrect", "f");
    leg2->Draw();

    cout << "f1 " << f1->GetChisquare() << "/" << f1->GetNDF() - 5 << " = "
         << f1->GetChisquare()/(f1->GetNDF() - 5) << endl;
    cout << "f2 " << f2->GetChisquare() << "/" << f2->GetNDF() << " = "
         << f2->GetChisquare()/f2->GetNDF() << endl;
    cout << "f3 " << f3->GetChisquare() << "/" << f3->GetNDF() << " = "
         << f3->GetChisquare()/f3->GetNDF() << endl;
    cout << "f4 " << f4->GetChisquare() << "/" << f4->GetNDF() << " = "
         << f4->GetChisquare()/f4->GetNDF() << endl;
    cout << "g1 " << g1->GetChisquare() << "/" << g1->GetNDF() - 5 << " = "
         << g1->GetChisquare()/(g1->GetNDF() - 5) << endl;
    cout << "g4 " << g4->GetChisquare() << "/" << g4->GetNDF() << " = "
         << g4->GetChisquare()/g4->GetNDF() << endl;

    CMS_lumi(c2, 4, 33);

    return;
}
