import FWCore.ParameterSet.Config as cms

scoutingntuplizer = cms.EDAnalyzer(
    'ScoutingNtuplizer',
    jet_collection       = cms.InputTag('hltScoutingPFPacker'),
    candidate_collection = cms.InputTag('hltScoutingPFPacker'),
    vertex_collection    = cms.InputTag('hltScoutingPFPacker'),
    rho                  = cms.InputTag('hltScoutingPFPacker:rho'),
    output_file_name     = cms.string('scouting_ntuple.root')
)
