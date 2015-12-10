#include "ScoutingFitter.cc"
#include "CMS_lumi.C"

void Fit()
{
    TFile *file_data = new TFile("../../../plots/Analysis/2015-11-21/histograms_data.root");
    TFile *file_correct_signal = new TFile("../../../plots/Analysis/2015-11-21/correct_histograms_TTJets.root");

    TH1D *h_data, *h_correct_signal;

    TString name = "Dalitz_Cuts/DalitzCut_0.06/h_M_DalitzCut_0.06_DeltaCut_130";
    file_data->GetObject(name, h_data);
    file_correct_signal->GetObject(name, h_correct_signal);
    h_data->Rebin(2);
    h_correct_signal->Rebin(2);

    for (int i=1; i<h_data->GetSize()-1; ++i) {
        double x = h_data->GetBinContent(i)/h_data->GetXaxis()->GetBinWidth(i);
        double err = h_data->GetBinError(i)/h_data->GetXaxis()->GetBinWidth(i);
        h_data->SetBinContent(i, x);
        h_data->SetBinError(i, err);
    }
    h_data->GetYaxis()->SetTitle("dN/dm");

    double min = 120.0; // 120
    double max = 300.0; // 300

    // Do fit
    ScoutingFitter fit(h_data);
    TF1 *f1 = fit.FitP4(min, max, 160.0, 188.0);  // Fit P4
    TF1 *f2 = fit.FitP4PlusGauss(min, max, 0xf);  // Fit fixed P4 + gauss
    TF1 *f3 = fit.FitP4PlusGauss(min, max, 0x70); // Fit P4 + fixed gauss
    TF1 *f4 = fit.FitP4PlusGauss(min, max);       // Fit P4 + gauss
    TF1 *f5 = fit.GetP4(min, max);                // Get P4 for display

    cout << "f1 " << f1->GetChisquare() << "/" << f1->GetNDF() << " = "
         << f1->GetChisquare()/f1->GetNDF() << endl;
    cout << "f2 " << f2->GetChisquare() << "/" << f2->GetNDF() << " = "
         << f2->GetChisquare()/f2->GetNDF() << endl;
    cout << "f3 " << f3->GetChisquare() << "/" << f3->GetNDF() << " = "
         << f3->GetChisquare()/f3->GetNDF() << endl;
    cout << "f4 " << f4->GetChisquare() << "/" << f4->GetNDF() << " = "
         << f4->GetChisquare()/f4->GetNDF() << endl;

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

    h_data->SetTitle();
    h_data->GetYaxis()->SetTitleOffset(1.4);

    h_data->Draw();
    f4->Draw("same");
    f5->Draw("same");

    TLegend *leg = new TLegend(0.6, 0.4, 0.89, 0.6);
    leg->SetLineColor(0);
    leg->SetFillColor(0);
    leg->AddEntry(h_data, "data", "lp");
    leg->AddEntry(f4, "P4 + Gaussian", "l");
    leg->AddEntry(f5, "P4", "l");
    leg->Draw();

    CMS_lumi(c1, 4, 33);

    cout << "Integral " << f4->Integral(min, max) - f5->Integral(min, max)
         << endl;
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

    return;
}
