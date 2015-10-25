from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'ScoutingPFMuons_Run2015D_v1_Monitor'
config.General.workArea = 'jobs'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../python/MonitorScouting_cfg.py'

config.Data.inputDataset = '/ScoutingPFMuons/Run2015D-v1/RAW'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
NJOBS = 13
config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
config.Data.publication = False
config.Data.ignoreLocality = True

config.Site.storageSite = 'T3_US_FNALLPC'
