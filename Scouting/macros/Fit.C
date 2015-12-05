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

    double peak = 120.0; // 120
    double max_fit = 300.0; // 300

    ////////////////////////////////////////
    //
    // Fit signal
    //
    ////////////////////////////////////////

    h_correct_signal->Fit("gaus", "0");
    TF1 *signal_fit = h_correct_signal->GetFunction("gaus");

    ////////////////////////////////////////
    //
    // Fit background plus MC signal
    //
    ////////////////////////////////////////

    TF1 *background = new TF1("background",
                              "[0]*(1 - x/13000)^([1])/(x/13000)^([2] + [3]*log(x/13000)) + [4]*exp(-0.5*((x - [5])/[6])^2)",
                              peak, max_fit);
    background->SetParName(0, "P0");
    background->SetParName(1, "P1");
    background->SetParName(2, "P2");
    background->SetParName(3, "P3");
    background->SetParName(4, "Constant");
    background->SetParName(5, "Mean");
    background->SetParName(6, "Sigma");

    // Initialize parameters
    background->SetParameter(0, 1.13850e+05);
    background->SetParameter(1, 2.41596e+02);
    background->SetParameter(2, 2.53918e+00);
    background->SetParameter(3, 5.56648e-01);
    background->FixParameter(4, signal_fit->GetParameter(0));
    background->FixParameter(5, signal_fit->GetParameter(1));
    background->FixParameter(6, signal_fit->GetParameter(2));

    h_data->Fit("background", "R0");

    ////////////////////////////////////////
    //
    // Fit combined background plus signal
    //
    ////////////////////////////////////////

    TF1 *combined = new TF1("combined",
                            "[0]*(1 - x/13000)^([1])/(x/13000)^([2] + [3]*log(x/13000)) + [4]*exp(-0.5*((x - [5])/[6])^2)",
                            peak, max_fit);
    combined->SetParName(0, "P0");
    combined->SetParName(1, "P1");
    combined->SetParName(2, "P2");
    combined->SetParName(3, "P3");
    combined->SetParName(4, "Constant");
    combined->SetParName(5, "Mean");
    combined->SetParName(6, "Sigma");

    // Initialize parameters
    for (int i=0; i<7; ++i) {
        combined->SetParameter(i, background->GetParameter(i));
    }
    ///combined->SetParameter(5, 173.21);
    //combined->SetParameters(4, signal_fit->GetParameter(0));
    //combined->SetParameter(5, signal_fit->GetParameter(1));
    //combined->SetParameter(6, signal_fit->GetParameter(2));
    combined->SetParLimits(5, 150.0, 190.0);
    combined->SetParLimits(6, 2.0, 100.0);

    h_data->Fit("combined", "R0");

    ////////////////////////////////////////
    //
    // Display
    //
    ////////////////////////////////////////

    TF1 *background_display = new TF1("background_display",
                                      "[0]*(1 - x/13000)^([1])/(x/13000)^([2] + [3]*log(x/13000))",
                                      peak, max_fit);
    for (int i=0; i<4; ++i) {
        background_display->SetParameter(i, combined->GetParameter(i));
    }
    background_display->SetLineColor(4);

    // TF1 *bump_display = new TF1("bump_display",
    //                             "[0]*exp(-0.5*((x - [1])/[2])^2)",
    //                             peak, max_fit);
    // for (int i=0; i<3; ++i) {
    //     bump_display->SetParameter(i, combined->GetParameter(i+4));
    // }
    // bump_display->SetLineColor(6);

    gStyle->SetOptStat(0);

    TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
    c1->cd();

    h_data->SetLineColor(1);
    h_data->SetMarkerStyle(20);
    h_data->SetMarkerSize(0.25);
    h_data->GetXaxis()->SetRangeUser(100.0, 400.0);
    h_data->SetMinimum(0);
    h_data->GetFunction("combined")->SetBit(TF1::kNotDraw, 0);
    h_data->GetFunction("combined")->SetLineColor(2);

    h_correct_signal->SetLineColor(3);

    background->SetLineColor(6);

    h_data->Draw();
    background_display->Draw("same");
    //bump_display->Draw("same");
    h_correct_signal->Draw("hist same");
    //signal_fit->Draw("same");
    //background->Draw("same");

    double signal_area = signal_fit->GetParameter(0)
        *sqrt(2.0*TMath::Pi()*pow(signal_fit->GetParameter(2), 2))
        /h_data->GetXaxis()->GetBinWidth(1);
    double fit_area = combined->GetParameter(4)
        *sqrt(2.0*TMath::Pi()*pow(combined->GetParameter(6), 2))
        /h_correct_signal->GetXaxis()->GetBinWidth(1);
    double signal_cross_section = 831.76;
    double fit_cross_section = signal_cross_section*fit_area/signal_area;

    cout << "Signal area " << signal_area << "    Integral "
         << h_correct_signal->Integral(1, 1000) << endl;
    cout << "Fit area    " << fit_area << endl;
    cout << "Cross section " << fit_cross_section << " pb" << endl;

    cout << "chi^2/ndof " << h_data->GetFunction("combined")->GetChisquare()
         << "/" << h_data->GetFunction("combined")->GetNDF() << " = "
         << h_data->GetFunction("combined")->GetChisquare()
           /h_data->GetFunction("combined")->GetNDF() << endl;

    //////////

    TH1D *h2 = h_data->Clone();
    vector<double> errors;
    for (int i=38; i<50; ++i) {
        errors.push_back(h2->GetBinError(i));
        h2->SetBinError(i, 1e6);
    }

    TF1 *masked = new TF1("masked",
                          "[0]*(1 - x/13000)^([1])/(x/13000)^([2] + [3]*log(x/13000))",
                          peak, max_fit);
    masked->SetParName(0, "P0");
    masked->SetParName(1, "P1");
    masked->SetParName(2, "P2");
    masked->SetParName(3, "P3");
    for (int i=0; i<4; ++i) {
        masked->SetParameter(i, background->GetParameter(i));
    }

    h2->Fit("masked", "R0");

    for (int i=38; i<50; ++i) {
        h2->SetBinError(i, errors[i-38]);
    }
    h2->GetFunction("masked")->SetBit(TF1::kNotDraw, 0);

    TCanvas *c2 = new TCanvas("c2", "c2", 800, 600);
    c2->cd();

    h2->Draw();

    return;
}
