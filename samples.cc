#include "samples.h"

#include <iostream>
#include <cstdio>
#include <cstring>

namespace AnaSamples
{
    void FileSummary::readFileList() const
    {
        if(filelist_.size()) filelist_.clear();
        
        FILE *f = fopen(filePath.c_str(), "r");
        char buff[512];
        if(f)
        {
            while(!feof(f) && fgets(buff, 512, f))
            {
                for(char* k = strchr(buff, '\n'); k != 0; k = strchr(buff, '\n')) *k = '\0';
                filelist_.push_back(buff);
            }
            fclose(f);
        }
        else std::cout << "Filelist file \"" << filePath << "\" not found!!!!!!!" << std::endl;
    }

    void FileSummary::addCollection(std::string colName)
    {
        collections_.insert(colName);
    }

    std::map<std::string, FileSummary>& SampleSet::getMap()
    {
        return sampleSet_;
    }
    
    SampleSet::SampleSet(std::string fDir, double lumi) : fDir_(fDir), lumi_(lumi)
    {
        // ---------------
        // - backgrounds -
        // ---------------

        // branching ratio info from PDG
        double W_Lept_BR = 0.1086*3;
        double W_Had_BR = 1 - W_Lept_BR;
        double TTbar_SingleLept_BR = 0.43930872; // 2*W_Lept_BR*(1-W_Lept_BR)
        double TTbar_DiLept_BR = 0.10614564; // W_Lept_BR^2

        if(fDir.compare("condor") == 0)
        {
            // For condor jobs we copy the filelist locally, so no need to point to eos for that
            fDir_ = "";
        }

        //TTbar samples
        // TTbarInc has LO xsec on McM : 502.20 pb. The NNLO is 831.76 pb. The k-factor for ttbar is: kt = 831.76/502.20 ~ 1.656233    
        // Calculated from PDG BRs'. Not from the kt * xSec in McM
        //addSample("TTbarDiLep",         "filelists/TTbarDiLep.txt",         "TreeMaker2/PreSelection", 831.76*TTbar_DiLept_BR,         lumi, 30444678, 1.0, kGreen);
        //addSample("TTbarSingleLepT",    "filelists/TTbarSingleLepT.txt",    "TreeMaker2/PreSelection", 831.76*0.5*TTbar_SingleLept_BR, lumi, 61901450, 1.0, kGreen);
        //addSample("TTbarSingleLepTbar", "filelists/TTbarSingleLepTbar.txt", "TreeMaker2/PreSelection", 831.76*0.5*TTbar_SingleLept_BR, lumi, 59860282, 1.0, kGreen);
        addSample("TT", "filelists/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8.txt", "TreeMaker2/PreSelection", 831.76, lumi, 155087467, 1.0, kGreen);

        // From https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#W_jets, kw = 1.21
        addSample("WJetsToLNu_HT-70to100",    "filelists/WJetsToLNu_HT-70To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.txt",    "TreeMaker2/PreSelection", 1319,    lumi, 10094300,  1.21, kMagenta+1);
        addSample("WJetsToLNu_HT-100to200",   "filelists/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.txt",   "TreeMaker2/PreSelection", 1345,    lumi, 79356685,  1.21, kMagenta+1);
        addSample("WJetsToLNu_HT-200to400",   "filelists/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.txt",   "TreeMaker2/PreSelection", 359.7,   lumi, 39332650,  1.21, kMagenta+1);
        addSample("WJetsToLNu_HT-400to600",   "filelists/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.txt",   "TreeMaker2/PreSelection", 48.91,   lumi, 7759701,   1.21, kMagenta+1);
        addSample("WJetsToLNu_HT-600to800",   "filelists/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.txt",   "TreeMaker2/PreSelection", 12.05,   lumi, 18687480,  1.21, kMagenta+1);
        addSample("WJetsToLNu_HT-800to1200",  "filelists/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.txt",  "TreeMaker2/PreSelection", 5.501,   lumi, 7745467,   1.21, kMagenta+1);
        addSample("WJetsToLNu_HT-1200to2500", "filelists/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.txt", "TreeMaker2/PreSelection", 1.329,   lumi, 6872441,   1.21, kMagenta+1);
        addSample("WJetsToLNu_HT-2500toInf",  "filelists/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.txt",  "TreeMaker2/PreSelection", 0.03216, lumi, 2637821,   1.21, kMagenta+1);
        
        //Z -> nunu
        // From https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#DY_Z, kz = 1.23
        //addSample("ZJetsToNuNu_HT_100to200",   "filelists/ZJetsToNuNu_HT_100to200.txt",   "TreeMaker2/PreSelection", 280.35,    lumi, 24121326, 1.23*0.856710,  kTeal+4);
        //addSample("ZJetsToNuNu_HT_200to400",   "filelists/ZJetsToNuNu_HT_200to400.txt",   "TreeMaker2/PreSelection", 77.67,     lumi, 24663714, 1.23*0.856710,  kTeal+4);
        //addSample("ZJetsToNuNu_HT_400to600",   "filelists/ZJetsToNuNu_HT_400to600.txt",   "TreeMaker2/PreSelection", 10.73,     lumi, 9862869,  1.23*0.856710,  kTeal+4);
        //addSample("ZJetsToNuNu_HT_600to800",   "filelists/ZJetsToNuNu_HT_600to800.txt",   "TreeMaker2/PreSelection", 0.853*3,   lumi, 5611895,  1.23*0.856710,  kTeal+4);
        //addSample("ZJetsToNuNu_HT_800to1200",  "filelists/ZJetsToNuNu_HT_800to1200.txt",  "TreeMaker2/PreSelection", 0.394*3,   lumi, 2100324,  1.23*0.856710,  kTeal+4);
        //addSample("ZJetsToNuNu_HT_1200to2500", "filelists/ZJetsToNuNu_HT_1200to2500.txt", "TreeMaker2/PreSelection", 0.0974*3,  lumi, 513471,   1.23*0.856710,  kTeal+4);
        //addSample("ZJetsToNuNu_HT_2500toInf",  "filelists/ZJetsToNuNu_HT_2500toInf.txt",  "TreeMaker2/PreSelection", 0.00230*3, lumi, 405030,   1.23*0.856710,  kTeal+4);
       
        //QCD
        // Ref. https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#QCD. But numbers are from McM.
        //addSample("QCD_HT100to200"  , "filelists/QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.txt"  ,"TreeMaker2/PreSelection", 27540000, lumi, 80547699, 1.0,  kBlue);
        addSample("QCD_HT200to300"  , "filelists/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.txt"  ,"TreeMaker2/PreSelection", 1712000 , lumi, 57580393 , 1.0,  kBlue);
        addSample("QCD_HT300to500"  , "filelists/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.txt"  ,"TreeMaker2/PreSelection", 347700  , lumi, 54537903 , 1.0,  kBlue);
        addSample("QCD_HT500to700"  , "filelists/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.txt"  ,"TreeMaker2/PreSelection", 32100   , lumi, 62271343 , 1.0,  kBlue);
        addSample("QCD_HT700to1000" , "filelists/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.txt" ,"TreeMaker2/PreSelection", 6831    , lumi, 45412780 , 1.0,  kBlue);
        addSample("QCD_HT1000to1500", "filelists/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.txt","TreeMaker2/PreSelection", 1207    , lumi, 15127293 , 1.0,  kBlue);
        addSample("QCD_HT1500to2000", "filelists/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.txt","TreeMaker2/PreSelection", 119.9   , lumi, 11826702 , 1.0,  kBlue);
        addSample("QCD_HT2000toInf" , "filelists/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.txt" ,"TreeMaker2/PreSelection", 25.24   , lumi, 6039005 , 1.0,  kBlue);


        addSample("QCD_HT200to300_BGenFilter"  , "filelists/QCD_HT200to300_BGenFilter_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.txt"  ,"TreeMaker2/PreSelection", 156500, lumi, 8258754 , 1.0,  kBlue);
        addSample("QCD_HT300to500_BGenFilter"  , "filelists/QCD_HT300to500_BGenFilter_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.txt"  ,"TreeMaker2/PreSelection", 38970, lumi,  6046724 , 1.0,  kBlue);
        addSample("QCD_HT500to700_BGenFilter"  , "filelists/QCD_HT500to700_BGenFilter_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.txt"  ,"TreeMaker2/PreSelection", 4150, lumi,  7076024 , 1.0,  kBlue);
        addSample("QCD_HT700to1000_BGenFilter" , "filelists/QCD_HT700to1000_BGenFilter_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.txt" ,"TreeMaker2/PreSelection", 1000, lumi,  2869662 , 1.0,  kBlue);
        addSample("QCD_HT1000to1500_BGenFilter", "filelists/QCD_HT1000to1500_BGenFilter_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.txt","TreeMaker2/PreSelection", 184.4, lumi,  834688 , 1.0,  kBlue);
        addSample("QCD_HT1500to2000_BGenFilter", "filelists/QCD_HT1500to2000_BGenFilter_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.txt","TreeMaker2/PreSelection", 21.31, lumi,  240962 , 1.0,  kBlue);
        addSample("QCD_HT2000toInf_BGenFilter" , "filelists/QCD_HT2000toInf_BGenFilter_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.txt" ,"TreeMaker2/PreSelection", 4.16, lumi,   136826 , 1.0,  kBlue);


        //Other Samples
        // Aprox. NNLO
        addSample("ST_tW_top", "filelists/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1.txt", "TreeMaker2/PreSelection", 35.6, lumi, 6952830,  1.0,  kYellow);
        addSample("ST_tW_antitop", "filelists/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1.txt", "TreeMaker2/PreSelection", 35.6, lumi, 6933094,  1.0,  kYellow);
        //addSample("ST_s-channel", "filelists/ST_s-channel_4f_InclusiveDecays_13TeV-amcatnlo-pythia8.txt", "TreeMaker2/PreSelection", 10.32,  lumi, 2989199,  1.0,  kYellow); // apparently no neg weights after all..
        addSample("ST_t-channel_top", "filelists/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1.txt", "TreeMaker2/PreSelection", 136.02, lumi, 66559176,  1.0,  kYellow);
        addSample("ST_t-channel_antitop", "filelists/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1.txt", "TreeMaker2/PreSelection", 80.95,  lumi, 37834984,  1.0,  kYellow);

        //addSample("tZq_W_lept_Z_hadron",    "filelists/tZq_W_lept_Z_hadron_4f_ckm_NLO_13TeV_amcatnlo_pythia8.txt",    "TreeMaker2/PreSelection", 0.0758,  lumi, 9177845 - 5331675,  1.0,  kYellow); // 970479 again seems to have no negative weights..
        
        // NLO --> negative weights!
        // (sign of gen weight) * (lumi*xsec)/(effective number of events): effective number of events = N(evt) with positive weight - N(evt) with negative weight
        //addSample("TTZToLLNuNu", "filelists/TTZToLLNuNu.txt", "TreeMaker2/PreSelection", 0.2529, lumi, 1416634 - 516458,  1.0,  kOrange+2);
        //addSample("TTZToQQ",     "filelists/TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.txt",          "TreeMaker2/PreSelection", 0.5297, lumi, 435723 - 157814,  1.0,  kOrange+2); // 749400

        // NLO --> negative weights!
        //addSample("TTWJetsToLNu", "filelists/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.txt", "TreeMaker2/PreSelection", 0.2043, lumi, 3998407 - 1282158,   1.0,  kSpring+2); // 5280565
        //addSample("TTWJetsToQQ",  "filelists/TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.txt",  "TreeMaker2/PreSelection", 0.4062, lumi, 631804 - 201494,  1.0,  kSpring+2); // 833298

        addSample("TTHH",  "filelists/TTHH_TuneCUETP8M2T4_13TeV-madgraph-pythia8.txt",  "TreeMaker2/PreSelection", 0.000741, lumi, 100000,  1.0,  kSpring+2);
        //addSample("TTTT",  "filelists/TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.txt",  "TreeMaker2/PreSelection", 0.009103, lumi, 2456040,  1.0,  kSpring+2); // doesn't actually have negative weights! probably a madgraph sample rather than amcatnlo
        addSample("TTTW",  "filelists/TTTW_TuneCUETP8M2T4_13TeV-madgraph-pythia8.txt",  "TreeMaker2/PreSelection", 0.000861, lumi, 97232,  1.0,  kSpring+2);
        addSample("TTWH",  "filelists/TTWH_TuneCUETP8M2T4_13TeV-madgraph-pythia8.txt",  "TreeMaker2/PreSelection", 0.001360, lumi, 100000,  1.0,  kSpring+2);
        addSample("TTWW",  "filelists/TTWW_TuneCUETP8M2T4_13TeV-madgraph-pythia8.txt",  "TreeMaker2/PreSelection", 0.007834, lumi, 98692,  1.0,  kSpring+2);
        addSample("TTWZ",  "filelists/TTWZ_TuneCUETP8M2T4_13TeV-madgraph-pythia8.txt",  "TreeMaker2/PreSelection", 0.002970, lumi, 99142,  1.0,  kSpring+2);
        addSample("TTZH",  "filelists/TTZH_TuneCUETP8M2T4_13TeV-madgraph-pythia8.txt",  "TreeMaker2/PreSelection", 0.001250, lumi, 97855,  1.0,  kSpring+2);
        addSample("TTZZ",  "filelists/TTZZ_TuneCUETP8M2T4_13TeV-madgraph-pythia8.txt",  "TreeMaker2/PreSelection", 0.001570, lumi, 98713,  1.0,  kSpring+2);

        // NLO --> negative weights!  
        //addSample("TTGJets", "filelists/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.txt", "TreeMaker2/PreSelection", 3.697, lumi, 3224372 - 1646539,  1.0,  kOrange+2); //4870911
        //addSample("TTGamma_Hadronic", "filelists/TTGamma_Hadronic_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.txt", "TreeMaker2/PreSelection", 0.794, lumi, 3224372 - 1646539,  1.0,  kOrange+2); // 4966500

        // ttH 
        //addSample("ttHJetTobb",    "filelists/ttHJetTobb_M125_13TeV_amcatnloFXFX_madspin_pythia8.txt",   "TreeMaker2/PreSelection", 0.2953,  lumi, 3809292 - 36700,   1.0,  kOrange+2); // 9794226
        //addSample("ttHJetToNonbb", "filelists/ttHJetToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_mWCutfix.txt", "TreeMaker2/PreSelection", 0.2118,  lumi, 3943524 - 37726,  1.0,  kOrange+2); // 10045633

        // Di-boson
        // Ref. https://indico.cern.ch/event/439995/session/0/contribution/6/attachments/1143460/1638648/diboson_final.pdf (NNLO is given)
        addSample("WW", "filelists/WW_TuneCUETP8M1_13TeV-pythia8.txt", "TreeMaker2/PreSelection", 51.723,  lumi, 7981136,  1.0,  kViolet+4); 
        
        // Ref. https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns (NLO from MCFM)
        addSample("WZ", "filelists/WZ_TuneCUETP8M1_13TeV-pythia8.txt", "TreeMaker2/PreSelection", 47.13,  lumi, 3995828,  1.0,  kViolet+4);
        addSample("ZZ", "filelists/ZZ_TuneCUETP8M1_13TeV-pythia8.txt", "TreeMaker2/PreSelection", 16.523, lumi, 1988098,  1.0,  kViolet+4);
        
        // Tri-boson: negative weights!
        //addSample("WWW", "filelists/WWW.txt", "TreeMaker2/PreSelection", 0.2086,  lumi, 225269 - 14731,  1.0,  kViolet+2);
        //addSample("WWZ", "filelists/WWZ.txt", "TreeMaker2/PreSelection", 0.1651,  lumi, 235734 - 14266,  1.0,  kViolet+2);
        //addSample("WZZ", "filelists/WZZ.txt", "TreeMaker2/PreSelection", 0.05565, lumi, 231583 - 15217,  1.0,  kViolet+2);
        //addSample("ZZZ", "filelists/ZZZ.txt", "TreeMaker2/PreSelection", 0.01398, lumi, 231217 - 18020,  1.0,  kViolet+2);
        //addSample("WZG", "filelists/WZG.txt", "TreeMaker2/PreSelection", 0.04123, lumi, 921527 - 76673,  1.0,  kViolet+2);
        //addSample("WWG", "filelists/WWG.txt", "TreeMaker2/PreSelection", 0.2147 , lumi, 913515 - 85885,  1.0,  kViolet+2);

        // --------
        // - data -
        // --------
        //addSample("Data_MET_2016", "filelists/Data_MET_2016.txt","TreeMaker2/PreSelection",  (5787968233.150 + 2573399420.069 + 4248383597.366 + 4008663475.924 + 3101618402.006 + 7540487746.602 + 8390540442.688 + 215149415.251)/1000000., 1.0,  kBlack);

        // ----------
        // - signal -
        // ----------

        // cross lumi number of events 
        addSample("rpv_stop_350",  "filelists/R2_rpv_stop_350_t3j_uds.txt",  "TreeMaker2/PreSelection", 3.78661 , lumi,  69543, 1.0, kRed, true);
        addSample("rpv_stop_450",  "filelists/R2_rpv_stop_450_t3j_uds.txt",  "TreeMaker2/PreSelection", 0.948333 , lumi, 64566, 1.0, kRed, true);
        addSample("rpv_stop_550",  "filelists/R2_rpv_stop_550_t3j_uds.txt",  "TreeMaker2/PreSelection", 0.296128 , lumi, 61287, 1.0, kRed, true);
        addSample("rpv_stop_650",  "filelists/R2_rpv_stop_650_t3j_uds.txt",  "TreeMaker2/PreSelection", 0.107045 , lumi, 59334, 1.0, kRed, true);
        addSample("rpv_stop_750",  "filelists/R2_rpv_stop_750_t3j_uds.txt",  "TreeMaker2/PreSelection", 0.0431418, lumi, 58016, 1.0, kRed, true);
        addSample("rpv_stop_850",  "filelists/R2_rpv_stop_850_t3j_uds.txt",  "TreeMaker2/PreSelection", 0.0189612, lumi, 57069, 1.0, kRed, true);

        addSample("stealth_stop_350_SHuHd",  "filelists/R2_stealth_stop_350_singlino_SHuHd.txt",  "TreeMaker2/PreSelection", 3.78661, lumi, 72270, 1.0, kRed, true);
        addSample("stealth_stop_450_SHuHd",  "filelists/R2_stealth_stop_450_singlino_SHuHd.txt",  "TreeMaker2/PreSelection", 0.948333, lumi, 66340, 1.0, kRed, true);
        addSample("stealth_stop_550_SHuHd",  "filelists/R2_stealth_stop_550_singlino_SHuHd.txt",  "TreeMaker2/PreSelection", 0.296128, lumi, 63399, 1.0, kRed, true);
        addSample("stealth_stop_650_SHuHd",  "filelists/R2_stealth_stop_650_singlino_SHuHd.txt",  "TreeMaker2/PreSelection", 0.107045, lumi, 61442, 1.0, kRed, true);
        addSample("stealth_stop_750_SHuHd",  "filelists/R2_stealth_stop_750_singlino_SHuHd.txt",  "TreeMaker2/PreSelection", 0.0431418, lumi, 59992, 1.0, kRed, true);
        addSample("stealth_stop_850_SHuHd",  "filelists/R2_stealth_stop_850_singlino_SHuHd.txt",  "TreeMaker2/PreSelection", 0.0189612, lumi, 59737, 1.0, kRed, true);

        addSample("stealth_stop_350_SYY",  "filelists/R2_stealth_stop_350_singlino_SYY.txt",  "TreeMaker2/PreSelection", 3.78661, lumi, 71695, 1.0, kRed, true);
        addSample("stealth_stop_450_SYY",  "filelists/R2_stealth_stop_450_singlino_SYY.txt",  "TreeMaker2/PreSelection", 0.948333, lumi, 66250, 1.0, kRed, true);
        addSample("stealth_stop_550_SYY",  "filelists/R2_stealth_stop_550_singlino_SYY.txt",  "TreeMaker2/PreSelection", 0.296128, lumi, 63434, 1.0, kRed, true);
        addSample("stealth_stop_650_SYY",  "filelists/R2_stealth_stop_650_singlino_SYY.txt",  "TreeMaker2/PreSelection", 0.107045, lumi, 62097, 1.0, kRed, true);
        addSample("stealth_stop_750_SYY",  "filelists/R2_stealth_stop_750_singlino_SYY.txt",  "TreeMaker2/PreSelection", 0.0431418, lumi, 60023, 1.0, kRed, true);
        addSample("stealth_stop_850_SYY",  "filelists/R2_stealth_stop_850_singlino_SYY.txt",  "TreeMaker2/PreSelection", 0.0189612, lumi, 59107, 1.0, kRed, true);

    }

