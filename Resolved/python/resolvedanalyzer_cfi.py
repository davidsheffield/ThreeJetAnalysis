import FWCore.ParameterSet.Config as cms

resolvedanalyzer = cms.EDAnalyzer('ResolvedAnalyzer',
        jetPt                   = cms.InputTag('jetsAK4:jetAK4Pt'),
        jetEta                  = cms.InputTag('jetsAK4:jetAK4Eta'),
        jetPhi                  = cms.InputTag('jetsAK4:jetAK4Phi'),
        jetE                    = cms.InputTag('jetsAK4:jetAK4E'),
        jetMass                 = cms.InputTag('jetsAK4:jetAK4Mass')
)
