import FWCore.ParameterSet.Config as cms

scoutinganalyzer = cms.EDAnalyzer(
    'ScoutingAnalyzer',
    scale          = cms.double(1.0),
# Cuts
    cutHt          = cms.double(0.0),
    cutJetMaxEta   = cms.double(2.5),
    cutJetMinPt    = cms.double(30.0),
    cutJetMinN     = cms.int32(6),
    cutJetMaxN     = cms.int32(-1),
# Jet collection
    jet_collection = cms.InputTag('hltScoutingPFPacker')
)
