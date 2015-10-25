from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'Analysis_v1'
config.General.workArea = 'jobs'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../python/ScoutingAnalyzer_cfg.py'
config.JobType.pyCfgParams = ['monitor=True']

config.Data.inputDataset = '/ScoutingPFHT/Run2015D-v1/RAW'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
NJOBS = 180
config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
config.Data.publication = False
config.Data.ignoreLocality = True

config.Site.storageSite = 'T3_US_FNALLPC'
