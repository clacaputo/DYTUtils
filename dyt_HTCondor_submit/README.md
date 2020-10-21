## Get testing config file

In order to get a cms sequence for testing, _runTheMatrix.p_ has be used for the workflow `10809.0_SingleMuPt1000+SingleMuPt1000_pythia8_2018_GenSimFull+DigiFull_2018+RecoFull_2018+HARVESTFull_2018+ALCAFull_2018+NanoFull_2018`


```bash
runTheMatrix.py --dryRun --nThreads=4 -l 10809.0
```

where `--dryRun` has been used in order to get the config files without running the workflow.

### GEN-SIM

```bash
cmsDriver.py SingleMuPt1000_pythia8_cfi \ 
--conditions auto:phase1_2018_realistic \
-n 10 \ 
--era Run2_2018 \
--eventcontent FEVTDEBUG \
--relval 9000,100 \
-s GEN,SIM \
--datatier GEN-SIM \
--beamspot Realistic25ns13TeVEarly2018Collision \
--geometry DB:Extended \
--fileout file:step1.root \
--no_exec
```

If you want to split the production in multiple jobs, you should add these lines in the python file generated, right after the `process.Schedule`

```python
# Set different random numbers seeds every time one runs cmsRun
from IOMC.RandomEngine.RandomServiceHelper import RandomNumberServiceHelper
randSvc = RandomNumberServiceHelper(process.RandomNumberGeneratorService)
randSvc.populate()
print '='*30
print 'Generator initial seed'
seed = process.RandomNumberGeneratorService.generator.initialSeed.value()
print seed
process.FEVTDEBUGoutput.fileName.setValue('file:step1_'+str(seed)+'.root')
print process.FEVTDEBUGoutput.fileName.value()
print '='*30
```

Doing so you also rename the output file obtained.

### DIGI-RAW

```bash
cmsDriver.py step2 \
--conditions auto:phase1_2018_realistic \
-s DIGI:pdigi_valid,L1,DIGI2RAW,HLT:@relval2018 \
--datatier GEN-SIM-DIGI-RAW \
-n 10 \
--geometry DB:Extended \
--era Run2_2018 \
--eventcontent FEVTDEBUGHLT \
--filein  file:step1.root \
--fileout file:step2.root \
--no_exec
```

### RECO

```bash
cmsDriver.py step3  \
--conditions auto:phase1_2018_realistic \
-n 10 \
--era Run2_2018 \
--eventcontent RECOSIM,MINIAODSIM,DQM \
--runUnscheduled  \
-s RAW2DIGI,L1Reco,RECO,RECOSIM,EI,PAT,VALIDATION:@standardValidation+@miniAODValidation,DQM:@standardDQM+@ExtraHLT+@miniAODDQM \
--datatier GEN-SIM-RECO,MINIAODSIM,DQMIO \
--geometry DB:Extended \
--filein  file:step2.root  \
--fileout file:step3.root \
--no_exec
```
It is possible to activate/deactivate `DYTuseThrsParametrization` using the option `--customise_commands` in `cmsDriver.py`

```python
--customise_commands="process.tevMuons.RefitterParameters.DYTuseThrsParametrization = True; process.glbTrackQual.RefitterParameters.DYTuseThrsParametrization = True"
```

### HARVESTING

```bash
cmsDriver.py step4  \
--conditions auto:phase1_2018_realistic \
-s HARVESTING:@standardValidation+@standardDQM+@ExtraHLT+@miniAODValidation+@miniAODDQM \
--scenario pp \
--filetype DQM \
--geometry DB:Extended \
--era Run2_2018 \
--mc  \
-n 1000  \
--filein file:step3_inDQM.root \
--fileout file:step4.root  \
--no_exec
```
