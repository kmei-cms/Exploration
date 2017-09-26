#define NtupleClassAddTopVars_cxx
#include "NtupleClassAddTopVars.h"
#include <TH1D.h>
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

double calcDR( TLorentzVector& lv1, TLorentzVector& lv2 ) {
   double dphi = calcDPhi( lv1.Phi(), lv2.Phi() ) ;
   double deta = fabs( lv1.Eta() - lv2.Eta() ) ;
   return sqrt( dphi*dphi + deta*deta ) ;
}

void NtupleClassAddTopVars::Loop()
{
   if (fChain == 0) return;


   bool verbose ;

  //--- Additional variables for top tagger output to be added to ntuple

   std::vector<TLorentzVector> toptag_tlv ;
   output_tree -> Branch( "toptag_tlv", &toptag_tlv ) ;

   std::vector<int> toptag_nconstituents ;
   output_tree -> Branch( "toptag_nconstituents", &toptag_nconstituents ) ;

   std::vector<int> Jets_toptag_index ;
   output_tree -> Branch( "Jets_toptag_index", &Jets_toptag_index ) ;

   std::vector<int> JetsAK8_toptag_index ;
   output_tree -> Branch( "JetsAK8_toptag_index", &JetsAK8_toptag_index ) ;







   Long64_t nentries = fChain->GetEntries();

   Long64_t nbytes = 0, nb = 0;


   TopTagger tt;
   tt.setCfgFile("TopTagger.cfg");

   for (Long64_t jentry=0; jentry<nentries;jentry++) 
   {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
   
      nb = fChain->GetEntry(jentry);   
      nbytes += nb;

      if ( jentry % (nentries/10) == 0 ) printf("  Event %9llu / %9llu  (%2.0f%%)\n", jentry, nentries, 100*(jentry*1.)/(nentries*1.) ) ;


      if ( jentry < 100 ) {
         verbose = true ;
      } else {
         verbose = false ;
      }

      if ( verbose ) printf("\n\n =========== number %9llu : Run %9u , Lumi %9u , Event %9llu\n", jentry, RunNum, LumiBlockNum, EvtNum ) ;


      // Try to get the hadronic tops in the event
      // genparticles seem to have a new ordering here, so make a dummy list
      std::vector<int> mydummylist;
      for(int d=0; d<GenParticles->size(); ++d)
          mydummylist.push_back(d);
/*
      std::vector<TLorentzVector> hadtops = ttUtility::GetHadTopLVec(*GenParticles, *GenParticles_PdgId, mydummylist, *GenParticles_ParentIdx);
      for (TLorentzVector hadtop : hadtops){
          std::cout << hadtop.M() << ", " << hadtop.Pt() << std::endl;
      }
*/
      // Use helper function to create input list 
      // Create AK4 inputs object
      ttUtility::ConstAK4Inputs AK4Inputs = ttUtility::ConstAK4Inputs(*Jets, *Jets_bDiscriminatorCSV);
    

      // stick all the subjets in one list for now (this is what the top tagger expects)
      std::vector<TLorentzVector> JetsAK8_subjets_all;
      for (std::vector<TLorentzVector> subjets : *JetsAK8_subjets)
      {
          for (TLorentzVector subjet : subjets)
              JetsAK8_subjets_all.push_back(subjet);
      }
      
      // Create AK8 inputs object
      ttUtility::ConstAK8Inputs AK8Inputs = ttUtility::ConstAK8Inputs(
          *JetsAK8,
          *JetsAK8_NsubjettinessTau1,
          *JetsAK8_NsubjettinessTau2,
          *JetsAK8_NsubjettinessTau3,
          *JetsAK8_softDropMass,
          JetsAK8_subjets_all    // These should be the subjets!
          );
      
      // Create jets constituents list combining AK4 and AK8 jets, these are used to construct top candiates
      // The vector of input constituents can also be constructed "by hand"
      std::vector<Constituent> constituents = ttUtility::packageConstituents(AK4Inputs, AK8Inputs);

      // run the top tagger
      tt.runTagger(constituents);

      // retrieve the top tagger results object
      const TopTaggerResults& ttr = tt.getResults();

      // get reconstructed top
      const std::vector<TopObject*>& tops = ttr.getTops();

      // print the number of tops found in the event 
      if( verbose )
          printf("\tN tops: %ld\n", tops.size());

      if ( verbose ) 
      {
          // print top properties
          for(const TopObject* top : tops)
          {
              //print basic top properties (top->p() gives a TLorentzVector)
              //N constituents refers to the number of jets included in the top
              //3 for resolved tops 
              //2 for W+jet tops
              //1 for fully merged AK8 tops
              printf("\tTop properties: N constituents: %3d,   Pt: %6.1lf,   Eta: %7.3lf,   Phi: %7.3lf,   Mass: %6.1lf\n",
                 top->getNConstituents(), top->p().Pt(), top->p().Eta(), top->p().Phi(), top->p().M());
              
              //get vector of top constituents 
              const std::vector<Constituent const *>& constituents = top->getConstituents();
              
              //Print properties of individual top constituent jets 
              for(const Constituent* constituent : constituents)
              {
                  printf("\t\tConstituent properties: Constituent type: %3d,   Pt: %6.1lf,   Eta: %7.3lf,   Phi: %7.3lf,   Mass: %6.1lf\n",
                      constituent->getType(), constituent->p().Pt(), constituent->p().Eta(), constituent->p().Phi(), constituent->p().M());
              }        
          }        
      }






     //--- load the new top tag ntuple variables.


      toptag_tlv.clear() ;
      toptag_nconstituents.clear() ;
      Jets_toptag_index.clear() ;
      JetsAK8_toptag_index.clear() ;

      for ( int ti=0; ti<tops.size() ; ti++ ) {

         const TopObject* top = tops.at(ti) ;

         TLorentzVector tlv( top->p() ) ;
         toptag_tlv.emplace_back( tlv ) ;
         toptag_nconstituents.emplace_back( top->getNConstituents() ) ;

         if ( verbose ) {
            printf("  storing top tag %2d : Pt: %6.1f , Eta: %7.3f,  Phi: %7.3f,  Mass: %6.1f\n",
                         ti, tlv.Pt(), tlv.Eta(), tlv.Phi(), tlv.M() ) ;
         }

      } // top




      for ( int ji=0; ji<Jets->size() ; ji++ ) {

         TLorentzVector jlv( Jets->at(ji) ) ;

         int ttind(-1) ;

         for ( int ti=0; ti<tops.size() ; ti++ ) {

             const TopObject* top = tops.at(ti) ;

             const std::vector<Constituent const *>& constituents = top->getConstituents();
             for ( int tci=0; tci<constituents.size(); tci++ ) {

                TLorentzVector tclv( constituents.at( tci )->p() ) ; 

                double dr = calcDR( jlv, tclv ) ;
                if ( dr < 0.001 ) {
                   ttind = ti ;
                   if ( verbose ) {
                      printf( " top tag %2d constituent %d matches AK4 jet %2d : dR = %7.4f\n", ti, tci, ji, dr ) ;
                   }
                }

             } // tci

         } // ti.

         Jets_toptag_index.emplace_back( ttind ) ;

      } // ji




      for ( int ji=0; ji<JetsAK8->size() ; ji++ ) {

         TLorentzVector jlv( JetsAK8->at(ji) ) ;

         int ttind(-1) ;

         for ( int ti=0; ti<tops.size() ; ti++ ) {

             const TopObject* top = tops.at(ti) ;

             const std::vector<Constituent const *>& constituents = top->getConstituents();
             for ( int tci=0; tci<constituents.size(); tci++ ) {

                TLorentzVector tclv( constituents.at( tci )->p() ) ; 

                double dr = calcDR( jlv, tclv ) ;
                if ( dr < 0.001 ) {
                   ttind = ti ;
                   if ( verbose ) {
                      printf( " top tag %2d constituent %d matches AK8 jet %2d : dR = %7.4f\n", ti, tci, ji, dr ) ;
                   }
                }

             } // tci

         } // ti.

         JetsAK8_toptag_index.emplace_back( ttind ) ;

      } // ji






      output_tree -> Fill() ;
      
      
   } // jentry

   output_tree -> AutoSave() ;


} // Loop





