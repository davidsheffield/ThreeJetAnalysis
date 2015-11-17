GluinoGluinoToJets Code
=======================

Author: David G. Sheffield (Rutgers)

Analysis code for RPV gluinos decaying to jets.

Setup
-----

Run the following commands to setup this analysis code.

```
cmsrel CMSSW_7_4_15
cd CMSSW_7_4_15/src/
cmsenv
git clone https://github.com/davidsheffield/ThreeJetAnalysis.git
scram b -j 16
```

Subpackages
-----------

* **Resolved** analysis as well as RECO MC for scouting analysis.
* **Scouting** analysis.
* **Utilities** used by other parts of the code.
* **Generation** of signal with matrix element generators.
* **Simulation** of MC.
* **MonitorScouting** datasets and validation.
* **DiPhoton** scouting analysis.
