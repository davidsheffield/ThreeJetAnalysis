#ifndef _THREEJETANALYSIS_UTILITIES_TH1DINITIALIZER_H_
#define _THREEJETANALYSIS_UTILITIES_TH1DINITIALIZER_H_

//
// TH1DInitializer.h
//
//     Package:  ThreeJetAnalysis/Utilities
//
// Description:  Helper function for initializing and formatting
//               one-dimensional histograms.
//
//      Author:  David G. Sheffield (Rutgers)
//

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TH1D.h"
#include "TMath.h"

TH1D* TH1DInitializer(const TString, const TString, const Int_t, const Double_t,
                      const Double_t, const TString, const TString,
                      const bool doLogX = false);

template<class T>
TH1D* TH1DInitializer(T, const TString, const TString, const Int_t,
                      const Double_t, const Double_t, const TString,
                      const TString, const bool doLogX = false);

extern template TH1D* TH1DInitializer<edm::Service<TFileService>>(
    edm::Service<TFileService>, const TString, const TString, const Int_t,
    const Double_t, const Double_t, const TString, const TString, const bool);
extern template TH1D* TH1DInitializer<TFileDirectory*>(
    TFileDirectory*, const TString, const TString, const Int_t, const Double_t,
    const Double_t, const TString, const TString, const bool);
#endif
