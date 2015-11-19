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

To create histograms from analysis ntuples, run

```
python bin/makeScoutingHistograms.py
```
