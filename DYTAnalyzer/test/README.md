## How to create yml files

```bash
for f in `ls -d /storage/data/cms/store/user/ccaputo/DYT_ThresholdStudies_2022/ThrScan/SingleMuonP*/*/*/`
do 
    #extract the name
    echo `echo $f | cut -d / -f 11 | sed -e 's/crab_//g'`":"

    # extract psim and thr from the name (hoping the convention still remains the same)
    echo $f | cut -d / -f 11| grep -o -E '[0-9]+'| sed -e '1s/[0-9]*/  psim: &/'|sed -e '2s/[0-9]*/  thr: &/'

    # create the full path to root files
    echo "  path: $f/000*/*.root"
done
```

To run in quickly from the command line (NOTA: change the input folder)

```bash
for f in `ls -d /storage/data/cms/store/user/ccaputo/DYT_ThresholdStudies_2022/ThrScan/SingleMuonP*/*/*/`; do echo `echo $f | cut -d / -f 11 | sed -e 's/crab_//g'`":"; echo $f | cut -d / -f 11| grep -o -E '[0-9]+'| sed -e '1s/[0-9]*/  psim: &/'|sed -e '2s/[0-9]*/  thr: &/'; echo "  path: \"$f/000*/*.root\"" ;done > test.yml
```
