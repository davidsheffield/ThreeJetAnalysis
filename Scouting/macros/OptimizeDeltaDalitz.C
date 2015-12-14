#include "ScoutingFitter.cc"
#include "CMS_lumi.C"

void OptimizeDeltaDalitz()
{
    TFile *file_data = new TFile("../../../plots/Analysis/2015-11-21/histograms_data.root");
    TFile *file_correct_signal = new TFile("../../../plots/Analysis/2015-11-21/correct_histograms_TTJets.root");
    TFile *file_incorrect_signal = new TFile("../../../plots/Analysis/2015-11-21/incorrect_histograms_TTJets.root");

    TFile *out_file = new TFile("../../../plots/Analysis/2015-11-21/optimize_deltadalitz.root", "RECREATE");
    TDirectory *dir_plots = out_file->mkdir("Plots");
    dir_plots->cd();

    TH1D *h_data, *h_correct_signal, *h_incorrect_signal;

    const int size_h_M_DeltaCut = 31;
    const int number_of_Dalitz_cuts = 10;

    double min = 120.0; // 120
    double max = 300.0; // 300
    double min_range = 100.0; // 100
    double max_range = 400.0; // 400

    TH2D *h_peak = new TH2D("h_peak", "Peak [GeV]", size_h_M_DeltaCut,
                            0.0, 310.0, number_of_Dalitz_cuts, 0.0, 0.1);
    h_peak->GetXaxis()->SetTitle("#Delta cut");
    h_peak->GetYaxis()->SetTitle("Dalitz cut");
    TH2D *h_SoverSB = new TH2D("h_SoverSB", "S/#sqrt{S + B}",
                               size_h_M_DeltaCut, 0.0, 310.0,
                               number_of_Dalitz_cuts, 0.0, 0.1);
    h_SoverSB->GetXaxis()->SetTitle("#Delta cut");
    h_SoverSB->GetYaxis()->SetTitle("Dalitz cut");

    for (int i=0; i<number_of_Dalitz_cuts; ++i) {
        for (int j=0; j<size_h_M_DeltaCut; ++j) {
            int delta = 10*j;
            double cut_Dalitz_low = 0.01*static_cast<double>(i) + 0.01;
            char str[10];
            sprintf(str, "DalitzCut_%.2f", cut_Dalitz_low);
            TString Dalitz_cut_name = str;
            sprintf(str, "%d", delta);
            TString delta_string = str;
            TString name = "h_M_" + Dalitz_cut_name + "_DeltaCut_"
                         + delta_string;
            TString full_name = "Dalitz_Cuts/" + Dalitz_cut_name +  "/" + name;

            file_data->GetObject(full_name, h_data);

            ScoutingFitter fit(h_data, min, max);
            TF1 *f1 = fit.FitP4(160.0, 188.0);  // Fit P4
            TF1 *f2 = fit.FitP4PlusGauss(0xf);  // Fit fixed P4 + gauss
            TF1 *f3 = fit.FitP4PlusGauss(0x70); // Fit P4 + fixed gauss
            TF1 *f4 = fit.FitP4PlusGauss();     // Fit P4 + gauss
            TF1 *f5 = fit.GetP4();              // Get P4 for display
            TF1 *f6 = fit.GetGauss();           // Get gauss for display

            h_data->SetLineColor(1);
            h_data->SetMarkerStyle(20);
            h_data->SetMarkerSize(0.25);
            h_data->GetXaxis()->SetRangeUser(min_range, max_range);
            h_data->SetMinimum(0);

            f4->SetLineColor(2);
            f5->SetLineColor(4);

            TCanvas *c1 = new TCanvas(name, name, 800, 600);
            h_data->Draw();
            f4->Draw("same");
            f5->Draw("same");
            c1->Write();

            h_peak->SetBinContent(j+1, i+1, f5->GetMaximumX(min, max));
            double mean = f6->GetParameter(1);
            double sigma = f6->GetParameter(2);
            double S = f6->Integral(mean - 2.0*sigma, mean + 2.0*sigma);
            double SB = f4->Integral(mean - 2.0*sigma, mean + 2.0*sigma);
            h_SoverSB->SetBinContent(j+1, i+1, S/sqrt(SB));
        }
    }

    out_file->cd();
    h_peak->Write();
    h_SoverSB->Write();
    out_file->Clone();

    return;
}
