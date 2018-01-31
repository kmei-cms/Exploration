#include "cut_var.h"
#include "utility_functions.h"
#define analysis_bins_filler_1lep_cxx
#include "analysis_bins_filler_1lep.h"
#include "bin_1d.h"
#include "bin_nd.h"
#include "histio.c"


void analysis_bins_filler_1lep::Loop()
{

   bool verb(false) ;

   gDirectory -> Delete( "h*" ) ;

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();


   double nleptons(0.) ;
   double pfht_pt40_eta24(0.) ;
   double nbtag_csv85_pt30_eta24(0.) ;
   double pfht7p_pt30_eta24(0.) ;

   double leppt1(0.) ;
   double leppt2(0.) ;
   double m_lep1_b(0.) ;
   double m_lep2_b(0.) ;



      bin_1d* bin ;

    //----

///   double pfht7p_pt30_eta24(0.) ;

///   vector<bin_1d*> pfht7p_bins ;

///   bin = new bin_1d( "pfht7p0", "PFHT7+ 0-100", "PFHT(7+), 0 to 100",     pfht7p_pt30_eta24,   0., 100. ) ;
///   pfht7p_bins.push_back( bin ) ;

///   bin = new bin_1d( "pfht7p100", "PFHT7+ 100-200", "PFHT(7+), 100 to 200", pfht7p_pt30_eta24, 100., 200. ) ;
///   pfht7p_bins.push_back( bin ) ;

///   bin = new bin_1d( "pfht7p200", "PFHT7+ 200-300", "PFHT(7+), 200 to 200", pfht7p_pt30_eta24, 200., 300. ) ;
///   pfht7p_bins.push_back( bin ) ;

///   bin = new bin_1d( "pfht7p300", "PFHT7+ 300-350", "PFHT(7+), 300 to 200", pfht7p_pt30_eta24, 300., 350. ) ;
///   pfht7p_bins.push_back( bin ) ;

///   bin = new bin_1d( "pfht7p350", "PFHT7+ 350+", "PFHT(7+), 350+"      , pfht7p_pt30_eta24, 350., 20000. ) ;
///   pfht7p_bins.push_back( bin ) ;

///   printf("\n") ;
///   for ( bi=0; bi<pfht7p_bins.size(); bi++ ) {
///      printf("  %2d : %10s : %s\n", bi, pfht7p_bins[bi]->get_name(), pfht7p_bins[bi]->get_description() ) ;
///   } // bi
///   printf("\n") ;


    //----

      double njets_pt45_eta24(0.) ;

      vector<bin_1d*> njets_bins ;

      bin = new bin_1d( "njets6", "Njets = 6", "Njets = 6", njets_pt45_eta24, 5.5, 6.5 ) ;
      njets_bins.push_back( bin ) ;

      bin = new bin_1d( "njets7", "Njets = 7", "Njets = 7", njets_pt45_eta24, 6.5, 7.5 ) ;
      njets_bins.push_back( bin ) ;

      bin = new bin_1d( "njets8", "Njets = 8", "Njets = 8", njets_pt45_eta24, 7.5, 8.5 ) ;
      njets_bins.push_back( bin ) ;

      bin = new bin_1d( "njets9", "Njets = 9", "Njets = 9", njets_pt45_eta24, 8.5, 9.5 ) ;
      njets_bins.push_back( bin ) ;

      bin = new bin_1d( "njets10", "Njets = 10", "Njets = 10", njets_pt45_eta24, 9.5, 10.5 ) ;
      njets_bins.push_back( bin ) ;

      bin = new bin_1d( "njets11", "Njets = 11", "Njets = 11", njets_pt45_eta24, 10.5, 11.5 ) ;
      njets_bins.push_back( bin ) ;

      bin = new bin_1d( "njets12p", "Njets >= 12 ", "Njets >= 12", njets_pt45_eta24, 11.5, 20.5 ) ;
      njets_bins.push_back( bin ) ;




    //----

      double ncon_top1(0) ;

      vector<bin_1d*> ncontop1_bins ;

      bin = new bin_1d( "top1ncon0", "top1ncon0", "Top tag 1, N constituents = 0 (no tag)",  ncon_top1, -0.5, 0.5 ) ;
      ncontop1_bins.push_back( bin ) ;

      bin = new bin_1d( "top1ncon3L", "top1ncon3L", "Top tag 1, N constituents = 3, pt<200",  ncon_top1, 2.5, 3.5 ) ;
      ncontop1_bins.push_back( bin ) ;

      bin = new bin_1d( "top1ncon3H", "top1ncon3H", "Top tag 1, N constituents = 3, pt>200",  ncon_top1, 3.5, 4.5 ) ;
      ncontop1_bins.push_back( bin ) ;

      bin = new bin_1d( "top1ncon2", "top1ncon2", "Top tag 1, N constituents = 2",  ncon_top1, 1.5, 2.5 ) ;
      ncontop1_bins.push_back( bin ) ;

      bin = new bin_1d( "top1ncon1", "top1ncon1", "Top tag 1, N constituents = 1",  ncon_top1, 0.5, 1.5 ) ;
      ncontop1_bins.push_back( bin ) ;

      printf("\n") ;
      for ( unsigned int bi=0; bi<ncontop1_bins.size(); bi++ ) {
         printf("  %2d : %10s : %s\n", bi, ncontop1_bins[bi]->get_name(), ncontop1_bins[bi]->get_description() ) ;
      } // bi
      printf("\n") ;


    //----

      double nlepb_pairs(0) ;

      vector<bin_1d*> nlepb_bins ;

      bin = new bin_1d( "nlepb1", "nlepb1", "One lepton-b pair", nlepb_pairs, 0.5, 1.5 ) ;
      nlepb_bins.push_back( bin ) ;

      bin = new bin_1d( "nlepb2", "nlepb2", "Two lepton-b pairs", nlepb_pairs, 1.5, 2.5 ) ;
      nlepb_bins.push_back( bin ) ;





    //----

      vector<bin_nd*> analysis_bins ;


    //---- 1 lepb pair bins
      for ( unsigned int nci=0; nci<ncontop1_bins.size(); nci++ ) {
         for ( unsigned int nji=0; nji<njets_bins.size(); nji++ ) {
            char name[100] ;
            char short_description[100] ;
            char description[100] ;
            sprintf( name, "%s_%s_%s", nlepb_bins[0]->get_name(), ncontop1_bins[nci]->get_name(), njets_bins[nji]->get_name() ) ;
            sprintf( description, "%s ; %s ; %s", nlepb_bins[0]->get_description(), ncontop1_bins[nci]->get_description(), njets_bins[nji]->get_description() ) ;
            sprintf( short_description, "%s ; %s ; %s", nlepb_bins[0]->get_short_description(), ncontop1_bins[nci]->get_short_description(), njets_bins[nji]->get_short_description() ) ;
            bin_nd* abin = new bin_nd( name, short_description, description ) ;
            abin -> add_1d_bin( nlepb_bins[0] ) ;
            abin -> add_1d_bin( ncontop1_bins[nci] ) ;
            abin -> add_1d_bin( njets_bins[nji] ) ;
            analysis_bins.push_back( abin ) ;
         } // nji
      } // nci

    //---- 2 lepb pair bins
      for ( unsigned int nji=0; nji<njets_bins.size(); nji++ ) {
         char name[100] ;
         char short_description[100] ;
         char description[100] ;
         sprintf( name, "%s_%s", nlepb_bins[1]->get_name(), njets_bins[nji]->get_name() ) ;
         sprintf( description, "%s ; %s", nlepb_bins[1]->get_description(), njets_bins[nji]->get_description() ) ;
         sprintf( short_description, "%s ; %s", nlepb_bins[1]->get_short_description(), njets_bins[nji]->get_short_description() ) ;
         bin_nd* abin = new bin_nd( name, short_description, description ) ;
         abin -> add_1d_bin( nlepb_bins[1] ) ;
         abin -> add_1d_bin( njets_bins[nji] ) ;
         analysis_bins.push_back( abin ) ;
      } // nji


      printf("\n") ;
      for ( unsigned int abi=0; abi<analysis_bins.size(); abi++ ) {
         printf(" %2d : %20s : %s\n", abi, analysis_bins[abi]->get_name(), analysis_bins[abi]->get_description() ) ;
      } // abi
      printf("\n") ;

      TH1F* h_analysis_bins = new TH1F( "h_analysis_bins", "Analysis bins", analysis_bins.size(), 0.5, analysis_bins.size()+0.5 ) ;
      for ( unsigned int bi=1; bi<=analysis_bins.size(); bi++ ) {
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

      nleptons = 0 ;
      njets_pt45_eta24 = 0 ;
      pfht_pt40_eta24 = 0 ;
      nbtag_csv85_pt30_eta24 = 0 ;

      pfht7p_pt30_eta24 = 0 ;
      ncon_top1 = 0. ;


      int ntop1b = 0 ;
      int ntop1bnot3prong = 0 ;


      TLorentzVector lep1_tlv ;
      TLorentzVector lep2_tlv ;
      bool lep1_is_mu(false) ;
      bool lep1_is_e(false) ;
      bool lep2_is_mu(false) ;
      bool lep2_is_e(false) ;
      int lep1_q(0) ;
      int lep2_q(0) ;
      for ( unsigned int mi=0; mi<Muons->size(); mi++ ) {
         if ( Muons->at(mi).Pt() > 0 ) nleptons ++ ;
         if ( Muons->at(mi).Pt() > lep1_tlv.Pt() ) {
            if ( lep1_tlv.Pt() > 0 ) {
               lep2_tlv = lep1_tlv ;
               lep2_q = lep1_q ;
               lep2_is_mu = lep1_is_mu ;
               lep2_is_e  = lep1_is_e  ;
            }
            lep1_tlv =  Muons->at(mi) ;
            lep1_q = Muons_charge->at(mi) ;
            lep1_is_mu = true ;
         } else if ( Muons->at(mi).Pt() > lep2_tlv.Pt() ) {
            lep2_tlv =  Muons->at(mi) ;
            lep2_q = Muons_charge->at(mi) ;
            lep2_is_mu = true ;
         }
      }
      for ( unsigned int ei=0; ei<Electrons->size(); ei++ ) {
         if ( Electrons->at(ei).Pt() > 0 ) nleptons ++ ;
         if ( Electrons->at(ei).Pt() > lep1_tlv.Pt() ) {
            if ( lep1_tlv.Pt() > 0 ) {
               lep2_tlv = lep1_tlv ;
               lep2_q = lep1_q ;
               lep2_is_mu = lep1_is_mu ;
               lep2_is_e  = lep1_is_e ;
            }
            lep1_tlv =  Electrons->at(ei) ;
            lep1_q = Electrons_charge->at(ei) ;
            lep1_is_e = true ;
         } else if ( Electrons->at(ei).Pt() > lep2_tlv.Pt() ) {
            lep2_tlv =  Electrons->at(ei) ;
            lep2_q = Electrons_charge->at(ei) ;
            lep2_is_e = true ;
         }
      }
      leppt1 = lep1_tlv.Pt() ;
      leppt2 = lep2_tlv.Pt() ;
      int lepqq = lep1_q * lep2_q ;




      bool have_two_lepb_pairs = false ;




      int lowest_m_lep1_b_bjet_rji(-1) ;
      int lowest_m_lep2_b_bjet_rji(-1) ;

      TLorentzVector lowest_m_lep1_b_tlv ;
      TLorentzVector lowest_m_lep2_b_tlv ;

      if ( nleptons > 0 ) {

         double lowest_m_lep1_b(999.) ;
         double lowest_m_lep2_b(999.) ;

         for ( unsigned int rji=0; rji<Jets->size(); rji++ ) {

            TLorentzVector j_tlv = Jets->at(rji) ;

            if ( lep1_tlv.Pt() > 5 && lep1_tlv.DeltaR( j_tlv ) < 0.05 ) {
               if ( verb  ) {
                  printf( "\n  jet %2u is a DR match for lep1 %2s : %7.3f  p ratio = %7.3f  mu Efr = %5.3f  EMfr = %5.3f  \n", rji,
                    ( lep1_is_mu ? "mu" : "e " ),
                    lep1_tlv.DeltaR( j_tlv ),
                    j_tlv.P() / lep1_tlv.P(),
                    Jets_muonEnergyFraction->at(rji),
                    Jets_neutralEmEnergyFraction->at(rji) ) ;
                  printf("   lepton  Pt = %7.1f, Eta = %7.3f, Phi = %7.3f\n", lep1_tlv.Pt(), lep1_tlv.Eta(), lep1_tlv.Phi() ) ;
                  printf("   jet     Pt = %7.1f, Eta = %7.3f, Phi = %7.3f\n", j_tlv.Pt(), j_tlv.Eta(), j_tlv.Phi() ) ;
               }
               continue ;
            }
            if ( lep2_tlv.Pt() > 5 && lep2_tlv.DeltaR( j_tlv ) < 0.05 ) {
               if ( verb  ) {
                  printf( "\n  jet %2u is a DR match for lep2 %2s : %7.3f  p ratio = %7.3f  mu Efr = %5.3f  EMfr = %5.3f  \n", rji,
                    ( lep2_is_mu ? "mu" : "e " ),
                    lep2_tlv.DeltaR( j_tlv ),
                    j_tlv.P() / lep2_tlv.P(),
                    Jets_muonEnergyFraction->at(rji),
                    Jets_neutralEmEnergyFraction->at(rji) ) ;
                  printf("   lepton  Pt = %7.1f, Eta = %7.3f, Phi = %7.3f\n", lep2_tlv.Pt(), lep2_tlv.Eta(), lep2_tlv.Phi() ) ;
                  printf("   jet     Pt = %7.1f, Eta = %7.3f, Phi = %7.3f\n", j_tlv.Pt(), j_tlv.Eta(), j_tlv.Phi() ) ;
               }
               continue ;
            }


            if ( Jets_bDiscriminatorCSV->at(rji) > 0.85 ) {

               TLorentzVector lep1_b_tlv = lep1_tlv + j_tlv ;
               TLorentzVector lep2_b_tlv = lep2_tlv + j_tlv ;

               if ( lep1_b_tlv.M() < lowest_m_lep1_b ) {
                  lowest_m_lep1_b = lep1_b_tlv.M() ;
                  m_lep1_b = lep1_b_tlv.M() ;
                  lowest_m_lep1_b_bjet_rji = rji ;
                  lowest_m_lep1_b_tlv = lep1_b_tlv ;
               }
               if ( lep2_tlv.Pt() > 0 && lep2_b_tlv.M() < lowest_m_lep2_b ) {
                  lowest_m_lep2_b = lep2_b_tlv.M() ;
                  m_lep2_b = lep2_b_tlv.M() ;
                  lowest_m_lep2_b_bjet_rji = rji ;
                  lowest_m_lep2_b_tlv = lep2_b_tlv ;
               }


            }

         } // rji



        //--- If have two lepton-b pairs, make sure they don't both use the same b jet.

         if ( nleptons >= 2 && m_lep1_b > 0 && m_lep2_b > 0 ) {

            if ( lowest_m_lep1_b_bjet_rji == lowest_m_lep2_b_bjet_rji ) {

               if ( verb ) {
                  printf("  both leptons pair with the same b jet.  Choosing one with mass in (30,180).\n" ) ;
                  printf("     rji for lep1 = %d, mass = %7.1f, rji for b with lep2 = %d, mass = %7.1f\n",
                       lowest_m_lep1_b_bjet_rji, m_lep1_b, lowest_m_lep2_b_bjet_rji, m_lep2_b ) ;
               }

               bool m_lep1_b_in_window(false) ;
               bool m_lep2_b_in_window(false) ;
               if ( m_lep1_b > 30 && m_lep1_b < 180 ) m_lep1_b_in_window = true ;
               if ( m_lep2_b > 30 && m_lep2_b < 180 ) m_lep2_b_in_window = true ;

               if ( m_lep1_b_in_window && !m_lep2_b_in_window ) m_lep2_b = 0 ;
               if ( m_lep2_b_in_window && !m_lep1_b_in_window ) m_lep1_b = 0 ;
               if ( m_lep1_b_in_window && m_lep2_b_in_window ) {
                  if ( m_lep1_b < m_lep2_b ) {
                     m_lep2_b = 0. ;
                  } else {
                     m_lep1_b = 0. ;
                  }
               }
               if ( !m_lep1_b_in_window && !m_lep2_b_in_window ) {
                  if ( m_lep1_b < m_lep2_b ) {
                     m_lep2_b = 0. ;
                  } else {
                     m_lep1_b = 0. ;
                  }
               }



            } // same b jet?

         } // two lepton-b pairs?


      } // any leptons?




      nlepb_pairs = 0 ;
      if ( m_lep1_b > 30 && m_lep1_b < 180 && leppt1 > 30 ) nlepb_pairs = nlepb_pairs + 1 ;
      if ( m_lep2_b > 30 && m_lep2_b < 180 && leppt2 > 30 ) nlepb_pairs = nlepb_pairs + 1 ;
      if ( nlepb_pairs > 1 && !( lepqq < -0.5 ) ) nlepb_pairs = nlepb_pairs - 1 ; // require leptons to be opposite charge.








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

      TLorentzVector toptag1_tlv ;
      int toptag1_tti(-1) ;
      for ( unsigned int tti=0; tti < toptag_tlv->size(); tti++ ) {
         vector<int> btag_jets ;
         int nb(0) ;
         for ( unsigned int rji=0; rji < Jets->size(); rji++ ) {
            int int_tti = tti ;
            if ( Jets_toptag_index->at(rji) == int_tti ) {
               if ( Jets_bDiscriminatorCSV->at(rji) > 0.85 ) {
                  nb ++ ;
                  btag_jets.push_back( rji ) ;
               }
            }
         } // rji
         for ( unsigned int fji=0; fji < JetsAK8->size(); fji++ ) {
            for ( unsigned int rji=0; rji < Jets->size(); rji++ ) {
               if ( calcDR( JetsAK8->at(fji), Jets->at(rji) ) < 0.8 ) {
                  if ( Jets_bDiscriminatorCSV->at(rji) > 0.85 ) {
                     bool already_in_top_tag(false) ;
                     for ( unsigned int bji=0; bji<btag_jets.size(); bji++ ) {
                        if ( btag_jets[bji] == rji ) {
                           already_in_top_tag = true ;
                           break ;
                        }
                     }
                     if ( !already_in_top_tag ) nb ++ ;
                  }
               } // dr match
            } // rji
         } // fji
         if ( nb == 1 ) {
            ntop1b += 1 ;
            if ( toptag1_tti < 0 ) {
               toptag1_tti = tti ;
               ncon_top1 = toptag_nconstituents->at(tti) ;
               if ( ncon_top1 == 3 && toptag_tlv->at(tti).Pt() > 200 ) ncon_top1 = 4 ;
            }
         }
      } // tti



     //----  Apply baseline (hadronic trigger, plus 1 lepton selection)

      if ( njets_pt45_eta24 < 6 ) continue ;

 ///  if ( pfht_pt40_eta24 < 500 ) continue ;

      if ( nbtag_csv85_pt30_eta24 < 2 ) continue ;

      if ( nleptons < 1 ) continue ;


      if ( nlepb_pairs < 0 ) continue ;


     //----  Fill histograms.

         int analysis_bin(-1) ;
         for ( unsigned int abi=0; abi<analysis_bins.size(); abi++ ) {
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
