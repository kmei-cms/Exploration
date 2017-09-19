#include "NtupleClass.h"

#include "TH1D.h"
#include "TFile.h"

#include<iostream>

int main()
{
    // Read file
    std::string infile = "Summer16_private.stealth_stop_350_singlino_SHuHd_1_RA2AnalysisTree.root"; 
    std::cout << "Reading file " << infile << std::endl;

    TFile* myinfile = TFile::Open(infile.c_str());
    TTree* mytree = (TTree*) myinfile->Get("TreeMaker2/PreSelection");

    TFile* myfile = TFile::Open("mytest.root", "RECREATE");

    
    NtupleClass t = NtupleClass(mytree);
    t.Loop();


    myfile->Close();

    return 0;
}
