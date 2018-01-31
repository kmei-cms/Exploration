#include "ExploreBackground.h"

#include "TH1D.h"
#include "TFile.h"

#include<iostream>

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        std::cout << "Please provide a filename to run over" << std::endl;
        return 0;
    }
    // Read file
    std::string infile = argv[1];
    //std::string infile = "Summer16_private.stealth_stop_350_singlino_SHuHd_1_RA2AnalysisTree.root"; 
    std::cout << "Reading file " << infile << std::endl;

    TFile* myinfile = TFile::Open(infile.c_str());
    TTree* mytree = (TTree*) myinfile->Get("TreeMaker2/PreSelection");

    std::string outfile = "mytest.root";
    if (argc > 2)
    {
        outfile = argv[2];
    } 
    double weight = 1.0;
    if (argc > 3)
    {
        weight = atof(argv[3]);
    }

    TFile* myfile = TFile::Open(outfile.c_str(), "RECREATE");

    std::string type = "";
    if(infile.find("qcd") != std::string::npos)
        type = "qcd";
    
    ExploreBackground t = ExploreBackground(mytree);
    t.InitHistos();
    t.Loop(type, weight);
    t.WriteHistos();


    myfile->Close();

    return 0;
}
