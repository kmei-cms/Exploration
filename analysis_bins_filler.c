#include "cut_var.h"
#include "utility_functions.h"
#define analysis_bins_filler_cxx
#include "analysis_bins_filler.h"
#include "bin_1d.h"
#include "bin_nd.h"
#include "histio.c"


void analysis_bins_filler::Loop()
{

   gDirectory -> Delete( "h*" ) ;

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();


   double njets_pt45_eta24(0.) ;
   double pfht_pt40_eta24(0.) ;
   double nbtag_csv85_pt30_eta24(0.) ;
   double ntop1bnot3prong(0.) ;
   double ntop1b(0.) ;
   double pfht7p_pt30_eta24(0.) ;
   double pfhtextra_pt30_eta24(0.) ;
   double nleptons(0.) ;

      bin_1d* bin ;

    //----

      double njetsextra_pt30_eta24(0.) ;

      vector<bin_1d*> nj_bins ;

      bin = new bin_1d( "nje0to2", "Nje 0-2", "Njets(extra) in 0 to 2", njetsextra_pt30_eta24, 0, 2 ) ;
      nj_bins.push_back( bin ) ;

      bin = new bin_1d( "nje3to4", "Nje 3-4", "Njets(extra) in 3 to 4", njetsextra_pt30_eta24, 3, 4 ) ;
      nj_bins.push_back( bin ) ;

      bin = new bin_1d( "nje5to6", "Nje 5-6", "Njets(extra) in 5 to 6", njetsextra_pt30_eta24, 5, 6 ) ;
      nj_bins.push_back( bin ) ;

      bin = new bin_1d( "nje7p", "Nje 7+", "Njets(extra) in 7+", njetsextra_pt30_eta24, 7, 20 ) ;
      nj_bins.push_back( bin ) ;


      printf("\n") ;
      for ( bi=0; bi<nj_bins.size(); bi++ ) {
         printf("  %2d : %10s : %s\n", bi, nj_bins[bi]->get_name(), nj_bins[bi]->get_description() ) ;
      } // bi
      printf("\n") ;

    //----

      double dtop_cat ;

      vector<bin_1d*> dtop_bins ;

      bin = new bin_1d( "dtop11", "TT 1-1", "double top, 1-prong & 1-prong", dtop_cat, 1, 1 ) ;
      dtop_bins.push_back( bin ) ;

      bin = new bin_1d( "dtop12", "TT 1-2", "double top, 1-prong & 2-prong", dtop_cat, 2, 2 ) ;
      dtop_bins.push_back( bin ) ;

      bin = new bin_1d( "dtop13", "TT 1-3", "double top, 1-prong & 3-prong", dtop_cat, 3, 3 ) ;
      dtop_bins.push_back( bin ) ;

      bin = new bin_1d( "dtop22", "TT 2-2", "double top, 2-prong & 2-prong", dtop_cat, 4, 4 ) ;
      dtop_bins.push_back( bin ) ;

      bin = new bin_1d( "dtop23", "TT 2-3", "double top, 2-prong & 3-prong", dtop_cat, 5, 5 ) ;
      dtop_bins.push_back( bin ) ;


      printf("\n") ;
      for ( bi=0; bi<dtop_bins.size(); bi++ ) {
         printf("  %2d : %10s : %s\n", bi, dtop_bins[bi]->get_name(), dtop_bins[bi]->get_description() ) ;
      } // bi
      printf("\n") ;


    //----

      vector<bin_nd*> analysis_bins ;

      for ( int nji=0; nji<nj_bins.size(); nji++ ) {
         for ( int dti=0; dti<dtop_bins.size(); dti++ ) {
            char name[100] ;
            char short_description[100] ;
            char description[100] ;
            sprintf( name, "%s_%s", nj_bins[nji]->get_name(), dtop_bins[dti]->get_name() ) ;
            sprintf( description, "%s ; %s", nj_bins[nji]->get_description(), dtop_bins[dti]->get_description() ) ;
            sprintf( short_description, "%s ; %s", nj_bins[nji]->get_short_description(), dtop_bins[dti]->get_short_description() ) ;
            bin_nd* abin = new bin_nd( name, short_description, description ) ;
            abin -> add_1d_bin( nj_bins[nji] ) ;
            abin -> add_1d_bin( dtop_bins[dti] ) ;
            analysis_bins.push_back( abin ) ;
         } // dti
      } // nji


      printf("\n") ;
      for ( int abi=0; abi<analysis_bins.size(); abi++ ) {
         printf(" %2d : %20s : %s\n", abi, analysis_bins[abi]->get_name(), analysis_bins[abi]->get_description() ) ;
      } // abi
      printf("\n") ;

      TH1F* h_analysis_bins = new TH1F( "h_analysis_bins", "Analysis bins", analysis_bins.size(), 0.5, analysis_bins.size()+0.5 ) ;
      for ( int bi=1; bi<=analysis_bins.size(); bi++ ) {
         h_analysis_bins -> GetXaxis() -> SetBinLabel( bi, analysis_bins[bi-1]->get_short_description() ) ;
      } // bi
      h_analysis_bins -> GetXaxis() -> LabelsOption( "v" ) ;

    //----



   int modnum = nentries/50 ;
   if ( modnum == 0 ) modnum = 1 ;


   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {

      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if ( jentry % modnum == 0 ) printf("  Event %9llu / %9llu  (%2.0f%%)\n", jentry, nentries, 100*(jentry*1.)/(nentries*1.) ) ;

      njets_pt45_eta24 = 0 ;
      pfht_pt40_eta24 = 0 ;
      nbtag_csv85_pt30_eta24 = 0 ;
      ntop1b = 0 ;
      ntop1bnot3prong = 0 ;
      njetsextra_pt30_eta24 = 0 ;
      pfht7p_pt30_eta24 = 0 ;
      pfhtextra_pt30_eta24 = 0 ;
      dtop_cat = -1 ;
      nleptons = 0 ;

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
         }
      } // rji

      vector<int> toptag_nb ;
      int ntop1b_1prong(0) ;
      int ntop1b_2prong(0) ;
      int ntop1b_3prong(0) ;
      for ( unsigned int tti=0; tti < toptag_tlv->size(); tti++ ) {
         int nb(0) ;
         vector<int> bjets_in_this_top_tag ;
         for ( unsigned int rji=0; rji < Jets->size(); rji++ ) {
            if ( Jets_toptag_index->at(rji) == tti ) {
               if ( Jets_bDiscriminatorCSV->at(rji) > 0.85 ) {
                  nb ++ ;
                  bjets_in_this_top_tag.push_back(rji) ;
               }
            }
         } // rji
         for ( unsigned int fji=0; fji < JetsAK8->size(); fji++ ) {
            if ( JetsAK8_toptag_index->at(fji) == tti ) {
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
            if ( toptag_nconstituents->at(tti) == 1 ) ntop1b_1prong += 1 ;
            if ( toptag_nconstituents->at(tti) == 2 ) ntop1b_2prong += 1 ;
            if ( toptag_nconstituents->at(tti) == 3 ) ntop1b_3prong += 1 ;
            if ( toptag_nconstituents->at(tti) != 3 ) ntop1bnot3prong += 1 ;
         }
      } // tti

      if ( ntop1b_2prong == 1 && ntop1b_3prong >= 1 ) dtop_cat = 5 ;
      if ( ntop1b_2prong >=2                        ) dtop_cat = 4 ;
      if ( ntop1b_1prong == 1 && ntop1b_3prong >= 1 ) dtop_cat = 3 ;
      if ( ntop1b_1prong == 1 && ntop1b_2prong >= 1 ) dtop_cat = 2 ;
      if ( ntop1b_1prong >= 2                       ) dtop_cat = 1 ;

      for ( unsigned int rji=0; rji < Jets->size(); rji++ ) {
         bool in_a_good_tag(false) ;
         if ( Jets_toptag_index->at(rji) >= 0 ) {
            if ( toptag_nb[ Jets_toptag_index->at(rji) ] == 1 ) {
               in_a_good_tag = true ;
            }
         }
         for ( unsigned int fji=0; fji<JetsAK8->size(); fji++ ) {
            if ( JetsAK8_toptag_index->at(fji) >= 0 ) {
               if ( toptag_nb[ JetsAK8_toptag_index->at(fji)] == 1 ) {
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


     //----  Apply baseline (hadronic trigger)

      if ( njets_pt45_eta24 < 6 ) continue ;
      if ( pfht_pt40_eta24 < 500 ) continue ;
      if ( nbtag_csv85_pt30_eta24 < 1 ) continue ;

      if ( nleptons > 0 ) continue ;

     //----  Fill histograms.

         int analysis_bin(-1) ;
         for ( int abi=0; abi<analysis_bins.size(); abi++ ) {
            if ( analysis_bins[abi]->in_bin() ) {
               if ( analysis_bin > 0 ) {
                  printf("\n\n *** event falls in more than one exclusive analysis bin.\n\n") ;
                  gSystem -> Exit(-1) ;
               }
               analysis_bin = abi+1 ; // count from 1, not zero.
            }
         } // abi

         h_analysis_bins -> Fill( analysis_bin, ds_weight ) ;


   } // jentry

   printf("\n\n" ) ;
   gDirectory -> ls() ;

   printf("\n\n" ) ;
   saveHist( hist_file_name, "h*" ) ;

   h_analysis_bins->Draw() ;

   printf("\n\n" ) ;


} // Loop
