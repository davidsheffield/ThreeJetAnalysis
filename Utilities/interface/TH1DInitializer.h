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

TH1D* TH1DInitializer(edm::Service<TFileService>, const TString, const TString,
		      const Int_t, const Double_t, const Double_t,
		      const TString, const TString, const bool doLogX = false);
TH1D* TH1DInitializer(TFileDirectory*, const TString, const TString,
		      const Int_t, const Double_t, const Double_t,
		      const TString, const TString, const bool doLogX = false);

#endif
