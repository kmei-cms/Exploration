#define NtupleClassMicroNtuple_cxx
#include "NtupleClassMicroNtuple.h"
#include <TH1D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

#include "EventShapeVariables.h"

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

void NtupleClassMicroNtuple::Loop()
{
   if (fChain == 0) return;


   bool verbose ;

  //--- Additional variables for top tagger output to be added to ntuple

   std::vector<TLorentzVector> toptag_tlv ;
   ///output_tree -> Branch( "toptag_tlv", &toptag_tlv ) ;

   std::vector<int> toptag_nconstituents ;
   ///output_tree -> Branch( "toptag_nconstituents", &toptag_nconstituents ) ;

   std::vector<int> Jets_toptag_index ;
   ///output_tree -> Branch( "Jets_toptag_index", &Jets_toptag_index ) ;

   std::vector<int> JetsAK8_toptag_index ;
   ///output_tree -> Branch( "JetsAK8_toptag_index", &JetsAK8_toptag_index ) ;


   int njets_pt45_eta24 ;
   output_tree -> Branch( "njets_pt45_eta24", &njets_pt45_eta24, "njets_pt45_eta24/I" ) ;

   float pfht_pt40_eta24 ;
   output_tree -> Branch( "pfht_pt40_eta24", &pfht_pt40_eta24, "pfht_pt40_eta24/F" ) ;

   int nbtag_csv85_pt30_eta24 ;
   output_tree -> Branch( "nbtag_csv85_pt30_eta24", &nbtag_csv85_pt30_eta24, "nbtag_csv85_pt30_eta24/I" ) ;

   int ntop1b ;
   output_tree -> Branch( "ntop1b", &ntop1b, "ntop1b/I" ) ;

   int ntop1bpt200 ;
   output_tree -> Branch( "ntop1bpt200", &ntop1bpt200, "ntop1bpt200/I" ) ;

   int ntop1bnot3prong ;
   output_tree -> Branch( "ntop1bnot3prong", &ntop1bnot3prong, "ntop1bnot3prong/I" ) ;

   int ntop1bnot3prongpt200 ;
   output_tree -> Branch( "ntop1bnot3prongpt200", &ntop1bnot3prongpt200, "ntop1bnot3prongpt200/I" ) ;

   int njetsextra_pt30_eta24 ;
   output_tree -> Branch( "njetsextra_pt30_eta24", &njetsextra_pt30_eta24, "njetsextra_pt30_eta24/I" ) ;

   float pfht7p_pt30_eta24 ;
   output_tree -> Branch( "pfht7p_pt30_eta24", &pfht7p_pt30_eta24, "pfht7p_pt30_eta24/F" ) ;

   float pfhtextra_pt30_eta24 ;
   output_tree -> Branch( "pfhtextra_pt30_eta24", &pfhtextra_pt30_eta24, "pfhtextra_pt30_eta24/F" ) ;

   int nleptons ;
   output_tree -> Branch( "nleptons", &nleptons, "nleptons/I" ) ;



   float lambda1 ;
   output_tree -> Branch( "lambda1", &lambda1, "lambda1/F" ) ;

   float lambda2 ;
   output_tree -> Branch( "lambda2", &lambda2, "lambda2/F" ) ;

   float lambda3 ;
   output_tree -> Branch( "lambda3", &lambda3, "lambda3/F" ) ;



   float lambda1nonorm ;
   output_tree -> Branch( "lambda1nonorm", &lambda1nonorm, "lambda1nonorm/F" ) ;

   float lambda2nonorm ;
   output_tree -> Branch( "lambda2nonorm", &lambda2nonorm, "lambda2nonorm/F" ) ;

   float lambda3nonorm ;
   output_tree -> Branch( "lambda3nonorm", &lambda3nonorm, "lambda3nonorm/F" ) ;


   int ntop1b_1prong ;
   output_tree -> Branch( "ntop1b_1prong", &ntop1b_1prong, "ntop1b_1prong/I" ) ;

   int ntop1b_2prong ;
   output_tree -> Branch( "ntop1b_2prong", &ntop1b_2prong, "ntop1b_2prong/I" ) ;

   int ntop1b_3prong ;
   output_tree -> Branch( "ntop1b_3prong", &ntop1b_3prong, "ntop1b_3prong/I" ) ;



   float jpt1 ;
   output_tree -> Branch( "jpt1", &jpt1, "jpt1/F" ) ;

   float jpt2 ;
   output_tree -> Branch( "jpt2", &jpt2, "jpt2/F" ) ;

   float jpt3 ;
   output_tree -> Branch( "jpt3", &jpt3, "jpt3/F" ) ;

   float jpt4 ;
   output_tree -> Branch( "jpt4", &jpt4, "jpt4/F" ) ;

   float jpt5 ;
   output_tree -> Branch( "jpt5", &jpt5, "jpt5/F" ) ;

   float jpt6 ;
   output_tree -> Branch( "jpt6", &jpt6, "jpt6/F" ) ;

   float jpt7 ;
   output_tree -> Branch( "jpt7", &jpt7, "jpt7/F" ) ;

   float jpt8 ;
   output_tree -> Branch( "jpt8", &jpt8, "jpt8/F" ) ;

   float jpt9 ;
   output_tree -> Branch( "jpt9", &jpt9, "jpt9/F" ) ;

   float jpt10 ;
   output_tree -> Branch( "jpt10", &jpt10, "jpt10/F" ) ;

   float jpt11 ;
   output_tree -> Branch( "jpt11", &jpt11, "jpt11/F" ) ;

   float jpt12 ;
   output_tree -> Branch( "jpt12", &jpt12, "jpt12/F" ) ;





   TH1F* h_njets_pt45_eta24 = new TH1F( "h_njets_pt45", "Njets, pt>45, |eta|<2.4", 11, -0.5, 10.5 ) ;
   TH1F* h_pfht_pt40_eta24 = new TH1F( "h_pfht_pt40_eta24", "PF HT, jet pt>40, |eta|<2.4", 100, 0., 4000. ) ;
   TH1F* h_nbtag_csv50 = new TH1F( "h_nbtag_csv50", "Nbtag, CSV>0.50", 6, -0.5, 5.5 ) ;





   Long64_t nentries = fChain->GetEntries();

   Long64_t nbytes = 0, nb = 0;

   Long64_t nsave(0) ;


   TopTagger tt;
   tt.setCfgFile("TopTagger.cfg");

   for (Long64_t jentry=0; jentry<nentries;jentry++) 
   {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
   
      nb = fChain->GetEntry(jentry);   
      nbytes += nb;


      if ( jentry % (nentries/20) == 0 ) { printf("  Event %9llu / %9llu  (%2.0f%%)\n", jentry, nentries, 100*(jentry*1.)/(nentries*1.) ) ; fflush(stdout) ; }


      if ( jentry < 100 ) {
         verbose = true ;
      } else {
         verbose = false ;
      }

      if ( verbose ) printf("\n\n =========== number %9llu : Run %9u , Lumi %9u , Event %9llu\n", jentry, RunNum, LumiBlockNum, EvtNum ) ;



      int rec_njet_pt45(0) ;
      int nbtag_csv50(0) ;
      int nbtag_csv85(0) ;

      njets_pt45_eta24 = 0 ;
      pfht_pt40_eta24 = 0 ;
      nbtag_csv85_pt30_eta24 = 0 ;
      ntop1b = 0 ;
      ntop1bpt200 = 0 ;
      ntop1bnot3prong = 0 ;
      ntop1bnot3prongpt200 = 0 ;
      njetsextra_pt30_eta24 = 0 ;
      pfht7p_pt30_eta24 = 0 ;
      pfhtextra_pt30_eta24 = 0 ;
      nleptons = 0 ;

      lambda1 = 0. ;
      lambda2 = 0. ;
      lambda3 = 0. ;

      lambda1nonorm = 0. ;
      lambda2nonorm = 0. ;
      lambda3nonorm = 0. ;

      ntop1b_1prong = 0 ;
      ntop1b_2prong = 0 ;
      ntop1b_3prong = 0 ;

      jpt1 = 0. ;
      jpt2 = 0. ;
      jpt3 = 0. ;
      jpt4 = 0. ;
      jpt5 = 0. ;
      jpt6 = 0. ;
      jpt7 = 0. ;
      jpt8 = 0. ;
      jpt9 = 0. ;
      jpt10 = 0. ;
      jpt11 = 0. ;
      jpt12 = 0. ;




      nleptons += Muons->size() ;
      nleptons += Electrons->size() ;

      int ngood_pt30_eta24(0) ;
      for ( unsigned int rji=0; rji<Jets->size(); rji++ ) {
         TLorentzVector tlv = Jets->at(rji) ;
         if ( tlv.Pt() > 45 && fabs(tlv.Eta()) < 2.4 ) {
            njets_pt45_eta24 += 1 ;
         }
         if ( tlv.Pt() > 40 && fabs(tlv.Eta()) < 2.4 ) {
            pfht_pt40_eta24 += tlv.Pt() ;
         }
         if ( tlv.Pt() > 30 && fabs(tlv.Eta()) < 2.4 ) {
            ngood_pt30_eta24 ++ ;
            if ( ngood_pt30_eta24 >= 7 ) {
               pfht7p_pt30_eta24 += tlv.Pt() ;
            }
            if ( Jets_bDiscriminatorCSV->at(rji) > 0.85 ) {
               nbtag_csv85_pt30_eta24 += 1 ;
            }
            if ( ngood_pt30_eta24 == 1 )  jpt1  = tlv.Pt() ;
            if ( ngood_pt30_eta24 == 2 )  jpt2  = tlv.Pt() ;
            if ( ngood_pt30_eta24 == 3 )  jpt3  = tlv.Pt() ;
            if ( ngood_pt30_eta24 == 4 )  jpt4  = tlv.Pt() ;
            if ( ngood_pt30_eta24 == 5 )  jpt5  = tlv.Pt() ;
            if ( ngood_pt30_eta24 == 6 )  jpt6  = tlv.Pt() ;
            if ( ngood_pt30_eta24 == 7 )  jpt7  = tlv.Pt() ;
            if ( ngood_pt30_eta24 == 8 )  jpt8  = tlv.Pt() ;
            if ( ngood_pt30_eta24 == 9 )  jpt9  = tlv.Pt() ;
            if ( ngood_pt30_eta24 == 10 ) jpt10 = tlv.Pt() ;
            if ( ngood_pt30_eta24 == 11 ) jpt11 = tlv.Pt() ;
            if ( ngood_pt30_eta24 == 12 ) jpt12 = tlv.Pt() ;
         }
      } // rji


     //----

      for ( unsigned int rji=0; rji < Jets->size() ; rji++ ) {

            TLorentzVector jlv( Jets->at(rji) ) ;

            if ( jlv.Pt() > 45 && fabs(jlv.Eta())<2.4 ) rec_njet_pt45++ ;
            //////////////////if ( jlv.Pt() > 40 && fabs(jlv.Eta())<2.4 ) pfht_pt40_eta24 += jlv.Pt() ;  // bug in v1
            if ( Jets_bDiscriminatorCSV->at(rji) > 0.50 ) nbtag_csv50++ ;
            if ( Jets_bDiscriminatorCSV->at(rji) > 0.85 ) nbtag_csv85++ ;

      } // rji

      h_njets_pt45_eta24 -> Fill( rec_njet_pt45 ) ;
      h_pfht_pt40_eta24 -> Fill( pfht_pt40_eta24 ) ;
      h_nbtag_csv50 -> Fill( nbtag_csv50 ) ;


      if ( do_skim ) {
         if ( rec_njet_pt45 < 6 ) continue ;
         if ( pfht_pt40_eta24 < 500 ) continue ;
         if ( nbtag_csv85 < 2 ) continue ;
      }




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



      int n_toptag_not3prong(0) ;



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

         if ( top->getNConstituents() != 3 ) n_toptag_not3prong++ ;

         if ( verbose ) {
            printf("  storing top tag %2d : Pt: %6.1f , Eta: %7.3f,  Phi: %7.3f,  Mass: %6.1f\n",
                         ti, tlv.Pt(), tlv.Eta(), tlv.Phi(), tlv.M() ) ;
         }

      } // top

      ///////////////////// if ( do_skim && n_toptag_not3prong == 0 ) continue ;






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


      std::vector<int> toptag_nb ;
      for ( unsigned int tti=0; tti < toptag_tlv.size(); tti++ ) {
         int nb(0) ;
         std::vector<int> bjets_in_this_top_tag ;
         for ( unsigned int rji=0; rji < Jets->size(); rji++ ) {
            if ( Jets_toptag_index.at(rji) == tti ) {
               if ( Jets_bDiscriminatorCSV->at(rji) > 0.85 ) {
                  nb ++ ;
                  bjets_in_this_top_tag.push_back(rji) ;
               }
            }
         } // rji
         for ( unsigned int fji=0; fji < JetsAK8->size(); fji++ ) {
            if ( JetsAK8_toptag_index.at(fji) == tti ) {
               for ( unsigned int rji=0; rji < Jets->size(); rji++ ) {
                  if ( calcDR( JetsAK8->at(fji), Jets->at(rji) ) < 0.8 ) {
                     bool already_in_this_top_tag(false) ;
                     for ( unsigned int bji=0; bji<bjets_in_this_top_tag.size(); bji++ ) {
                        if ( rji == bjets_in_this_top_tag[bji] ) already_in_this_top_tag = true ;
                     } // bji
                     if ( Jets_bDiscriminatorCSV->at(rji) > 0.85 && !already_in_this_top_tag ) {
                        nb ++ ;
                     }
                  } // dr match
               } // rji
            }
         } // fji
         toptag_nb.emplace_back( nb ) ;
         if ( nb == 1 ) {
            ntop1b += 1 ;
            if ( toptag_nconstituents.at(tti) == 1 ) ntop1b_1prong += 1 ;
            if ( toptag_nconstituents.at(tti) == 2 ) ntop1b_2prong += 1 ;
            if ( toptag_nconstituents.at(tti) == 3 ) ntop1b_3prong += 1 ;
            if ( toptag_tlv.at(tti).Pt() > 200 ) ntop1bpt200 += 1 ;
            if ( toptag_nconstituents.at(tti) != 3 ) ntop1bnot3prong += 1 ;
            if ( toptag_tlv.at(tti).Pt() > 200 && toptag_nconstituents.at(tti) != 3 ) ntop1bnot3prongpt200 += 1 ;
         }
      } // tti

      for ( unsigned int rji=0; rji < Jets->size(); rji++ ) {
         bool in_a_good_tag(false) ;
         if ( Jets_toptag_index.at(rji) >= 0 ) {
            if ( toptag_nb[ Jets_toptag_index.at(rji) ] == 1 ) {
               in_a_good_tag = true ;
            }
         }
         for ( unsigned int fji=0; fji<JetsAK8->size(); fji++ ) {
            if ( JetsAK8_toptag_index.at(fji) >= 0 ) {
               if ( toptag_nb[ JetsAK8_toptag_index.at(fji)] == 1 ) {
                  double dr = calcDR( Jets->at(rji), JetsAK8->at(fji) ) ;
                  if ( dr < 0.8 ) in_a_good_tag = true ;
               }
            }
         } // fji
         if ( !in_a_good_tag ) {
            if ( Jets->at(rji).Pt() > 30 && fabs(Jets->at(rji).Eta())<2.4 ) {
               njetsextra_pt30_eta24 += 1 ;
               pfhtextra_pt30_eta24 += Jets->at(rji).Pt() ;
            }
         } // is extra (not in a good tag)?
      } // rji








      //--- Find boost to CM frame.

      TLorentzVector rlv_all_jets ;

      for ( unsigned int rji=0; rji < Jets->size() ; rji++ ) {

         TLorentzVector jlv( Jets->at(rji) ) ;

         rlv_all_jets += jlv ;

      } // rji






      double reco_jets_beta = rlv_all_jets.Pz() / rlv_all_jets.E() ;

      TVector3 rec_boost_beta_vec( 0., 0., -1.*reco_jets_beta ) ;



     //--- Fill vector of jet momenta in CM frame.

      std::vector<math::RThetaPhiVector> cm_jets ;

      for ( unsigned int rji=0; rji < Jets->size() ; rji++ ) {

         TLorentzVector jlvcm( Jets->at(rji) ) ;
         jlvcm.Boost( rec_boost_beta_vec ) ;

         math::RThetaPhiVector cmvec( jlvcm.P(), jlvcm.Theta(), jlvcm.Phi() ) ;
         cm_jets.push_back( cmvec ) ;

      } // rji




     //--- Compute event shape variables and eigenvalues of jet momentum tensor.

      EventShapeVariables esv( cm_jets ) ;
      double sphericity = esv.sphericity() ;
      double aplanarity = esv.aplanarity() ;
      double es_c = esv.C() ;
      double es_d = esv.D() ;

      TVectorD eigen_vals_norm = esv.getEigenValues() ;
      TVectorD eigen_vals_nonorm = esv.getEigenValuesNoNorm() ;

      lambda1 = eigen_vals_norm[0] ;
      lambda2 = eigen_vals_norm[1] ;
      lambda3 = eigen_vals_norm[2] ;

      lambda1nonorm = eigen_vals_nonorm[0] ;
      lambda2nonorm = eigen_vals_nonorm[1] ;
      lambda3nonorm = eigen_vals_nonorm[2] ;

      if ( verbose ) {

         printf("\n\n =========== number %9llu : Run %9u , Lumi %9u , Event %9llu\n", jentry, RunNum, LumiBlockNum, EvtNum ) ;

         printf("   Number of extra jets : %2.0f\n", njetsextra_pt30_eta24 ) ;
         printf("   Sphericity : %6.3f\n", sphericity ) ;
         printf("   Aplanarity : %6.3f\n", aplanarity ) ;
         printf("   C          : %6.3f\n", es_c ) ;
         printf("   D          : %6.3f\n", es_d ) ;

         printf("   Normalized   eigen values       :  %9.3f , %9.3f, %9.3f\n", eigen_vals_norm[0], eigen_vals_norm[1], eigen_vals_norm[2] ) ;
         printf("   Unnormalized eigen values (sqrt):  %9.1f , %9.1f, %9.1f\n", sqrt(eigen_vals_nonorm[0]), sqrt(eigen_vals_nonorm[1]), sqrt(eigen_vals_nonorm[2]) ) ;
         printf("   Unnormalized eigen values       :  %9.1f , %9.1f, %9.1f\n", eigen_vals_nonorm[0], eigen_vals_nonorm[1], eigen_vals_nonorm[2] ) ;

      }






      nsave++ ;

      output_tree -> Fill() ;
      
      
   } // jentry

   if ( do_skim ) {

      printf("\n\n  Saved %lld / %lld (%.6f) in skimmed output.\n\n", nsave, nentries, (1.*nsave)/(1.*nentries) ) ;

   }

   output_tree -> AutoSave() ;

   h_njets_pt45_eta24 -> Write() ;
   h_pfht_pt40_eta24 -> Write() ;
   h_nbtag_csv50 -> Write() ;


} // Loop





