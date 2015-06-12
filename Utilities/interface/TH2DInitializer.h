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

TH2D* TH2DInitializer(edm::Service<TFileService>, TString, TString, Int_t,
		      Double_t, Double_t, Int_t, Double_t, Double_t, TString,
		      TString);
TH2D* TH2DInitializer(TFileDirectory*, TString, TString, Int_t,
		      Double_t, Double_t, Int_t, Double_t, Double_t, TString,
		      TString);

#endif
