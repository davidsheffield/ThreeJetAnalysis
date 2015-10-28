from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'Scouting_DiPhoton_Ntuplizer_v1'
config.General.workArea = 'jobs'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../python/DiPhotonNtuplizer_cfg.py'
config.JobType.outputFiles = ['scouting_diphoton_ntuple.root']

config.Data.inputDataset = '/ScoutingPFHT/Run2015D-v1/RAW'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
NJOBS = 188
config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
config.Data.publication = False
config.Data.ignoreLocality = True

config.Site.storageSite = 'T3_US_FNALLPC'
