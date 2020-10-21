#! /bin/sh
#
#SBATCH -N 1 # 1 nodes
#SBATCH -n 6 # 6 tasks
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


# Declare Hash Table
declare -A list_of_file
list_of_file=( ["newDyT_1000"]="/home/users/c/c/ccaputo/DyT/CMSSW_10_6_0_pre4/src/newDyT_co_MuonP1000.txt" \
               ["oldDyT_1000"]="/home/users/c/c/ccaputo/DyT/CMSSW_10_6_0_pre4/src/oldDyT_MuonP1000.txt" \
               ["newDyT_2000"]="/home/users/c/c/ccaputo/DyT/CMSSW_10_6_0_pre4/src/newDyT_co_MuonP2000.txt" \
               ["oldDyT_2000"]="/home/users/c/c/ccaputo/DyT/CMSSW_10_6_0_pre4/src/oldDyT_MuonP2000.txt" \
               ["newDyT_3000"]="/home/users/c/c/ccaputo/DyT/CMSSW_10_6_0_pre4/src/newDyT_co_MuonP3000.txt" \
               ["oldDyT_3000"]="/home/users/c/c/ccaputo/DyT/CMSSW_10_6_0_pre4/src/oldDyT_MuonP3000.txt" )


for category in "${!list_of_file[@]}"
do
    cat > exec_${category}.sh <<EOF
#!/bin/bash
set -e

file_name=\$1
category=\$2

pvalue=\`echo \$category | cut -d'_' -f2\`

export SCRAM_ARCH=slc7_amd64_gcc700

cd $LAUNCH_FOLDER

eval `scramv1 runtime -sh`

cd -
printf 'Running plotting on file='\${file_name}'\n'
cmsRun ${LAUNCH_FOLDER}/dytanalyzer_cfg.py psim=\${pvalue} tag=\${category} inputFileList=\${file_name}
printf '....plotting finished\n'
## stageOut
mv output.root ${LAUNCH_FOLDER}/output_V2_\${category}.root

EOF

    chmod 0700 exec_${category}.sh
    file=${list_of_file[$category]}
    printf "Category "$category" and file "$file"\n"
    srun -N1 -n1 --exclusive exec_${category}.sh ${file} ${category} &
done
wait
