from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.transferOutputs = True
config.General.transferLogs = False 

config.JobType.pluginName = 'PrivateMC'
config.JobType.psetName = 'SingleMuPtMOD_pythia8_cfi_GEN_SIM.py'
config.JobType.allowUndistributedCMSSW = True

config.Data.splitting = "EventBased"
config.Data.totalUnits = 1000000
config.Data.unitsPerJob = 1000

config.Data.outLFNDirBase = '/store/user/%s/DyT' % (getUsernameFromSiteDB())
config.Data.publication = True

config.Site.storageSite = 'T2_BE_UCL'

if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from CRABClient.ClientExceptions import ClientException
    from httplib import HTTPException
    
    samples = {'SingleMuonPt1000_pythia8_GEN-SIM': 1000,
	       'SingleMuonPt2000_pythia8_GEN-SIM': 2000,
               'SingleMuonPt3000_pythia8_GEN-SIM': 3000}
    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    config.General.workArea = 'crab_projects_DyT'

    def submit(config):
        try:
            crabCommand('submit', config = config)
        except HTTPException as hte:
            print "Failed submitting task: %s" % (hte.headers)
        except ClientException as cle:
            print "Failed submitting task: %s" % (cle)

    #############################################################################################
    ## From now on that's what users should modify: this is the a-la-CRAB2 configuration part. ##
    #############################################################################################
    for sample, pt in samples.items():
         config.General.requestName = sample
         config.JobType.pyCfgParams = ['pt={0}'.format(pt)]
         config.Data.outputPrimaryDataset = sample
         config.Data.outputDatasetTag = 'CMSSW_10_6_X_phase1_2018_realistic_April2019'
         submit(config)
