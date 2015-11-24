#include "ThreeJetAnalysis/Scouting/bin/NtupleTree.h"

int main(int argc, char* argv[])
{
    if (argc != 14)
        return 1;

    char *endptr;

    int isMC = strtol(argv[3], &endptr, 10);

    TString ntuple = argv[1];
    TChain *chain = new TChain("events");
    chain->Add(ntuple);

    if (isMC != 2) {
        NtupleTree ntuple_tree(chain, isMC);
        ntuple_tree.MakeHistograms(argv[2], strtod(argv[4], &endptr),
                                   strtol(argv[5], &endptr, 10),
                                   strtol(argv[6], &endptr, 10),
                                   strtol(argv[7], &endptr, 10),
                                   strtol(argv[8], &endptr, 10),
                                   strtol(argv[9], &endptr, 10),
                                   strtol(argv[10], &endptr, 10),
                                   strtod(argv[11], &endptr),
                                   strtod(argv[12], &endptr),
                                   strtod(argv[13], &endptr));
    } else if (isMC == 2) {
        TString name = argv[2];

        NtupleTree ntuple_tree_correct(chain, isMC);
        ntuple_tree_correct->MakeHistograms(
            "correct_" + name, strtod(argv[4], &endptr),
            strtol(argv[5], &endptr, 10), strtol(argv[6], &endptr, 10),
            strtol(argv[7], &endptr, 10), strtol(argv[8], &endptr, 10),
            strtol(argv[9], &endptr, 10), strtol(argv[10], &endptr, 10),
            strtod(argv[11], &endptr), strtod(argv[12], &endptr),
            strtod(argv[13], &endptr));

        NtupleTree ntuple_tree_incorrect(chain, -isMC);
        ntuple_tree_incorrect->MakeHistograms(
            "incorrect_" + name, strtod(argv[4], &endptr),
            strtol(argv[5], &endptr, 10), strtol(argv[6], &endptr, 10),
            strtol(argv[7], &endptr, 10), strtol(argv[8], &endptr, 10),
            strtol(argv[9], &endptr, 10), strtol(argv[10], &endptr, 10),
            strtod(argv[11], &endptr), strtod(argv[12], &endptr),
            strtod(argv[13], &endptr));
    }

    return 0;
}
