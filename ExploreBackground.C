#define ExploreBackground_cxx
#include "ExploreBackground.h"

#include "Utility.h"
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


void ExploreBackground::InitHistos()
{
    // Declare all your histograms here, that way we can fill them for multiple chains
    my_histos.emplace("h_HT",new TH1D("h_HT","h_HT",60,0,3000));
    my_histos.emplace("h_njets",new TH1D("h_njets","h_njets",15,0,15));

    my_histos.emplace("h_njets_0l",new TH1D("h_njets_0l","h_njets_0l",15,0,15));
    my_histos.emplace("h_njets_1l",new TH1D("h_njets_1l","h_njets_1l",15,0,15));
    my_histos.emplace("h_njets_2l",new TH1D("h_njets_2l","h_njets_2l",15,0,15));

    my_histos.emplace("h_njets_0l_g1b",new TH1D("h_njets_0l_g1b","h_njets_0l_g1b",15,0,15));
    my_histos.emplace("h_njets_1l_g1b",new TH1D("h_njets_1l_g1b","h_njets_1l_g1b",15,0,15));
    my_histos.emplace("h_njets_2l_g1b",new TH1D("h_njets_2l_g1b","h_njets_2l_g1b",15,0,15));

    my_histos.emplace("h_njets_0l_g1b_ht500",new TH1D("h_njets_0l_g1b_ht500","h_njets_0l_g1b_ht500",15,0,15));
    my_histos.emplace("h_njets_1l_g1b_ht500",new TH1D("h_njets_1l_g1b_ht500","h_njets_1l_g1b_ht500",15,0,15));
    my_histos.emplace("h_njets_2l_g1b_ht500",new TH1D("h_njets_2l_g1b_ht500","h_njets_2l_g1b_ht500",15,0,15));

    my_histos.emplace("h_njets_0l_g1b_g1t",new TH1D("h_njets_0l_g1b_g1t","h_njets_0l_g1b_g1t",15,0,15));
    my_histos.emplace("h_njets_1l_g1b_g1t",new TH1D("h_njets_1l_g1b_g1t","h_njets_1l_g1b_g1t",15,0,15));
    my_histos.emplace("h_njets_2l_g1b_g1t",new TH1D("h_njets_2l_g1b_g1t","h_njets_2l_g1b_g1t",15,0,15));

    my_histos.emplace("h_njets_0l_g1b_g1t_ht500",new TH1D("h_njets_0l_g1b_g1t_ht500","h_njets_0l_g1b_g1t_ht500",15,0,15));
    my_histos.emplace("h_njets_1l_g1b_g1t_ht500",new TH1D("h_njets_1l_g1b_g1t_ht500","h_njets_1l_g1b_g1t_ht500",15,0,15));
    my_histos.emplace("h_njets_2l_g1b_g1t_ht500",new TH1D("h_njets_2l_g1b_g1t_ht500","h_njets_2l_g1b_g1t_ht500",15,0,15));

}

