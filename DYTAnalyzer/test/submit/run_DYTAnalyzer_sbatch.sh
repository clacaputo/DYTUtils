#! /bin/sh
#
#SBATCH -N 1 # 1 nodes
#SBATCH -n 1 # 6 tasks
#SBATCH --partition=cp3
#SBATCH --qos=cp3
#SBATCH --workdir=.
#SBATCH --time=0-08:00
#SBATCH --mem-per-cpu=4096
#SBATCH --array=1-6
#SBATCH --output=/dev/null
#SBATCH --error=/dev/null

# Script stop when a line fail
set -e

LAUNCH_FOLDER=$SLURM_SUBMIT_DIR


# Declare Hash Table
declare -A categories
categories=( [1]="newDyT_1000" \
             [2]="oldDyT_1000" \
             [3]="newDyT_2000" \
             [4]="oldDyT_2000" \
             [5]="newDyT_3000" \
             [6]="oldDyT_3000" )

declare -A list_of_file
list_of_file=( [1]="/home/users/c/c/ccaputo/DyT/CMSSW_10_6_0_pre4/src/newDyT_co_MuonP1000.txt" \
               [2]="/home/users/c/c/ccaputo/DyT/CMSSW_10_6_0_pre4/src/oldDyT_MuonP1000.txt" \
               [3]="/home/users/c/c/ccaputo/DyT/CMSSW_10_6_0_pre4/src/newDyT_co_MuonP2000.txt" \
               [4]="/home/users/c/c/ccaputo/DyT/CMSSW_10_6_0_pre4/src/oldDyT_MuonP2000.txt" \
               [5]="/home/users/c/c/ccaputo/DyT/CMSSW_10_6_0_pre4/src/newDyT_co_MuonP3000.txt" \
               [6]="/home/users/c/c/ccaputo/DyT/CMSSW_10_6_0_pre4/src/oldDyT_MuonP3000.txt" )


file_name=${list_of_file[${SLURM_ARRAY_TASK_ID}]}
category=${categories[${SLURM_ARRAY_TASK_ID}]}

pvalue=`echo $category | cut -d'_' -f2`

export SCRAM_ARCH=slc7_amd64_gcc700

cd $LAUNCH_FOLDER

eval `scramv1 runtime -sh`

cd -
printf 'Running plotting on file='${file_name}'\n'
cmsRun ${LAUNCH_FOLDER}/dytanalyzer_cfg.py psim=${pvalue} tag=${category} useSelections=True inputFileList=${file_name}
printf '....plotting finished\n'
## stageOut
mv *.root ${LAUNCH_FOLDER}
