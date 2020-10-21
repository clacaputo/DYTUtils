#!/bin/bash
#
#SBATCH -N 1 # 1 nodes
#SBATCH -n 1 # 6 tasks
#SBATCH --partition=cp3
#SBATCH --qos=cp3
#SBATCH --workdir=.
#SBATCH --time=0-08:00
#SBATCH --mem-per-cpu=4096
#SBATCH --array=1-2
#SBATCH --nodelist=mb-sky008
#SBATCH --output=log_output.log
#SBATCH --output=log_error.log
# error=/dev/null
#error=/dev/null

# Script stop when a line fail
set -e

LAUNCH_FOLDER=$SLURM_SUBMIT_DIR


# Declare Hash Table
declare -A categories
categories=( [1]="newDyT_APE_3000" \
             [2]="newDyT_noAPE_3000"  )

declare -A list_of_file
list_of_file=( [1]="/home/users/c/c/ccaputo/DyT/CMSSW_10_6_0_pre4/src/Analysis/DYTAnalyzer/newDyT_APE_RECO.txt" \
               [2]="/home/users/c/c/ccaputo/DyT/CMSSW_10_6_0_pre4/src/Analysis/DYTAnalyzer/newDyT_noAPE_RECO.txt" )


file_name=${list_of_file[${SLURM_ARRAY_TASK_ID}]}
category=${categories[${SLURM_ARRAY_TASK_ID}]}

pvalue=`echo $category | cut -d'_' -f3`

export SCRAM_ARCH=slc7_amd64_gcc700

cd $LAUNCH_FOLDER
ls -lrta
pwd
#module load cms/cmssw

eval `scramv1 runtime -sh`

cd -
printf 'Running plotting on file='${file_name}'\n'
cmsRun ${LAUNCH_FOLDER}/ntuplizer_cfg.py psim=${pvalue} tag=${category} useSelections=True inputFileList=${file_name}
printf '....plotting finished\n'
## stageOut
mv *.root ${LAUNCH_FOLDER}
