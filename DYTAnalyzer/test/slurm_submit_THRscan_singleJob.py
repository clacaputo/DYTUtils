import os
import yaml
import glob

payload_template = """#! /bin/sh
#
#SBATCH -N 1 # 1 nodes
#SBATCH -n 1 # 6 tasks
#SBATCH --partition=cp3
#SBATCH --time=0-08:00
#SBATCH --mem-per-cpu=4096
#SBATCH --output=/dev/null
#SBATCH --error=/dev/null

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
cmsRun ntuplizer_cfg.py psim=1000 tag=NTuplizer_${category} outputFile=/nfs/user/ccaputo/DyT/slurm_outputs/DYT_ThrScan/output.root useSelections=False inputFileList=${file_name}
printf '....plotting finished\\n'
rm file_name
"""
f = open("samples.yml")

samples = yaml.load(f, Loader= yaml.FullLoader)

for sample in samples:
    options = samples[sample]
    path    = options["path"]
    psim    = options["psim"]
    thr     = options["thr"]
    
    print(sample)
    if psim == 500:
        continue

    list_of_files = glob.glob("{}".format(path))
    of = open("{}.txt".format(sample),"w")
    MyList=map(lambda x:x+'\n', list_of_files)
    of.writelines(MyList)
    of.close()
    filepath = os.path.abspath("{}.txt".format(sample))
    print(filepath)


    payload = payload_template.replace("__FILES_LIST_TXT__", filepath).replace("__CATEGORY__", sample)
    
    sbatch_script_name = "sbatch_{}.sh".format(sample)
    sbfile = open(sbatch_script_name,"w")
    sbfile.write(payload)
    sbfile.close()

    os.system("sbatch {}".format(sbatch_script_name))


