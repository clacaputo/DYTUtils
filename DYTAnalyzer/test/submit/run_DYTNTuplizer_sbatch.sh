#! /bin/sh
#
#SBATCH -N 1 # 1 nodes
#SBATCH -n 1 # 6 tasks
#SBATCH --partition=cp3
#SBATCH --time=0-08:00
#SBATCH --mem-per-cpu=4096
#SBATCH --array=1
###SBATCH --output=/dev/null
###SBATCH --error=/dev/null

# Script stop when a line fail
set -e

LAUNCH_FOLDER=$SLURM_SUBMIT_DIR


# Declare Hash Table
declare -A categories
categories=(  [1]="SingleMuonP2000_Thr55_INC_FIX"  )

declare -A list_of_file
list_of_file=([1]="/home/users/c/c/ccaputo/DyT/CMSSW_11_1_4/src/SingleMuonP2000_pythia8_APE_Thr55_FIX.txt" )


file_name=${list_of_file[${SLURM_ARRAY_TASK_ID}]}
category=${categories[${SLURM_ARRAY_TASK_ID}]}

# pvalue=`echo $category | cut -d'_' -f3`

export SCRAM_ARCH=slc7_amd64_gcc700

cd $LAUNCH_FOLDER

eval `scramv1 runtime -sh`

cd -

printf 'Running plotting on file='${file_name}'\n'
cmsRun ntuplizer_cfg.py psim=2000 tag=NTuplizer_${category} outputFile=/nfs/user/ccaputo/DyT/slurm_outputs/output.root useSelections=False inputFileList=${file_name}
printf '....plotting finished\n'
## stageOut
#cp -r *.root /nfs/user/ccaputo/DyT/slurm_outputs/DYT_ThrScan/
#rm *.root
