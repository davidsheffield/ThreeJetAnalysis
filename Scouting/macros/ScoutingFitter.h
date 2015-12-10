#ifndef THREEJETANALYSIS_SCOUTING_SCOUTINGFITTER_H
#define THREEJETANALYSIS_SCOUTING_SCOUTINGFITTER_H

#include "TH1D.h"
#include "TF1.h"

class ScoutingFitter {
public:
    ScoutingFitter(TH1D *h_data, TH1D *h_signal=0);
    ~ScoutingFitter();

    TF1* FitP4(double, double, double, double);
    TF1* FitP4PlusGauss(double, double, int fixed=0);

private:
    TH1D *h_data_;
    TH1D *h_signal_;

    double P0;
    double P1;
    double P2;
    double P3;
    double constant;
    double mean;
    double sigma;
};

#endif
