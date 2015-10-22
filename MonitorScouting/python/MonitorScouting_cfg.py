import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing

process = cms.Process("ScoutingMonitor")

process.load("FWCore.MessageService.MessageLogger_cfi")

options = VarParsing.VarParsing('analysis')
options.outputFile = 'monitoring_histograms.root'
options.inputFiles = 'file:/uscmst1b_scratch/lpc1/3DayLifetime/dgsheffi/ScoutingPFHT.root'
options.maxEvents = -1
options.register('reportEvery',
                 10000, # default value
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.int,
                 "Number of events to process before reporting progress.")
options.register('muon',
                 False, # default value
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.bool,
                 "Is a scouting muon dataset.")
options.parseArguments()

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.maxEvents)
)
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(
    options.reportEvery)

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(options.inputFiles)
)

process.load('ThreeJetAnalysis.MonitorScouting.monitorscouting_cfi')

process.TFileService = cms.Service(
    "TFileService",
    fileName = cms.string(options.outputFile)
)

process.monitorscouting.dimuon = cms.bool(options.muon)

process.p = cms.Path(process.monitorscouting)
