//#include "ThreeJetAnalysis/Utilities/interface/MakeHistograms.h"
#include "ThreeJetAnalysis/DiPhoton/bin/MakeHistograms.h"

#include "TChain.h"

int main()
{
    TChain *tree = new TChain("events");
    tree->Add("/eos/uscms/store/user/dgsheffi/ScoutingPFMuons/DiPhoton_ntuples/scouting_diphoton_ntuple_*.root");
    MakeHistograms t(tree);
    t.Make("test.root");
    return 0;
}
