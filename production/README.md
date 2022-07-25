If you need to change the `step3*_cfg.py`, you need to  use `dyt_recostudies.patch` on a new config file to include VarParsing, DYTInfo storage and DYT configurable options.
This additional code is used to configure the crab jobs, allowing to:
- turn ON/OFF APEs
- turn ON/OFF the DYT parameterization (default in Run2)
- select the DYT threshold <-- NOTE: only if DYT parameterization is OFF  
