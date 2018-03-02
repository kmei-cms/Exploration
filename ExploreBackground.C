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
    TH1::SetDefaultSumw2();

    // Declare all your histograms here, that way we can fill them for multiple chains
    std::vector<std::string> jettypes {"pt30", "pt45"};
    for(std::string jettype : jettypes)
    {
        std::string base = "h_njets_" + jettype;
        my_histos.emplace(base,new TH1D(base.c_str(),base.c_str(),15,0,15));
        
        my_histos.emplace(base + "_0l",new TH1D( (base+"_0l").c_str(),(base+"_0l").c_str(),17,0,17));
        my_histos.emplace(base + "_1l",new TH1D((base+"_1l").c_str(),(base+"_1l").c_str(),15,0,15));
        my_histos.emplace(base + "_2l",new TH1D((base+"_2l").c_str(),(base+"_2l").c_str(),15,0,15));
        
        my_histos.emplace(base + "_0l_g1b",new TH1D((base+"_0l_g1b").c_str(),(base+"_0l_g1b").c_str(),17,0,17));
        my_histos.emplace(base + "_1l_g1b",new TH1D((base+"_1l_g1b").c_str(),(base+"_1l_g1b").c_str(),15,0,15));
        my_histos.emplace(base + "_2l_g1b",new TH1D((base+"_2l_g1b").c_str(),(base+"_2l_g1b").c_str(),15,0,15));
        
        my_histos.emplace(base + "_0l_g1b_ht500",new TH1D((base+"_0l_g1b_ht500").c_str(),(base+"_0l_g1b_ht500").c_str(),17,0,17));
        my_histos.emplace(base + "_1l_g1b_ht500",new TH1D((base+"_1l_g1b_ht500").c_str(),(base+"_1l_g1b_ht500").c_str(),15,0,15));
        my_histos.emplace(base + "_2l_g1b_ht500",new TH1D((base+"_2l_g1b_ht500").c_str(),(base+"_2l_g1b_ht500").c_str(),15,0,15));
        
        my_histos.emplace(base + "_0l_g1b_g1t",new TH1D((base+"_0l_g1b_g1t").c_str(),(base+"_0l_g1b_g1t").c_str(),17,0,17));
        my_histos.emplace(base + "_1l_g1b_g1t",new TH1D((base+"_1l_g1b_g1t").c_str(),(base+"_1l_g1b_g1t").c_str(),15,0,15));
        my_histos.emplace(base + "_2l_g1b_g1t",new TH1D((base+"_2l_g1b_g1t").c_str(),(base+"_2l_g1b_g1t").c_str(),15,0,15));
        
        my_histos.emplace(base + "_0l_g1b_g1t_ht500",new TH1D((base+"_0l_g1b_g1t_ht500").c_str(),(base+"_0l_g1b_g1t_ht500").c_str(),17,0,17));
        my_histos.emplace(base + "_1l_g1b_g1t_ht500",new TH1D((base+"_1l_g1b_g1t_ht500").c_str(),(base+"_1l_g1b_g1t_ht500").c_str(),15,0,15));
        my_histos.emplace(base + "_2l_g1b_g1t_ht500",new TH1D((base+"_2l_g1b_g1t_ht500").c_str(),(base+"_2l_g1b_g1t_ht500").c_str(),15,0,15));

        my_histos.emplace(base + "_1l_g1b_mbl",new TH1D((base+"_1l_g1b_mbl").c_str(),(base+"_1l_g1b_mbl").c_str(),15,0,15));
        my_histos.emplace(base + "_1l_g1b_mbl_g1t",new TH1D((base+"_1l_g1b_mbl_g1t").c_str(),(base+"_1l_g1b_mbl_g1t").c_str(),15,0,15));
        
        // For Z->ll control region
        my_histos.emplace(base + "_2l_onZ",new TH1D((base+"_2l_onZ").c_str(),(base+"_2l_onZ").c_str(),15,0,15));
        my_histos.emplace(base + "_2l_onZ_g1b",new TH1D((base+"_2l_onZ_g1b").c_str(),(base+"_2l_onZ_g1b").c_str(),15,0,15));
        my_histos.emplace(base + "_2l_onZ_g1b_nombl",new TH1D((base+"_2l_onZ_g1b_nombl").c_str(),(base+"_2l_onZ_g1b_nombl").c_str(),15,0,15));
        my_histos.emplace(base + "_2l_onZ_g1b_g1t",new TH1D((base+"_2l_onZ_g1b_g1t").c_str(),(base+"_2l_onZ_g1b_g1t").c_str(),15,0,15));
    }
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

      double eventweight = Weight;
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
      int rec_njet_pt30(0) ;
      int rec_njet_pt45_btag(0) ;
      int rec_njet_pt30_btag(0) ;
      double HT_trigger = 0.0;
      std::vector<TLorentzVector> rec_bjets_pt30;
      for ( unsigned int rji=0; rji < Jets->size() ; rji++ ) {
          TLorentzVector jlv( Jets->at(rji) ) ;
          if (abs(jlv.Eta()) > 2.4) continue;
          if ( jlv.Pt() > 30 ) 
          {
              rec_njet_pt30++;
              if ( Jets_bDiscriminatorCSV->at(rji) > 0.8484) 
              {
                  rec_njet_pt30_btag++;
                  rec_bjets_pt30.push_back(jlv);
              }
          }
          if (jlv.Pt() > 40)
              HT_trigger += jlv.Pt();
          if ( jlv.Pt() > 45 ) 
          {
              rec_njet_pt45++ ;
              if ( Jets_bDiscriminatorCSV->at(rji) > 0.8484) 
              {
                  rec_njet_pt45_btag++;
              }
          }
      } 
      if ( !( HT_trigger>500 && rec_njet_pt45>=6 ) ) 
          passTrigger = false;

      // Count leptons > 30 GeV
      std::vector<TLorentzVector> rec_muon_pt30;
      std::vector<int> rec_charge_muon_pt30;
      for (unsigned int imu = 0; imu < Muons->size(); ++imu)
      {
          TLorentzVector lvmu(Muons->at(imu));
          if( abs(lvmu.Eta()) < 2.4 && lvmu.Pt() > 30 && Muons_passIso->at(imu))
          {
              rec_muon_pt30.push_back(lvmu);
              rec_charge_muon_pt30.push_back(Muons_charge->at(imu));
          }
      }
      std::vector<TLorentzVector> rec_electron_pt30;
      std::vector<int> rec_charge_electron_pt30;
      for (unsigned int iel = 0; iel < Electrons->size(); ++iel)
      {
          TLorentzVector lvel(Electrons->at(iel));
          if( abs(lvel.Eta()) < 2.4 && lvel.Pt() > 30 && Electrons_tightID->at(iel) && Electrons_passIso->at(iel))
          {
              rec_electron_pt30.push_back(lvel);
              rec_charge_electron_pt30.push_back(Electrons_charge->at(iel));
          }
      }
      int nleptons = rec_muon_pt30.size() + rec_electron_pt30.size();
      bool passBaseline0l = nleptons==0 && rec_njet_pt45>=6 && HT_trigger > 500 && rec_njet_pt45_btag >= 1;
      bool passBaseline1l = nleptons==1 && rec_njet_pt30>=6 ;
      bool passBaseline2l = nleptons==2;

      bool passNtop = tops.size() >= 1;
      bool passNb = rec_njet_pt45_btag >= 1;
      bool onZ = false;
      bool passMbl_2l = false;
      if ( (rec_muon_pt30.size() == 2) && (rec_charge_muon_pt30[0] != rec_charge_muon_pt30[1]) )
      {
          double mll = (rec_muon_pt30[0] + rec_muon_pt30[1]).M();
          if( mll > 81.2 && mll < 101.2)
              onZ = true;          

          // check whether a bl pair passes the M(b,l) cut
          for (TLorentzVector myb : rec_bjets_pt30)
          {
              double mass_bl_1 = (rec_muon_pt30[0] + myb).M();
              if(mass_bl_1 < 180 && mass_bl_1 > 30)
                  passMbl_2l = true;
              double mass_bl_2 = (rec_muon_pt30[1] + myb).M();
              if(mass_bl_2 < 180 && mass_bl_2 > 30)
                  passMbl_2l = true;
          }
      } 
      else if ( (rec_electron_pt30.size() == 2) && (rec_charge_electron_pt30[0] != rec_charge_electron_pt30[1]) )
      {
          double mll = (rec_electron_pt30[0] + rec_electron_pt30[1]).M();
          if( mll > 81.2 && mll < 101.2)
              onZ = true;  
          // check whether a bl pair passes the M(b,l) cut
          for (TLorentzVector myb : rec_bjets_pt30)
          {
              double mass_bl_1 = (rec_electron_pt30[0] + myb).M();
              if(mass_bl_1 < 180 && mass_bl_1 > 30)
                  passMbl_2l = true;
              double mass_bl_2 = (rec_electron_pt30[1] + myb).M();
              if(mass_bl_2 < 180 && mass_bl_2 > 30)
                  passMbl_2l = true;
          }
      }
        
      // -------------------------
      // -- Check r(j) behavior --
      // -------------------------

      int njets_rj = 0;
      std::vector<std::string> jettypes {"pt30", "pt45"};
      for(std::string jettype : jettypes)
      {
          if(jettype == "pt30")
              njets_rj = rec_njet_pt30;
          else if(jettype == "pt45")
              njets_rj = rec_njet_pt45;
          std::string base = "h_njets_" + jettype;

          my_histos[base]->Fill(njets_rj, eventweight);
          if(nleptons == 0)
              my_histos[base+"_0l"]->Fill(njets_rj, eventweight);
          else if(nleptons == 1)
              my_histos[base+"_1l"]->Fill(njets_rj, eventweight);
          else if(nleptons == 2)
              my_histos[base+"_2l"]->Fill(njets_rj, eventweight);
          if (passNb)
          {
              if(nleptons == 0)
                  my_histos[base+"_0l_g1b"]->Fill(njets_rj, eventweight);
              else if(nleptons == 1)
                  my_histos[base+"_1l_g1b"]->Fill(njets_rj, eventweight);
              else if(nleptons == 2)
                  my_histos[base+"_2l_g1b"]->Fill(njets_rj, eventweight);
              
              if (HT_trigger > 500)
              {
                  if(nleptons == 0)
                      my_histos[base+"_0l_g1b_ht500"]->Fill(njets_rj, eventweight);
                  else if(nleptons == 1)
                      my_histos[base+"_1l_g1b_ht500"]->Fill(njets_rj, eventweight);
                  else if(nleptons == 2)
                      my_histos[base+"_2l_g1b_ht500"]->Fill(njets_rj, eventweight);
              }
              
              if (passNtop)
              {
                  if(nleptons == 0)
                      my_histos[base+"_0l_g1b_g1t"]->Fill(njets_rj, eventweight);
                  else if(nleptons == 1)
                      my_histos[base+"_1l_g1b_g1t"]->Fill(njets_rj, eventweight);
                  else if(nleptons == 2)
                      my_histos[base+"_2l_g1b_g1t"]->Fill(njets_rj, eventweight);
                  
                  if (HT_trigger > 500)
                  {
                      if(nleptons == 0)
                          my_histos[base+"_0l_g1b_g1t_ht500"]->Fill(njets_rj, eventweight);
                      else if(nleptons == 1)
                          my_histos[base+"_1l_g1b_g1t_ht500"]->Fill(njets_rj, eventweight);
                      else if(nleptons == 2)
                          my_histos[base+"_2l_g1b_g1t_ht500"]->Fill(njets_rj, eventweight);
                  }
              }
          }

          // Dedicated 1l region
          if(nleptons == 1 && passNb)
          {
              TLorentzVector mylepton = (rec_electron_pt30.size() == 1) ? rec_electron_pt30[0] : rec_muon_pt30[0];
              bool passMtop = false;
              for (TLorentzVector myb : rec_bjets_pt30)
              {
                  double mass_bl = (mylepton + myb).M();
                  if(mass_bl < 180 && mass_bl > 30)
                      passMtop = true;
              }
              if(passMtop)
              {
                  my_histos[base+"_1l_g1b_mbl"]->Fill(njets_rj, eventweight);
                  if(passNtop)
                  {
                      my_histos[base+"_1l_g1b_mbl_g1t"]->Fill(njets_rj, eventweight);
                  }
              }
          }
          
          // Now for the Z->ll region
          // h_njets_2l_onZ_g1b_g1t
          if (onZ)
          {
              my_histos[base+"_2l_onZ"]->Fill(njets_rj, eventweight);
              if(passNb)
              {
                  my_histos[base+"_2l_onZ_g1b"]->Fill(njets_rj, eventweight);
                  if(!passMbl_2l)
                  {
                      my_histos[base+"_2l_onZ_g1b_nombl"]->Fill(njets_rj, eventweight);
                  }
                  
                  if(passNtop)
                  {
                      my_histos[base+"_2l_onZ_g1b_g1t"]->Fill(njets_rj, eventweight);
                  }
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
