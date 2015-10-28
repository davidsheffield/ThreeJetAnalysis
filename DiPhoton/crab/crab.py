from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'Scouting_DiPhoton_Ntuplizer_v1'
config.General.workArea = 'jobs'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '../python/DiPhotonNtuplizer_cfg.py'
config.JobType.outputFiles = ['scouting_diphoton_ntuple.root']

config.Data.primaryDataset = 'ScoutingPFHT'
config.Data.userInputFiles = ['/store/data/Run2015D/ScoutingPFHT/RAW/v1/000/259/636/00000/E037F887-2678-E511-8C8F-02163E0136BE.root',
       '/store/data/Run2015D/ScoutingPFHT/RAW/v1/000/259/637/00000/4C8EBDCE-5877-E511-957C-02163E014600.root',
       '/store/data/Run2015D/ScoutingPFHT/RAW/v1/000/259/681/00000/4A355DA1-C377-E511-9668-02163E011F9C.root',
       '/store/data/Run2015D/ScoutingPFHT/RAW/v1/000/259/682/00000/0EF1146B-D677-E511-8B72-02163E011F9F.root',
       '/store/data/Run2015D/ScoutingPFHT/RAW/v1/000/259/683/00000/96E801B9-2078-E511-9650-02163E01362C.root',
       '/store/data/Run2015D/ScoutingPFHT/RAW/v1/000/259/685/00000/060E8D9F-8278-E511-91B3-02163E01350C.root',
       '/store/data/Run2015D/ScoutingPFHT/RAW/v1/000/259/685/00000/063FAF5F-E377-E511-8AE5-02163E01396C.root',
       '/store/data/Run2015D/ScoutingPFHT/RAW/v1/000/259/685/00000/282FADA0-8278-E511-8F83-02163E013493.root',
       '/store/data/Run2015D/ScoutingPFHT/RAW/v1/000/259/685/00000/D890C7A1-8278-E511-B12B-02163E0138B9.root',
       '/store/data/Run2015D/ScoutingPFHT/RAW/v1/000/259/686/00000/04CC2D7F-AE79-E511-B54D-02163E014735.root',
       '/store/data/Run2015D/ScoutingPFHT/RAW/v1/000/259/686/00000/E636EAB7-AD79-E511-8CB6-02163E01358B.root',
       '/store/data/Run2015D/ScoutingPFHT/RAW/v1/000/259/714/00000/5EA40DAA-2778-E511-985B-02163E011EB2.root',
       '/store/data/Run2015D/ScoutingPFHT/RAW/v1/000/259/721/00000/B654221B-6C78-E511-9873-02163E013493.root',
       '/store/data/Run2015D/ScoutingPFHT/RAW/v1/000/259/809/00000/9AAC52C6-3579-E511-921E-02163E013571.root',
       '/store/data/Run2015D/ScoutingPFHT/RAW/v1/000/259/810/00000/106DFA3F-4C79-E511-8BDE-02163E0141B0.root',
       '/store/data/Run2015D/ScoutingPFHT/RAW/v1/000/259/811/00000/0E854A20-4779-E511-AB0E-02163E013533.root',
       '/store/data/Run2015D/ScoutingPFHT/RAW/v1/000/259/812/00000/0EDD241B-4279-E511-AFC0-02163E01199A.root',
       '/store/data/Run2015D/ScoutingPFHT/RAW/v1/000/259/813/00000/CA9391E7-4579-E511-8C8C-02163E01374E.root',
       '/store/data/Run2015D/ScoutingPFHT/RAW/v1/000/259/817/00000/9875BC27-4479-E511-BD0F-02163E01190D.root',
       '/store/data/Run2015D/ScoutingPFHT/RAW/v1/000/259/818/00000/A80BAF98-5379-E511-8624-02163E0133EC.root',
       '/store/data/Run2015D/ScoutingPFHT/RAW/v1/000/259/820/00000/AC3FDAA3-5D79-E511-93AC-02163E012A2E.root',
       '/store/data/Run2015D/ScoutingPFHT/RAW/v1/000/259/821/00000/6E1D9420-6979-E511-8E88-02163E0134AE.root',
       '/store/data/Run2015D/ScoutingPFHT/RAW/v1/000/259/822/00000/6CAB2312-9879-E511-AFD0-02163E011D5A.root',
       '/store/data/Run2015D/ScoutingPFHT/RAW/v1/000/259/822/00000/A41FBB2F-7879-E511-B999-02163E011E54.root',
       '/store/data/Run2015D/ScoutingPFHT/RAW/v1/000/259/857/00000/24CC5F10-DA79-E511-9EAF-02163E01362C.root',
       '/store/data/Run2015D/ScoutingPFHT/RAW/v1/000/259/862/00000/00653D54-2A7A-E511-BD97-02163E01372F.root',
       '/store/data/Run2015D/ScoutingPFHT/RAW/v1/000/259/862/00000/2AEC5D4E-0E7A-E511-BB36-02163E014693.root',
       '/store/data/Run2015D/ScoutingPFHT/RAW/v1/000/259/862/00000/669F4A73-2B7A-E511-8C5D-02163E011B63.root',
       '/store/data/Run2015D/ScoutingPFHT/RAW/v1/000/259/890/00000/E42079EF-C67A-E511-9805-02163E01432E.root',
       '/store/data/Run2015D/ScoutingPFHT/RAW/v1/000/259/891/00000/7260A808-1A7B-E511-95D3-02163E0125E7.root' ]
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
NJOBS = 30
config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
config.Data.publication = False
config.Data.ignoreLocality = True

config.Site.storageSite = 'T3_US_FNALLPC'
