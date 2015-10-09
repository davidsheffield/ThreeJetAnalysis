import FWCore.ParameterSet.Config as cms

process = cms.Process('ScoutingAnalysis')

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet(input=cms.untracked.int32(-1))
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(100)

process.load('ThreeJetAnalysis.Scouting.scoutinganalyzer_cfi')

process.source = cms.Source("PoolSource", fileNames=cms.untracked.vstring())

process.p = cms.Path(process.scoutinganalyzer)
