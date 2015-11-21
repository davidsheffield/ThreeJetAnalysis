#!/usr/bin/env python

import subprocess
import os
import FWCore.ParameterSet.VarParsing as VarParsing

def getArguments():
    options = VarParsing.VarParsing('analysis')
    options.maxEvents = -1
    options.outputFile = "histograms.root"
    options.register('reportEvery',
                     1000000, # default value
                     VarParsing.VarParsing.multiplicity.singleton,
                     VarParsing.VarParsing.varType.int,
                     "Number of events to process before reporting progress.")
    options.register('cutNJetsMin',
                     6, # default value
                     VarParsing.VarParsing.multiplicity.singleton,
                     VarParsing.VarParsing.varType.int,
                     "Minimum number of jets.")
    options.register('cutNJetsMax',
                     -1, # default value
                     VarParsing.VarParsing.multiplicity.singleton,
                     VarParsing.VarParsing.varType.int,
                     "Maximum number of jets.")
    options.register('cutNPVMin',
                     0, # default value
                     VarParsing.VarParsing.multiplicity.singleton,
                     VarParsing.VarParsing.varType.int,
                     "Minimum number of primary vertices.")
    options.register('cutNPVMax',
                     -1, # default value
                     VarParsing.VarParsing.multiplicity.singleton,
                     VarParsing.VarParsing.varType.int,
                     "Maximum number of primary vertices.")
    options.register('Ht',
                     450.0, # default value
                     VarParsing.VarParsing.multiplicity.singleton,
                     VarParsing.VarParsing.varType.float,
                     "Minimum Ht.")
    options.register('Pt',
                     20.0, # default value
                     VarParsing.VarParsing.multiplicity.singleton,
                     VarParsing.VarParsing.varType.float,
                     "Minimum jet Pt.")
    options.register('eta',
                     3.0, # default value
                     VarParsing.VarParsing.multiplicity.singleton,
                     VarParsing.VarParsing.varType.float,
                     "Maximum |eta|.")
    options.register('do',
                     'data', # default value
                     VarParsing.VarParsing.multiplicity.singleton,
                     VarParsing.VarParsing.varType.string,
                     "What datasets to run over")
    options.register('luminosity',
                     1.317741, # default value
                     VarParsing.VarParsing.multiplicity.singleton,
                     VarParsing.VarParsing.varType.float,
                     "Integrated luminosity in /fb.")
    options.parseArguments()

    return options


def fillSamples():
    return {'data':
                [{'dataset': 'data',
                  'ntuples': '/cms/data26/sheffield/Scouting/ntuples/v4/scouting_ntuple_*.root',
                  'cross_section': 1.0,
                  'events': 1.0,
                  'isMC': 0}],
            'qcd':
                [{'dataset': 'QCD_Pt-120To170',
                  'ntuples': '/cms/data26/sheffield/ThreeJets/ntuples/Resolved_Ntuples_QCD_Pt-120To170_v1/resolved_QCD_Pt-120To170ntuple_*.root',
                  'cross_section': 471100.0,
                  'events': 3452896.0,
                  'isMC': 1},
                 {'dataset': 'QCD_Pt-170To300',
                  'ntuples': '/cms/data26/sheffield/ThreeJets/ntuples/Resolved_Ntuples_QCD_Pt-170To300_v1/resolved_ntuple_QCD_Pt-170To300_v1_*.root',
                  'cross_section': 117276.0,
                  'events': 3342746.09768638,
                  'isMC': 1},
                 {'dataset': 'QCD_Pt-300To470',
                  'ntuples': '/cms/data26/sheffield/ThreeJets/ntuples/Resolved_Ntuples_QCD_Pt-300To470_v1/resolved_ntuple_QCD_Pt-300To470_v1_*.root',
                  'cross_section': 7823.0,
                  'events': 2912596.59455587,
                  'isMC': 1},
                 {'dataset': 'QCD_Pt-470To600',
                  'ntuples': '/cms/data26/sheffield/ThreeJets/ntuples/Resolved_Ntuples_QCD_Pt-470To600_v1/resolved_ntuple_QCD_Pt-470To600_v1_*.root',
                  'cross_section': 648.2,
                  'events': 1933310.48727273,
                  'isMC': 1},
                 {'dataset': 'QCD_Pt-600To800',
                  'ntuples': '/cms/data26/sheffield/ThreeJets/ntuples/Resolved_Ntuples_QCD_Pt-600To800_v1/resolved_ntuple_QCD_Pt-600To800_v1_*.root',
                  'cross_section': 186.9,
                  'events': 1964128.0,
                  'isMC': 1},
                 {'dataset': 'QCD_Pt-800To1000',
                  'ntuples': '/cms/data26/sheffield/ThreeJets/ntuples/Resolved_Ntuples_QCD_Pt-800To1000_v1/resolved_ntuple_QCD_Pt-800To1000_v1_*.root',
                  'cross_section': 32.293,
                  'events': 1937216.0,
                  'isMC': 1},
                 {'dataset': 'QCD_Pt-1000To1400',
                  'ntuples': '/cms/data26/sheffield/ThreeJets/ntuples/Resolved_Ntuples_QCD_Pt-1000To1400_v1/resolved_ntuple_QCD_Pt-1000To1400_v1_*.root',
                  'cross_section': 9.4183,
                  'events': 1487136.0,
                  'isMC': 1}],
            'ttbar':
                [{'dataset': 'TTJets',
                  'ntuples': '',
                  'cross_section': 831.76,
                  'events': 40989797.3916084,
                  'isMC': 2}],
            'debug':
                [{'dataset': 'debug',
                  'ntuples': '/uscmst1b_scratch/lpc1/3DayLifetime/dgsheffi/test_ntuple_ttbar.root',
                  'cross_section': 1.0,
                  'events': 1.0,
                  'isMC': 2}]}


def main():
    cmssw_base = os.environ['CMSSW_BASE']
    architecture = os.environ['SCRAM_ARCH']
    executable = '{0}/bin/{1}/ScoutingHistogramsMaker'.format(cmssw_base,
                                                              architecture)

    options = getArguments()
    command = [executable, '', 'histograms.root', '0', '1.0',
               str(options.maxEvents), str(options.reportEvery),
               str(options.cutNJetsMin), str(options.cutNJetsMax),
               str(options.cutNPVMin), str(options.cutNPVMax), str(options.Ht),
               str(options.Pt), str(options.eta)]

    samples = fillSamples()

    for doing in options.do.split(','):
        for i in range(len(samples[doing])):
            print "Processing {0}".format(samples[doing][i]['dataset'])

            scale = 1.0
            if doing != "data":
                scale = (options.luminosity*1000.0) \
                    *samples[doing][i]['cross_section'] \
                    /samples[doing][i]['events']

            command[1] = samples[doing][i]['ntuples']
            command[2] = '{0}_{1}.root'.format(options.outputFile.split('.')[0],
                                               samples[doing][i]['dataset'])
            command[3] = str(samples[doing][i]['isMC'])
            command[4] = str(scale)

            subprocess.call(command)

    return

if __name__ == '__main__':
    main()
