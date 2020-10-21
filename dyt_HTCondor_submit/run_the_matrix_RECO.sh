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
cp ${LAUNCH_FOLDER}/Results/step2_${ProcId}.root . 

printf 'Running RECO step old DyT....\n'
cmsRun ${LAUNCH_FOLDER}/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_EI_PAT_VALIDATION_DQM.py inputFile=step2_${ProcId}.root newDyT=False tag=oldDyT
printf '....RECO old DyT finished\n'

rename step3 step3_${ProcId} step3*.root
mv step3*root $LAUNCH_FOLDER/Results

printf 'Running RECO step new DyT....\n'
cmsRun ${LAUNCH_FOLDER}/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_EI_PAT_VALIDATION_DQM.py inputFile=step2_${ProcId}.root newDyT=True tag=newDyT
printf '....RECO new DyT finished\n'

rename step3 step3_${ProcId} step3*.root
mv  step3*.root $LAUNCH_FOLDER/Results 
