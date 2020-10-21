Universe                = vanilla
Environment             = CONDORJOBID=$(Process)
notification            = Error
when_to_transfer_output = ON_EXIT
transfer_output_files   = "" 
should_transfer_files   = YES
executable              = run_the_matrix_RECO.sh
arguments               = $(ProcId)
output                  = logs/$Fn(executable).$(ClusterId).$(ProcId).out
error                   = logs/$Fn(executable).$(ClusterId).$(ProcId).err
log                     = logs/$Fn(executable).$(ClusterId).$(ProcId).log
+JobFlavour             = "workday"
queue 20 
