# Auto generated configuration file
# using:
# Revision: 1.19
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v
# with command line options: step3 --conditions auto:phase1_2018_realistic -n 10 --era Run2_2018 --eventcontent RECOSIM,MINIAODSIM --runUnscheduled -s RAW2DIGI,L1Reco,RECO,RECOSIM,EI,PAT --datatier GEN-SIM-RECO,MINIAODSIM --geometry DB:Extended --filein file:step2.root --fileout file:step3.root --nThreads 4 --no_exec
import FWCore.ParameterSet.Config as cms

from Configuration.Eras.Era_Run2_2018_cff import Run2_2018

from FWCore.ParameterSet.VarParsing import VarParsing

obj = VarParsing ('analysis')
obj.register ('inputFile',
              'step2.root',
               VarParsing.multiplicity.singleton,
               VarParsing.varType.string,
               info="input file name")
obj.register ('newDyT',
               True,
               VarParsing.multiplicity.singleton,
               VarParsing.varType.bool,
               info="switch between the different version of DyT")
obj.register ('DyTthrValue',
               10,
               VarParsing.multiplicity.singleton,
               VarParsing.varType.int,
               info="DyT threshold values for old parameterization")
obj.register ('runAPEs',
               False,
               VarParsing.multiplicity.singleton,
               VarParsing.varType.bool,
               info="turn on APEs in DyT")
# get and parse the command line arguments
obj.parseArguments()

process = cms.Process('RECO',Run2_2018)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.RecoSim_cff')
process.load('CommonTools.ParticleFlow.EITopPAG_cff')
process.load('PhysicsTools.PatAlgos.slimming.metFilterPaths_cff')
process.load('Configuration.StandardSequences.PATMC_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10),
    output = cms.optional.untracked.allowed(cms.int32,cms.PSet)
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('file:{}'.format(obj.inputFile)),
    secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(
    FailPath = cms.untracked.vstring(),
    IgnoreCompletely = cms.untracked.vstring(),
    Rethrow = cms.untracked.vstring(),
    SkipEvent = cms.untracked.vstring(),
    allowUnscheduled = cms.obsolete.untracked.bool,
    canDeleteEarly = cms.untracked.vstring(),
    emptyRunLumiMode = cms.obsolete.untracked.string,
    eventSetup = cms.untracked.PSet(
        forceNumberOfConcurrentIOVs = cms.untracked.PSet(

        ),
        numberOfConcurrentIOVs = cms.untracked.uint32(1)
    ),
    fileMode = cms.untracked.string('FULLMERGE'),
    forceEventSetupCacheClearOnNewRun = cms.untracked.bool(False),
    makeTriggerResults = cms.obsolete.untracked.bool,
    numberOfConcurrentLuminosityBlocks = cms.untracked.uint32(1),
    numberOfConcurrentRuns = cms.untracked.uint32(1),
    numberOfStreams = cms.untracked.uint32(0),
    numberOfThreads = cms.untracked.uint32(1),
    printDependencies = cms.untracked.bool(False),
    sizeOfStackForThreadsInKB = cms.optional.untracked.uint32,
    throwIfIllegalParameter = cms.untracked.bool(True),
    wantSummary = cms.untracked.bool(False)
)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('step3 nevts:10'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.RECOSIMoutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM-RECO'),
        filterName = cms.untracked.string('')
    ),
    fileName = cms.untracked.string('step3.root'),
    outputCommands = process.RECOSIMEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

process.RECOSIMoutput_slim = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM-RECO'),
        filterName = cms.untracked.string('')
    ),
    fileName = cms.untracked.string('file:step3_slim.root'),
    outputCommands = cms.untracked.vstring('drop *_*_*_*',
                                           'keep *_offlinePrimaryVertices_*_*',
                                           'keep recoMuons_muons_*_*',
                                           'keep *_muons_muonShowerInformation_*',
                                           'keep recoTracks_globalMuons_*_*',
                                           'keep recoTracks_tevMuons_*_*',
                                           'keep *_particleFlow_muons_*',
                                           'keep *_tevMuons_dytInfo_*'),
    splitLevel = cms.untracked.int32(0)
)

