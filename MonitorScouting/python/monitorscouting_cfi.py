import FWCore.ParameterSet.Config as cms

monitorscouting = cms.EDAnalyzer(
    'MonitorScouting',
    jet_collection = cms.InputTag('hltScoutingPFPacker')
)
