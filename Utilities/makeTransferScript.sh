#!/bin/bash

datasets=(
    #"/eos/uscms/store/user/dgsheffi/ScoutingPFHT/crab_Scouting_Ntuples_v5/151121_194850/0000/"
    "/eos/uscms/store/user/dgsheffi/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_Resolved_Ntuples_TTJets_v1/151121_195850/0000/"
    #"/eos/uscms/store/user/dgsheffi/QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8/Resolved_Ntuples_QCD_Pt_120to170_v2/151122_005720/0000/"
    "/eos/uscms/store/user/dgsheffi/QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8/Resolved_Ntuples_QCD_Pt_170to300_v2/151122_005728/0000/"
    "/eos/uscms/store/user/dgsheffi/QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8/Resolved_Ntuples_QCD_Pt_300to470_v2/151122_005735/0000/"
    #"/eos/uscms/store/user/dgsheffi/QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8/Resolved_Ntuples_QCD_Pt_470to600_v2/151122_005748/0000/"
    #"/eos/uscms/store/user/dgsheffi/QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8/Resolved_Ntuples_QCD_Pt_600to800_v2/151122_005756/0000/"
    "/eos/uscms/store/user/dgsheffi/QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8/Resolved_Ntuples_QCD_Pt_800to1000_v2/151122_005804/0000/"
    "/eos/uscms/store/user/dgsheffi/QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8/Resolved_Ntuples_QCD_Pt_1000to1400_v2/151122_005812/0000/"
    "/eos/uscms/store/user/dgsheffi/QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8/Resolved_Ntuples_QCD_Pt_1400to1800_v2/151122_005822/0000/"
    "/eos/uscms/store/user/dgsheffi/QCD_Pt_1800to2400_TuneCUETP8M1_13TeV_pythia8/Resolved_Ntuples_QCD_Pt_1800to2400_v2/151122_005829/0000/"
    "/eos/uscms/store/user/dgsheffi/QCD_Pt_2400to3200_TuneCUETP8M1_13TeV_pythia8/Resolved_Ntuples_QCD_Pt_2400to3200_v2/151122_005837/0000/"
    "/eos/uscms/store/user/dgsheffi/QCD_Pt_2400to3200_TuneCUETP8M1_13TeV_pythia8/Resolved_Ntuples_QCD_Pt_2400to3200_v2/151122_005837/0000/"
)

names=(
    #"Scouting_Ntuples_Data_v5"
    "Resolved_Ntuples_TTJets_v1"
    #"Resolved_Ntuples_QCD_Pt-120To170_v2"
    "Resolved_Ntuples_QCD_Pt-170To300_v2"
    "Resolved_Ntuples_QCD_Pt-300To470_v2"
    #"Resolved_Ntuples_QCD_Pt-470To600_v2"
    #"Resolved_Ntuples_QCD_Pt-600To800_v2"
    "Resolved_Ntuples_QCD_Pt-800To1000_v2"
    "Resolved_Ntuples_QCD_Pt-1000To1400_v2"
    "Resolved_Ntuples_QCD_Pt-1400To1800_v2"
    "Resolved_Ntuples_QCD_Pt-1800To2400_v2"
    "Resolved_Ntuples_QCD_Pt-2400To3200_v2"
    "Resolved_Ntuples_QCD_Pt-3200_v2"
)

script="transfer.sh"
echo "#!/bin/bash" > $script
echo "" >> $script

for ((i=0;i<${#datasets[@]};++i)); do
    echo ${names[i]}
    for file in $(ls -v --color=never ${datasets[i]}*.root); do
        echo "scp dgsheffi@cmslpc-sl6.fnal.gov:${file} ${names[i]}/" >> $script
    done
done
