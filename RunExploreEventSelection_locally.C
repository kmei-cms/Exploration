#include "ExploreEventSelection.h"

#include "TH1D.h"
#include "TFile.h"

#include "TSystem.h"
#include <fstream>

#include<iostream>

int main(int argc, char *argv[])
{

    TChain* ch = new TChain( "TreeMaker2/PreSelection" ) ;
    ch -> Add( "file:/uscms/homes/k/kmei91/PrivateSamples.stealth_stop_650_singlino_SHuHd_0_RA2AnalysisTree.root" ) ;
    
    int nentries = ch->GetEntries() ;
    printf("\n\n Number of entries %d\n\n", nentries ) ;
    if ( nentries <= 0 ) { printf("\n\n Nothing to do.\n\n") ; gSystem->Exit(-1) ; }


    TFile* myfile = TFile::Open("temp.root", "RECREATE");
    
    bool isQuiet = true;
    ExploreEventSelection t = ExploreEventSelection( ch );
    t.InitHistos();
    t.Loop(1.0, -1, "", "",isQuiet);
    t.WriteHistos();

    myfile->Close();

    return 0;
}
