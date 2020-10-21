#! /bin/sh

INPUTFILE=$1
OUTPUTPREFIX=$2

# Script stop when a line fail
set -e

LAUNCH_FOLDER=$SLURM_SUBMIT_DIR

export SCRAM_ARCH=slc7_amd64_gcc700

cd $LAUNCH_FOLDER 

eval `scramv1 runtime -sh`

cd -

printf 'Running RECO step old DyT....\n'
cmsRun ${LAUNCH_FOLDER}/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_EI_PAT_VALIDATION_DQM.py inputFile=$INPUTFILE newDyT=False tag=oldDyT
printf '....RECO old DyT finished\n'

rename step3 $OUTPUTPREFIX step3*.root
