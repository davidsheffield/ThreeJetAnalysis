from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'RPV_GluinoGluinoToJets_M-1000_13TeV-madgraph_GENSIM_v2'
config.General.workArea = 'jobs'

config.JobType.pluginName = 'PrivateMC'
config.JobType.generator = 'lhe'
config.JobType.psetName = 'step1_GEN-SIM_cfg.py'

config.Data.primaryDataset = 'RPV_GluinoGluinoToJets_M-1000_13TeV-madgraph'
config.Data.splitting = 'EventBased'
config.Data.unitsPerJob = 100
NJOBS = 1000
config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
config.Data.publication = True
config.Data.publishDataName = 'RunIISummer15GS_GENSIM'
config.Data.ignoreLocality = True

config.Site.storageSite = 'T3_US_FNALLPC'
