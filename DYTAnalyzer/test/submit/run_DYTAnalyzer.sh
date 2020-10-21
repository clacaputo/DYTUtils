#! /bin/sh
#
#SBATCH --partition=cp3
#SBATCH --qos=cp3
#SBATCH --workdir=.
#SBATCH --time=0-08:00
#SBATCH --mem-per-cpu=4096
#SBATCH -o run_dytAnalyzer_%A.out # Standard output
#SBATCH -e run_dytAnalyzer_%A.err # Standard error

# Script stop when a line fail
set -e

LAUNCH_FOLDER=$SLURM_SUBMIT_DIR

export SCRAM_ARCH=slc7_amd64_gcc700

cd $LAUNCH_FOLDER

eval `scramv1 runtime -sh`

cd -

# Declare Hash Table
declare -A list_of_file
list_of_file=( ["newDyT_cutOff"]="/home/users/c/c/ccaputo/DyT/CMSSW_10_6_0_pre4/src/newDyT_co_MuonP1000.txt" \
               ["oldDyT"]="/home/users/c/c/ccaputo/DyT/CMSSW_10_6_0_pre4/src/oldDyT_MuonP1000.txt" )

for category in "${!list_of_file[@]}"
do
    file=${list_of_file[$category]}
    
    printf "Category "$category" and file "$file"\n"
    printf 'Running plotting on file='${file}'\n'
    
    cmsRun ${LAUNCH_FOLDER}/dytanalyzer_cfg.py inputFileList=${file} tag=${category} &
    
    printf '....plotting finished\n'
    
done
wait

## stageOut
mv output*.root ${LAUNCH_FOLDER}
