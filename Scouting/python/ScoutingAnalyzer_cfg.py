import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing

process = cms.Process('ScoutingAnalysis')

process.load("FWCore.MessageService.MessageLogger_cfi")

options = VarParsing.VarParsing('analysis')
options.outputFile = 'scouting_histograms.root'
options.inputFiles = 'file:/uscmst1b_scratch/lpc1/3DayLifetime/dgsheffi/ScoutingPFHT.root'
options.maxEvents = -1
options.register('reportEvery',
                 10000, # default value
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.int,
                 "Number of events to process before reporting progress.")
options.parseArguments()

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.maxEvents)
)
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(
    options.reportEvery)

process.load('ThreeJetAnalysis.Scouting.scoutinganalyzer_cfi')

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(options.inputFiles)
)

process.TFileService = cms.Service(
    "TFileService",
    fileName = cms.string(options.outputFile)
)

process.p = cms.Path(process.scoutinganalyzer)
