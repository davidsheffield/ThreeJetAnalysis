import FWCore.ParameterSet.Config as cms

process = cms.Process('ResolvedAnalysis')

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet(input=cms.untracked.int32(-1))
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(100)
process.options = cms.untracked.PSet(wantSummary=cms.untracked.bool(True))

process.load('ThreeJetAnalysis.Resolved.resolvedanalyzer_cfi')

import FWCore.Utilities.FileUtils as FileUtils
readFiles = cms.untracked.vstring(FileUtils.loadListFromFile('files.list'))
process.source = cms.Source("PoolSource", fileNames=readFiles)
print readFiles

process.p = cms.Path(process.resolvedanalyzer)
