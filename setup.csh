#!/bin/tcsh

# set up the top tagger libraries etc
echo "Set up top tagger"
source ${CMSSW_BASE}/src/TopTagger/TopTagger/test/taggerSetup.csh

# Copy over filelists if they are not present or have changed
if (! -d condor/filelists_Kevin ) then
    echo "No filelists found, copying from eos"
    eos cp -r  root://cmseos.fnal.gov//store/user/lpcsusyhad/StealthStop/filelists_Kevin/ condor/
else
    echo "You already have the filelists. To get the current version, delete condor/filelists_Kevin and run this again"
endif
