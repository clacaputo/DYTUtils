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

if obj.inputFileList.find('txt') > -1 :
    readFileList(process.source.fileNames, obj.inputFileList,'file:')
else:
    process.source.fileNames.extend([ 'file:' + obj.inputFileList ])
# process.source = cms.Source("PoolSource",
#			    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
#                            fileNames = cms.untracked.vstring(
#)
#			)

process.demo = cms.EDAnalyzer('DYTNtuplizer',
                              psim = cms.double(obj.psim),
                              useSelections = cms.bool(obj.useSelections)
                              )

#if len(obj.outputFile) == 0:
#    output_file_name = 'output'+('_'+obj.tag if len(obj.tag)!=0 else '')+'.root'
#else:
output_file_name = obj.outputFile
print("Output file in python: {}".format(output_file_name))

process.TFileService = cms.Service("TFileService", fileName = cms.string(output_file_name))

process.p = cms.Path(process.demo)
