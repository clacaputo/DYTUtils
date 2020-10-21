from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.transferOutputs = True
config.General.transferLogs = False 

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'step2_DIGI_L1_DIGI2RAW_HLT.py'
config.JobType.allowUndistributedCMSSW = True

config.Data.splitting = "FileBased"
config.Data.unitsPerJob = 1

config.Data.outLFNDirBase = '/store/user/%s/DyT_MuonPGun' % (getUsernameFromSiteDB())
config.Data.publication = True

config.Site.storageSite = 'T2_BE_UCL'

if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from CRABClient.ClientExceptions import ClientException
    from httplib import HTTPException
    
    samples = {'SingleMuonP1000_DIGI_l1_DIG2RAW_HLT': '/SingleMuonP1000_pythia8/ccaputo-GEN-SIM_CMSSW_10_6_X_phase1_2018_realistic_April2019-bb9d985c4f76b0a7721748ed65e14929/USER',
	       'SingleMuonP2000_DIGI_l1_DIG2RAW_HLT': '/SingleMuonP2000_pythia8/ccaputo-GEN-SIM_CMSSW_10_6_X_phase1_2018_realistic_April2019-193bda4e341667c1cc2c7e9685397567/USER',
               'SingleMuonP3000_DIGI_l1_DIG2RAW_HLT': '/SingleMuonP3000_pythia8/ccaputo-GEN-SIM_CMSSW_10_6_X_phase1_2018_realistic_April2019-c7fce0638b0a94c413185b620cd96641/USER'}    
    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    config.General.workArea = 'crab_projects_DyT_BlackList'

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
         config.Data.outputDatasetTag = 'DIGI_CMSSW_10_6_X_phase1_2018_realistic_step2_NoPU'
         submit(config)
