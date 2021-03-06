#include "ScoutingFitter.cc"
#include "CMS_lumi.C"

void Fit()
{
    TString version = "";//noBtag_";
    TFile *file_data = new TFile("../../../plots/Analysis/2015-11-21/histograms_"
                                 + version + "data.root");
    TFile *file_correct_signal = new TFile("../../../plots/Analysis/2015-11-21/correct_histograms_"
                                           + version + "TTJets.root");
    TFile *file_incorrect_signal = new TFile("../../../plots/Analysis/2015-11-21/incorrect_histograms_"
                                             + version + "TTJets.root");

    TH1D *h_data, *h_correct_signal, *h_incorrect_signal;

    TString name = "Dalitz_Cuts/DalitzCut_0.06/h_M_DalitzCut_0.06_DeltaCut_110";
    file_data->GetObject(name, h_data);
    file_correct_signal->GetObject(name, h_correct_signal);
    file_incorrect_signal->GetObject(name, h_incorrect_signal);
    TH1D *h_signal = h_correct_signal->Clone();
    h_signal->Add(h_incorrect_signal);

    int rebin = 2;
    h_data->Rebin(rebin);
    h_signal->Rebin(rebin);

    TLatex *text = new TLatex(230.0, 4900, "#splitline{#splitline{#Delta = 110 GeV}{D_{low} > 0.06}}{1 jet with CSV > 0.95}");
    text.SetTextFont(43);
    text.SetTextSize(24);

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
    h_data->GetYaxis()->SetTitleOffset(0.9);
    h_signal->GetYaxis()->SetTitle("dN/dm");
    h_correct_signal->GetYaxis()->SetTitle("dN/dm");
    h_incorrect_signal->GetYaxis()->SetTitle("dN/dm");

    double min = 120.0; // 120
    double max = 300.0; // 300
    double min_range = 100.0; // 100
    double max_range = 400.0; // 400

    // Do fit
    ScoutingFitter fit(h_data, min, max);
    TF1 *f1 = fit.FitP4(160.0, 300.0);  // Fit P4
    TF1 *f2 = fit.FitP4PlusGauss(0xf);  // Fit fixed P4 + gauss
    TF1 *f3 = fit.FitP4PlusGauss(0x70); // Fit P4 + fixed gauss
    TF1 *f4 = fit.FitP4PlusGauss();     // Fit P4 + gauss
    TF1 *f5 = fit.GetP4();              // Get P4 for display
    TF1 *f6 = fit.GetGauss();           // Get gauss for display
    TF1 *f7 = fit.FitP4(0.0, 0.0);      // Fit P4 without mask

    ScoutingFitter fit_signal(h_signal, min, max);
    TF1 *sf1 = fit_signal.FitP4(160.0, 188.0);  // Fit P4
    TF1 *sf2 = fit_signal.FitP4PlusGauss(0xf);  // Fit fixed P4+gauss
    TF1 *sf3 = fit_signal.FitP4PlusGauss(0x70); // Fit P4+fixed gauss
    TF1 *sf4 = fit_signal.FitP4PlusGauss();     // Fit P4 + gauss
    TF1 *sf5 = fit_signal.GetP4();              // Get P4 for display
    TF1 *sf6 = fit_signal.GetGauss();           // Get gauss for display

    gStyle->SetOptStat(0);

    TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
    TPad *pad1a = new TPad("pad1a", "The pad 80% of the height",
                           0.0, 0.2, 1.0, 1.0, 0);
    TPad *pad1b = new TPad("pad1b", "The pad 20% of the height",
                           0.0, 0.0, 1.0, 0.2, 0);
    c1->cd();
    pad1a->Draw();
    pad1b->Draw();

    h_data->SetLineColor(1);
    h_data->SetMarkerStyle(20);
    h_data->SetMarkerSize(0.5);
    h_data->GetXaxis()->SetRangeUser(min_range, max_range);
    h_data->SetMinimum(0);

    f4->SetLineColor(2);
    f5->SetLineColor(4);
    h_correct_signal->SetLineColor(1);
    h_incorrect_signal->SetLineColor(1);
    h_correct_signal->SetFillColor(91);
    h_incorrect_signal->SetFillColor(5);
    sf4->SetLineColor(2);
    sf5->SetLineColor(4);
    sf4->SetLineStyle(2);
    sf5->SetLineStyle(2);

    h_data->SetTitle();
    h_data->GetYaxis()->SetTitleSize(0.05);
    //h_data->GetYaxis()->SetTitleOffset(1.4);
    h_data->GetXaxis()->SetTitle();

    THStack *h_signal_stack = new THStack("h_signal_stack", "signal stack");
    h_signal_stack->Add(h_incorrect_signal);
    h_signal_stack->Add(h_correct_signal);

    pad1a->cd();
    pad1a->SetTickx();
    pad1a->SetTicky();
    pad1a->SetBottomMargin(0.0);
    h_data->Draw();
    f4->Draw("same");
    f5->Draw("same");
    h_signal_stack->Draw("hist same");
    sf4->Draw("same");
    sf5->Draw("same");
    h_data->Draw("sameaxis"); // Redraw axes

    TLegend *leg1 = new TLegend(0.6, 0.4, 0.89, 0.6);
    leg1->SetLineColor(0);
    leg1->SetFillColor(0);
    leg1->AddEntry(h_data, "data", "lp");
    leg1->AddEntry(f4, "P4 + Gaussian", "l");
    leg1->AddEntry(f5, "P4", "l");
    leg1->AddEntry(h_correct_signal, "t#bar{t}, correct", "f");
    leg1->AddEntry(h_incorrect_signal, "t#bar{t}, incorrect", "f");
    leg1->Draw();

    text->Draw();

    TH1D *h_pull_f5 = new TH1D("h_pull_f5", "Pulls", h_data->GetSize()-2,
                               h_data->GetXaxis()->GetXmin(),
                               h_data->GetXaxis()->GetXmax());
    TH1D *h_pull_f4 = new TH1D("h_pull_f4", "Pulls", h_data->GetSize()-2,
                               h_data->GetXaxis()->GetXmin(),
                               h_data->GetXaxis()->GetXmax());
    for (int i=0; i<h_pull_f5->GetSize(); ++i) {
        if (h_pull_f5->GetBinCenter(i) >= min
            && h_pull_f5->GetBinCenter(i) <= max) {
            h_pull_f5->SetBinContent(i, (h_data->GetBinContent(i)
                                         - f5->Eval(h_data->GetBinCenter(i)))
                                        /h_data->GetBinError(i));
            h_pull_f5->SetBinError(i, 1.0);
            h_pull_f4->SetBinContent(i, (h_data->GetBinContent(i)
                                         - f4->Eval(h_data->GetBinCenter(i)))
                                        /h_data->GetBinError(i));
            h_pull_f4->SetBinError(i, 1.0);
        } else {
            h_pull_f5->SetBinContent(i, 0.0);
            h_pull_f5->SetBinError(i, 0.0);
            h_pull_f4->SetBinContent(i, 0.0);
            h_pull_f4->SetBinError(i, 0.0);
        }
    }
    h_pull_f5->SetTitle();
    h_pull_f5->GetXaxis()->SetLabelSize(0.14);
    h_pull_f5->GetYaxis()->SetLabelSize(0.14);
    h_pull_f5->GetXaxis()->SetTitleSize(0.2);
    h_pull_f5->GetYaxis()->SetTitleSize(0.15);
    h_pull_f5->GetXaxis()->SetTitleOffset(0.75);
    h_pull_f5->GetYaxis()->SetTitleOffset(0.2);
    h_pull_f5->GetXaxis()->SetTitle("M_{jjj} [GeV]");
    //h_pull_f5->GetYaxis()->SetTitle("pull");
    h_pull_f5->GetYaxis()->SetTitle("#frac{data - fit}{#sigma_{data}}");
    h_pull_f5->GetXaxis()->SetTickLength(0.1);
    h_pull_f5->GetYaxis()->SetNdivisions(210);
    h_pull_f5->GetXaxis()->SetRange(h_data->GetXaxis()->GetFirst(),
                                    h_data->GetXaxis()->GetLast());
    h_pull_f5->SetLineColor(1);
    h_pull_f5->SetFillColor(4);
    h_pull_f4->SetLineColor(2);

    pad1b->cd();
    pad1b->SetTickx();
    pad1b->SetTicky();
    pad1b->SetGridy();
    pad1b->SetTopMargin(0.0);
    pad1b->SetBottomMargin(0.4);
    h_pull_f5->Draw("hist");
    h_pull_f4->Draw("hist same");

    CMS_lumi(pad1a, 4, 33);

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
    TPad *pad2a = new TPad("pad2a", "The pad 80% of the height",
                           0.0, 0.2, 1.0, 1.0, 0);
    TPad *pad2b = new TPad("pad2b", "The pad 20% of the height",
                           0.0, 0.0, 1.0, 0.2, 0);
    c2->cd();
    pad2a->Draw();
    pad2b->Draw();

    g4->SetLineColor(2);
    g5->SetLineColor(4);
    sg4->SetLineColor(2);
    sg5->SetLineColor(4);
    sg4->SetLineStyle(2);
    sg5->SetLineStyle(2);

    pad2a->cd();
    h_data->Draw();
    g4->Draw("same");
    g5->Draw("same");
    h_signal_stack->Draw("hist same");
    sg4->Draw("same");
    sg5->Draw("same");
    h_data->Draw("sameaxis"); // Redraw axes

    TLegend *leg2 = new TLegend(0.6, 0.4, 0.89, 0.6);
    leg2->SetLineColor(0);
    leg2->SetFillColor(0);
    leg2->AddEntry(h_data, "data", "lp");
    leg2->AddEntry(g4, "LandGauss + Gauss", "l");
    leg2->AddEntry(g5, "LandGauss", "l");
    leg2->AddEntry(h_correct_signal, "t#bar{t}, correct", "f");
    leg2->AddEntry(h_incorrect_signal, "t#bar{t}, incorrect", "f");
    leg2->Draw();

    TH1D *h_pull_g5 = new TH1D("h_pull_g5", "Pulls", h_data->GetSize()-2,
                               h_data->GetXaxis()->GetXmin(),
                               h_data->GetXaxis()->GetXmax());
    TH1D *h_pull_g4 = new TH1D("h_pull_g4", "Pulls", h_data->GetSize()-2,
                               h_data->GetXaxis()->GetXmin(),
                               h_data->GetXaxis()->GetXmax());
    for (int i=0; i<h_pull_g5->GetSize(); ++i) {
        if (h_pull_g5->GetBinCenter(i) >= min
            && h_pull_g5->GetBinCenter(i) <= max) {
            h_pull_g5->SetBinContent(i, (h_data->GetBinContent(i)
                                         - g5->Eval(h_data->GetBinCenter(i)))
                                        /h_data->GetBinError(i));
            h_pull_g5->SetBinError(i, 1.0);
            h_pull_g4->SetBinContent(i, (h_data->GetBinContent(i)
                                         - g4->Eval(h_data->GetBinCenter(i)))
                                        /h_data->GetBinError(i));
            h_pull_g4->SetBinError(i, 1.0);
        } else {
            h_pull_g5->SetBinContent(i, 0.0);
            h_pull_g5->SetBinError(i, 0.0);
            h_pull_g4->SetBinContent(i, 0.0);
            h_pull_g4->SetBinError(i, 0.0);
        }
    }
    h_pull_g5->SetTitle();
    h_pull_g5->GetXaxis()->SetLabelSize(0.14);
    h_pull_g5->GetYaxis()->SetLabelSize(0.14);
    h_pull_g5->GetXaxis()->SetTitleSize(0.2);
    h_pull_g5->GetYaxis()->SetTitleSize(0.2);
    h_pull_g5->GetXaxis()->SetTitleOffset(0.75);
    h_pull_g5->GetYaxis()->SetTitleOffset(0.2);
    h_pull_g5->GetXaxis()->SetTitle("M_{jjj} [GeV]");
    h_pull_g5->GetYaxis()->SetTitle("pull");
    h_pull_g5->GetXaxis()->SetRange(h_data->GetXaxis()->GetFirst(),
                                    h_data->GetXaxis()->GetLast());
    h_pull_g5->SetLineColor(1);
    h_pull_g5->SetFillColor(4);
    h_pull_g4->SetLineColor(2);

    pad2b->cd();
    pad2b->SetGridy();
    pad2b->SetTopMargin(0.05);
    pad2b->SetBottomMargin(0.4);
    h_pull_g5->Draw("hist");
    h_pull_g4->Draw("hist same");

    CMS_lumi(pad2a, 4, 33);

    cout << "f1 " << f1->GetChisquare() << "/" << f1->GetNDF() - 5 << " = "
         << f1->GetChisquare()/(f1->GetNDF() - 5) << endl;
    cout << "f2 " << f2->GetChisquare() << "/" << f2->GetNDF() << " = "
         << f2->GetChisquare()/f2->GetNDF() << endl;
    cout << "f3 " << f3->GetChisquare() << "/" << f3->GetNDF() << " = "
         << f3->GetChisquare()/f3->GetNDF() << endl;
    cout << "f4 " << f4->GetChisquare() << "/" << f4->GetNDF() << " = "
         << f4->GetChisquare()/f4->GetNDF() << endl;
    cout << "f5 " << h_data->Chisquare(f5, "R") << endl;
    cout << "f4 " << h_data->Chisquare(f4, "R") << endl;
    cout << "f7 " << f7->GetChisquare() << "/" << f7->GetNDF() << " = "
         << f7->GetChisquare()/f7->GetNDF() << endl;
    cout << "f5 max " << f5->GetMaximumX(min, max) << endl;
    cout << "g1 " << g1->GetChisquare() << "/" << g1->GetNDF() - 5 << " = "
         << g1->GetChisquare()/(g1->GetNDF() - 5) << endl;
    cout << "g4 " << g4->GetChisquare() << "/" << g4->GetNDF() << " = "
         << g4->GetChisquare()/g4->GetNDF() << endl;

    double mean = f6->GetParameter(1);
    double sigma = f6->GetParameter(2);
    cout << "data: mean " << mean << " sigma " << sigma << " integral "
         << f6->Integral(mean - 4.0*sigma, mean + 4.0*sigma) << endl;
    mean = sf6->GetParameter(1);
    sigma = sf6->GetParameter(2);
    cout << "ttbar: mean " << mean << " sigma " << sigma << " integral "
         << sf6->Integral(mean - 4.0*sigma, mean + 4.0*sigma) << endl;
    cout << h_correct_signal->Integral(0,10000) + h_incorrect_signal->Integral(0,10000) << endl;

    return;
}
