# Exploration
Collection of scripts, macros, tools to help us explore our signal models and design the analysis.


## How to use the Top Tagger in a simple code

First, set up a CMSSW area so that you have access to ROOT etc. 
```
cmsrel CMSSW_8_0_28
cd CMSSW_8_0_28/src/
cmsenv
```

Then checkout this repository
```
git clone git@github.com:StealthStop/Exploration.git
```

The TopTagger instructions can be found here: https://github.com/susy2015/TopTagger/tree/StandaloneRelease_v1.0.1

The first step is to install opencv. If you are working locally on the lpc machines, you can just link to the opencv installation in Nadja's area:
/uscms/home/nstrobbe/nobackup/SOFTWARE/opencv

Once you have access to opencv, you can proceed to install the toptagger: 

First check out the code. We are now using a branch on top of the StandaloneRelease_v1.0.1, so make sure to check that you have the correct branch. 
```
git clone git@github.com:susy2015/TopTagger.git
cd TopTagger
git checkout StandaloneUpdates
```

Then configure the tagger:
```
cd TopTagger/test
./configure OPENCVDIR=/uscms/home/nstrobbe/nobackup/SOFTWARE/opencv
make -j4
``` 
Of course, if you are not on the lpc, you should update the OPENCVDIR to match your system.
This created a shared library, libTopTagger.so that we can use with our simple scripts. 

If you previously checked out a different branch/tag, do the following to update: 
```
cd $CMSSW_BASE/src/TopTagger
git fetch
git checkout StandaloneUpdates
cd TopTagger/test
make -j4
```
There is no need to rerun the configure step. 

To make sure that we have access to the created library, we should add its location to our path. A setup script was created during configuration for this purpose (CMSSW_8_0_28/src/TopTagger/TopTagger/test/taggerSetup.sh). Note that this is a bash script. If you use tcsh it will not work. I have provided a tcsh script for you to customize based on the first two lines of the bash script (i.e. location of opencv and location of the TopTagger code on your system). You can check that out from the Exploration repository and execute it instead of the taggerSetup.sh script. 

```
cd $CMSSW_BASE/src
cd Exploration
source ../TopTagger/TopTagger/test/taggerSetup.sh
# or
source taggerSetup.csh
```

Then we need to get the cfg file for the top tagger, and the MVA model file for the resolved part. 
```
$CMSSW_BASE/src/TopTagger/Tools/getTaggerCfg.sh  -t MVAAK8_Tight_noQGL_binaryCSV_v1.0.2
```

Now you should be ready to use the top tagger in your code. 
An example of how to do this based on our ntuples can be found in this repository. 
The relevant files are MyAnalysis.C, NtupleClass.C, NtupleClass.h, Makefile. 
The NtupleClass was created from an earlier version of the ntuple, so it will complain about some branches not being found. We can ignore this for now. 

Update MyAnalysis.C to include the file you wish to run over, and compile by doing
```
make
```
The Makefile currently assumes that you are in a CMSSW environment. If you set up your code without it, then you will have to update the Makefile. 

To run: 
```
./MyAnalysis myinputfile optional_outputfilename
```
This will give a printout for the first 10 event containing the number of tops it found, and some information on each top. 
You can customize TopTagger.cfg to enable/disable certain top candidates, i.e. in the TTMBasicClusterAlgo block, set doTrijet/doDijet/doMonojet to true or false. 
