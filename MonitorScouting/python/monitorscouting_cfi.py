import FWCore.ParameterSet.Config as cms

monitorscouting = cms.EDAnalyzer(
    'MonitorScouting',
    jet_collection       = cms.InputTag('hltScoutingPFPacker'),
    candidate_collection = cms.InputTag('hltScoutingPFPacker'),
    vertex_collection    = cms.InputTag('hltScoutingPFPacker'),
    MetPt                = cms.InputTag('hltScoutingPFPacker:pfMetPt'),
    MetPhi               = cms.InputTag('hltScoutingPFPacker:pfMetPhi'),
    rho                  = cms.InputTag('hltScoutingPFPacker:rho')
)
