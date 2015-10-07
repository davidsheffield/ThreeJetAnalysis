import FWCore.ParameterSet.Config as cms

process = cms.Process("ScoutingMonitor")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(10000)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'file:/uscmst1b_scratch/lpc1/3DayLifetime/dgsheffi/ScoutingPFHT.root '
    )
)

process.load('ThreeJetAnalysis.MonitorScouting.monitorscouting_cfi')

process.TFileService = cms.Service(
    "TFileService",
    fileName = cms.string("monitoring_histograms.root")
)

process.p = cms.Path(process.monitorscouting)
