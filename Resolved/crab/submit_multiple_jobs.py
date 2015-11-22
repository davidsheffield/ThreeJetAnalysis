##################################################################
########   TO RUN THIS: python submit_multiple_jobs.py
########   DO NOT DO: crab submit submit_multiple_jobs.py
########
########   From https://github.com/alefisico/RUNA
##################################################################

from CRABClient.UserUtilities import config
from httplib import HTTPException
from multiprocessing import Process
from CRABAPI.RawCommand import crabCommand

def submit(config):
    try:
        crabCommand('submit', config = config)
    except HTTPException, hte:
        print 'Cannot execute command'
        print hte.headers

if __name__ == '__main__':
    Samples = [
        '/QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8/jsomalwa-RunIISpring15MiniAODv2-74X_RUNA_Asympt25ns_v12-6cd9a37acb7fba8686d9247b86713620/USER',
        '/QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8/jsomalwa-RunIISpring15MiniAODv2-74X_RUNA_Asympt25ns_v12-6cd9a37acb7fba8686d9247b86713620/USER',
        '/QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8/jsomalwa-RunIISpring15MiniAODv2-74X_RUNA_Asympt25ns_v12-6cd9a37acb7fba8686d9247b86713620/USER',
        '/QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8/algomez-RunIISpring15MiniAODv2-74X_RUNA_Asympt25ns_v09-6cd9a37acb7fba8686d9247b86713620/USER',
        '/QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8/algomez-RunIISpring15MiniAODv2-74X_RUNA_Asympt25ns_v09-6cd9a37acb7fba8686d9247b86713620/USER',
        '/QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8/algomez-RunIISpring15MiniAODv2-74X_RUNA_Asympt25ns_v09-6cd9a37acb7fba8686d9247b86713620/USER',
        '/QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8/algomez-RunIISpring15MiniAODv2-74X_RUNA_Asympt25ns_v09-6cd9a37acb7fba8686d9247b86713620/USER',
        '/QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8/mmorris-RunIISpring15MiniAODv2-74X_RUNA_Asympt25ns_v09-7bcba442d2602d92a19f8ca61d13bc6c/USER',
        '/QCD_Pt_1800to2400_TuneCUETP8M1_13TeV_pythia8/mmorris-RunIISpring15MiniAODv2-74X_RUNA_Asympt25ns_v09-7bcba442d2602d92a19f8ca61d13bc6c/USER',
        '/QCD_Pt_2400to3200_TuneCUETP8M1_13TeV_pythia8/mmorris-RunIISpring15MiniAODv2-74X_RUNA_Asympt25ns_v09-7bcba442d2602d92a19f8ca61d13bc6c/USER',
        '/QCD_Pt_3200toInf_TuneCUETP8M1_13TeV_pythia8/mmorris-RunIISpring15MiniAODv2-74X_RUNA_Asympt25ns_v09-7bcba442d2602d92a19f8ca61d13bc6c/USER',
        # '/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/dsheffie-RunIISpring15MiniAODv2-74X_RUNA_Asympt25ns_v09-6cd9a37acb7fba8686d9247b86713620/USER'
        ]

    config = config()

    version = 'v2'

    config.General.requestName = ''
    config.General.workArea = 'jobs'

    config.JobType.pluginName = 'Analysis'
    config.JobType.psetName = '../python/ResolvedNtuplizer_cfg.py'
    config.JobType.allowUndistributedCMSSW = True

    config.Data.inputDataset = ''
    config.Data.splitting = 'LumiBased'
    config.Data.unitsPerJob = 500
    config.Data.publication = False
    config.Data.ignoreLocality = True

    config.Site.storageSite = 'T3_US_FNALLPC'


    for dataset in Samples:
        dataset_name = dataset.split('/')[1].split('_TuneCUETP8M1')[0]
        name = 'Resolved_Ntuples_{0}_{1}'.format(dataset_name, version)
        config.General.requestName = name
        config.Data.outputDatasetTag = name
        output_name = 'resolved_ntuple_{0}_{1}.root'.format(dataset_name,
                                                            version)
        config.JobType.pyCfgParams = ['outputFile={0}'.format(output_name)]
        config.JobType.outputFiles = [output_name]
        config.Data.inputDataset = dataset
        config.Data.inputDBS = 'phys03'
        p = Process(target=submit, args=(config,))
        p.start()
        p.join()
