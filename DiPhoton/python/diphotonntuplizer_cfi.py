import FWCore.ParameterSet.Config as cms

diphotonntuplizer = cms.EDAnalyzer(
    'DiPhotonNtuplizer',
    jet_collection       = cms.InputTag('hltScoutingPFPacker'),
    candidate_collection = cms.InputTag('hltScoutingPFPacker'),
    vertex_collection    = cms.InputTag('hltScoutingPFPacker'),
    MetPt                = cms.InputTag('hltScoutingPFPacker:pfMetPt'),
    MetPhi               = cms.InputTag('hltScoutingPFPacker:pfMetPhi'),
    rho                  = cms.InputTag('hltScoutingPFPacker:rho'),
    muon_collection      = cms.InputTag('hltScoutingMuonPacker'),
    electron_collection  = cms.InputTag('hltScoutingEgammaPacker'),
    photon_collection    = cms.InputTag('hltScoutingEgammaPacker'),
    output_file_name     = cms.string('scouting_diphoton_ntuple.root')
)
