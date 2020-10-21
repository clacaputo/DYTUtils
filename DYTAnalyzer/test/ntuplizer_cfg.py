import FWCore.ParameterSet.Config as cms
import os

from FWCore.ParameterSet.VarParsing import VarParsing

obj = VarParsing ('analysis')
obj.register ('inputFileList',
              os.environ.get('CMSSW_BASE')+'/src/Analysis/DYTAnalyzer/test_list.txt',
               VarParsing.multiplicity.singleton,
               VarParsing.varType.string,
               info="input files list")
obj.register ('psim',
               1000,
               VarParsing.multiplicity.singleton,
               VarParsing.varType.float,
               info="momentum simulated. Used for the definition of some plots range and binning")
obj.register ('useSelections',
               False,
               VarParsing.multiplicity.singleton,
               VarParsing.varType.bool,
               info="use events selections cuts")
# get and parse the command line arguments
obj.parseArguments()

if obj.useSelections:
    obj.tag = obj.tag+'_SelectionsUsed'

process = cms.Process("Demo")
def readFileList(fileList, inputFileName, fileNamePrefix):
    inputFile = open(inputFileName, 'r')
    for name in inputFile:
        fileList.extend([ fileNamePrefix + name ])
        print 'Added: %s + %s' %(fileNamePrefix, name)
    inputFile.close()



process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )


process.source = cms.Source('PoolSource', fileNames = cms.untracked.vstring())

readFileList(process.source.fileNames, obj.inputFileList,'file:')

# process.source = cms.Source("PoolSource",
#			    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
#                            fileNames = cms.untracked.vstring(
#)
#			)

process.demo = cms.EDAnalyzer('DYTNtuplizer',
                              psim = cms.double(obj.psim),
                              useSelections = cms.bool(obj.useSelections)
                              )
process.TFileService = cms.Service("TFileService", fileName = cms.string('output'+('_'+obj.tag if len(obj.tag)!=0 else '')+'.root'))

process.p = cms.Path(process.demo)
