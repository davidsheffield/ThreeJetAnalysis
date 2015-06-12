#ifndef _THREEJETANALYSIS_UTILITIES_TH2DINITIALIZER_H_
#define _THREEJETANALYSIS_UTILITIES_TH2DINITIALIZER_H_

//
// TH2DInitializer.h
//
//     Package:  ThreeJetAnalysis/Utilities
//
// Description:  Helper function for initializing and formatting
//               two-dimensional histograms.
//
//      Author:  David G. Sheffield (Rutgers)
//

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TH2D.h"

TH2D* TH2DInitializer(edm::Service<TFileService>, const TString, const TString,
		      const Int_t, const Double_t, const Double_t, const Int_t,
		      const Double_t, const Double_t, const TString,
		      const TString);
TH2D* TH2DInitializer(TFileDirectory*, const TString, const TString,
		      const Int_t, const Double_t, const Double_t, const Int_t,
		      const Double_t, const Double_t, const TString,
		      const TString);

#endif
