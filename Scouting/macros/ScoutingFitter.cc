#ifndef THREEJETANALYSIS_SCOUTING_SCOUTINGFITTER_CC
#define THREEJETANALYSIS_SCOUTING_SCOUTINGFITTER_CC

#include "ScoutingFitter.h"

ScoutingFitter::ScoutingFitter(TH1D *h_data, double min, double max,
                               TH1D *h_signal):
    h_data_(h_data), min_(min), max_(max), h_signal_(h_signal)
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
    width    = 2.15783e+01;
    mp       = 1.12572e+02;
    area     = 5.79198e+05;
    gsigma   = 6.49301e+01;

    return;
}


ScoutingFitter::~ScoutingFitter()
{
}


TF1* ScoutingFitter::FitP4(double mask_min, double mask_max)
{
    TF1 *p4 = new TF1("p4",
                      "[0]*(1 - x/13000)^([1])/(x/13000)^([2] + [3]*log(x/13000))",
                      min_, max_);
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


TF1* ScoutingFitter::FitP4PlusGauss(int fixed)
{
    TF1 *p4_gauss = new TF1("p4_gauss",
                            "[0]*(1 - x/13000)^([1])/(x/13000)^([2] + [3]*log(x/13000))  + [4]*exp(-0.5*((x - [5])/[6])^2)",
                            min_, max_);
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

    for (int i=0; i<7; ++i) {
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
    sigma = fabs(p4_gauss->GetParameter(6));

    return p4_gauss;
}


TF1* ScoutingFitter::FitLandGauss(double mask_min, double mask_max)
{
    TF1 *landgauss = new TF1("landgauss", landgauss_function, min_, max_, 4);
    landgauss->SetParName(0, "Width");
    landgauss->SetParName(1, "MP");
    landgauss->SetParName(2, "Area");
    landgauss->SetParName(3, "GSigma");

    // Initialize parameters
    landgauss->SetParameter(0, width);
    landgauss->SetParameter(1, mp);
    landgauss->SetParameter(2, area);
    landgauss->SetParameter(3, gsigma);

    TH1D *hist = h_data_->Clone();
    for (int i=1; i<h_data_->GetSize()-1; ++i) {
        if (h_data_->GetXaxis()->GetBinLowEdge(i) >= mask_min
            && h_data_->GetXaxis()->GetBinUpEdge(i) <= mask_max) {
            hist->SetBinError(i, 1e12);
        }
    }

    hist->Fit("landgauss", "R0");

    width = landgauss->GetParameter(0);
    mp = landgauss->GetParameter(1);
    area = landgauss->GetParameter(2);
    gsigma = landgauss->GetParameter(3);

    return landgauss;
}

TF1* ScoutingFitter::FitLandGaussPlusGauss(int fixed)
{
    TF1 *landgauss_gauss = new TF1("landgauss_gauss", landgauss_gauss_function,
                                   min_, max_, 7);
    landgauss_gauss->SetParName(0, "Width");
    landgauss_gauss->SetParName(1, "MP");
    landgauss_gauss->SetParName(2, "Area");
    landgauss_gauss->SetParName(3, "GSigma");
    landgauss_gauss->SetParName(4, "Constant");
    landgauss_gauss->SetParName(5, "Mean");
    landgauss_gauss->SetParName(6, "Sigma");

    // Initialize parameters
    landgauss_gauss->SetParameter(0, width);
    landgauss_gauss->SetParameter(1, mp);
    landgauss_gauss->SetParameter(2, area);
    landgauss_gauss->SetParameter(3, gsigma);
    landgauss_gauss->SetParameter(4, constant);
    landgauss_gauss->SetParameter(5, mean);
    landgauss_gauss->SetParameter(6, sigma);

    for (int i=0; i<7; ++i) {
        if ((fixed >> i) & 1) {
            landgauss_gauss->FixParameter(i, landgauss_gauss->GetParameter(i));
        }
    }

    TH1D *hist = h_data_->Clone();

    hist->Fit("landgauss_gauss", "R0");

    width = landgauss_gauss->GetParameter(0);
    mp = landgauss_gauss->GetParameter(1);
    area = landgauss_gauss->GetParameter(2);
    gsigma = landgauss_gauss->GetParameter(3);
    constant = landgauss_gauss->GetParameter(4);
    mean = landgauss_gauss->GetParameter(5);
    sigma = fabs(landgauss_gauss->GetParameter(6));

    return landgauss_gauss;
}


TF1* ScoutingFitter::GetP4()
{
    TF1 *p4 = new TF1("p4",
                      "[0]*(1 - x/13000)^([1])/(x/13000)^([2] + [3]*log(x/13000))",
                      min_, max_);
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

TF1* ScoutingFitter::GetLandGauss()
{
    TF1 *landgauss = new TF1("landgauss", landgauss_function, min_, max_, 4);
    landgauss->SetParName(0, "Width");
    landgauss->SetParName(1, "MP");
    landgauss->SetParName(2, "Area");
    landgauss->SetParName(3, "GSigma");

    // Initialize parameters
    landgauss->SetParameter(0, width);
    landgauss->SetParameter(1, mp);
    landgauss->SetParameter(2, area);
    landgauss->SetParameter(3, gsigma);

    return landgauss;
}


double landgauss_function(double *x, double *par)
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


double landgauss_gauss_function(double *x, double *par)
{
    double par_landgauss[4];
    par_landgauss[0] = par[0];
    par_landgauss[1] = par[1];
    par_landgauss[2] = par[2];
    par_landgauss[3] = par[3];

    double gaussian_value = par[4]*TMath::Gaus(x[0], par[5], par[6]);

    return landgauss_function(x, par_landgauss) + gaussian_value;
}

#endif
