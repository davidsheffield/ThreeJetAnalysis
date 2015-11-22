import FWCore.ParameterSet.Config as cms

theoryminituplizer = cms.EDAnalyzer(
    'TheoryMiniTuplizer',
    jet_collection      = cms.InputTag('hltScoutingPFPacker'),
    muon_collection     = cms.InputTag('hltScoutingMuonPacker'),
    electron_collection = cms.InputTag('hltScoutingEgammaPacker'),
    photon_collection   = cms.InputTag('hltScoutingEgammaPacker'),
    MET_pt              = cms.InputTag('hltScoutingPFPacker:pfMetPt'),
    MET_phi             = cms.InputTag('hltScoutingPFPacker:pfMetPhi'),
    output_file_name    = cms.string('theory_minituple.root')
)
