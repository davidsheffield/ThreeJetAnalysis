import FWCore.ParameterSet.Config as cms

jetsntuplizer = cms.EDAnalyzer(
    'JetsNtuplizer',
    jet_collection       = cms.InputTag('hltScoutingPFPacker'),
    candidate_collection = cms.InputTag('hltScoutingPFPacker'),
    vertex_collection    = cms.InputTag('hltScoutingPFPacker'),
    rho                  = cms.InputTag('hltScoutingPFPacker:rho'),
    output_file_name     = cms.string('scouting_jets_ntuple.root')
)