    SampleCollection::SampleCollection(SampleSet& samples)
    {
        //Define sets of samples for later use
        addSampleSet(samples, "TT", {"TT"});

        addSampleSet(samples, "WJetsToLNu", {"WJetsToLNu_HT_2500toInf", "WJetsToLNu_HT_1200to2500", "WJetsToLNu_HT_800to1200", "WJetsToLNu_HT_600to800", "WJetsToLNu_HT_400to600", "WJetsToLNu_HT_200to400", "WJetsToLNu_HT_100to200", "WJetsToLNu_HT_70to100"});

        addSampleSet(samples, "QCD", {"QCD_HT2000toInf", "QCD_HT1500to2000", "QCD_HT1000to1500", "QCD_HT700to1000", "QCD_HT500to700", "QCD_HT300to500", "QCD_HT200to300"});

        addSampleSet(samples, "ST", {"ST_tW_top", "ST_tW_antitop", /*"ST_s",*/ "ST_t-channel_top", "ST_t-channel_antitop"});

        addSampleSet(samples, "Diboson", {"WW", "WZ", "ZZ"});

        addSampleSet(samples, "Rare", {"TTHH", "TTTW", "TTWH", "TTWW", "TTWZ", "TTZH", "TTZZ"});

        addSampleSet(samples, "ALL_MC", {});

        //addSampleSet(samples, "Data_MET", {"Data_MET_2016"});

        addSampleSet(samples, "AllSignal", {"rpv_stop_350","rpv_stop_450","rpv_stop_550","rpv_stop_650","rpv_stop_750","rpv_stop_850",
                    "stealth_stop_350_SHuHd","stealth_stop_450_SHuHd","stealth_stop_550_SHuHd","stealth_stop_650_SHuHd","stealth_stop_750_SHuHd","stealth_stop_850_SHuHd", 
                    "stealth_stop_350_SYY","stealth_stop_450_SYY","stealth_stop_550_SYY","stealth_stop_650_SYY","stealth_stop_750_SYY","stealth_stop_850_SYY", 
                    });

    }

// if name contains the keyword "ALL", then:
// ] vss serves as a SKIPPING list and support keyword matching!
// ] if has "MC" --> refer to all fullsim MC
// ] if has "fastsim" --> refer to all fastsim
// ] if has "Data" --> refer to all data
    void SampleCollection::addSampleSet(SampleSet& samples, std::string name, std::vector<std::string> vss)
    {
        if(vss.size() > 1)
        {
            for(std::string& sn : vss)
            {
                if(sn.compare(name) == 0)
                {
                    std::cout << "You have named a sampleCollection the same as one of its member sampleSets, but it has more than one sampleSet!!!! This is bad!!!  Stop!!! Stop now!!!  This collection will be skipped until it is properly named." << std::endl;
                    return;
                }
            }
        }

        auto& map = samples.getMap();

// if keyword "ALL" appears, by-passing the regular adding procedure...
        if( name.find("ALL") != std::string::npos )
        {
           bool incl_fullsim = false;
           bool incl_fastsim = false;
           bool incl_Data = false;
           if( name.find("MC") != std::string::npos ) incl_fullsim = true;
           if( name.find("fastsim") != std::string::npos ) incl_fastsim = true;
           if( name.find("Data") != std::string::npos ) incl_Data = true;
           if( !incl_fullsim && !incl_fastsim && !incl_Data )
           {
              std::cout<<"WARNING ... will not add any samples with your requests ..."<<std::endl;
              return;
           }
           for(auto im : map)
           {
              std::string persn = im.first;
              bool excluded = false;
              for(std::string & exc_sn : vss )
              {
                 if( persn.find(exc_sn) != std::string::npos ){ excluded = true; break; }
              }
              if( excluded ) continue;
              if( !incl_fastsim && persn.find("fastsim") != std::string::npos ) continue;
              if( !incl_Data && persn.find("Data") != std::string::npos ) continue;
              im.second.addCollection(name);
              sampleSet_[name].push_back(im.second);
              nameVec_[name].push_back(im.first);
              totalLumiMap_[name] += im.second.lumi;
           }
           return;
        }

        for(std::string& sn : vss)
        {
            map[sn].addCollection(name);
            sampleSet_[name].push_back(samples[sn]);
            nameVec_[name].push_back(sn);
            totalLumiMap_[name] += samples[sn].lumi;
        }
    }

    std::vector<std::string>& SampleCollection::getSampleLabels(std::string name)
    {
        return nameVec_[name];
    }

    bool operator< (const FileSummary& lhs, const FileSummary& rhs)
    {
        return lhs.filePath < rhs.filePath || lhs.treePath < rhs.treePath;
    }

    bool operator== (const FileSummary& lhs, const FileSummary& rhs)
    {
        return lhs.filePath == rhs.filePath && lhs.treePath == rhs.treePath && lhs.xsec == rhs.xsec && lhs.lumi == rhs.lumi && lhs.kfactor == rhs.kfactor && lhs.nEvts == rhs.nEvts;
    }

    bool operator!= (const FileSummary& lhs, const FileSummary& rhs)
    {
        return !(lhs == rhs);
    }
}
