import FWCore.ParameterSet.Config as cms

process = cms.Process('ScoutingAnalysis')

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet(input=cms.untracked.int32(-1))
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(10000)
process.options = cms.untracked.PSet(wantSummary=cms.untracked.bool(True))

process.load('ThreeJetAnalysis.Scouting.scoutinganalyzer_cfi')

import FWCore.Utilities.FileUtils as FileUtils
readFiles = cms.untracked.vstring(FileUtils.loadListFromFile('files.list'))
process.source = cms.Source("PoolSource", fileNames=readFiles)
print readFiles

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('test.root')
                                   )

process.p = cms.Path(process.scoutinganalyzer)