void ExploreBackground::Loop(double weight, int maxevents, bool isQuiet)
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes_total = 0, nbytes = 0;

   TopTagger tt;
   tt.setCfgFile("TopTagger.cfg");

   for (Long64_t jentry=0; jentry<nentries;jentry++) 
   {
      if (maxevents > 0 && jentry >= maxevents) break;
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
   
      nbytes = fChain->GetEntry(jentry);   
      nbytes_total += nbytes;

      if ( jentry % 1000 == 0 ) printf("  Event %9llu\n", jentry ) ;

      // -----------------
      // check for number of hadronic tops at gen level
      // -----------------
      int nhadWs = 0;
      std::vector<TLorentzVector> hadtops;
      std::vector<TLorentzVector> hadWs;
      std::vector<int> hadtops_idx;
      std::vector<std::vector<const TLorentzVector*> > hadtopdaughters;
      std::vector<TLorentzVector> neutralinos;
      std::vector<TLorentzVector> singlets;
      std::vector<TLorentzVector> singlinos;
      for ( unsigned int gpi=0; gpi < GenParticles->size() ; gpi++ ) 
      {
          int pdgid = abs( GenParticles_PdgId->at(gpi) ) ;
          int momid = abs( GenParticles_ParentId->at(gpi) ) ;
          int momidx = GenParticles_ParentIdx->at(gpi);
          int status = GenParticles_Status->at(gpi);
          if(pdgid == 1000022 && (status==22 || status == 52))
          {
              neutralinos.push_back(GenParticles->at(gpi));
          }
          if(pdgid == 5000001 && (status == 22 || status == 52))
          {
              singlinos.push_back(GenParticles->at(gpi));
          }
          if(pdgid == 5000002 && (status == 22 || status == 52))
          {
              singlets.push_back(GenParticles->at(gpi));
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

      // get set of all constituents (i.e. AK4 and AK8 jets) used in one of the tops
      std::set<Constituent const *> usedConstituents = ttr.getUsedConstituents();

          
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

      int nleptons = Muons->size() + Electrons->size();
      bool passBaseline = HT_pt40>500 && rec_njet_pt45>=6 && rec_njet_pt45_btag>1 && tops.size()>1;
      bool passNtop = tops.size() >= 1;
      bool passNb = rec_njet_pt45_btag >= 1;

      // -------------------------
      // -- Check r(j) behavior --
      // -------------------------

      my_histos["h_njets"]->Fill(rec_njet_pt45, weight);
      if(nleptons == 0)
          my_histos["h_njets_0l"]->Fill(rec_njet_pt45, weight);
      else if(nleptons == 1)
          my_histos["h_njets_1l"]->Fill(rec_njet_pt45, weight);
      else if(nleptons == 2)
          my_histos["h_njets_2l"]->Fill(rec_njet_pt45, weight);
      if (passNb)
      {
          if(nleptons == 0)
              my_histos["h_njets_0l_g1b"]->Fill(rec_njet_pt45, weight);
          else if(nleptons == 1)
              my_histos["h_njets_1l_g1b"]->Fill(rec_njet_pt45, weight);
          else if(nleptons == 2)
              my_histos["h_njets_2l_g1b"]->Fill(rec_njet_pt45, weight);

          if (HT_pt40 > 500)
          {
              if(nleptons == 0)
                  my_histos["h_njets_0l_g1b_ht500"]->Fill(rec_njet_pt45, weight);
              else if(nleptons == 1)
                  my_histos["h_njets_1l_g1b_ht500"]->Fill(rec_njet_pt45, weight);
              else if(nleptons == 2)
                  my_histos["h_njets_2l_g1b_ht500"]->Fill(rec_njet_pt45, weight);
          }
          
          if (passNtop)
          {
              if(nleptons == 0)
                  my_histos["h_njets_0l_g1b_g1t"]->Fill(rec_njet_pt45, weight);
              else if(nleptons == 1)
                  my_histos["h_njets_1l_g1b_g1t"]->Fill(rec_njet_pt45, weight);
              else if(nleptons == 2)
                  my_histos["h_njets_2l_g1b_g1t"]->Fill(rec_njet_pt45, weight);
              
              if (HT_pt40 > 500)
              {
                  if(nleptons == 0)
                      my_histos["h_njets_0l_g1b_g1t_ht500"]->Fill(rec_njet_pt45, weight);
                  else if(nleptons == 1)
                      my_histos["h_njets_1l_g1b_g1t_ht500"]->Fill(rec_njet_pt45, weight);
                  else if(nleptons == 2)
                      my_histos["h_njets_2l_g1b_g1t_ht500"]->Fill(rec_njet_pt45, weight);
              }
          }
      }

   }

}

void ExploreBackground::WriteHistos()
{
    for (const auto &p : my_histos) {
        p.second->Write();
    }
    
    for (const auto &p : my_2d_histos) {
        p.second->Write();
    }
    
    for (const auto &p : my_efficiencies) {
        p.second->Write();
    }
    
}
