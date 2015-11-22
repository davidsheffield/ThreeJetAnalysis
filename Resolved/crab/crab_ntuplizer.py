from CRABClient.UserUtilities import config
config = config()

dataset = 'TTJets' #'QCD_Pt-1000To1400'
version = 'v1'

config.General.requestName = 'Resolved_Ntuples_{0}_{1}'.format(dataset, version)
config.General.workArea = 'jobs'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../python/ResolvedNtuplizer_cfg.py'
output_name = 'resolved_ntuple_{0}_{1}.root'.format(dataset, version)
config.JobType.pyCfgParams = ['outputFile={0}'.format(output_name)]
config.JobType.outputFiles = [output_name]

#config.Data.inputDataset = '/QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8/algomez-RunIISpring15MiniAODv2-74X_RUNA_Asympt25ns_v08-4a60e85fe45fa92e3d679925522bbd7b/USER'
#config.Data.inputDataset = '/QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8/algomez-RunIISpring15MiniAODv2-74X_RUNA_Asympt25ns_v08-4a60e85fe45fa92e3d679925522bbd7b/USER'
#config.Data.inputDataset = '/QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8/algomez-RunIISpring15MiniAODv2-74X_RUNA_Asympt25ns_v08-4a60e85fe45fa92e3d679925522bbd7b/USER'
#config.Data.inputDataset = '/QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8/algomez-RunIISpring15MiniAODv2-74X_RUNA_Asympt25ns_v08-4a60e85fe45fa92e3d679925522bbd7b/USER'
#config.Data.inputDataset = '/QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8/algomez-RunIISpring15MiniAODv2-74X_RUNA_Asympt25ns_v08-4a60e85fe45fa92e3d679925522bbd7b/USER'
#config.Data.inputDataset = '/QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8/algomez-RunIISpring15MiniAODv2-74X_RUNA_Asympt25ns_v08-4a60e85fe45fa92e3d679925522bbd7b/USER'
#config.Data.inputDataset = '/QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8/algomez-RunIISpring15MiniAODv2-74X_RUNA_Asympt25ns_v08-4a60e85fe45fa92e3d679925522bbd7b/USER'
#config.Data.inputDataset = '/QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8/algomez-RunIISpring15MiniAODv2-74X_RUNA_Asympt25ns_v08-4a60e85fe45fa92e3d679925522bbd7b/USER'
#config.Data.inputDataset = '/QCD_Pt_1800to2400_TuneCUETP8M1_13TeV_pythia8/algomez-RunIISpring15MiniAODv2-74X_RUNA_Asympt25ns_v08-4a60e85fe45fa92e3d679925522bbd7b/USER'
#config.Data.inputDataset = '/QCD_Pt_2400to3200_TuneCUETP8M1_13TeV_pythia8/algomez-RunIISpring15MiniAODv2-74X_RUNA_Asympt25ns_v08-4a60e85fe45fa92e3d679925522bbd7b/USER'
#config.Data.inputDataset = '/QCD_Pt_3200toInf_TuneCUETP8M1_13TeV_pythia8/algomez-RunIISpring15MiniAODv2-74X_RUNA_Asympt25ns_v08-4a60e85fe45fa92e3d679925522bbd7b/USER'
config.Data.inputDataset = '/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/dsheffie-RunIISpring15MiniAODv2-74X_RUNA_Asympt25ns_v09-6cd9a37acb7fba8686d9247b86713620/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 35
#NJOBS = 264
#config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
#config.Data.totalUnits = 3890
#config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions15/13TeV/Cert_246908-260426_13TeV_PromptReco_Collisions15_25ns_JSON_Silver.txt'
config.Data.publication = False
config.Data.ignoreLocality = True

config.Site.storageSite = 'T3_US_FNALLPC'
