#include "ThreeJetAnalysis/DiPhoton/src/MakeHistograms.cc"

void makeHistograms()
{
    TChain *tree = new TChain("events");
    tree->Add("/cms/data26/sheffield/ScoutingDiPhotons/ntuples/scouting_diphoton_ntuple_*.root");
    MakeHistograms t(tree);
    t.Make("histograms.root");
    return;
}
