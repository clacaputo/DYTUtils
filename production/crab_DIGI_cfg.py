from CRABClient.UserUtilities import config, getUsernameFromCRIC
from multiprocessing import Process

config = config()

config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'step2_DIGI_L1_DIGI2RAW_HLT.py'
config.JobType.allowUndistributedCMSSW = True
config.JobType.numCores = 1

config.Data.splitting = "FileBased"
config.Data.unitsPerJob = 1

config.Data.outLFNDirBase = '/store/user/%s/DyT_ThresholdStudies' % (getUsernameFromCRIC())
config.Data.publication = True

config.Site.storageSite = 'T2_BE_UCL'

if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from CRABClient.ClientExceptions import ClientException
    from httplib import HTTPException

    samples = {'SingleMuonP500_DIGI': '/SingleMuonP500_pythia8/ccaputo-GEN-SIM_CMSSW_11_1_3_phase1_2018_realistic_Sep2020-5039397c640947c030917240fa439a0f/USER',
               'SingleMuonP1000_RECO': '/SingleMuonP1000_pythia8/ccaputo-GEN-SIM_CMSSW_11_1_3_phase1_2018_realistic_Sep2020-05177126e7cf8289284d2240120f911c/USER',
	           'SingleMuonP2000_RECO': '/SingleMuonP2000_pythia8/ccaputo-GEN-SIM_CMSSW_11_1_3_phase1_2018_realistic_Sep2020-2c47df87831f2829e08782073e820c42/USER',
               'SingleMuonP3000_RECO': '/SingleMuonP3000_pythia8/ccaputo-GEN-SIM_CMSSW_11_1_3_phase1_2018_realistic_Sep2020-a78212fc9ea17f88ba9aff1047353552/USER'
               }
    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    config.General.workArea = 'crab_projects_DyT_DIGI'

    def submit(config):
        try:
            crabCommand('submit', config = config, dryrun=False)
        except HTTPException as hte:
            print "Failed submitting task: %s" % (hte.headers)
        except ClientException as cle:
            print "Failed submitting task: %s" % (cle)

    #############################################################################################
    ## From now on that's what users should modify: this is the a-la-CRAB2 configuration part. ##
    #############################################################################################
    for sample, gen_dataset in samples.items():
         config.General.requestName = sample
         config.Data.inputDataset = gen_dataset
         config.Data.inputDBS = 'phys03'
         #config.Data.outputPrimaryDataset = sample
         config.Data.outputDatasetTag = 'DIGI_CMSSW_11_1_3_phase1_2018_realistic_NoPU'

         p = Process(target=submit, args=(config,))
         p.start()
         p.join()
