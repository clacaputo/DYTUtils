import os
import glob
import sys
import yaml

from CP3SlurmUtils.Configuration import Configuration
from CP3SlurmUtils.SubmitWorker import SubmitWorker
from CP3SlurmUtils.Exceptions import CP3SlurmUtilsException


yml = "samples_DIGI.yml"

with open(yml,'r') as f:

    samples = yaml.load(f,Loader=yaml.FullLoader)

    for sample in samples:

        options = samples[sample]
        folder = sample.split('_')[0]
        thr    = 15 # options['thr']
        inpath = options['path']
        psim   = options['psim']

        # if psim == 1000: continue

        sample_name = "{}_thr{}".format(sample,str(thr))
        config = Configuration()

        #--------------------------------------------------------------------------------
        # 1. SLURM sbatch command options
        #--------------------------------------------------------------------------------

        config.sbatch_partition = 'cp3'
        config.sbatch_qos = 'cp3'
        config.sbatch_chdir = '.'
        config.sbatch_time = '0-08:00'
        config.sbatch_memPerCPU = '4092'
        config.sbatch_output = '/dev/null'
        config.sbatch_error = '/dev/null'
        config.sbatch_additionalOptions = []

        #--------------------------------------------------------------------------------
        # 2. User batch script parameters that are same for all jobs
        #--------------------------------------------------------------------------------

        config.environmentType = "cms"
        config.cmsswDir = os.environ.get('CMSSW_BASE')

        config.inputSandboxContent = ['step3_RAW2DIGI_L1Reco_RECO_RECOSIM_EI_PAT_slurm.py']
        config.inputSandboxDir = config.sbatch_chdir + '/slurm_input_sandboxes'

        config.batchScriptsDir = config.sbatch_chdir + '/slurm_batch_scripts'

        config.stageout = True
        config.stageoutFiles = ['output*.root']
        # We chose the filename of the outputs to be independent of the job array id number (but dependent on the job array task id number).
        # So let's put the output files in a directory whose name contains the job array id number,
        # so that each job array we may submit will write in a different directory.

        config.writeLogsOnWN = True
        config.separateStdoutStderrLogs = False
        config.stageoutLogs = False
        # The default filename of the slurm logs has already a job array id number and a job array task id number in it.
        # So we can put all logs together (even from different job arrays we may submit) in a unique directory; they won't overwrite each other.
        config.stageoutLogsDir = '/nfs/user/ccaputo/DyT/slurm_outputs/RECO_APE_NewParameters_Barrel_Endcaps/slurm_logs'

        config.useJobArray = True

        # 2 jobs will be submitted, because the config parameter 'inputParams' has length 2.
        config.numJobs = None
        #--------------------------------------------------------------------------------
        # 3 Job-specific input parameters and payload
        #--------------------------------------------------------------------------------
        config.inputParamsNames = ['inputFile', 'outputFile']

        config.stageoutDir = '/nfs/user/ccaputo/DyT/slurm_outputs/RECO_APE_NewParameters_Barrel_Endcaps/'+folder#'/job_array_${SLURM_ARRAY_JOB_ID}'
        # Get a list with all the input files.
        inputFiles = glob.glob(inpath)

# Now we will assume something that is almost always true: that the name of the input files
# contains an index and that we want to assign the same index to the output filename.
# In this example the input filename has the index just before the '.root' file extension (my_input_file_<index>.root).
# We will loop over the list of input files and for each input file define the name of the output file,
# extracting from the input filename the desired index and adding it to the output filename.
        config.inputParams = []
        for inputFile in inputFiles:
            thr = thr
            inputFileBasename = os.path.basename(inputFile) # here we removed the directory part and we are left with 'my_input_file_<index>.root'
            inputFileBasenameWithoutExt = os.path.splitext(inputFileBasename)[0] # here we removed the '.root' part and we are left with 'my_input_file_<index>'
            index = inputFileBasenameWithoutExt.split('_')[1] # here we removed the 'my_input_file_' part and we are left with the index
            outputFile = 'output_%s' % (index)
            # Once we have defined all the input parameters for the job, we append them
            # in the right order (as defined in 'config.inputParamsNames') to the list of input parameters.
            config.inputParams.append([inputFile, outputFile])


        config.payload = \
        """
        printf 'Running plotting on file='${file_name}'\n'
        cmsRun step3_RAW2DIGI_L1Reco_RECO_RECOSIM_EI_PAT_slurm.py inputFile=${inputFile} runAPEs=True newDyT=True
        printf '....plotting finished\n'

        rename step3 ${outputFile} step3*.root
        """




        rc = 1
        try:
            submitWorker = SubmitWorker(config=config, submit=True, yes=True, quiet=True)
            submitWorker()
            rc = 0
        except CP3SlurmUtilsException as ex:
            print(str(ex))

        #sys.exit(rc)
