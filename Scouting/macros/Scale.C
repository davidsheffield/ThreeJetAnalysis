void Scale()
{
    TFile *f_data = new TFile("../../../plots/Analysis/2015-11-21/histograms_data.root");
    TFile *f_background = new TFile("../../../plots/Analysis/2015-11-21/histograms_4jets_data.root");

    TFile *f_scale = new TFile("scales_4jet_pt.root", "RECREATE");

    TH1D *h_data, *h_background;
    TString histogram_name = "h_triplet_scalar_pt";
    f_data->GetObject(histogram_name, h_data);
    f_background->GetObject(histogram_name, h_background);

    double global_scale = h_data->Integral(0, 10000)
                         /h_background->Integral(0, 10000);
    cout << "Scaling background by global factor " << global_scale << endl;
    h_background->Scale(global_scale);

    TH1D *h_scales = new TH1D("h_scales", "Scalar p_{T} scale factors",
                              5000, 0.0, 5000.0);
    for (int i=1; i<5001; ++i) {
        double bkg = h_background->GetBinContent(i);
        double scale = 1.0;
        if (bkg != 0) {
            double scale = h_data->GetBinContent(i)/bkg;
            if (scale > 1000 && bkg < 100)
                scale = 1.0;
        }
        h_scales->SetBinContent(i, scale);
    }

    TH1D *h_scaled_bkg = h_background->Clone();
    h_scaled_bkg->Multiply(h_scales);

    TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
    c1->cd();

    h_data->SetLineColor(1);
    h_data->SetMarkerStyle(20);
    h_data->SetMarkerSize(0.25);
    h_background->SetLineColor(4);

    h_data->Draw();
    h_background->Draw("hist same");

    TCanvas *c2 = new TCanvas("c2", "c2", 800, 600);
    c2->cd();

    h_scales->SetLineColor(1);
    h_scales->SetMarkerStyle(20);
    h_scales->SetMarkerSize(0.25);

    h_scales->Draw();

    TCanvas *c3 = new TCanvas("c3", "c3", 800, 600);
    c3->cd();

    h_scaled_bkg->SetLineColor(4);

    h_data->Draw();
    h_scaled_bkg->Draw("hist same");

    // Write out scales
    f_scale->cd();
    h_scales->Write();

    return;
}