process.MINIAODSIMoutput = cms.OutputModule("PoolOutputModule",
    compressionAlgorithm = cms.untracked.string('LZMA'),
    compressionLevel = cms.untracked.int32(4),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('MINIAODSIM'),
        filterName = cms.untracked.string('')
    ),
    dropMetaData = cms.untracked.string('ALL'),
    eventAutoFlushCompressedSize = cms.untracked.int32(-900),
    fastCloning = cms.untracked.bool(False),
    fileName = cms.untracked.string('file:step3_inMINIAODSIM.root'),
    outputCommands = process.MINIAODSIMEventContent.outputCommands,
    overrideBranchesSplitLevel = cms.untracked.VPSet(
        cms.untracked.PSet(
            branch = cms.untracked.string('patPackedCandidates_packedPFCandidates__*'),
            splitLevel = cms.untracked.int32(99)
        ),
        cms.untracked.PSet(
            branch = cms.untracked.string('recoGenParticles_prunedGenParticles__*'),
            splitLevel = cms.untracked.int32(99)
        ),
        cms.untracked.PSet(
            branch = cms.untracked.string('patTriggerObjectStandAlones_slimmedPatTrigger__*'),
            splitLevel = cms.untracked.int32(99)
        ),
        cms.untracked.PSet(
            branch = cms.untracked.string('patPackedGenParticles_packedGenParticles__*'),
            splitLevel = cms.untracked.int32(99)
        ),
        cms.untracked.PSet(
            branch = cms.untracked.string('patJets_slimmedJets__*'),
            splitLevel = cms.untracked.int32(99)
        ),
        cms.untracked.PSet(
            branch = cms.untracked.string('recoVertexs_offlineSlimmedPrimaryVertices__*'),
            splitLevel = cms.untracked.int32(99)
        ),
        cms.untracked.PSet(
            branch = cms.untracked.string('recoCaloClusters_reducedEgamma_reducedESClusters_*'),
            splitLevel = cms.untracked.int32(99)
        ),
        cms.untracked.PSet(
            branch = cms.untracked.string('EcalRecHitsSorted_reducedEgamma_reducedEBRecHits_*'),
            splitLevel = cms.untracked.int32(99)
        ),
        cms.untracked.PSet(
            branch = cms.untracked.string('EcalRecHitsSorted_reducedEgamma_reducedEERecHits_*'),
            splitLevel = cms.untracked.int32(99)
        ),
        cms.untracked.PSet(
            branch = cms.untracked.string('recoGenJets_slimmedGenJets__*'),
            splitLevel = cms.untracked.int32(99)
        ),
        cms.untracked.PSet(
            branch = cms.untracked.string('patJets_slimmedJetsPuppi__*'),
            splitLevel = cms.untracked.int32(99)
        ),
        cms.untracked.PSet(
            branch = cms.untracked.string('EcalRecHitsSorted_reducedEgamma_reducedESRecHits_*'),
            splitLevel = cms.untracked.int32(99)
        )
    ),
    overrideInputFileSplitLevels = cms.untracked.bool(True),
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase1_2018_realistic', '')

DYTthrsParameters_APE = cms.PSet( eta0p8 = cms.vdouble(1, -0.91038786, 0.98907528),
                                  eta1p2 = cms.vdouble(1, -0.89248105,  0.98684518),
                                  eta2p0 = cms.vdouble(4, -0.86643508,  0.98238113),
                                  eta2p2 = cms.vdouble(1, -0.90890539,  0.98838502),
                                  eta2p4 = cms.vdouble(1, -0.9201779,  0.98993168),
                                    )
runNewParameters = True

print 'Getting Refitter PSet'
print ' Default DYTuseThrsParametrization.value(): %s' % process.tevMuons.RefitterParameters.DYTuseThrsParametrization.value()
print ' Default DYTthrs.value(): %s' % process.tevMuons.RefitterParameters.DYTthrs.value()
# Loading Recontruction_cff adds all the processes to process.
if not obj.newDyT:
    newDYTthrs = cms.vint32( obj.DyTthrValue, obj.DyTthrValue )
    process.tevMuons.RefitterParameters.DYTuseThrsParametrization.setValue(obj.newDyT)
    process.tevMuons.RefitterParameters.DYTthrs.setValue(newDYTthrs)
    process.glbTrackQual.RefitterParameters.DYTuseThrsParametrization.setValue(obj.newDyT)
    process.glbTrackQual.RefitterParameters.DYTthrs.setValue(newDYTthrs)
