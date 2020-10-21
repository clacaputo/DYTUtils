#! /bin/sh
#

# Script stop when a line fail
set -e

LAUNCH_FOLDER=$PWD

# Declare Hash Table
declare -A list_of_file
list_of_file=( ["newDyT_cutOff"]="/home/users/c/c/ccaputo/DyT/CMSSW_10_6_0_pre4/src/newDyT_co_MuonP3000.txt" \
               ["oldDyT"]="/home/users/c/c/ccaputo/DyT/CMSSW_10_6_0_pre4/src/oldDyT_MuonP3000.txt" )

for category in "${!list_of_file[@]}"
do
    file=${list_of_file[$category]}
    
    printf "Category "$category" and file "$file"\n"
    printf 'Running plotting on file='${file}'\n'
    
    cmsRun ${LAUNCH_FOLDER}/dytanalyzer_cfg.py psim=3000 inputFileList=${file} tag=${category}_local &> ${category}.log &
    
    printf '....cmsRun lunched\n'
    
done
printf 'Waiting for cmsRun to finish\n'
wait
printf 'All cmsRun have finished\n'
