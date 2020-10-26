from CRABClient.UserUtilities import config, getUsernameFromCRIC
from multiprocessing import Process

config = config()

config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'step3_RAW2DIGI_L1Reco_RECO_RECOSIM_EI_PAT.py'
config.JobType.allowUndistributedCMSSW = True

config.Data.splitting = "FileBased"
config.Data.unitsPerJob = 1

config.Data.outLFNDirBase = '/store/user/%s/DyT_ThresholdStudies/ThrScan' % (getUsernameFromCRIC())
#config.Data.publication = True

config.Site.storageSite = 'T2_BE_UCL'
# UCL added ot black list because doesn't have IB
# config.Site.blacklist   = ['T2_BE_UCL']
# config.Site.whitelist   = ['T2_FR_*','T2_CH_CERN','T2_IT_*']

if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from CRABClient.ClientExceptions import ClientException
    from httplib import HTTPException

    samples = {
                'SingleMuonP500_RECO_RECOSIM_EI_PAT':'/SingleMuonP500_pythia8/ccaputo-DIGI_CMSSW_11_1_3_phase1_2018_realistic_NoPU-04b931a98bc758ab97a385c878d13b9b/USER',
                'SingleMuonP1000_RECO_RECOSIM_EI_PAT': '/SingleMuonP1000_pythia8/ccaputo-DIGI_CMSSW_11_1_3_phase1_2018_realistic_NoPU-04b931a98bc758ab97a385c878d13b9b/USER',
                'SingleMuonP2000_RECO_RECOSIM_EI_PAT': '/SingleMuonP2000_pythia8/ccaputo-DIGI_CMSSW_11_1_3_phase1_2018_realistic_NoPU-04b931a98bc758ab97a385c878d13b9b/USER',
                'SingleMuonP3000_RECO_RECOSIM_EI_PAT':'/SingleMuonP3000_pythia8/ccaputo-DIGI_CMSSW_11_1_3_phase1_2018_realistic_NoPU-04b931a98bc758ab97a385c878d13b9b/USER'
                }
    thr_values = range(11,50,2)
    #           'SingleMuonPt3000_DIGI_l1_DIG2RAW_HLT': '/SingleMuonPt3000_pythia8_GEN-SIM/ccaputo-CMSSW_10_6_X_phase1_2018_realistic_April2019-fdce3adde275acc548e9b0b9ce6ab138/USER'}
    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    config.General.workArea = 'crab_projects_DyT_RECO_ThrScan_fine'

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
    for sample, digi_dataset in samples.items():
        for thr_value in thr_values:
            config.General.requestName = sample+'_APE_Thr{}'.format(thr_value)
            config.JobType.pyCfgParams = ['runAPEs=True','newDyT=False','DyTthrValue={}'.format(thr_value)]
            config.Data.inputDataset = digi_dataset
            config.Data.inputDBS = 'phys03'
         #config.Data.outputPrimaryDataset = sample
         #config.Data.outputDatasetTag = 'CMSSW_10_6_X_phase1_2018_realistic_step3_April2019'
            p = Process(target=submit, args=(config,))
            p.start()
            p.join()
