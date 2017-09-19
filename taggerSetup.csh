# Change these two lines to match your area
set OPENCVPATH=/uscms/home/nstrobbe/nobackup/SOFTWARE/opencv/lib
set TAGGERDIR=/uscms/home/nstrobbe/work/StealthStop/CMSSW_8_0_28/src/TopTagger/TopTagger/test/../..//TopTagger/test

set OSNAME=`uname -s`

if ( "$OSNAME" == "Darwin" ) then
    set test=`echo $DYLD_LIBRARY_PATH | grep "${OPENCVPATH}"`
    if ( $test == "" ) then
	setenv DYLD_LIBRARY_PATH ${OPENCVPATH}:${LD_LIBRARY_PATH}
    endif
    
    set test2=`echo $DYLD_LIBRARY_PATH | grep "${TAGGERDIR}"`
    if ( $test2 == "" ) then
	setenv DYLD_LIBRARY_PATH ${TAGGERDIR}:${LD_LIBRARY_PATH}
    endif
else
    set test=`echo $LD_LIBRARY_PATH | grep "${OPENCVPATH}"`
    if ( $test == "" ) then
	setenv LD_LIBRARY_PATH ${OPENCVPATH}:${LD_LIBRARY_PATH}
    endif
    
    set test2=`echo $LD_LIBRARY_PATH | grep "${TAGGERDIR}"`
    if ( $test2 == "" ) then
	setenv LD_LIBRARY_PATH ${TAGGERDIR}:${LD_LIBRARY_PATH}
    endif
endif
