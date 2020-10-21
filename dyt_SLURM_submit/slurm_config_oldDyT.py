import os
import glob

from CP3SlurmUtils.Configuration import Configuration

config = Configuration()

#--------------------------------------------------------------------------------
# 1. SLURM sbatch command options
#--------------------------------------------------------------------------------

config.sbatch_partition = 'cp3'
config.sbatch_qos = 'cp3'
config.sbatch_workdir = '.'
config.sbatch_time = '0-08:00'
config.sbatch_mem = '4096'
config.sbatch_output = '/dev/null'
config.sbatch_error = '/dev/null'
config.sbatch_additionalOptions = []

#--------------------------------------------------------------------------------
# 2. User batch script parameters that are same for all jobs
#--------------------------------------------------------------------------------

config.cmsswDir = os.environ.get('CMSSW_BASE')

config.inputSandboxContent = ['run_the_matrix_RECO_oldDyT.sh']
config.inputSandboxDir = config.sbatch_workdir + '/slurm_input_sandboxes'

config.batchScriptsDir = config.sbatch_workdir + '/slurm_batch_scripts'

config.stageout = True
config.stageoutFiles = ['output_file_for_job_*.root']
# We chose the filename of the outputs to be independent of the job array id number (but dependent on the job array task id number).
# So let's put the output files in a directory whose name contains the job array id number,
# so that each job array we may submit will write in a different directory.
config.stageoutDir = '/nfs/user/ccaputo/DyT/slurm_outputs/job_array_${SLURM_ARRAY_JOB_ID}'

config.writeLogsOnWN = True
config.separateStdoutStderrLogs = False
config.stageoutLogs = True
# The default filename of the slurm logs has already a job array id number and a job array task id number in it.
# So we can put all logs together (even from different job arrays we may submit) in a unique directory; they won't overwrite each other.
config.stageoutLogsDir = config.sbatch_workdir + '/slurm_logs'

config.useJobArray = True

# 2 jobs will be submitted, because the config parameter 'inputParams' has length 2.
config.numJobs = None

#--------------------------------------------------------------------------------
# 3 Job-specific input parameters and payload
#--------------------------------------------------------------------------------
config.inputParamsNames = ['inputFile', 'outputFile']

# Get a list with all the input files.
inputFiles = glob.glob('/storage/data/cms/store/user/ccaputo/DyT/SingleMuonPt1000_pythia8_GEN-SIM/CMSSW_10_6_X_phase1_2018_realistic_spet2_NoPU_April2019/190421_215343/0000/output_*.root')

# Now we will assume something that is almost always true: that the name of the input files
# contains an index and that we want to assign the same index to the output filename. 
# In this example the input filename has the index just before the '.root' file extension (my_input_file_<index>.root).
# We will loop over the list of input files and for each input file define the name of the output file,
# extracting from the input filename the desired index and adding it to the output filename.
config.inputParams = []
for inputFile in inputFiles:
    inputFileBasename = os.path.basename(inputFile) # here we removed the directory part and we are left with 'my_input_file_<index>.root'
    inputFileBasenameWithoutExt = os.path.splitext(inputFileBasename)[0] # here we removed the '.root' part and we are left with 'my_input_file_<index>'
    index = inputFileBasenameWithoutExt.split('_')[1] # here we removed the 'my_input_file_' part and we are left with the index
    outputFile = 'output_file_for_job_%s' % (index)
    # Once we have defined all the input parameters for the job, we append them
    # in the right order (as defined in 'config.inputParamsNames') to the list of input parameters.
    config.inputParams.append([inputFile, outputFile])

config.payload = \
"""
./run_the_matrix_RECO_oldDyT.sh ${inputFile} ${outputFile}
"""

