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

TH1D* TH1DInitializer(edm::Service<TFileService> fs, TString name,
		      TString title, Int_t nbinsx, Double_t xlow, Double_t xup,
		      TString xaxis_title, TString yaxis_title)
{
    TH1D *histogram = fs->make<TH1D>(name, title, nbinsx, xlow, xup);
    histogram->GetXaxis()->SetTitle(xaxis_title);
    histogram->GetYaxis()->SetTitle(yaxis_title);

    return histogram;
}

TH1D* TH1DInitializer(TFileDirectory *dir, TString name,
		      TString title, Int_t nbinsx, Double_t xlow, Double_t xup,
		      TString xaxis_title, TString yaxis_title)
{
    TH1D *histogram = dir->make<TH1D>(name, title, nbinsx, xlow, xup);
    histogram->GetXaxis()->SetTitle(xaxis_title);
    histogram->GetYaxis()->SetTitle(yaxis_title);

    return histogram;
}
