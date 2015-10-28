import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing

process = cms.Process("ScoutingNtuplizer")

process.load("FWCore.MessageService.MessageLogger_cfi")

options = VarParsing.VarParsing('analysis')
options.outputFile = 'scouting_ntuple.root'
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

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(options.inputFiles)
)

process.load('ThreeJetAnalysis.Scouting.scoutingntuplizer_cfi')

process.scoutingntuplizer.output_file_name = cms.string(options.outputFile)

process.p = cms.Path(process.scoutingntuplizer)
