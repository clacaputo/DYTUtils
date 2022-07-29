import os
import yaml
import glob
from datetime import datetime

import argparse
parser = argparse.ArgumentParser()
parser.add_argument("--yml", type=str, required=True, help="yml files" )
parser.add_argument("--outputFolder", type=str, required=True, help="output folder name stored in /nfs/user/ccaputo/DyT/slurm_outputs/" )
#parser.add_argument("--p", type=int, choices=[1,2,3,4,5,6,8,10,15,20], nargs='*',
#                                help="HNL mass value [1,2,3,4,5,6,8,10,15,20]" )
#parser.add_argument("--newIVF", action='store_true', default=False, help="Process events with the modify IVF")


now = datetime.now()
time = now.strftime("%y%m%d")

args = parser.parse_args()
yml = args.yml
outputFolder = args.outputFolder
#masses = args.masses
#cfgfile = os.path.abspath(args.cfgfile)
#newIVF = args.newIVF

def createFolder(path):
    if os.path.isdir(path) == False:
        os.system('mkdir -p ' + path)

payload_template = """#! /bin/sh
#
#SBATCH -N 1 # 1 nodes
#SBATCH -n 1 # 6 tasks
#SBATCH --partition=cp3
#SBATCH --time=0-08:00
#SBATCH --mem-per-cpu=4096
#SBATCH --output=%x.%A.%a.out
#SBATCH --error=%x.%A.%a.err

# Script stop when a line fail
set -e

LAUNCH_FOLDER=$SLURM_SUBMIT_DIR

file_name=__FILES_LIST_TXT__
category=__CATEGORY__

# pvalue=`echo $category | cut -d'_' -f3`

export SCRAM_ARCH=slc7_amd64_gcc700

cd $LAUNCH_FOLDER

eval `scramv1 runtime -sh`

cd -
printf 'Running plotting on file='${file_name}'\\n'
cmsRun ntuplizer_cfg.py psim=1000 tag=NTuplizer_${category} outputFile=__OUTPUTPATH__/output.root useSelections=False inputFileList=${file_name}
printf '....plotting finished\\n'
rm ${file_name}
"""
f = open(yml)

samples = yaml.load(f)#, Loader= yaml.FullLoader)

for sample in samples:
    outpath = "/nfs/user/ccaputo/DyT/slurm_outputs/{}".format(outputFolder)
    createFolder(outpath)
    options = samples[sample]
    path    = options["path"]
    psim    = options["psim"]
    thr     = options["thr"]

    print(sample)
    #if psim == 2000 or psim==3000: continue

    list_of_files = glob.glob("{}".format(path))
    of = open("{}.txt".format(sample),"w")
    MyList=map(lambda x:x+'\n', list_of_files)
    of.writelines(MyList)
    of.close()
    filepath = os.path.abspath("{}.txt".format(sample))
    print(filepath)


    payload = payload_template.replace("__FILES_LIST_TXT__", filepath).replace("__CATEGORY__", sample).replace("__OUTPUTPATH__", outpath)

    sbatch_script_name = "sbatch_{}.sh".format(sample)
    sbfile = open(sbatch_script_name,"w")
    sbfile.write(payload)
    sbfile.close()

    os.system("sbatch {}".format(sbatch_script_name))
