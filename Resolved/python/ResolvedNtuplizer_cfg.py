import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing

process = cms.Process("ResolvedNtuplizer")

process.load("FWCore.MessageService.MessageLogger_cfi")

options = VarParsing.VarParsing('analysis')
options.outputFile = 'resolved_ntuple.root'
options.inputFiles = 'file:/eos/uscms/store/user/algomez/QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8/RunIISpring15MiniAODv2-74X_RUNA_Asympt25ns_v08/151109_223653/0000/RUNtuple_1.root'
options.maxEvents = -1
options.register('reportEvery',
                 1000, # default value
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.int,
                 "Number of events to process before reporting progress.")
options.register('isSignal',
                 False, # default value
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.bool,
                 "If signal, get correct triplets.")
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

process.load('ThreeJetAnalysis.Resolved.resolvedntuplizer_cfi')

process.resolvedntuplizer.output_file_name = cms.string(options.outputFile)
process.resolvedntuplizer.is_signal = cms.bool(options.isSignal)

process.p = cms.Path(process.resolvedntuplizer)
