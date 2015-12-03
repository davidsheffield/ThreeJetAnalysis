Double_t langaufun(Double_t *x, Double_t *par)
{
    //Fit parameters:
    //par[0]=Width (scale) parameter of Landau density
    //par[1]=Most Probable (MP, location) parameter of Landau density
    //par[2]=Total area (integral -inf to inf, normalization constant)
    //par[3]=Width (sigma) of convoluted Gaussian function
    //
    //In the Landau distribution (represented by the CERNLIB approximation),
    //the maximum is located at x=-0.22278298 with the location parameter=0.
    //This shift is corrected within this function, so that the actual
    //maximum is identical to the MP parameter.

    // Numeric constants
    Double_t invsq2pi = 0.3989422804014;   // (2 pi)^(-1/2)
    Double_t mpshift  = -0.22278298;       // Landau maximum location

    // Control constants
    Double_t np = 100.0;      // number of convolution steps
    Double_t sc =   5.0;      // convolution extends to +-sc Gaussian sigmas

    // Variables
    Double_t xx;
    Double_t mpc;
    Double_t fland;
    Double_t sum = 0.0;
    Double_t xlow,xupp;
    Double_t step;
    Double_t i;


    // MP shift correction
    mpc = par[1] - mpshift * par[0];

    // Range of convolution integral
    xlow = x[0] - sc * par[3];
    xupp = x[0] + sc * par[3];

    step = (xupp-xlow) / np;

    // Convolution integral of Landau and Gaussian by sum
    for(i=1.0; i<=np/2; i++) {
        xx = xlow + (i-.5) * step;
        fland = TMath::Landau(xx,mpc,par[0]) / par[0];
        sum += fland * TMath::Gaus(x[0],xx,par[3]);

        xx = xupp - (i-.5) * step;
        fland = TMath::Landau(xx,mpc,par[0]) / par[0];
        sum += fland * TMath::Gaus(x[0],xx,par[3]);
    }

    return (par[2] * step * sum * invsq2pi / par[3]);
}

void FitLandGaus()
{
    TFile *file_data = new TFile("../../../plots/Analysis/2015-11-21/histograms_data.root");
    TFile *file_correct_signal = new TFile("../../../plots/Analysis/2015-11-21/correct_histograms_TTJets.root");

    TH1D *h_data, *h_correct_signal;

    TString name = "Dalitz_Cuts/DalitzCut_0.06/h_M_DalitzCut_0.06_DeltaCut_130";
    file_data->GetObject(name, h_data);
    file_correct_signal->GetObject(name, h_correct_signal);
    h_data->Rebin(2);
    h_correct_signal->Rebin(2);

    double peak = 100.0; // 120
    double max_fit = 400.0; // 300

    ////////////////////////////////////////
    //
    // Fit signal
    //
    ////////////////////////////////////////

    h_correct_signal->Fit("gaus", "0");
    TF1 *signal_fit = h_correct_signal->GetFunction("gaus");

    ////////////////////////////////////////
    //
    // Fit landgauss
    //
    ////////////////////////////////////////

    TF1 *ffit = new TF1("landgaus", langaufun, peak, max_fit, 4);
    double startvalues[4] = {24, 119.0, 2.22e6, 56.0};
    ffit->SetParameters(startvalues);
    ffit->SetParNames("Width", "MP", "Area", "GSigma");
    h_data->Fit("landgaus", "R");

    ////////////////////////////////////////
    //
    // Display
    //
    ////////////////////////////////////////

    gStyle->SetOptStat(0);

    TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
    c1->cd();

    h_data->SetLineColor(1);
    h_data->SetMarkerStyle(20);
    h_data->SetMarkerSize(0.25);
    h_data->GetXaxis()->SetRangeUser(100.0, 400.0);
    h_data->SetMinimum(0);
    //h_data->GetFunction("combined")->SetBit(TF1::kNotDraw, 0);
    //h_data->GetFunction("combined")->SetLineColor(2);

    h_correct_signal->SetLineColor(3);

    //background->SetLineColor(6);

    h_data->Draw();
    //background_display->Draw("same");
    //bump_display->Draw("same");
    h_correct_signal->Draw("hist same");
    //signal_fit->Draw("same");
    //background->Draw("same");

    double signal_area = signal_fit->GetParameter(0)
        *sqrt(2.0*TMath::Pi()*pow(signal_fit->GetParameter(2), 2))
        /h_data->GetXaxis()->GetBinWidth(1);
    // double fit_area = combined->GetParameter(4)
    //     *sqrt(2.0*TMath::Pi()*pow(combined->GetParameter(6), 2))
    //     /h_correct_signal->GetXaxis()->GetBinWidth(1);
    double signal_cross_section = 831.76;
    // double fit_cross_section = signal_cross_section*fit_area/signal_area;

    cout << "Signal area " << signal_area << "    Integral "
         << h_correct_signal->Integral(1, 1000) << endl;
    // cout << "Fit area    " << fit_area << endl;
    // cout << "Cross section " << fit_cross_section << " pb" << endl;

    // cout << "chi^2/ndof " << h_data->GetFunction("combined")->GetChisquare()
    //      << "/" << h_data->GetFunction("combined")->GetNDF() << endl;

    return;
}
