#define NtupleClass_cxx
#include "NtupleClass.h"
#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TEfficiency.h>
#include <iostream>

//mandatory includes to use top tagger
#include "TopTagger/TopTagger/include/TopTagger.h"
#include "TopTagger/TopTagger/include/TopTaggerResults.h"
#include "TopTagger/TopTagger/include/TopTaggerUtilities.h"
#include "TopTagger/CfgParser/include/TTException.h"


double calcDPhi(double phi1, double phi2)
{
    double dphi = phi1 - phi2 ;
    if ( dphi >  3.14159265 ) dphi -= 2*3.14159265 ;
    if ( dphi < -3.14159265 ) dphi += 2*3.14159265 ;
    return dphi;
}

double calcDR(double eta1, double eta2, double phi1, double phi2)
{
    double deta = fabs( eta1 - eta2 ) ;
    
    double dphi = phi1 - phi2 ;
    if ( dphi > 3.1415926 ) dphi -= 2*3.1415926 ;
    if ( dphi <-3.1415926 ) dphi += 2*3.1415926 ;
    
    return sqrt( dphi*dphi + deta*deta ) ;
}

void NtupleClass::Loop()
{
//   In a ROOT session, you can do:
//      root> .L NtupleClass.C
//      root> NtupleClass t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;

   // -----------------------
   // make some histograms
   // -----------------------
   TH1D *myHisto  = new TH1D("njets","njets", 20, 0, 20);
   TH1D *h_ntops  = new TH1D("h_ntops","h_ntops", 5, 0, 5);
   TH1D *h_ntops_3jet  = new TH1D("h_ntops_3jet","h_ntops_3jet", 5, 0, 5);
   TH1D *h_ntops_2jet  = new TH1D("h_ntops_2jet","h_ntops_2jet", 5, 0, 5);
   TH1D *h_ntops_1jet  = new TH1D("h_ntops_1jet","h_ntops_1jet", 5, 0, 5);
   TH1D *h_baseline_ntops  = new TH1D("h_baseline_ntops","h_baseline_ntops", 5, 0, 5);
   TH1D *h_baseline_ntops_3jet  = new TH1D("h_baseline_ntops_3jet","h_baseline_ntops_3jet", 5, 0, 5);
   TH1D *h_baseline_ntops_2jet  = new TH1D("h_baseline_ntops_2jet","h_baseline_ntops_2jet", 5, 0, 5);
   TH1D *h_baseline_ntops_1jet  = new TH1D("h_baseline_ntops_1jet","h_baseline_ntops_1jet", 5, 0, 5);

   TH1D *h_dphi_2tops  = new TH1D("dphi_2tops","dphi_2tops", 40, -4, 4);

   // -----------------------
   // Histograms without event selection (only presence of 2 hadronic gen tops
   // -----------------------
   TH2D *h_gentop_pT_daughterDR = new TH2D("h_gentop_pT_daughterDR","h_gentop_pT_daughterDR",50,0,1000,60,0,3);
   TH1D *h_gentop_pT = new TH1D("h_gentop_pT","h_gentop_pT",50,0,1000);
   TH1D *h_gentop_pT_type1 = new TH1D("h_gentop_pT_type1","h_gentop_pT_type1",50,0,1000);
   TH1D *h_gentop_pT_type2 = new TH1D("h_gentop_pT_type2","h_gentop_pT_type2",50,0,1000);
   TH1D *h_gentop_pT_type3 = new TH1D("h_gentop_pT_type3","h_gentop_pT_type3",50,0,1000);

   TH1D *h_top_gentop_minDR = new TH1D("h_top_gentop_minDR","h_top_gentop_minDR", 60, 0, 3);
   TH1D *h_top_gentop_Dpt = new TH1D("h_top_gentop_Dpt","h_top_gentop_Dpt", 50, 0, 5);
   TH2D *h_top_gentop_minDR_Dpt = new TH2D("h_top_gentop_minDR_Dpt", "h_top_gentop_minDR_Dpt", 60, 0, 3, 50, 0, 5);

   TH1D *h_top_3jet_gentop_minDR = new TH1D("h_top_3jet_gentop_minDR","h_top_3jet_gentop_minDR", 60, 0, 3);
   TH1D *h_top_3jet_gentop_Dpt = new TH1D("h_top_3jet_gentop_Dpt","h_top_3jet_gentop_Dpt", 50, 0, 5);
   TH2D *h_top_3jet_gentop_minDR_Dpt = new TH2D("h_top_3jet_gentop_minDR_Dpt", "h_top_3jet_gentop_minDR_Dpt", 60, 0, 3, 50, 0, 5);
   TH1D *h_top_2jet_gentop_minDR = new TH1D("h_top_2jet_gentop_minDR","h_top_2jet_gentop_minDR", 60, 0, 3);
   TH1D *h_top_2jet_gentop_Dpt = new TH1D("h_top_2jet_gentop_Dpt","h_top_2jet_gentop_Dpt", 50, 0, 5);
   TH2D *h_top_2jet_gentop_minDR_Dpt = new TH2D("h_top_2jet_gentop_minDR_Dpt", "h_top_2jet_gentop_minDR_Dpt", 60, 0, 3, 50, 0, 5);
   TH1D *h_top_1jet_gentop_minDR = new TH1D("h_top_1jet_gentop_minDR","h_top_1jet_gentop_minDR", 60, 0, 3);
   TH1D *h_top_1jet_gentop_Dpt = new TH1D("h_top_1jet_gentop_Dpt","h_top_1jet_gentop_Dpt", 50, 0, 5);
   TH2D *h_top_1jet_gentop_minDR_Dpt = new TH2D("h_top_1jet_gentop_minDR_Dpt", "h_top_1jet_gentop_minDR_Dpt", 60, 0, 3, 50, 0, 5);

   TH1D *h_top_gentop_minDR_3jet_daughters = new TH1D("h_top_gentop_minDR_3jet_daughters", "h_top_gentop_minDR_3jet_daughters", 60, 0, 3); 
   TH1D *h_top_gentop_Dpt_3jet_daughters = new TH1D("h_top_gentop_Dpt_3jet_daughters", "h_top_gentop_Dpt_3jet_daughters", 50, 0, 5); 
   TH2D *h_top_gentop_minDR_Dpt_3jet_daughters = new TH2D("h_top_gentop_minDR_Dpt_3jet_daughters", "h_top_gentop_minDR_Dpt_3jet_daughters", 60, 0, 3, 50, 0, 5); 
   TH1D *h_top_gentop_topmatch_minDR_3jet_daughters = new TH1D("h_top_gentop_topmatch_minDR_3jet_daughters", "h_top_gentop_topmatch_minDR_3jet_daughters", 60, 0, 3); 
   TH1D *h_top_gentop_topmatch_Dpt_3jet_daughters = new TH1D("h_top_gentop_topmatch_Dpt_3jet_daughters", "h_top_gentop_topmatch_Dpt_3jet_daughters", 50, 0, 5); 
   TH2D *h_top_gentop_topmatch_minDR_Dpt_3jet_daughters = new TH2D("h_top_gentop_topmatch_minDR_Dpt_3jet_daughters", "h_top_gentop_topmatch_minDR_Dpt_3jet_daughters", 60, 0, 3, 50, 0, 5); 

   TH1D *h_top_trijet_n_matched_constituents = new TH1D("h_top_trijet_n_matched_constituents", "h_top_trijet_n_matched_constituents", 4, -0.5, 3.5);
   TH2D *h_top_gentop_minDR_Dpt_anymatch = new TH2D("h_top_gentop_minDR_Dpt_anymatch", "h_top_gentop_minDR_Dpt_anymatch", 60, 0, 3, 50, 0, 5);
   TH2D *h_top_gentop_minDR_Dpt_3match = new TH2D("h_top_gentop_minDR_Dpt_3match", "h_top_gentop_minDR_Dpt_3match", 60, 0, 3, 50, 0, 5);
   TH2D *h_top_gentop_minDR_Dpt_2match = new TH2D("h_top_gentop_minDR_Dpt_2match", "h_top_gentop_minDR_Dpt_2match", 60, 0, 3, 50, 0, 5);
   TH2D *h_top_gentop_minDR_Dpt_1match = new TH2D("h_top_gentop_minDR_Dpt_1match", "h_top_gentop_minDR_Dpt_1match", 60, 0, 3, 50, 0, 5);
   TH2D *h_top_gentop_minDR_Dpt_0match = new TH2D("h_top_gentop_minDR_Dpt_0match", "h_top_gentop_minDR_Dpt_0match", 60, 0, 3, 50, 0, 5);

   TH1D *h_top_gentop_discr_anymatch = new TH1D("h_top_gentop_discr_anymatch", "h_top_gentop_discr_anymatch", 40, 0.8, 1);
   TH1D *h_top_gentop_discr_3match = new TH1D("h_top_gentop_discr_3match", "h_top_gentop_discr_3match", 40, 0.8, 1);
   TH1D *h_top_gentop_discr_2match = new TH1D("h_top_gentop_discr_2match", "h_top_gentop_discr_2match", 40, 0.8, 1);
   TH1D *h_top_gentop_discr_1match = new TH1D("h_top_gentop_discr_1match", "h_top_gentop_discr_1match", 40, 0.8, 1);
   TH1D *h_top_gentop_discr_0match = new TH1D("h_top_gentop_discr_0match", "h_top_gentop_discr_0match", 40, 0.8, 1);

   TH1D *h_top_gentop_discr_anymatch_topmatch = new TH1D("h_top_gentop_discr_anymatch_topmatch", "h_top_gentop_discr_anymatch_topmatch", 40, 0.8, 1);
   TH1D *h_top_gentop_discr_3match_topmatch = new TH1D("h_top_gentop_discr_3match_topmatch", "h_top_gentop_discr_3match_topmatch", 40, 0.8, 1);
   TH1D *h_top_gentop_discr_2match_topmatch = new TH1D("h_top_gentop_discr_2match_topmatch", "h_top_gentop_discr_2match_topmatch", 40, 0.8, 1);
   TH1D *h_top_gentop_discr_1match_topmatch = new TH1D("h_top_gentop_discr_1match_topmatch", "h_top_gentop_discr_1match_topmatch", 40, 0.8, 1);
   TH1D *h_top_gentop_discr_0match_topmatch = new TH1D("h_top_gentop_discr_0match_topmatch", "h_top_gentop_discr_0match_topmatch", 40, 0.8, 1);

   TH1D *h_gentop_top_minDR     = new TH1D("h_gentop_top_minDR",     "h_gentop_top_minDR", 60, 0, 3);
   TH1D *h_gentop_top_Dpt       = new TH1D("h_gentop_top_Dpt",       "h_gentop_top_Dpt", 50, 0, 5);
   TH2D *h_gentop_top_minDR_Dpt = new TH2D("h_gentop_top_minDR_Dpt", "h_gentop_top_minDR_Dpt", 60, 0, 3, 50, 0, 5);

   TH1D *h_top_type1_matched_nsub = new TH1D("h_top_type1_matched_nsub","h_top_type1_matched_nsub",50,0,1);
   TH1D *h_top_type1_unmatched_nsub = new TH1D("h_top_type1_unmatched_nsub","h_top_type1_unmatched_nsub",50,0,1);
   TH1D *h_top_type1_matched_softdrop = new TH1D("h_top_type1_matched_softdrop","h_top_type1_matched_softdrop",60,0,300);
   TH1D *h_top_type1_unmatched_softdrop = new TH1D("h_top_type1_unmatched_softdrop","h_top_type1_unmatched_softdrop",60,0,300);

   TEfficiency* toptag_eff = new TEfficiency("toptag_eff","Top tagging efficiency;gentop p_T;#epsilon",10,0,1000);
   TEfficiency* toptag_eff_type1 = new TEfficiency("toptag_eff_type1","Top tagging efficiency;type1 gentop p_T;#epsilon",10,0,1000);
   TEfficiency* toptag_eff_type2 = new TEfficiency("toptag_eff_type2","Top tagging efficiency;type2 gentop p_T;#epsilon",10,0,1000);
   TEfficiency* toptag_eff_type3 = new TEfficiency("toptag_eff_type3","Top tagging efficiency;type3 gentop p_T;#epsilon",10,0,1000);

   // -----------------------
   // Histograms after baseline event selection
   // -----------------------
   TH2D *h_baseline_gentop_pT_daughterDR = new TH2D("h_baseline_gentop_pT_daughterDR","h_baseline_gentop_pT_daughterDR",50,0,1000,60,0,3);
   TH1D *h_baseline_gentop_pT = new TH1D("h_baseline_gentop_pT","h_baseline_gentop_pT",50,0,1000);
   TH1D *h_baseline_gentop_pT_type1 = new TH1D("h_baseline_gentop_pT_type1","h_baseline_gentop_pT_type1",50,0,1000);
   TH1D *h_baseline_gentop_pT_type2 = new TH1D("h_baseline_gentop_pT_type2","h_baseline_gentop_pT_type2",50,0,1000);
   TH1D *h_baseline_gentop_pT_type3 = new TH1D("h_baseline_gentop_pT_type3","h_baseline_gentop_pT_type3",50,0,1000);

   TH1D *h_baseline_top_gentop_minDR = new TH1D("h_baseline_top_gentop_minDR","h_baseline_top_gentop_minDR", 60, 0, 3);
   TH1D *h_baseline_top_gentop_Dpt = new TH1D("h_baseline_top_gentop_Dpt","h_baseline_top_gentop_Dpt", 50, 0, 5);
   TH2D *h_baseline_top_gentop_minDR_Dpt = new TH2D("h_baseline_top_gentop_minDR_Dpt", "h_baseline_top_gentop_minDR_Dpt", 60, 0, 3, 50, 0, 5);

   TH1D *h_baseline_top_3jet_gentop_minDR = new TH1D("h_baseline_top_3jet_gentop_minDR","h_baseline_top_3jet_gentop_minDR", 60, 0, 3);
   TH1D *h_baseline_top_3jet_gentop_Dpt = new TH1D("h_baseline_top_3jet_gentop_Dpt","h_baseline_top_3jet_gentop_Dpt", 50, 0, 5);
   TH2D *h_baseline_top_3jet_gentop_minDR_Dpt = new TH2D("h_baseline_top_3jet_gentop_minDR_Dpt", "h_baseline_top_3jet_gentop_minDR_Dpt", 60, 0, 3, 50, 0, 5);
   TH1D *h_baseline_top_2jet_gentop_minDR = new TH1D("h_baseline_top_2jet_gentop_minDR","h_baseline_top_2jet_gentop_minDR", 60, 0, 3);
   TH1D *h_baseline_top_2jet_gentop_Dpt = new TH1D("h_baseline_top_2jet_gentop_Dpt","h_baseline_top_2jet_gentop_Dpt", 50, 0, 5);
   TH2D *h_baseline_top_2jet_gentop_minDR_Dpt = new TH2D("h_baseline_top_2jet_gentop_minDR_Dpt", "h_baseline_top_2jet_gentop_minDR_Dpt", 60, 0, 3, 50, 0, 5);
   TH1D *h_baseline_top_1jet_gentop_minDR = new TH1D("h_baseline_top_1jet_gentop_minDR","h_baseline_top_1jet_gentop_minDR", 60, 0, 3);
   TH1D *h_baseline_top_1jet_gentop_Dpt = new TH1D("h_baseline_top_1jet_gentop_Dpt","h_baseline_top_1jet_gentop_Dpt", 50, 0, 5);
   TH2D *h_baseline_top_1jet_gentop_minDR_Dpt = new TH2D("h_baseline_top_1jet_gentop_minDR_Dpt", "h_baseline_top_1jet_gentop_minDR_Dpt", 60, 0, 3, 50, 0, 5);

   TH1D *h_baseline_top_gentop_minDR_3jet_daughters = new TH1D("h_baseline_top_gentop_minDR_3jet_daughters", "h_baseline_top_gentop_minDR_3jet_daughters", 60, 0, 3); 
   TH1D *h_baseline_top_gentop_Dpt_3jet_daughters = new TH1D("h_baseline_top_gentop_Dpt_3jet_daughters", "h_baseline_top_gentop_Dpt_3jet_daughters", 50, 0, 5); 
   TH2D *h_baseline_top_gentop_minDR_Dpt_3jet_daughters = new TH2D("h_baseline_top_gentop_minDR_Dpt_3jet_daughters", "h_baseline_top_gentop_minDR_Dpt_3jet_daughters", 60, 0, 3, 50, 0, 5); 
   TH1D *h_baseline_top_gentop_topmatch_minDR_3jet_daughters = new TH1D("h_baseline_top_gentop_topmatch_minDR_3jet_daughters", "h_baseline_top_gentop_topmatch_minDR_3jet_daughters", 60, 0, 3); 
   TH1D *h_baseline_top_gentop_topmatch_Dpt_3jet_daughters = new TH1D("h_baseline_top_gentop_topmatch_Dpt_3jet_daughters", "h_baseline_top_gentop_topmatch_Dpt_3jet_daughters", 50, 0, 5); 
   TH2D *h_baseline_top_gentop_topmatch_minDR_Dpt_3jet_daughters = new TH2D("h_baseline_top_gentop_topmatch_minDR_Dpt_3jet_daughters", "h_baseline_top_gentop_topmatch_minDR_Dpt_3jet_daughters", 60, 0, 3, 50, 0, 5); 

   TH1D *h_baseline_top_trijet_n_matched_constituents = new TH1D("h_baseline_top_trijet_n_matched_constituents", "h_baseline_top_trijet_n_matched_constituents", 4, -0.5, 3.5);
   TH2D *h_baseline_top_gentop_minDR_Dpt_anymatch = new TH2D("h_baseline_top_gentop_minDR_Dpt_anymatch", "h_baseline_top_gentop_minDR_Dpt_anymatch", 60, 0, 3, 50, 0, 5);
   TH2D *h_baseline_top_gentop_minDR_Dpt_3match = new TH2D("h_baseline_top_gentop_minDR_Dpt_3match", "h_baseline_top_gentop_minDR_Dpt_3match", 60, 0, 3, 50, 0, 5);
   TH2D *h_baseline_top_gentop_minDR_Dpt_2match = new TH2D("h_baseline_top_gentop_minDR_Dpt_2match", "h_baseline_top_gentop_minDR_Dpt_2match", 60, 0, 3, 50, 0, 5);
   TH2D *h_baseline_top_gentop_minDR_Dpt_1match = new TH2D("h_baseline_top_gentop_minDR_Dpt_1match", "h_baseline_top_gentop_minDR_Dpt_1match", 60, 0, 3, 50, 0, 5);
   TH2D *h_baseline_top_gentop_minDR_Dpt_0match = new TH2D("h_baseline_top_gentop_minDR_Dpt_0match", "h_baseline_top_gentop_minDR_Dpt_0match", 60, 0, 3, 50, 0, 5);

   TH1D *h_baseline_top_gentop_discr_anymatch = new TH1D("h_baseline_top_gentop_discr_anymatch", "h_baseline_top_gentop_discr_anymatch", 40, 0.8, 1);
   TH1D *h_baseline_top_gentop_discr_3match = new TH1D("h_baseline_top_gentop_discr_3match", "h_baseline_top_gentop_discr_3match", 40, 0.8, 1);
   TH1D *h_baseline_top_gentop_discr_2match = new TH1D("h_baseline_top_gentop_discr_2match", "h_baseline_top_gentop_discr_2match", 40, 0.8, 1);
   TH1D *h_baseline_top_gentop_discr_1match = new TH1D("h_baseline_top_gentop_discr_1match", "h_baseline_top_gentop_discr_1match", 40, 0.8, 1);
   TH1D *h_baseline_top_gentop_discr_0match = new TH1D("h_baseline_top_gentop_discr_0match", "h_baseline_top_gentop_discr_0match", 40, 0.8, 1);

   TH1D *h_baseline_top_gentop_discr_anymatch_topmatch = new TH1D("h_baseline_top_gentop_discr_anymatch_topmatch", "h_baseline_top_gentop_discr_anymatch_topmatch", 40, 0.8, 1);
   TH1D *h_baseline_top_gentop_discr_3match_topmatch = new TH1D("h_baseline_top_gentop_discr_3match_topmatch", "h_baseline_top_gentop_discr_3match_topmatch", 40, 0.8, 1);
   TH1D *h_baseline_top_gentop_discr_2match_topmatch = new TH1D("h_baseline_top_gentop_discr_2match_topmatch", "h_baseline_top_gentop_discr_2match_topmatch", 40, 0.8, 1);
   TH1D *h_baseline_top_gentop_discr_1match_topmatch = new TH1D("h_baseline_top_gentop_discr_1match_topmatch", "h_baseline_top_gentop_discr_1match_topmatch", 40, 0.8, 1);
   TH1D *h_baseline_top_gentop_discr_0match_topmatch = new TH1D("h_baseline_top_gentop_discr_0match_topmatch", "h_baseline_top_gentop_discr_0match_topmatch", 40, 0.8, 1);

   TH1D *h_baseline_gentop_top_minDR     = new TH1D("h_baseline_gentop_top_minDR",     "h_baseline_gentop_top_minDR", 60, 0, 3);
   TH1D *h_baseline_gentop_top_Dpt       = new TH1D("h_baseline_gentop_top_Dpt",       "h_baseline_gentop_top_Dpt", 50, 0, 5);
   TH2D *h_baseline_gentop_top_minDR_Dpt = new TH2D("h_baseline_gentop_top_minDR_Dpt", "h_baseline_gentop_top_minDR_Dpt", 60, 0, 3, 50, 0, 5);

   TH1D *h_baseline_top_type1_matched_nsub = new TH1D("h_baseline_top_type1_matched_nsub","h_baseline_top_type1_matched_nsub",50,0,1);
   TH1D *h_baseline_top_type1_unmatched_nsub = new TH1D("h_baseline_top_type1_unmatched_nsub","h_baseline_top_type1_unmatched_nsub",50,0,1);
   TH1D *h_baseline_top_type1_matched_softdrop = new TH1D("h_baseline_top_type1_matched_softdrop","h_baseline_top_type1_matched_softdrop",60,0,300);
   TH1D *h_baseline_top_type1_unmatched_softdrop = new TH1D("h_baseline_top_type1_unmatched_softdrop","h_baseline_top_type1_unmatched_softdrop",60,0,300);

   TEfficiency* toptag_eff_baseline = new TEfficiency("toptag_eff_baseline","Top tagging efficiency;gentop p_T;#epsilon",10,0,1000);
   TEfficiency* toptag_eff_type1_baseline = new TEfficiency("toptag_eff_type1_baseline","Top tagging efficiency;type1 gentop p_T;#epsilon",10,0,1000);
   TEfficiency* toptag_eff_type2_baseline = new TEfficiency("toptag_eff_type2_baseline","Top tagging efficiency;type2 gentop p_T;#epsilon",10,0,1000);
   TEfficiency* toptag_eff_type3_baseline = new TEfficiency("toptag_eff_type3_baseline","Top tagging efficiency;type3 gentop p_T;#epsilon",10,0,1000);

   TEfficiency* toptag_fakerate_baseline = new TEfficiency("toptag_fakerate_baseline","Top tagging fake rate;reco top p_T;#epsilon",10,0,1000);
   TEfficiency* toptag_fakerate = new TEfficiency("toptag_fakerate","Top tagging fake rate;reco top p_T;#epsilon",10,0,1000);
   TEfficiency* toptag_chitagrate = new TEfficiency("toptag_chitagrate","Tagged top fraction that matches a neutralino;reco top p_T;#epsilon",10,0,1000);
   TEfficiency* toptag_chitagrate_baseline = new TEfficiency("toptag_chitagrate_baseline","Tagged top fraction that matches a neutralino;reco top p_T;#epsilon",10,0,1000);


   // Cut flows
   TEfficiency* event_sel = new TEfficiency("event_sel","Event selection efficiency wrt previous cut;Cut;#epsilon",7,0,7);
   TEfficiency* event_sel_total = new TEfficiency("event_sel_total","Total event selection efficiency;Cut;#epsilon",7,0,7);

   TopTagger tt;
   tt.setCfgFile("TopTagger.cfg");

   for (Long64_t jentry=0; jentry<nentries;jentry++) 
   {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
   
      nb = fChain->GetEntry(jentry);   
      nbytes += nb;

      if ( jentry % (nentries/10) == 0 ) printf("  Event %9llu / %9llu  (%2.0f%%)\n", jentry, nentries, 100*(jentry*1.)/(nentries*1.) ) ;

      myHisto->Fill(NJets);

      // -----------------
      // check for number of hadronic tops at gen level
      // -----------------
      int nhadWs = 0;
      std::vector<TLorentzVector> hadtops;
      std::vector<TLorentzVector> hadWs;
      std::vector<int> hadtops_idx;
      std::vector<std::vector<const TLorentzVector*> > hadtopdaughters;
      std::vector<TLorentzVector> neutralinos;
      for ( unsigned int gpi=0; gpi < GenParticles->size() ; gpi++ ) 
      {
          int pdgid = abs( GenParticles_PdgId->at(gpi) ) ;
          int momid = abs( GenParticles_ParentId->at(gpi) ) ;
          int momidx = GenParticles_ParentIdx->at(gpi);
          int status = GenParticles_Status->at(gpi);
          if(pdgid == 1000022 && status==22)
          {
              neutralinos.push_back(GenParticles->at(gpi));
          }
          if(status == 23 && momid == 24 && pdgid < 6)
          {
              // Should be the quarks from W decay
              nhadWs++;
              // find the top
              int Wmotherid = GenParticles_ParentId->at(momidx);
              if (abs(Wmotherid) == 6){
                  int Wmotheridx = GenParticles_ParentIdx->at(momidx);
                  std::vector<int>::iterator found = std::find(hadtops_idx.begin(), hadtops_idx.end(), Wmotheridx);
                  if (found != hadtops_idx.end())
                  {
                      // already found before
                      // std::cout << "Found this top before: " << *found << std::endl;
                      int position = distance(hadtops_idx.begin(),found);
                      // add the daughter to the list
                      hadtopdaughters[position].push_back(&(GenParticles->at(gpi)));
                  } else
                  {
                      // not yet found
                      hadtops_idx.push_back(Wmotheridx);
                      hadtops.push_back(GenParticles->at(Wmotheridx));
                      hadWs.push_back(GenParticles->at(momidx));
                      std::vector<const TLorentzVector*> daughters;
                      daughters.push_back(&(GenParticles->at(gpi)));
                      hadtopdaughters.push_back(daughters);
                      //std::cout << "Found a new top at idx " << Wmotheridx << std::endl;
                  }
              }
          } 
      }
      if(neutralinos.size() > 2)
          std::cout << "Found " << neutralinos.size() << " neutralinos!" << std::endl;

      // Now check the b quarks (we only want the ones associated with a hadronic W decay for now)
      for ( unsigned int gpi=0; gpi < GenParticles->size() ; gpi++ ) 
      {
          int pdgid = abs( GenParticles_PdgId->at(gpi) ) ;
          int momid = abs( GenParticles_ParentId->at(gpi) ) ;
          int momidx = GenParticles_ParentIdx->at(gpi);
          int status = GenParticles_Status->at(gpi);
          
          if(status == 23 && momid == 6 && pdgid == 5)
          {
              // found a b quark from top decay, need to add this to the list of daughters
              std::vector<int>::iterator found = std::find(hadtops_idx.begin(), hadtops_idx.end(), momidx);
              if (found != hadtops_idx.end())
              {
                  // already found
                  int position = distance(hadtops_idx.begin(),found);
                  hadtopdaughters[position].push_back(&(GenParticles->at(gpi)));
                  //std::cout << "(b) Found this top before: " << *found << std::endl;
              } 
              //else
              //{
                  // not yet found
                  //std::cout << "(b) Found a new leptonic top at idx " << momidx << std::endl;
              //}
          }
      }

      bool verbose = false;
      if (verbose)
      {
          for (int ht=0; ht<hadtops.size(); ++ht){
              std::cout << "Hadtop index = " << hadtops_idx[ht] << std::endl;
              std::cout << "       daughters: ";
              for (int htd=0; htd<hadtopdaughters[ht].size(); ++htd){
                  std::cout << (*hadtopdaughters[ht][htd]).Pt() << " " ;
              }
              std::cout << std::endl;
          }
      }

      // Only keep events with two hadronic top decays
      if (nhadWs != 4) continue;  

      // Figure out whether the gentop is more similar to a monojet, dijet or trijet reco top
      // Monojet criterion: pT>400, DR(daughter,top)<0.8
      std::vector<int> hadtoptype;
      for (int igentop=0; igentop<hadtops.size(); igentop++ )
      {
          double maxDR_gentop_daughter = 0;
          for(int idaughter=0; idaughter<hadtopdaughters[igentop].size(); idaughter++)
          {
              double DR_gentop_daughter = calcDR(hadtops[igentop].Eta(), hadtopdaughters[igentop][idaughter]->Eta(), hadtops[igentop].Phi(), hadtopdaughters[igentop][idaughter]->Phi());
              if(DR_gentop_daughter>maxDR_gentop_daughter && hadtopdaughters[igentop][idaughter]->Pt()/hadtops[igentop].Pt() > 0.1)
                  maxDR_gentop_daughter = DR_gentop_daughter;
          }
          h_gentop_pT_daughterDR->Fill(hadtops[igentop].Pt(), maxDR_gentop_daughter);
          
          h_gentop_pT->Fill(hadtops[igentop].Pt());
          // fully merged case
          if (hadtops[igentop].Pt() > 450 && maxDR_gentop_daughter < 0.8)
          {
              hadtoptype.push_back(1);
              h_gentop_pT_type1->Fill(hadtops[igentop].Pt());
          }
          else if (hadWs[igentop].Pt() > 250) // merged W case
          {
              hadtoptype.push_back(2);
              h_gentop_pT_type2->Fill(hadtops[igentop].Pt());
          }
          else // assume everything else would be a resolved top
          {
              hadtoptype.push_back(3);
              h_gentop_pT_type3->Fill(hadtops[igentop].Pt());
          }
      }

      // ------------------
      // --- TOP TAGGER ---
      // ------------------
      
      // Use helper function to create input list 
      // Create AK4 inputs object
      ttUtility::ConstAK4Inputs AK4Inputs = ttUtility::ConstAK4Inputs(
          *Jets, 
          *Jets_bDiscriminatorCSV,
          *Jets_qgLikelihood, 
          hadtops, 
          hadtopdaughters);
    
      // Create AK8 inputs object
      ttUtility::ConstAK8Inputs AK8Inputs = ttUtility::ConstAK8Inputs(
          *JetsAK8,
          *JetsAK8_NsubjettinessTau1,
          *JetsAK8_NsubjettinessTau2,
          *JetsAK8_NsubjettinessTau3,
          *JetsAK8_softDropMass,
          *JetsAK8_subjets,    // These should be the subjets!
          hadtops,
          hadtopdaughters);
      
      // Create jets constituents list combining AK4 and AK8 jets, these are used to construct top candiates
      // The vector of input constituents can also be constructed "by hand"
      std::vector<Constituent> constituents = ttUtility::packageConstituents(AK4Inputs, AK8Inputs);

      // run the top tagger
      tt.runTagger(constituents);

      // retrieve the top tagger results object
      const TopTaggerResults& ttr = tt.getResults();

      // get reconstructed top
      const std::vector<TopObject*>& tops = ttr.getTops();
      h_ntops->Fill(tops.size());

      // get set of all constituents (i.e. AK4 and AK8 jets) used in one of the tops
      std::set<Constituent const *> usedConstituents = ttr.getUsedConstituents();

      if (jentry < 10) 
      {
          printf("\tN tops: %ld\n", tops.size());

          // print top properties
          for(const TopObject* top : tops)
          {
              //print basic top properties (top->p() gives a TLorentzVector)
              //N constituents refers to the number of jets included in the top
              //3 for resolved tops 
              //2 for W+jet tops
              //1 for fully merged AK8 tops
              printf("\tTop properties: N constituents: %3d,   Pt: %6.1lf,   Eta: %7.3lf,   Phi: %7.3lf,   Mass: %6.1lf\n", top->getNConstituents(), top->p().Pt(), top->p().Eta(), top->p().Phi(), top->p().M());
              
              //get vector of top constituents 
              const std::vector<Constituent const *>& constituents = top->getConstituents();
              
              //Print properties of individual top constituent jets 
              for(const Constituent* constituent : constituents)
              {
                  printf("\t\tConstituent properties: Constituent type: %3d,   Pt: %6.1lf,   Eta: %7.3lf,   Phi: %7.3lf,   Mass: %6.1lf\n", constituent->getType(), constituent->p().Pt(), constituent->p().Eta(), constituent->p().Phi(), constituent->p().M());
              }        
          }        

          std::cout << "Properties of all used constituents" << std::endl;
          // Print properties of individual top constituent jets 
          for(const Constituent* constituent : usedConstituents)
          {
              printf("\t\tConstituent properties: Constituent type: %3d,   Pt: %6.1lf,   Eta: %7.3lf,   Phi: %7.3lf,   Mass: %6.1lf\n", constituent->getType(), constituent->p().Pt(), constituent->p().Eta(), constituent->p().Phi(), constituent->p().M());
          }        
          
      }


      // -------------------------------
      // -- Basic event selection stuff
      // -------------------------------

      // Check whether event would pass the trigger requirement
      bool passTrigger = true;
      int rec_njet_pt45(0) ;
      int rec_njet_pt20(0) ;
      int rec_njet_pt45_btag(0) ;
      double HT_pt40 = 0.0;
      for ( unsigned int rji=0; rji < Jets->size() ; rji++ ) {
          TLorentzVector jlv( Jets->at(rji) ) ;
          if (abs(jlv.Eta()) > 2.4) continue;
          if ( jlv.Pt() > 20 ) 
              rec_njet_pt20++;
          if (jlv.Pt() > 40)
              HT_pt40 += jlv.Pt();
          if ( jlv.Pt() > 45 ) 
          {
              rec_njet_pt45++ ;
              if ( Jets_bDiscriminatorCSV->at(rji) > 0.8484) 
                  rec_njet_pt45_btag++;
          }
      } 
      if ( !( HT_pt40>500 && rec_njet_pt45>=6 ) ) 
          passTrigger = false;

      bool passBaseline = HT_pt40>500 && rec_njet_pt45>=6 && rec_njet_pt45_btag>1 && tops.size()>1;

      if(passBaseline)
      {
          for (int igentop=0; igentop<hadtops.size(); igentop++ )
          {
              double maxDR_gentop_daughter = 0;
              for(int idaughter=0; idaughter<hadtopdaughters[igentop].size(); idaughter++)
              {
                  double DR_gentop_daughter = calcDR(hadtops[igentop].Eta(), hadtopdaughters[igentop][idaughter]->Eta(), hadtops[igentop].Phi(), hadtopdaughters[igentop][idaughter]->Phi());
                  if(DR_gentop_daughter>maxDR_gentop_daughter && hadtopdaughters[igentop][idaughter]->Pt()/hadtops[igentop].Pt() > 0.1)
                      maxDR_gentop_daughter = DR_gentop_daughter;
              }
              h_baseline_gentop_pT_daughterDR->Fill(hadtops[igentop].Pt(), maxDR_gentop_daughter);
              
              h_baseline_gentop_pT->Fill(hadtops[igentop].Pt());
              // fully merged case
              if (hadtops[igentop].Pt() > 450 && maxDR_gentop_daughter < 0.8)
              {
                  h_baseline_gentop_pT_type1->Fill(hadtops[igentop].Pt());
              }
              else if (hadWs[igentop].Pt() > 250) // merged W case
              {
                  h_baseline_gentop_pT_type2->Fill(hadtops[igentop].Pt());
              }
              else // assume everything else would be a resolved top
              {
                  h_baseline_gentop_pT_type3->Fill(hadtops[igentop].Pt());
              }
          }

      }



      // Fill event selection efficiencies
      event_sel_total->Fill(HT_pt40>500,0);
      event_sel_total->Fill(HT_pt40>500 && rec_njet_pt45>=6 ,1);
      event_sel_total->Fill(HT_pt40>500 && rec_njet_pt45>=6 && rec_njet_pt45_btag>0 ,2);
      event_sel_total->Fill(HT_pt40>500 && rec_njet_pt45>=6 && rec_njet_pt45_btag>0 && tops.size()>0 ,3);
      event_sel_total->Fill(HT_pt40>500 && rec_njet_pt45>=6 && rec_njet_pt45_btag>0 && tops.size()>0 && rec_njet_pt45_btag>1 ,4);
      event_sel_total->Fill(HT_pt40>500 && rec_njet_pt45>=6 && rec_njet_pt45_btag>0 && tops.size()>0 && rec_njet_pt45_btag>1 && tops.size()>1 ,5);
      event_sel_total->Fill(HT_pt40>500 && rec_njet_pt45>=6 && rec_njet_pt45_btag>0 && tops.size()>0 && rec_njet_pt45_btag>1 && tops.size()>1 && rec_njet_pt20>=8 ,6);
      
      event_sel->Fill(HT_pt40>500,0);
      if(HT_pt40>500)
      {
          event_sel->Fill(rec_njet_pt45>=6,1);
          if (rec_njet_pt45>=6)
          {
              event_sel->Fill(rec_njet_pt45_btag>0,2);
              if (rec_njet_pt45_btag>0)
              {
                  event_sel->Fill(tops.size()>0,3);
                  if (tops.size()>0)
                  {
                      event_sel->Fill(rec_njet_pt45_btag>1,4);
                      if (rec_njet_pt45_btag>1)
                      {
                          event_sel->Fill(tops.size()>1,5);
                          if (tops.size()>1)
                          {
                              event_sel->Fill(rec_njet_pt20>=8,6);
                          }
                      }
                  }
              }
          }
      }


      // ----------------------------------
      // -- Study top tagger performance --
      // ----------------------------------

      // --- Gen matching ---
      int n_matched_recotops = 0;
      int n_matched_recotops_auto = 0;
      int ntops_3jet=0;
      int ntops_2jet=0;
      int ntops_1jet=0;
      // How often does a tagged top match with genlevel?
      for (const TopObject* top : tops)
      {
          TLorentzVector matched_top;
          std::vector<const TLorentzVector*> matched_top_constituents;
          double minDR = 999;
          for (int i_gentop=0; i_gentop<hadtops.size(); ++i_gentop)
          {
              double DR_top_gentop = calcDR(top->p().Eta(), hadtops[i_gentop].Eta(), top->p().Phi(), hadtops[i_gentop].Phi());
              if (DR_top_gentop < minDR)
              {
                  minDR = DR_top_gentop;
                  matched_top = hadtops[i_gentop];
                  matched_top_constituents = hadtopdaughters[i_gentop];
              }
          }
          // std::cout << "Top Pt, Eta, Phi: " << top->p().Pt() << " " << top->p().Eta() << " " << top->p().Phi() << std::endl;
          //std::cout << "Gen top Pt, Eta, Phi, DR: " << matched_top.Pt() << " " << matched_top.Eta() << " " << matched_top.Phi() << " " << minDR << std::endl;

          double Dpt_top_gentop = abs(top->p().Pt() - matched_top.Pt())/top->p().Pt();
          h_top_gentop_minDR->Fill(minDR);
          h_top_gentop_Dpt->Fill(Dpt_top_gentop);
          h_top_gentop_minDR_Dpt->Fill(minDR, Dpt_top_gentop);
          
          double minDR_top_neutralino = 999;
          double Dpt_top_neutralino = -1;
          for (int i_chi=0; i_chi<neutralinos.size(); ++i_chi)
          {
              double DR_top_neutralino = calcDR(top->p().Eta(), neutralinos[i_chi].Eta(), top->p().Phi(), neutralinos[i_chi].Phi());
              if(DR_top_neutralino < minDR_top_neutralino)
              {
                  minDR_top_neutralino = DR_top_neutralino;
                  Dpt_top_neutralino = abs(top->p().Pt() - neutralinos[i_chi].Pt())/top->p().Pt();
              }
          }
          if ((minDR_top_neutralino < 0.4 && Dpt_top_neutralino < 0.5 && minDR < 0.4 && Dpt_top_gentop < 0.5))
          {
              std::cout << "Matched to a neutralino and to a top quark..." << std::endl;
              std::cout << "DR and Dpt for neutralino: " << minDR_top_neutralino << ", " << Dpt_top_neutralino << std::endl;
              std::cout << "DR and Dpt for top:        " << minDR << ", " << Dpt_top_gentop << std::endl;
          }
          toptag_chitagrate->Fill( (minDR_top_neutralino<0.4 && Dpt_top_neutralino<0.5), top->p().Pt());
          toptag_fakerate->Fill( (minDR_top_neutralino>0.4 || Dpt_top_neutralino > 0.5) && (minDR > 0.4 || Dpt_top_gentop > 0.5) , top->p().Pt());
          if(passBaseline)
          {
              h_baseline_top_gentop_minDR->Fill(minDR);
              h_baseline_top_gentop_Dpt->Fill(Dpt_top_gentop);
              h_baseline_top_gentop_minDR_Dpt->Fill(minDR, Dpt_top_gentop);
              toptag_fakerate_baseline->Fill( (minDR_top_neutralino>0.4 || Dpt_top_neutralino>0.5) && (minDR > 0.4 || Dpt_top_gentop > 0.5) , top->p().Pt());
              toptag_chitagrate_baseline->Fill( (minDR_top_neutralino<0.4 && Dpt_top_neutralino<0.5), top->p().Pt());
          }
          if(minDR <= 0.4) n_matched_recotops++;
          
          // Compare with what comes out of the top tagger itself: 
          const TLorentzVector* bestgentop = top->getBestGenTopMatch(0.4);
          if(bestgentop != nullptr) n_matched_recotops_auto++;

          if(top->getNConstituents() == 3 )
          {
              ntops_3jet++;
              // do stuff for trijet
              h_top_3jet_gentop_minDR->Fill(minDR);
              h_top_3jet_gentop_Dpt->Fill(Dpt_top_gentop);
              h_top_3jet_gentop_minDR_Dpt->Fill(minDR, Dpt_top_gentop);

              int n_matched_constituents = 0;
              for(const Constituent* constituent : top->getConstituents())
              {
                  double minDR_AK4_daughter = 999;
                  const TLorentzVector *matched_daughter;

                  for(const TLorentzVector* daughter : matched_top_constituents)
                  {
                      // for each AK4, check whether we find a matched daughter
                      double DR_daughter_constituent = calcDR(daughter->Eta(), constituent->p().Eta(), daughter->Phi(), constituent->p().Phi());
                      if(DR_daughter_constituent < minDR_AK4_daughter)
                      {
                          minDR_AK4_daughter = DR_daughter_constituent;
                          matched_daughter = daughter;
                      }
                  }
                  double Dpt_3jet_daughter = abs(constituent->p().Pt() - matched_daughter->Pt())/constituent->p().Pt();
                  h_top_gentop_minDR_3jet_daughters->Fill(minDR_AK4_daughter);
                  h_top_gentop_Dpt_3jet_daughters->Fill( Dpt_3jet_daughter );
                  h_top_gentop_minDR_Dpt_3jet_daughters->Fill(minDR_AK4_daughter, Dpt_3jet_daughter );
                  if(passBaseline)
                  {
                      h_baseline_top_gentop_minDR_3jet_daughters->Fill(minDR_AK4_daughter);
                      h_baseline_top_gentop_Dpt_3jet_daughters->Fill( Dpt_3jet_daughter );
                      h_baseline_top_gentop_minDR_Dpt_3jet_daughters->Fill(minDR_AK4_daughter, Dpt_3jet_daughter );                      
                  }
                  if(minDR<0.4)
                  {
                      h_top_gentop_topmatch_minDR_3jet_daughters->Fill(minDR_AK4_daughter);
                      h_top_gentop_topmatch_Dpt_3jet_daughters->Fill( Dpt_3jet_daughter );
                      h_top_gentop_topmatch_minDR_Dpt_3jet_daughters->Fill(minDR_AK4_daughter, Dpt_3jet_daughter );
                      if(passBaseline)
                      {
                          h_baseline_top_gentop_topmatch_minDR_3jet_daughters->Fill(minDR_AK4_daughter);
                          h_baseline_top_gentop_topmatch_Dpt_3jet_daughters->Fill( Dpt_3jet_daughter );
                          h_baseline_top_gentop_topmatch_minDR_Dpt_3jet_daughters->Fill(minDR_AK4_daughter, Dpt_3jet_daughter );
                      }
                  }

                  if(minDR_AK4_daughter < 0.3 && Dpt_3jet_daughter < 0.5)
                  {
                      n_matched_constituents++;
                      //std::cout << "Found a match for this AK4 jet" << std::endl;
                      //std::cout << "\t matched daughter pt, eta, phi: " << matched_daughter->Pt() << ", " << matched_daughter->Eta() << ", " << matched_daughter->Phi() << std::endl;
                      //std::cout << "\t AK4 jet pt, eta, phi: " << constituent->p().Pt() << ", " << constituent->p().Eta() << ", " << constituent->p().Phi() << std::endl;
                  }
                  else 
                  {
                      //std::cout << "Did not find a match for this AK4 jet" << std::endl;
                      //std::cout << "\t AK4 jet pt, eta, phi: " << constituent->p().Pt() << ", " << constituent->p().Eta() << ", " << constituent->p().Phi() << std::endl;
                  }
              }
              //std::cout << "Was able to match " << n_matched_constituents << " AK4 constituents to a genlevel top daughter" << std::endl;
              h_top_trijet_n_matched_constituents->Fill(n_matched_constituents);
              h_top_gentop_minDR_Dpt_anymatch->Fill(minDR, Dpt_top_gentop);
              h_top_gentop_discr_anymatch->Fill(top->getDiscriminator());
              if(passBaseline)
              {
                  h_baseline_top_3jet_gentop_minDR->Fill(minDR);
                  h_baseline_top_3jet_gentop_Dpt->Fill(Dpt_top_gentop);
                  h_baseline_top_3jet_gentop_minDR_Dpt->Fill(minDR, Dpt_top_gentop);

                  h_baseline_top_trijet_n_matched_constituents->Fill(n_matched_constituents);
                  h_baseline_top_gentop_minDR_Dpt_anymatch->Fill(minDR, Dpt_top_gentop);
                  h_baseline_top_gentop_discr_anymatch->Fill(top->getDiscriminator());
              }
              if(minDR<0.4)
              {
                  h_top_gentop_discr_anymatch_topmatch->Fill(top->getDiscriminator());
                  if(passBaseline)
                      h_baseline_top_gentop_discr_anymatch_topmatch->Fill(top->getDiscriminator());
              }
              if(n_matched_constituents == 3)
              {
                  h_top_gentop_minDR_Dpt_3match->Fill(minDR, Dpt_top_gentop);
                  h_top_gentop_discr_3match->Fill(top->getDiscriminator());
                  if(minDR<0.4)
                      h_top_gentop_discr_3match_topmatch->Fill(top->getDiscriminator());
              }
              else if(n_matched_constituents == 2)
              {
                  h_top_gentop_minDR_Dpt_2match->Fill(minDR, Dpt_top_gentop);
                  h_top_gentop_discr_2match->Fill(top->getDiscriminator());
                  if(minDR<0.4)
                      h_top_gentop_discr_2match_topmatch->Fill(top->getDiscriminator());
              }
              else if(n_matched_constituents == 1)
              {
                  h_top_gentop_minDR_Dpt_1match->Fill(minDR, Dpt_top_gentop);
                  h_top_gentop_discr_1match->Fill(top->getDiscriminator());
                  if(minDR<0.4)
                      h_top_gentop_discr_1match_topmatch->Fill(top->getDiscriminator());
              }
              else if(n_matched_constituents == 0)
              {
                  h_top_gentop_minDR_Dpt_0match->Fill(minDR, Dpt_top_gentop);
                  h_top_gentop_discr_0match->Fill(top->getDiscriminator());
                  if(minDR<0.4)
                      h_top_gentop_discr_0match_topmatch->Fill(top->getDiscriminator());
              }
              if(passBaseline)
              {
                  if(n_matched_constituents == 3)
                  {
                      h_baseline_top_gentop_minDR_Dpt_3match->Fill(minDR, Dpt_top_gentop);
                      h_baseline_top_gentop_discr_3match->Fill(top->getDiscriminator());
                      if(minDR<0.4)
                          h_baseline_top_gentop_discr_3match_topmatch->Fill(top->getDiscriminator());
                  }
                  else if(n_matched_constituents == 2)
                  {
                      h_baseline_top_gentop_minDR_Dpt_2match->Fill(minDR, Dpt_top_gentop);
                      h_baseline_top_gentop_discr_2match->Fill(top->getDiscriminator());
                      if(minDR<0.4)
                          h_baseline_top_gentop_discr_2match_topmatch->Fill(top->getDiscriminator());
                  }
                  else if(n_matched_constituents == 1)
                  {
                      h_baseline_top_gentop_minDR_Dpt_1match->Fill(minDR, Dpt_top_gentop);
                      h_baseline_top_gentop_discr_1match->Fill(top->getDiscriminator());
                      if(minDR<0.4)
                          h_baseline_top_gentop_discr_1match_topmatch->Fill(top->getDiscriminator());
                  }
                  else if(n_matched_constituents == 0)
                  {
                      h_baseline_top_gentop_minDR_Dpt_0match->Fill(minDR, Dpt_top_gentop);
                      h_baseline_top_gentop_discr_0match->Fill(top->getDiscriminator());
                      if(minDR<0.4)
                          h_baseline_top_gentop_discr_0match_topmatch->Fill(top->getDiscriminator());
                  }
                  
              }
          }
          else if(top->getNConstituents() == 2 )
          {
              ntops_2jet++;
              // do stuff for dijet
              h_top_2jet_gentop_minDR->Fill(minDR);
              h_top_2jet_gentop_Dpt->Fill(Dpt_top_gentop);
              h_top_2jet_gentop_minDR_Dpt->Fill(minDR, Dpt_top_gentop);
              if(passBaseline)
              {
                  h_baseline_top_2jet_gentop_minDR->Fill(minDR);
                  h_baseline_top_2jet_gentop_Dpt->Fill(Dpt_top_gentop);
                  h_baseline_top_2jet_gentop_minDR_Dpt->Fill(minDR, Dpt_top_gentop);
              }
          }
          else if(top->getNConstituents() == 1 )
          {
              ntops_1jet++;
              h_top_1jet_gentop_minDR->Fill(minDR);
              h_top_1jet_gentop_Dpt->Fill(Dpt_top_gentop);
              h_top_1jet_gentop_minDR_Dpt->Fill(minDR, Dpt_top_gentop);
              if(passBaseline)
              {
                  h_baseline_top_1jet_gentop_minDR->Fill(minDR);
                  h_baseline_top_1jet_gentop_Dpt->Fill(Dpt_top_gentop);
                  h_baseline_top_1jet_gentop_minDR_Dpt->Fill(minDR, Dpt_top_gentop);
              }

              Constituent const *thistop = top->getConstituents()[0];
              // do stuff for monojet
              // check mindr, dpt/pt, nsubjettiness
              //TLorentzVector matched_top;
              //std::vector<const TLorentzVector*> matched_top_constituents;
              //double minDR = 999;
              // need to look at the AK4s that were removed as well. 
              if (minDR<0.4 && Dpt_top_gentop < 0.5)
              {
                  h_top_type1_matched_nsub->Fill(thistop->getTau3()/thistop->getTau2());
                  h_top_type1_matched_softdrop->Fill(thistop->getSoftDropMass());
              } 
              else 
              {
                  h_top_type1_unmatched_nsub->Fill(thistop->getTau3()/thistop->getTau2());
                  h_top_type1_unmatched_softdrop->Fill(thistop->getSoftDropMass());
              }
              if (passBaseline)
              {
                  if (minDR<0.4 && Dpt_top_gentop < 0.5)
                  {
                      h_baseline_top_type1_matched_nsub->Fill(thistop->getTau3()/thistop->getTau2());
                      h_baseline_top_type1_matched_softdrop->Fill(thistop->getSoftDropMass());
                  } 
                  else 
                  {
                      h_baseline_top_type1_unmatched_nsub->Fill(thistop->getTau3()/thistop->getTau2());
                      h_baseline_top_type1_unmatched_softdrop->Fill(thistop->getSoftDropMass());
                  }                  
              }
          }
      }
      h_ntops_3jet->Fill(ntops_3jet);
      h_ntops_2jet->Fill(ntops_2jet);
      h_ntops_1jet->Fill(ntops_1jet);
      if(n_matched_recotops>2)
          std::cout << "Double matched a gentop!" << std::endl;

      //if (n_matched_recotops_auto != n_matched_recotops)
      //    std::cout << "top tagger code found different number of matches" << std::endl;


      // How often is a gentop actually reconstructed as a final reco top
      for (int i_gentop=0; i_gentop<hadtops.size(); ++i_gentop)
      {
          //std::cout << "Gen top Pt, Eta, Phi: " << hadtops[i_gentop].Pt() << " " << hadtops[i_gentop].Eta() << " " << hadtops[i_gentop].Phi()  << std::endl;

          const TopObject* matched_top;
          double minDR = 999;
          for (const TopObject* top : tops)
          {
              double DR_top_gentop = calcDR(top->p().Eta(), hadtops[i_gentop].Eta(), top->p().Phi(), hadtops[i_gentop].Phi());
              if (DR_top_gentop < minDR)
              {
                  minDR = DR_top_gentop;
                  matched_top = top;
              }          
          }
          if (minDR < 999)
          {
              //std::cout << "For this gentop, the closest reco top is at DR= " << minDR << " and has pT, eta, phi of: " << matched_top->p().Pt() << " " << matched_top->p().Eta() << " " << matched_top->p().Phi() << std::endl;
              double Dpt_gentop_top = abs(hadtops[i_gentop].Pt() - matched_top->p().Pt())/hadtops[i_gentop].Pt();
              h_gentop_top_minDR->Fill(minDR);
              h_gentop_top_Dpt->Fill(Dpt_gentop_top);
              h_gentop_top_minDR_Dpt->Fill(minDR,Dpt_gentop_top);

              // Call it a match if dR<0.4 and dPT/PT < 0.5
              toptag_eff->Fill( (minDR < 0.4 && Dpt_gentop_top < 0.5) , hadtops[i_gentop].Pt());
              if (hadtoptype[i_gentop] == 1)
                  toptag_eff_type1->Fill( (minDR < 0.4 && Dpt_gentop_top < 0.5) , hadtops[i_gentop].Pt());
              else if (hadtoptype[i_gentop] == 2)
                  toptag_eff_type2->Fill( (minDR < 0.4 && Dpt_gentop_top < 0.5) , hadtops[i_gentop].Pt());
              else if (hadtoptype[i_gentop] == 3)
                  toptag_eff_type3->Fill( (minDR < 0.4 && Dpt_gentop_top < 0.5) , hadtops[i_gentop].Pt());

              if(passBaseline)
              {
                  h_baseline_gentop_top_minDR->Fill(minDR);
                  h_baseline_gentop_top_Dpt->Fill(Dpt_gentop_top);
                  h_baseline_gentop_top_minDR_Dpt->Fill(minDR,Dpt_gentop_top);
                  
                  // Call it a match if dR<0.4 and dPT/PT < 0.5
                  toptag_eff_baseline->Fill( (minDR < 0.4 && Dpt_gentop_top < 0.5) , hadtops[i_gentop].Pt());
                  if (hadtoptype[i_gentop] == 1)
                      toptag_eff_type1_baseline->Fill( (minDR < 0.4 && Dpt_gentop_top < 0.5) , hadtops[i_gentop].Pt());
                  else if (hadtoptype[i_gentop] == 2)
                      toptag_eff_type2_baseline->Fill( (minDR < 0.4 && Dpt_gentop_top < 0.5) , hadtops[i_gentop].Pt());
                  else if (hadtoptype[i_gentop] == 3)
                      toptag_eff_type3_baseline->Fill( (minDR < 0.4 && Dpt_gentop_top < 0.5) , hadtops[i_gentop].Pt());
              }
          }
          else
          {
              //std::cout << "No reco top found" << std::endl;
          }

      }
      


      if(!passBaseline) continue;
      
      h_baseline_ntops->Fill(tops.size());
      h_baseline_ntops_3jet->Fill(ntops_3jet);
      h_baseline_ntops_2jet->Fill(ntops_2jet);
      h_baseline_ntops_1jet->Fill(ntops_1jet);
      
      if (tops.size() == 2)
      {
          h_dphi_2tops->Fill(calcDPhi(tops[0]->p().Phi(), tops[1]->p().Phi()));
      }




      
   }

   myHisto->Write();
   h_ntops->Write();
   h_ntops_3jet->Write();
   h_ntops_2jet->Write();
   h_ntops_1jet->Write();
   h_baseline_ntops->Write();
   h_baseline_ntops_3jet->Write();
   h_baseline_ntops_2jet->Write();
   h_baseline_ntops_1jet->Write();
   h_dphi_2tops->Write();

   h_gentop_pT_daughterDR->Write();

   h_top_gentop_minDR->Write();
   h_top_gentop_Dpt->Write();
   h_top_gentop_minDR_Dpt->Write();

   h_top_3jet_gentop_minDR->Write();
   h_top_3jet_gentop_Dpt->Write();
   h_top_3jet_gentop_minDR_Dpt->Write();
   h_top_2jet_gentop_minDR->Write();
   h_top_2jet_gentop_Dpt->Write();
   h_top_2jet_gentop_minDR_Dpt->Write();
   h_top_1jet_gentop_minDR->Write();
   h_top_1jet_gentop_Dpt->Write();
   h_top_1jet_gentop_minDR_Dpt->Write();

   h_top_gentop_minDR_3jet_daughters->Write(); 
   h_top_gentop_Dpt_3jet_daughters->Write(); 
   h_top_gentop_minDR_Dpt_3jet_daughters->Write(); 
   
   h_top_trijet_n_matched_constituents->Write();
   h_top_gentop_minDR_Dpt_anymatch->Write();
   h_top_gentop_minDR_Dpt_3match->Write();
   h_top_gentop_minDR_Dpt_2match->Write();
   h_top_gentop_minDR_Dpt_1match->Write();
   h_top_gentop_minDR_Dpt_0match->Write();

   h_top_gentop_discr_anymatch->Write();
   h_top_gentop_discr_3match->Write();
   h_top_gentop_discr_2match->Write();
   h_top_gentop_discr_1match->Write();
   h_top_gentop_discr_0match->Write();

   h_top_gentop_discr_anymatch_topmatch->Write();
   h_top_gentop_discr_3match_topmatch->Write();
   h_top_gentop_discr_2match_topmatch->Write();
   h_top_gentop_discr_1match_topmatch->Write();
   h_top_gentop_discr_0match_topmatch->Write();

   h_top_type1_matched_nsub->Write();
   h_top_type1_unmatched_nsub->Write();
   h_top_type1_matched_softdrop->Write();
   h_top_type1_unmatched_softdrop->Write();

   h_gentop_top_minDR->Write();
   h_gentop_top_Dpt->Write();
   h_gentop_top_minDR_Dpt->Write();

   h_gentop_pT->Write();
   h_gentop_pT_type1->Write();
   h_gentop_pT_type2->Write();
   h_gentop_pT_type3->Write();


   h_baseline_gentop_pT_daughterDR->Write();

   h_baseline_top_gentop_minDR->Write();
   h_baseline_top_gentop_Dpt->Write();
   h_baseline_top_gentop_minDR_Dpt->Write();

   h_baseline_top_3jet_gentop_minDR->Write();
   h_baseline_top_3jet_gentop_Dpt->Write();
   h_baseline_top_3jet_gentop_minDR_Dpt->Write();
   h_baseline_top_2jet_gentop_minDR->Write();
   h_baseline_top_2jet_gentop_Dpt->Write();
   h_baseline_top_2jet_gentop_minDR_Dpt->Write();
   h_baseline_top_1jet_gentop_minDR->Write();
   h_baseline_top_1jet_gentop_Dpt->Write();
   h_baseline_top_1jet_gentop_minDR_Dpt->Write();


   h_baseline_top_gentop_minDR_3jet_daughters->Write(); 
   h_baseline_top_gentop_Dpt_3jet_daughters->Write(); 
   h_baseline_top_gentop_minDR_Dpt_3jet_daughters->Write(); 
   
   h_baseline_top_trijet_n_matched_constituents->Write();
   h_baseline_top_gentop_minDR_Dpt_anymatch->Write();
   h_baseline_top_gentop_minDR_Dpt_3match->Write();
   h_baseline_top_gentop_minDR_Dpt_2match->Write();
   h_baseline_top_gentop_minDR_Dpt_1match->Write();
   h_baseline_top_gentop_minDR_Dpt_0match->Write();

   h_baseline_top_gentop_discr_anymatch->Write();
   h_baseline_top_gentop_discr_3match->Write();
   h_baseline_top_gentop_discr_2match->Write();
   h_baseline_top_gentop_discr_1match->Write();
   h_baseline_top_gentop_discr_0match->Write();

   h_baseline_top_gentop_discr_anymatch_topmatch->Write();
   h_baseline_top_gentop_discr_3match_topmatch->Write();
   h_baseline_top_gentop_discr_2match_topmatch->Write();
   h_baseline_top_gentop_discr_1match_topmatch->Write();
   h_baseline_top_gentop_discr_0match_topmatch->Write();

   h_baseline_top_type1_matched_nsub->Write();
   h_baseline_top_type1_unmatched_nsub->Write();
   h_baseline_top_type1_matched_softdrop->Write();
   h_baseline_top_type1_unmatched_softdrop->Write();

   h_baseline_gentop_top_minDR->Write();
   h_baseline_gentop_top_Dpt->Write();
   h_baseline_gentop_top_minDR_Dpt->Write();
  
   h_baseline_gentop_pT->Write();
   h_baseline_gentop_pT_type1->Write();
   h_baseline_gentop_pT_type2->Write();
   h_baseline_gentop_pT_type3->Write();


   std::cout << "Top tagging efficiency: " << toptag_eff->GetEfficiency(6) << std::endl; 
   toptag_eff->Write();
   toptag_eff_type1->Write();
   toptag_eff_type2->Write();
   toptag_eff_type3->Write();

   toptag_eff_baseline->Write();
   toptag_eff_type1_baseline->Write();
   toptag_eff_type2_baseline->Write();
   toptag_eff_type3_baseline->Write();

   toptag_fakerate->Write();
   toptag_fakerate_baseline->Write();
   toptag_chitagrate->Write();
   toptag_chitagrate_baseline->Write();

   event_sel->Write();
   event_sel_total->Write();
}
