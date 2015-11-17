Scouting jets low mass analysis code
=====================================

Author: David G. Sheffield (Rutgers)

Analysis code for low mass RPV gluinos decaying to three jets in scouting data.

Instructions
------------

To create ntuple locally, run

```
cmsRun python/ScoutingNtuplizer_cfg.py
```

Ntuples can be created through crab with `crab/crab_ntuplizer.py`.

The code to make histograms from ntuples is in `bin/`. Create histograms by running the binary `../../../bin/slc6_amd64_gcc491/makeScoutingHistograms`.