if obj.runAPEs:
    process.tevMuons.RefitterParameters.DYTuseAPE.setValue(obj.runAPEs)
    process.glbTrackQual.RefitterParameters.DYTuseAPE.setValue(obj.runAPEs)
    print "  APEs turn on in DyT: %s" % process.tevMuons.RefitterParameters.DYTuseAPE.value()
    if runNewParameters:
        print process.glbTrackQual.RefitterParameters.DYTthrsParameters.value()
        process.tevMuons.RefitterParameters.DYTthrsParameters.eta0p8.setValue(DYTthrsParameters_APE.eta0p8)
        process.tevMuons.RefitterParameters.DYTthrsParameters.eta1p2.setValue(DYTthrsParameters_APE.eta1p2)
        process.tevMuons.RefitterParameters.DYTthrsParameters.eta2p0.setValue(DYTthrsParameters_APE.eta2p0)
        process.tevMuons.RefitterParameters.DYTthrsParameters.eta2p2.setValue(DYTthrsParameters_APE.eta2p2)
        process.tevMuons.RefitterParameters.DYTthrsParameters.eta2p4.setValue(DYTthrsParameters_APE.eta2p4)
        process.glbTrackQual.RefitterParameters.DYTthrsParameters.eta0p8.setValue(DYTthrsParameters_APE.eta0p8)
        process.glbTrackQual.RefitterParameters.DYTthrsParameters.eta1p2.setValue(DYTthrsParameters_APE.eta1p2)
        process.glbTrackQual.RefitterParameters.DYTthrsParameters.eta2p0.setValue(DYTthrsParameters_APE.eta2p0)
        process.glbTrackQual.RefitterParameters.DYTthrsParameters.eta2p2.setValue(DYTthrsParameters_APE.eta2p2)
        process.glbTrackQual.RefitterParameters.DYTthrsParameters.eta2p4.setValue(DYTthrsParameters_APE.eta2p4)
        print process.glbTrackQual.RefitterParameters.DYTthrsParameters.value()
print ' New DYTuseThrsParametrization.value(): %s' % process.tevMuons.RefitterParameters.DYTuseThrsParametrization.value()
print ' New DYTthrs.value(): %s' % process.tevMuons.RefitterParameters.DYTthrs.value()




# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.reconstruction_step = cms.Path(process.reconstruction)
process.recosim_step = cms.Path(process.recosim)
process.eventinterpretaion_step = cms.Path(process.EIsequence)
process.Flag_trackingFailureFilter = cms.Path(process.goodVertices+process.trackingFailureFilter)
process.Flag_goodVertices = cms.Path(process.primaryVertexFilter)
process.Flag_CSCTightHaloFilter = cms.Path(process.CSCTightHaloFilter)
process.Flag_trkPOGFilters = cms.Path(process.trkPOGFilters)
process.Flag_HcalStripHaloFilter = cms.Path(process.HcalStripHaloFilter)
process.Flag_trkPOG_logErrorTooManyClusters = cms.Path(~process.logErrorTooManyClusters)
process.Flag_EcalDeadCellTriggerPrimitiveFilter = cms.Path(process.EcalDeadCellTriggerPrimitiveFilter)
process.Flag_ecalLaserCorrFilter = cms.Path(process.ecalLaserCorrFilter)
process.Flag_globalSuperTightHalo2016Filter = cms.Path(process.globalSuperTightHalo2016Filter)
process.Flag_eeBadScFilter = cms.Path(process.eeBadScFilter)
process.Flag_METFilters = cms.Path(process.metFilters)
process.Flag_chargedHadronTrackResolutionFilter = cms.Path(process.chargedHadronTrackResolutionFilter)
process.Flag_globalTightHalo2016Filter = cms.Path(process.globalTightHalo2016Filter)
process.Flag_CSCTightHaloTrkMuUnvetoFilter = cms.Path(process.CSCTightHaloTrkMuUnvetoFilter)
process.Flag_HBHENoiseIsoFilter = cms.Path(process.HBHENoiseFilterResultProducer+process.HBHENoiseIsoFilter)
process.Flag_BadChargedCandidateSummer16Filter = cms.Path(process.BadChargedCandidateSummer16Filter)
process.Flag_hcalLaserEventFilter = cms.Path(process.hcalLaserEventFilter)
process.Flag_BadPFMuonFilter = cms.Path(process.BadPFMuonFilter)
process.Flag_ecalBadCalibFilter = cms.Path(process.ecalBadCalibFilter)
process.Flag_HBHENoiseFilter = cms.Path(process.HBHENoiseFilterResultProducer+process.HBHENoiseFilter)
process.Flag_trkPOG_toomanystripclus53X = cms.Path(~process.toomanystripclus53X)
process.Flag_EcalDeadCellBoundaryEnergyFilter = cms.Path(process.EcalDeadCellBoundaryEnergyFilter)
process.Flag_BadChargedCandidateFilter = cms.Path(process.BadChargedCandidateFilter)
process.Flag_trkPOG_manystripclus53X = cms.Path(~process.manystripclus53X)
process.Flag_BadPFMuonSummer16Filter = cms.Path(process.BadPFMuonSummer16Filter)
process.Flag_muonBadTrackFilter = cms.Path(process.muonBadTrackFilter)
process.Flag_CSCTightHalo2015Filter = cms.Path(process.CSCTightHalo2015Filter)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RECOSIMoutput_step = cms.EndPath(process.RECOSIMoutput)
process.RECOSIMoutputSlimmed_step = cms.EndPath(process.RECOSIMoutput_slim)
process.MINIAODSIMoutput_step = cms.EndPath(process.MINIAODSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.recosim_step,process.eventinterpretaion_step,process.Flag_HBHENoiseFilter,process.Flag_HBHENoiseIsoFilter,process.Flag_CSCTightHaloFilter,process.Flag_CSCTightHaloTrkMuUnvetoFilter,process.Flag_CSCTightHalo2015Filter,process.Flag_globalTightHalo2016Filter,process.Flag_globalSuperTightHalo2016Filter,process.Flag_HcalStripHaloFilter,process.Flag_hcalLaserEventFilter,process.Flag_EcalDeadCellTriggerPrimitiveFilter,process.Flag_EcalDeadCellBoundaryEnergyFilter,process.Flag_ecalBadCalibFilter,process.Flag_goodVertices,process.Flag_eeBadScFilter,process.Flag_ecalLaserCorrFilter,process.Flag_trkPOGFilters,process.Flag_chargedHadronTrackResolutionFilter,process.Flag_muonBadTrackFilter,process.Flag_BadChargedCandidateFilter,process.Flag_BadPFMuonFilter,process.Flag_BadChargedCandidateSummer16Filter,process.Flag_BadPFMuonSummer16Filter,process.Flag_trkPOG_manystripclus53X,process.Flag_trkPOG_toomanystripclus53X,process.Flag_trkPOG_logErrorTooManyClusters,process.Flag_METFilters,process.endjob_step,process.RECOSIMoutput_step) ##,process.RECOSIMoutputSlimmed_step,process.MINIAODSIMoutput_step
process.schedule.associate(process.patTask)
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

#Setup FWK for multithreaded
process.options.numberOfThreads=cms.untracked.uint32(1)
process.options.numberOfStreams=cms.untracked.uint32(0)
process.options.numberOfConcurrentLuminosityBlocks=cms.untracked.uint32(1)

#do not add changes to your config after this point (unless you know what you are doing)
from FWCore.ParameterSet.Utilities import convertToUnscheduled
process=convertToUnscheduled(process)

# customisation of the process.

# Automatic addition of the customisation function from PhysicsTools.PatAlgos.slimming.miniAOD_tools
from PhysicsTools.PatAlgos.slimming.miniAOD_tools import miniAOD_customizeAllMC

#call to customisation function miniAOD_customizeAllMC imported from PhysicsTools.PatAlgos.slimming.miniAOD_tools
process = miniAOD_customizeAllMC(process)

# End of customisation functions

# Customisation from command line

#Have logErrorHarvester wait for the same EDProducers to finish as those providing data for the OutputModule
from FWCore.Modules.logErrorHarvester_cff import customiseLogErrorHarvesterUsingOutputCommands
process = customiseLogErrorHarvesterUsingOutputCommands(process)

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion
