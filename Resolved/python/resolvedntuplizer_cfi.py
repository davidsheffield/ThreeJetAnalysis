import FWCore.ParameterSet.Config as cms

resolvedntuplizer = cms.EDAnalyzer(
    'ResolvedNtuplizer',
    jet_pt           = cms.InputTag('jetsAK4:jetAK4Pt'),
    jet_eta          = cms.InputTag('jetsAK4:jetAK4Eta'),
    jet_phi          = cms.InputTag('jetsAK4:jetAK4Phi'),
    jet_E            = cms.InputTag('jetsAK4:jetAK4E'),
    jet_mass         = cms.InputTag('jetsAK4:jetAK4Mass'),
    jet_csv          = cms.InputTag('jetsAK4:jetAK4CSV'),
    vertex_z         = cms.InputTag('vertexInfo:z'),
    genpart_ID       = cms.InputTag('genPart:genPartID'),
    genpart_status   = cms.InputTag('genPart:genPartStatus'),
    genpart_momID    = cms.InputTag('genPart:genPartMom0ID'),
    genpart_pt       = cms.InputTag('genPart:genPartPt'),
    genpart_eta      = cms.InputTag('genPart:genPartEta'),
    genpart_phi      = cms.InputTag('genPart:genPartPhi'),
    genpart_E        = cms.InputTag('genPart:genPartE'),
    #rho              = cms.InputTag('hltScoutingPFPacker:rho'),
    cut_nJets_min    = cms.int32(6),
    cut_pt           = cms.double(20.0),
    cut_eta          = cms.double(3.0),
    is_signal        = cms.bool(False),
    output_file_name = cms.string('resolved_ntuple.root')
)
