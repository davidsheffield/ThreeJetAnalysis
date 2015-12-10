#ifndef THREEJETANALYSIS_SCOUTING_SCOUTINGFITTER_CC
#define THREEJETANALYSIS_SCOUTING_SCOUTINGFITTER_CC

#include "ScoutingFitter.h"

ScoutingFitter::ScoutingFitter(TH1D *h_data, TH1D *h_signal):
    h_data_(h_data), h_signal_(h_signal)
{
    // if (h_signal != 0) {
    //     h_signal_->Draw();
    // }
    P0       = 3.35323e+05;
    P1       = 2.44941e+02;
    P2       = 2.20870e+00;
    P3       = 5.30630e-01;
    constant = 4.18961e+02;
    mean     = 1.74515e+02;
    sigma    = 9.81969e+00;

    return;
}

ScoutingFitter::~ScoutingFitter()
{
}

TF1* ScoutingFitter::FitP4(double min, double max, double mask_min,
                           double mask_max)
{
    TF1 *p4 = new TF1("p4",
                      "[0]*(1 - x/13000)^([1])/(x/13000)^([2] + [3]*log(x/13000))",
                      min, max);
    p4->SetParName(0, "P0");
    p4->SetParName(1, "P1");
    p4->SetParName(2, "P2");
    p4->SetParName(3, "P3");

    // Initialize parameters
    p4->SetParameter(0, P0);
    p4->SetParameter(1, P1);
    p4->SetParameter(2, P2);
    p4->SetParameter(3, P3);

    TH1D *hist = h_data_->Clone();
    for (int i=1; i<h_data_->GetSize()-1; ++i) {
        if (h_data_->GetXaxis()->GetBinLowEdge(i) >= mask_min
            && h_data_->GetXaxis()->GetBinUpEdge(i) <= mask_max) {
            hist->SetBinError(i, 1e12);
        }
    }

    hist->Fit("p4", "R0");

    P0 = p4->GetParameter(0);
    P1 = p4->GetParameter(1);
    P2 = p4->GetParameter(2);
    P3 = p4->GetParameter(3);

    return p4;
}

TF1* ScoutingFitter::FitP4PlusGauss(double min, double max, int fixed)
{
    TF1 *p4_gauss = new TF1("p4_gauss",
                            "[0]*(1 - x/13000)^([1])/(x/13000)^([2] + [3]*log(x/13000))  + [4]*exp(-0.5*((x - [5])/[6])^2)",
                            min, max);
    p4_gauss->SetParName(0, "P0");
    p4_gauss->SetParName(1, "P1");
    p4_gauss->SetParName(2, "P2");
    p4_gauss->SetParName(3, "P3");
    p4_gauss->SetParName(4, "Constant");
    p4_gauss->SetParName(5, "Mean");
    p4_gauss->SetParName(6, "Sigma");

    // Initialize parameters
    p4_gauss->SetParameter(0, P0);
    p4_gauss->SetParameter(1, P1);
    p4_gauss->SetParameter(2, P2);
    p4_gauss->SetParameter(3, P3);
    p4_gauss->SetParameter(4, constant);
    p4_gauss->SetParameter(5, mean);
    p4_gauss->SetParameter(6, sigma);

    for (i=0; i<7; ++i) {
        if ((fixed >> i) & 1) {
            p4_gauss->FixParameter(i, p4_gauss->GetParameter(i));
        }
    }

    TH1D *hist = h_data_->Clone();

    hist->Fit("p4_gauss", "R0");

    P0 = p4_gauss->GetParameter(0);
    P1 = p4_gauss->GetParameter(1);
    P2 = p4_gauss->GetParameter(2);
    P3 = p4_gauss->GetParameter(3);
    constant = p4_gauss->GetParameter(4);
    mean = p4_gauss->GetParameter(5);
    sigma = p4_gauss->GetParameter(6);

    return p4_gauss;
}

TF1* ScoutingFitter::GetP4(double min, double max)
{
    TF1 *p4 = new TF1("p4",
                      "[0]*(1 - x/13000)^([1])/(x/13000)^([2] + [3]*log(x/13000))",
                      min, max);
    p4->SetParName(0, "P0");
    p4->SetParName(1, "P1");
    p4->SetParName(2, "P2");
    p4->SetParName(3, "P3");

    // Initialize parameters
    p4->SetParameter(0, P0);
    p4->SetParameter(1, P1);
    p4->SetParameter(2, P2);
    p4->SetParameter(3, P3);

    return p4;
}

#endif
