from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'Scouting_Ntuples_v5'
config.General.workArea = 'jobs'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../python/ScoutingNtuplizer_cfg.py'
config.JobType.outputFiles = ['scouting_ntuple.root']

config.Data.inputDataset = '/ScoutingPFHT/Run2015D-v1/RAW'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 150
#NJOBS = 190
#config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
config.Data.totalUnits = 29997
config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions15/13TeV/Cert_246908-260627_13TeV_PromptReco_Collisions15_25ns_JSON_Silver.txt'
config.Data.publication = False
config.Data.ignoreLocality = True

config.Site.storageSite = 'T3_US_FNALLPC'
