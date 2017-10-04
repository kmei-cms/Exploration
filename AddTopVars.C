#include "NtupleClassAddTopVars.h"

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

    bool do_skim(false) ;
    if ( argc > 4 ) {
       if ( strcmp( argv[4], "skim" ) == 0 ) {
          printf("\n\n Will skim the output.\n\n") ;
          do_skim = true ;
       }
    }

    char command[1000] ;
    sprintf( command, "eos root://cmseos.fnal.gov ls %s > eos-files.txt", eos_dir_name ) ;
    gSystem -> Exec( command ) ;


    char file_pattern[1000] ;
    sprintf( file_pattern, "%s", argv[1] ) ;
    printf("\n\n Will load files that match %s from eos dir %s\n\n", file_pattern, eos_dir_name ) ;





    TChain* ch = new TChain( "TreeMaker2/PreSelection" ) ;

    std::ifstream ifs_files ;
    ifs_files.open( "eos-files.txt" ) ;
    while ( ifs_files.good() ) {
       TString tsline ;
       tsline.ReadLine( ifs_files ) ;
       if ( !ifs_files.good() ) break ;
       if ( tsline.Contains( file_pattern ) ) {
          char fname[1000] ;
          sscanf( tsline.Data(), "%s", fname ) ;
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

    TTree* output_tree = ch -> CloneTree( 0 ) ;
    
    NtupleClassAddTopVars t = NtupleClassAddTopVars( ch, output_tree, do_skim );
    t.Loop();


    myfile->Close();

    return 0;
}
