import FWCore.ParameterSet.Config as cms

resolvedanalyzer = cms.EDAnalyzer('ResolvedAnalyzer',
        scale        = cms.double(1.0),
# Cuts
        cutHt        = cms.double(0.0),
        cutJetMaxEta = cms.double(2.5),
        cutJetMinPt  = cms.double(20.0),
        cutJetMinN   = cms.int32(6),
        cutJetMaxN   = cms.int32(-1),
# Jet collection
        jetPt        = cms.InputTag('jetsAK4:jetAK4Pt'),
        jetEta       = cms.InputTag('jetsAK4:jetAK4Eta'),
        jetPhi       = cms.InputTag('jetsAK4:jetAK4Phi'),
        jetE         = cms.InputTag('jetsAK4:jetAK4E'),
        jetMass      = cms.InputTag('jetsAK4:jetAK4Mass')
)
