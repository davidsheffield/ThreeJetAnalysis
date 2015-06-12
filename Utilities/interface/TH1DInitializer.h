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

TH1D* TH1DInitializer(edm::Service<TFileService>, TString, TString, Int_t,
		      Double_t, Double_t, TString, TString, Color_t);

#endif
