void CheckPtBins()
{
    const int bin_num = 7;
    TString file_names[bin_num] = {"../bin/histograms_QCD_Pt-120To170.root",
                                   "../bin/histograms_QCD_Pt-170To300.root",
                                   "../bin/histograms_QCD_Pt-300To470.root",
                                   "../bin/histograms_QCD_Pt-470To600.root",
                                   "../bin/histograms_QCD_Pt-600To800.root",
                                   "../bin/histograms_QCD_Pt-800To1000.root",
                                   "../bin/histograms_QCD_Pt-1000To1400.root"};
    TFile *files[bin_num];
    TH1D *h_pts[bin_num];
    for (int i=0; i<bin_num; ++i) {
        files[i] = new TFile(file_names[i]);
        files[i]->GetObject("h_jet_pt", h_pts[i]);
        h_pts[i]->SetMarkerColor(i+2);
        h_pts[i]->SetLineColor(i+2);
    }

    h_pts[0]->SetMinimum(1e-2);

    TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
    c1->cd();
    h_pts[0]->Draw("e1");
    for (int i=1; i<bin_num; ++i) {
        h_pts[i]->Draw("e1 same");
    }

    return;
}
