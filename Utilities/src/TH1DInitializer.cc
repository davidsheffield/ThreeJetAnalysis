//
// TH1DInitializer.cc
//
//     Package:  ThreeJetAnalysis/Utilities
//
// Description:  Helper function for initializing and formatting
//               one-dimensional histograms.
//
//      Author:  David G. Sheffield (Rutgers)
//

#include "ThreeJetAnalysis/Utilities/interface/TH1DInitializer.h"

TH1D* TH1DInitializer(const TString name, const TString title,
                      const Int_t nbinsx, const Double_t xlow,
                      const Double_t xup, const TString xaxis_title,
                      const TString yaxis_title, const bool doLogX)
{
    TH1D *histogram;
    if (doLogX) {
        Double_t logxlow = TMath::Log10(xlow);
        Double_t logxup = TMath::Log10(xup);
        Double_t binwidth = (logxup - logxlow)/nbinsx;
        Double_t xbins[1001];
        for (int i=0; i<=nbinsx; ++i) {
            xbins[i] = TMath::Power(10, logxlow + i*binwidth);
        }
        histogram = new TH1D(name, title, nbinsx, xbins);
    } else {
        histogram = new TH1D(name, title, nbinsx, xlow, xup);
    }
    histogram->GetXaxis()->SetTitle(xaxis_title);
    histogram->GetYaxis()->SetTitle(yaxis_title);

    return histogram;
}

template<class T>
TH1D* TH1DInitializer(T fs, const TString name, const TString title,
                      const Int_t nbinsx, const Double_t xlow,
                      const Double_t xup, const TString xaxis_title,
                      const TString yaxis_title, const bool doLogX)
{
    TH1D *histogram;
    if (doLogX) {
        Double_t logxlow = TMath::Log10(xlow);
        Double_t logxup = TMath::Log10(xup);
        Double_t binwidth = (logxup - logxlow)/nbinsx;
        //Double_t xbins[nbinsx+1];
        Double_t xbins[1001];
        for (int i=0; i<=nbinsx; ++i) {
            xbins[i] = TMath::Power(10, logxlow + i*binwidth);
        }
        histogram = fs->template make<TH1D>(name, title, nbinsx, xbins);
    } else {
        histogram = fs->template make<TH1D>(name, title, nbinsx, xlow, xup);
    }
    histogram->GetXaxis()->SetTitle(xaxis_title);
    histogram->GetYaxis()->SetTitle(yaxis_title);

    return histogram;
}

template TH1D* TH1DInitializer<edm::Service<TFileService>>(
    edm::Service<TFileService>, const TString, const TString, const Int_t,
    const Double_t, const Double_t, const TString, const TString, const bool);
template TH1D* TH1DInitializer<TFileDirectory*>(
    TFileDirectory*, const TString, const TString, const Int_t, const Double_t,
    const Double_t, const TString, const TString, const bool);
