//
// TH2DInitializer.cc
//
//     Package:  ThreeJetAnalysis/Utilities
//
// Description:  Helper function for initializing and formatting
//               two-dimensional histograms.
//
//      Author:  David G. Sheffield (Rutgers)
//

#include "ThreeJetAnalysis/Utilities/interface/TH2DInitializer.h"

TH2D* TH2DInitializer(const TString name, const TString title,
                      const Int_t nbinsx, const Double_t xlow,
                      const Double_t xup, const Int_t nbinsy,
                      const Double_t ylow, const Double_t yup,
                      const TString xaxis_title, const TString yaxis_title)
{
    TH2D *histogram = new TH2D(name, title, nbinsx, xlow, xup,
                               nbinsy, ylow, yup);
    histogram->GetXaxis()->SetTitle(xaxis_title);
    histogram->GetYaxis()->SetTitle(yaxis_title);

    return histogram;
}

template<class T>
TH2D* TH2DInitializer(T fs, const TString name, const TString title,
                      const Int_t nbinsx, const Double_t xlow,
                      const Double_t xup, const Int_t nbinsy,
                      const Double_t ylow, const Double_t yup,
                      const TString xaxis_title, const TString yaxis_title)
{
    TH2D *histogram = fs->template make<TH2D>(name, title, nbinsx, xlow, xup,
                                              nbinsy, ylow, yup);
    histogram->GetXaxis()->SetTitle(xaxis_title);
    histogram->GetYaxis()->SetTitle(yaxis_title);

    return histogram;
}

template TH2D* TH2DInitializer<edm::Service<TFileService>>(
    edm::Service<TFileService>, const TString, const TString, const Int_t,
    const Double_t, const Double_t, const Int_t, const Double_t, const Double_t,
    const TString, const TString);
template TH2D* TH2DInitializer<TFileDirectory*>(
    TFileDirectory*, const TString, const TString, const Int_t, const Double_t,
    const Double_t, const Int_t, const Double_t, const Double_t, const TString,
    const TString);
