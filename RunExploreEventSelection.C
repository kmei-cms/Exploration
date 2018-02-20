#include "ExploreEventSelection.h"

#include "TH1D.h"
#include "TFile.h"

#include "TSystem.h"
#include <fstream>

#include<iostream>

int main(int argc, char *argv[])
{

    char eos_dir_name[1000] ;

    if (argc == 1)
    {
        std::cout << "Please provide a file pattern to run over" << std::endl;
        return 0;
    }

    std::string outfile = "mytest.root";
    if (argc > 2)
    {
        outfile = argv[2];
    } 

    if ( argc > 3 ) {
       sprintf( eos_dir_name, "%s", argv[3] ) ;
    } else {
       sprintf( eos_dir_name, "/store/user/soha/stealth_rpv_ntuples_subjets" ) ;
    }


    char command[1000] ;
    sprintf( command, "eos root://cmseos.fnal.gov ls %s > eos-files.txt", eos_dir_name ) ;
    gSystem -> Exec( command ) ;


    char file_pattern[1000] ;
    sprintf( file_pattern, "%s", argv[1] ) ;
    printf("\n\n Will load files that match %s from eos dir %s\n\n", file_pattern, eos_dir_name ) ;





     //------- NFG.  Can't use wildcard with eos files and TChain::Add apparently.
    ////////TChain* ch = new TChain( "TreeMaker2/PreSelection" ) ;
    ////////int nfiles = ch->Add( "root::cmsxrootd.fnal.gov//store/user/soha/stealth_rpv_ntuples_subjets/Summer16_private.rpv_stop_650_t3j_uds_*.root" ) ;
    ////////printf("\n\n Number of files added to TChain: %d\n\n", nfiles ) ;
    ////////printf("\n\n Number of entries %lld\n\n", ch->GetEntries() ) ;


    TChain* ch = new TChain( "TreeMaker2/PreSelection" ) ;
    std::string runtype = "";

    std::ifstream ifs_files ;
    ifs_files.open( "eos-files.txt" ) ;
    while ( ifs_files.good() ) {
       TString tsline ;
       tsline.ReadLine( ifs_files ) ;
       if ( !ifs_files.good() ) break ;
       if ( tsline.Contains( file_pattern ) ) {
          char fname[1000] ;
          sscanf( tsline.Data(), "%s", fname ) ;
          std::string strfname(fname);
          if(strfname.find("Run2016") != std::string::npos)
              runtype = "Data";
          char fnamewithpath[1000] ;
          sprintf( fnamewithpath, "root://cmsxrootd.fnal.gov/%s/%s", eos_dir_name, fname ) ;
          printf("  Adding file %s\n", fnamewithpath ) ;
          ch -> Add( fnamewithpath ) ;
       }
    }
    int nentries = ch->GetEntries() ;
    printf("\n\n Number of entries %d\n\n", nentries ) ;
    if ( nentries <= 0 ) { printf("\n\n Nothing to do.\n\n") ; gSystem->Exit(-1) ; }


    TFile* myfile = TFile::Open(outfile.c_str(), "RECREATE");
    
    bool isQuiet = true;
    ExploreEventSelection t = ExploreEventSelection( ch );
    t.InitHistos();
    t.Loop(1.0, -1, runtype, isQuiet);
    t.WriteHistos();

    myfile->Close();

    return 0;
}
