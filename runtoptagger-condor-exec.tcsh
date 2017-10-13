#!/bin/tcsh

#--- You should copy this to a scratch disk where you will manage your job submission and output
#    and prepare the two tar files as described below.

##--- See this web page: http://uscms.org/uscms_at_work/computing/setup/condor_worker_node.shtml

##--- See also make_condor_jdl_files.c which makes jdl files that go with this executable script.

set input_fpat = $1
set output_file = $2
set input_dir = $3

set base_dir = `pwd`
printf "\n\n base dir is $base_dir\n\n"

source /cvmfs/cms.cern.ch/cmsset_default.csh
setenv SCRAM_ARCH  slc6_amd64_gcc530

#--- You need to make a tar file of the opencv lib directory.
#      The expected directory structure in the tar file is opencv/lib.
#      That is, make it by doing something like this
#
#         mkdir opencv
#         cd opencv
#         cp -r /uscms/home/nstrobbe/nobackup/SOFTWARE/opencv/lib .
#         cd -
#         tar -cvf opencv.tar opencv
#         gzip -9v opencv.tar
#

printf "\n\n Unpacking opencv tar file.\n"
tar -xf opencv.tar.gz

printf "\n\n ls output\n"
ls -l


#--- You need to make a tar file of your CMSSW directory that contains the
#      TopTagger stuff and your compiled code from the Exploration directory.
#      You may need to change some symbolic links that reference full path
#      names to relative path names in order for the untarred file to work
#      on the batch node.  I forgot which specific changes I made.
#      Once you have done that, make the tar file with something like this
#
#        tar -cvf cmssw-toptagger.tar CMSSW_8_0_28
#

printf "\n\n unpacking CMSSW tar file.\n\n"
tar -xf cmssw-toptagger.tar.gz

printf "\n\n ls output\n"
ls -l

setenv OPENCVPATH ${base_dir}/opencv/lib
setenv TAGGERDIR ${base_dir}/CMSSW_8_0_28/src/TopTagger/TopTagger/test

printf "\n\n OPENCVPATH: ${OPENCVPATH}\n\n"

printf "\n\n TAGGERDIR: ${TAGGERDIR}\n\n"




printf "\n\n changing to CMSSW_8_0_28/src/ dir\n"
cd CMSSW_8_0_28/src/


printf "\n\n ls output\n"
ls -l

printf "\n\n about to do the scramv1 thing that is the same as cmsenv\n"
eval `scramv1 runtime -csh`

setenv CMSSW_BASE ${base_dir}/CMSSW_8_0_28

printf "\n\n output of uname -s : "
uname -s
printf "\n\n"

cd Exploration

setenv LD_LIBRARY_PATH ${OPENCVPATH}:${LD_LIBRARY_PATH}
setenv LD_LIBRARY_PATH ${TAGGERDIR}:${LD_LIBRARY_PATH}

printf "\n\n LD_LIBRARY_PATH: ${LD_LIBRARY_PATH}\n\n"


printf "\n\n ls output\n"
ls -l


printf "\n\n ls -l of AddTopVarsBatch returns\n"
ls -l AddTopVarsBatch

printf "\n\n Attempting to run AddTopVarsBatch executable.\n\n"
./AddTopVarsBatch ${input_fpat} ${output_file} ${input_dir} skim


printf "\n\n ls output\n"
ls -l

mv ${output_file} ${base_dir}

cd ${base_dir}

printf "\n\n ls output\n"
ls -l




