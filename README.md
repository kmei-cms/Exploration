# Exploration
Collection of scripts, macros, tools to help us explore our signal models and design the analysis.


## How to use the SUS-16-050 Top Tagger in a simple code

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




## Using the tensor-flow based top tagger

To have easy access to TensorFlow, we need to work in a CMSSW93 release:
```
cmsrel CMSSW_9_3_3
cd CMSSW_9_3_3/src/
cmsenv
```

Then, check out the latest tagged version of the top tagger repository. 

```
git clone git@github.com:susy2015/TopTagger.git -b IntermediateRecipeV0
cd TopTagger
```

Then configure and compile the tagger:
```
cd TopTagger/test
./configure 
make -j4
```

Now also check out our repository if not done already:
```
cd $CMSSW_BASE/src
git clone git@github.com:StealthStop/Exploration.git
cd Exploration
# best option:
source ../TopTagger/TopTagger/test/taggerSetup.sh
# or update the taggerSetup.csh in the Exploration repo to point to the TopTagger repo in the CMSSW93 area
source taggerSetup.csh
```

Last step is to get the cfg file for the top tagger, and the TF output model file for the resolved part.
```
$CMSSW_BASE/src/TopTagger/Tools/getTaggerCfg.sh  -t Tensorflow_Example_v1.0.1
```

No changes to the analysis code should be needed. 


## Condor submission

The condor directory contains some scripts to help submit jobs via condor on the cmslpc cluster. 
The requirements for condor submission are: 
 - A script to run on the worker node. This script should set up the area, copy any needed files, call your executable with the right options, and make sure the output gets copied to where you want. The example included here is [run_Exploration_condor.tcsh](condor/run_Exploration_condor.tcsh)
 - One or more tarballs to unpack on the worker node, these usually contain a slimmed down CMSSW area, and your executable with any needed libraries
 - A so-called jdl file that contains the condor setup and specifies the jobs to be submitted
The last two items are produced by a python script called [condorSubmit.py](condor/condorSubmit.py). 

```
[condor]$ python condorSubmit.py -h
Usage: condorSubmit.py [options]


Options:
  -h, --help         show this help message and exit
  -n NUMFILE         number of files per job
  -d DATASETS        List of datasets, comma separated
  -l                 List all datacollections
  -L                 List all datacollections and sub collections
  -c                 Do not submit jobs.  Only create condor_submit.txt.
  --explore=EXPLORE  ExploreTopTagger (t), ExploreBackground (b),
                     ExploreEventSelection (s)
```
As you can see from the above help menu, there are a number of options. 
With the `-n` option you can specify how many files to run over per job. The `--explore` option lets you pick which analyzer to use. 
The MyAnalysis program has been updated to have these same switches. 

MyAnalysis now also uses the samples code to keep track of datasets, their cross sections, and their names. 
To see a list of available datasets, you can call the submission script with the `-l` or `-L` options. Pass the list of datasets you want to run over to the script with the option `-d`. 
Before submitting jobs, make sure to have called `voms-proxy-init`. 
