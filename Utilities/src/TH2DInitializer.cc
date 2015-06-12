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

TH2D* TH2DInitializer(edm::Service<TFileService> fs, TString name,
		      TString title, Int_t nbinsx, Double_t xlow, Double_t xup,
		      Int_t nbinsy, Double_t ylow, Double_t yup,
		      TString xaxis_title, TString yaxis_title)
{
    TH2D *histogram = fs->make<TH2D>(name, title, nbinsx, xlow, xup, nbinsy,
				     ylow, yup);
    histogram->GetXaxis()->SetTitle(xaxis_title);
    histogram->GetYaxis()->SetTitle(yaxis_title);

    return histogram;
}

TH2D* TH2DInitializer(TFileDirectory *dir, TString name,
		      TString title, Int_t nbinsx, Double_t xlow, Double_t xup,
		      Int_t nbinsy, Double_t ylow, Double_t yup,
		      TString xaxis_title, TString yaxis_title)
{
    TH2D *histogram = dir->make<TH2D>(name, title, nbinsx, xlow, xup, nbinsy,
				      ylow, yup);
    histogram->GetXaxis()->SetTitle(xaxis_title);
    histogram->GetYaxis()->SetTitle(yaxis_title);

    return histogram;
}
