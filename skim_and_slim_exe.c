//#include "skim_and_slim.h"
#include "skim_and_slim.c"

#include "TH1D.h"
#include "TFile.h"

#include "TSystem.h"
#include <fstream>

#include<iostream>

using std::ifstream ;

int main(int argc, char *argv[])
{

   //                         1           2         3             4                 5         6                7                  8
   //--- expected arguments:  <ds-name>   <nfiles>  <first-file>  <file-list-file>  <skim?>   <lepton_skim?>   <dilepton_skim?>   <trigfile>
   //

    printf("\n\n argc is %d\n\n", argc ) ;
    for ( int i=1; i<argc; i++ ) {
       printf("  arg %d : %s\n", i, argv[i] ) ;
    }
    printf("\n\n") ;

    if (argc == 1)
    {
        printf("\n\n") ;
        printf("                         1           2         3             4                 5         6                7                  8\n") ;
        printf("--- expected arguments:  <ds-name>   <nfiles>  <first-file>  <file-list-file>  <skim?>   <lepton_skim?>   <dilepton_skim?>   <trigfile>\n") ;
        printf("\n") ;
        printf("  example:\n\n") ;
        printf("    slim_and_skim_exe   Data_SingleMuon  5  0  skim  lepton_skim  false  skim-slim-trigs-mu.txt\n\n") ;
        return 0;
    }


    char dsname[1000] ;
    if ( argc > 1 ) {
       sprintf( dsname, "%s", argv[1] ) ;
       printf("   Dataset: %s\n", dsname ) ;
    } else {
       printf("\n\n *** I need a dataset name.\n\n" ) ; return -1 ;
    }

    int nfiles(1) ;
    if ( argc > 2 ) {
       sscanf( argv[2], "%d", &nfiles ) ;
       printf("   Number of input files to run on : %d\n", nfiles ) ;
    } 

    int first_file(0) ;
    if ( argc > 3 ) {
       sscanf( argv[3], "%d", &first_file ) ;
       printf("   First file to run on : %d\n", first_file ) ;
    } 

    char flistfile[1000] ;
    if ( argc > 4 ) {
       sprintf( flistfile, "%s", argv[4] ) ;
    } else {
       printf("\n\n *** I need a file list file.\n\n") ; return -1 ;
    }





    TChain* tt_in = new TChain( "TreeMaker2/PreSelection" ) ;



    printf("\n Opening input file list file : %s\n", argv[4] ) ;

    ifstream ifs ;

    ifs.open( flistfile ) ;
    if ( !ifs.good() ) { printf("\n\n *** can't open %s\n\n", flistfile ) ; return -1 ; } 
    int file_ind(0) ;
    int files_loaded(0) ;
    while ( ifs.good() ) {
       TString tsline ;
       tsline.ReadLine( ifs ) ;
       if ( !ifs.good() ) break ;
       if ( file_ind >= first_file && file_ind < (first_file+nfiles) ) {
          printf( "  %5d %5d : Adding file to chain : %s\n", file_ind, files_loaded, tsline.Data() ) ;
          int n_added = tt_in -> Add( tsline ) ;
          files_loaded ++ ;
       }
       file_ind ++ ;
       if ( file_ind >= first_file+nfiles ) break ;
    }
    if ( files_loaded < nfiles ) {
       printf("\n\n *** Warning : only loaded %d files, not %d\n\n", files_loaded, nfiles ) ;
    }
    Long64_t n_entries = tt_in -> GetEntries() ;
    if ( n_entries <= 0 ) {
       printf("\n\n *** No entries in input chain?  %lld\n\n", n_entries ) ; return -1 ;
    } else {
       printf("\n\n  Total number of entries in the input chain : %lld\n", n_entries ) ;
    }


    char cmd[1000] ;
    sprintf( cmd, "mkdir -p output-files/%s", dsname ) ;
    gSystem -> Exec( cmd ) ;


    char outfile[1000] ;
    //////sprintf( outfile, "output-files/%s/skimandslim_%s_%d.root", dsname, dsname, first_file ) ;
    sprintf( outfile, "skimandslim_%s_%d.root", dsname, first_file ) ;
    printf("\n  Output file : %s\n\n", outfile ) ;




    bool do_skim(false) ;
    if ( argc > 5 ) {
       if ( strcmp( argv[5], "skim" ) == 0 ) {
          printf("\n\n Will skim the output.\n\n") ;
          do_skim = true ;
       }
    }

    bool lepton_skim(false) ;
    if ( argc > 6 ) {
       if ( strcmp( argv[6], "lepton_skim" ) == 0 ) {
          printf("\n\n Lepton skim is true.\n\n") ;
          lepton_skim = true ;
       }
    }

    bool dilepton_skim(false) ;
    if ( argc > 7 ) {
       if ( strcmp( argv[7], "dilepton_skim" ) == 0 ) {
          printf("\n\n Dilepton skim is true.\n\n") ;
          dilepton_skim = true ;
       }
    }

    char trigfile[1000] ;
    if ( argc > 8 ) {
       sprintf( trigfile, "%s", argv[8] ) ;
       printf("  trigger names file : %s\n", trigfile ) ;
    } else {
       sprintf( trigfile, "skim-slim-trigs.txt" ) ;
    }

    skim_and_slim( tt_in, outfile, do_skim, lepton_skim, dilepton_skim, trigfile ) ;



    return 0;
}
