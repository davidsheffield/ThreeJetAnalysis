#ifndef THREEJETANALYSIS_SCOUTING_SCOUTINGFITTER_H
#define THREEJETANALYSIS_SCOUTING_SCOUTINGFITTER_H

#include "TH1D.h"
#include "TF1.h"
#include "TMath.h"

class ScoutingFitter {
public:
    ScoutingFitter(TH1D*, double, double, TH1D *h_signal=0);
    ~ScoutingFitter();

    TF1* FitP4(double, double);
    TF1* FitP4PlusGauss(int fixed=0);
    TF1* FitLandGauss(double, double);
    TF1* FitLandGaussPlusGauss(int fixed=0);

    TF1* GetP4();
    TF1* GetLandGauss();
    TF1* GetGauss();

    static double landgauss_function(double*, double*);
    static double landgauss_gauss_function(double*, double*);

private:
    TH1D *h_data_;
    TH1D *h_signal_;
    double min_;
    double max_;

    double P0;
    double P1;
    double P2;
    double P3;
    double constant;
    double mean;
    double sigma;
    double width;
    double mp;
    double area;
    double gsigma;
};

#endif
