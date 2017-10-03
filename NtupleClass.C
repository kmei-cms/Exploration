#define NtupleClass_cxx
#include "NtupleClass.h"
#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

//manditory includes to use top tagger
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

   // make some histograms
   TH1D *myHisto  = new TH1D("njets","njets", 20, 0, 20);
   TH1D *h_ntops  = new TH1D("ntops","ntops", 5, 0, 5);
   TH1D *h_ntops_baseline  = new TH1D("ntops_baseline","ntops_baseline", 5, 0, 5);
   TH1D *h_dphi_2tops  = new TH1D("dphi_2tops","dphi_2tops", 40, -4, 4);
   TH1D *h_top_gentop_minDR = new TH1D("h_top_gentop_minDR","h_top_gentop_minDR", 60, 0, 3);
   TH1D *h_top_gentop_Dpt = new TH1D("h_top_gentop_Dpt","h_top_gentop_Dpt", 60, 0, 300);
   TH2D *h_top_gentop_minDR_Dpt = new TH2D("h_top_gentop_minDR_Dpt", "h_top_gentop_minDR_Dpt", 60, 0, 3, 60, 0, 300);
   TH1D *h_top_gentop_minDR_3jet_daughters = new TH1D("h_top_gentop_minDR_3jet_daughters", "h_top_gentop_minDR_3jet_daughters", 60, 0, 3); 
   TH1D *h_top_gentop_Dpt_3jet_daughters = new TH1D("h_top_gentop_Dpt_3jet_daughters", "h_top_gentop_Dpt_3jet_daughters", 60, 0, 300); 
   TH2D *h_top_gentop_minDR_Dpt_3jet_daughters = new TH2D("h_top_gentop_minDR_Dpt_3jet_daughters", "h_top_gentop_minDR_Dpt_3jet_daughters", 60, 0, 3, 60, 0, 300); 

   TH1D *h_top_trijet_n_matched_constituents = new TH1D("h_top_trijet_n_matched_constituents", "h_top_trijet_n_matched_constituents", 4, -0.5, 3.5);
   TH2D *h_top_gentop_minDR_Dpt_3match = new TH2D("h_top_gentop_minDR_Dpt_3match", "h_top_gentop_minDR_Dpt_3match", 60, 0, 3, 60, 0, 300);
   TH2D *h_top_gentop_minDR_Dpt_2match = new TH2D("h_top_gentop_minDR_Dpt_2match", "h_top_gentop_minDR_Dpt_2match", 60, 0, 3, 60, 0, 300);
   TH2D *h_top_gentop_minDR_Dpt_1match = new TH2D("h_top_gentop_minDR_Dpt_1match", "h_top_gentop_minDR_Dpt_1match", 60, 0, 3, 60, 0, 300);
   TH2D *h_top_gentop_minDR_Dpt_0match = new TH2D("h_top_gentop_minDR_Dpt_0match", "h_top_gentop_minDR_Dpt_0match", 60, 0, 3, 60, 0, 300);

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
      
      // check for number of hadronic tops
      int hadWs = 0;
      std::vector<TLorentzVector> hadtops;
      std::vector<int> hadtops_idx;
      std::vector<std::vector<const TLorentzVector*> > hadtopdaughters;
      for ( unsigned int gpi=0; gpi < GenParticles->size() ; gpi++ ) 
      {
          int pdgid = abs( GenParticles_PdgId->at(gpi) ) ;
          int momid = abs( GenParticles_ParentId->at(gpi) ) ;
          int momidx = GenParticles_ParentIdx->at(gpi);
          int status = GenParticles_Status->at(gpi);
          
          if(status == 23 && momid == 24 && pdgid < 6)
          {
              // Should be the quarks from W decay
              hadWs++;
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
                      std::vector<const TLorentzVector*> daughters;
                      daughters.push_back(&(GenParticles->at(gpi)));
                      hadtopdaughters.push_back(daughters);
                      //std::cout << "Found a new top at idx " << Wmotheridx << std::endl;
                  }
              }
          } 
      }

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
      if (hadWs != 4) continue;  

      // Check whether event would pass the trigger requirement
      bool passTrigger = true;
      int rec_njet_pt40(0) ;
      for ( unsigned int rji=0; rji < Jets->size() ; rji++ ) {
          TLorentzVector jlv( Jets->at(rji) ) ;
          if ( jlv.Pt() > 40 ) rec_njet_pt40++ ;
      } 
      if ( !( HT>450 && rec_njet_pt40>=6 ) ) 
          passTrigger = false;


      // --- TOP TAGGER ---
      
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

      // --- Gen matching ---
      int n_matched_recotops = 0;
      int n_matched_recotops_auto = 0;
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

          h_top_gentop_minDR->Fill(minDR);
          double Dpt_top_gentop = abs(top->p().Pt() - matched_top.Pt());
          h_top_gentop_Dpt->Fill(Dpt_top_gentop);
          h_top_gentop_minDR_Dpt->Fill(minDR, Dpt_top_gentop);
          
          if(minDR <= 0.4) n_matched_recotops++;

          // Compare with what comes out of the top tagger itself: 
          const TLorentzVector* bestgentop = top->getBestGenTopMatch(0.4);
          if(bestgentop != nullptr) n_matched_recotops_auto++;

          if(top->getNConstituents() == 3 )
          {
              // do stuff for trijet
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
                  h_top_gentop_minDR_3jet_daughters->Fill(minDR_AK4_daughter);
                  double Dpt_3jet_daughter = abs(constituent->p().Pt() - matched_daughter->Pt());
                  h_top_gentop_Dpt_3jet_daughters->Fill( Dpt_3jet_daughter );
                  h_top_gentop_minDR_Dpt_3jet_daughters->Fill(minDR_AK4_daughter, Dpt_3jet_daughter );

                  if(minDR_AK4_daughter < 0.3 && Dpt_3jet_daughter < 100)
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
              std::cout << "Was able to match " << n_matched_constituents << " AK4 constituents to a genlevel top daughter" << std::endl;
              h_top_trijet_n_matched_constituents->Fill(n_matched_constituents);
              if(n_matched_constituents == 3)
                  h_top_gentop_minDR_Dpt_3match->Fill(minDR, Dpt_top_gentop);
              else if(n_matched_constituents == 2)
                  h_top_gentop_minDR_Dpt_2match->Fill(minDR, Dpt_top_gentop);
              else if(n_matched_constituents == 1)
                  h_top_gentop_minDR_Dpt_1match->Fill(minDR, Dpt_top_gentop);
              else if(n_matched_constituents == 0)
                  h_top_gentop_minDR_Dpt_0match->Fill(minDR, Dpt_top_gentop);

          }
          else if(top->getNConstituents() == 2 )
          {
              // do stuff for dijet
          }
          else if(top->getNConstituents() == 1 )
          {
              // do stuff for monojet
          }
      }

      if(n_matched_recotops>2)
          std::cout << "Double matched a gentop!" << std::endl;

      if (n_matched_recotops_auto != n_matched_recotops)
          std::cout << "top tagger code found different number of matches" << std::endl;

      if(!passTrigger) continue;
      
      h_ntops_baseline->Fill(tops.size());
      
      if (tops.size() == 2)
      {
          h_dphi_2tops->Fill(calcDPhi(tops[0]->p().Phi(), tops[1]->p().Phi()));
      }

      
   }

   myHisto->Write();
   h_ntops->Write();
   h_ntops_baseline->Write();
   h_dphi_2tops->Write();

   h_top_gentop_minDR->Write();
   h_top_gentop_Dpt->Write();
   h_top_gentop_minDR_Dpt->Write();
   h_top_gentop_minDR_3jet_daughters->Write(); 
   h_top_gentop_Dpt_3jet_daughters->Write(); 
   h_top_gentop_minDR_Dpt_3jet_daughters->Write(); 
   
   h_top_trijet_n_matched_constituents->Write();
   h_top_gentop_minDR_Dpt_3match->Write();
   h_top_gentop_minDR_Dpt_2match->Write();
   h_top_gentop_minDR_Dpt_1match->Write();
   h_top_gentop_minDR_Dpt_0match->Write();
}
