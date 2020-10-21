import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

obj = VarParsing ('analysis')
obj.register ('newDyT',
               True,
               VarParsing.multiplicity.singleton,
               VarParsing.varType.bool,
               info="switch between the different version of DyT")
# get and parse the command line arguments
obj.parseArguments()


## List of samples w/ and w/o new DyT
newDyTfiles =  cms.untracked.vstring(   "file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_10_newDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_11_newDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_12_newDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_13_newDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_14_newDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_15_newDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_16_newDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_17_newDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_18_newDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_19_newDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_0_newDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_1_newDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_2_newDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_3_newDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_4_newDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_5_newDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_6_newDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_7_newDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_8_newDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_9_newDyT.root"
				   )

oldDyTfiles =  cms.untracked.vstring(   "file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_10_oldDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_11_oldDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_12_oldDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_13_oldDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_14_oldDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_15_oldDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_16_oldDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_17_oldDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_18_oldDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_19_oldDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_0_oldDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_1_oldDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_2_oldDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_3_oldDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_4_oldDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_5_oldDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_6_oldDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_7_oldDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_8_oldDyT.root",
					"file:/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-03-29-2300/src/testing_scripts/Results_1TeV/step3_9_oldDyT.root"
				   )

## Files dictionary

filesdict = {'oldDyT' : oldDyTfiles,
	     'newDyT' : newDyTfiles}
dytfiles = cms.untracked.vstring()

if obj.newDyT:
	dytfiles = filesdict['newDyT']
else:
	dytfiles = filesdict['oldDyT']	




process = cms.Process("Demo")

process.load('FWCore.MessageLogger.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 500

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
			    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
                            fileNames = dytfiles
			   )

process.demo = cms.EDAnalyzer('DYTAnalyzer',
                              psim = cms.double(1000))

filename = cms.string("output.root")
if obj.newDyT:
	filename = cms.string("output_newDyT.root")
else:
	filename = cms.string("output_oldDyT.root")

process.TFileService = cms.Service("TFileService", fileName = filename)

process.p = cms.Path(process.demo)
