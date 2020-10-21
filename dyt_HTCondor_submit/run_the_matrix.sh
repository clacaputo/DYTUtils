#! /bin/sh
####################################
#        LaunchOnFarm Script       #
#     Loic.quertenmont@cern.ch     #
#            April 2010            #
####################################

ProcId=$1

# Script stop when a line fail
set -e

LAUNCH_FOLDER=/afs/cern.ch/work/c/ccaputo/private/UCL/DyT/CMSSW_10_6_X_2019-04-07-2300/src/testing_scripts
export SCRAM_ARCH=slc7_amd64_gcc700

cd $LAUNCH_FOLDER 
if [[ ! -d 'Results' ]]; then
	mkdir Results
fi

eval `scramv1 runtime -sh`

cd -

printf 'Running GENSIM step....\n'
cmsRun ${LAUNCH_FOLDER}/SingleMuPt1000_pythia8_cfi_GEN_SIM.py 
printf '....GENSIM finished\n'

mv step1.root step1_${ProcId}.root

printf 'Running DIGI step....\n'
cmsRun ${LAUNCH_FOLDER}/step2_DIGI_L1_DIGI2RAW_HLT.py inputFile=step1_${ProcId}.root outputFile=step2_${ProcId}.root 
printf '....DIGI finished\n'

cp -r *.root $LAUNCH_FOLDER/Results 
