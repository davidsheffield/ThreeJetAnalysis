#include "ThreeJetAnalysis/Scouting/bin/NtupleTree.h"

int main(int argc, char* argv[])
{
    if (argc != 13)
        return 1;

    char *endptr;

    TString ntuple = argv[1];
    TChain *chain = new TChain("events");
    chain->Add(ntuple);

    NtupleTree ntuple_tree(chain);
    ntuple_tree.MakeHistograms(argv[2], strtod(argv[3], &endptr),
                               strtol(argv[4], &endptr, 10),
                               strtol(argv[5], &endptr, 10),
                               strtol(argv[6], &endptr, 10),
                               strtol(argv[7], &endptr, 10),
                               strtol(argv[8], &endptr, 10),
                               strtol(argv[9], &endptr, 10),
                               strtod(argv[10], &endptr),
                               strtod(argv[11], &endptr),
                               strtod(argv[12], &endptr));

    return 0;
}
