#include "NtupleClassAddTopVars.h"

#include "TH1D.h"
#include "TFile.h"

#include "TSystem.h"
#include <fstream>

#include<iostream>

int main(int argc, char *argv[])
{


    printf("\n\n argc is %d\n\n", argc ) ;
    for ( int i=1; i<argc; i++ ) {
       printf("  arg %d : %s\n", i, argv[i] ) ;
    }
    printf("\n\n") ;

    if (argc == 1)
    {
        std::cout << "Please provide a file to run over" << std::endl;
        return 0;
    }


    char fnamewithpath[10000] ;
    sprintf( fnamewithpath, "root://cmsxrootd.fnal.gov/%s", argv[1] ) ;

    std::string outfile = "mytest.root";
    if (argc > 2)
    {
        outfile = argv[2];
    } 

    bool do_skim(false) ;
    if ( argc > 3 ) {
       if ( strcmp( argv[3], "skim" ) == 0 ) {
          printf("\n\n Will skim the output.\n\n") ;
          do_skim = true ;
       }
    }



    printf("  Adding file %s\n", fnamewithpath ) ;
    TChain* ch = new TChain( "TreeMaker2/PreSelection" ) ;
    ch -> Add( fnamewithpath ) ;
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
