#include "cut_var.h"
#include "utility_functions.h"
#define nminus1_filler_micro_cxx
#include "nminus1_filler_micro.h"
#include "histio.c"

#include "TH1F.h"
#include "TH2F.h"
#include "TSystem.h"

//------------

TH2F* create_2d_hist( cut_var& cvx, cut_var& cvy, const char* name ) {
   char hname[100] ;
   sprintf( hname, "h_%s_vs_%s_%s", cvy.get_hist_name(), cvx.get_hist_name(), name ) ;
   TH2F* rv = new TH2F( hname, hname, cvx.get_hist_nbins(), cvx.get_hist_xlow(), cvx.get_hist_xhigh(),
                                      cvy.get_hist_nbins(), cvy.get_hist_xlow(), cvy.get_hist_xhigh() ) ;
   rv -> SetXTitle( cvx.get_hist_xtitle() ) ;
   rv -> SetYTitle( cvy.get_hist_xtitle() ) ;
   rv -> Sumw2() ;
   return rv ;
} // create_2d_hist

//------------

void nminus1_filler_micro::Loop()
{
   //bool use_pfht7p(false) ;
   bool use_pfht7p(true) ;

   gDirectory -> Delete( "h*" ) ;

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();

   bool is_2d_nm1_var_val ;

   vector<cut_var> cut_vars ;
   vector<bool> is_2d_nm1_var ;

   printf("\n\n Creating cut_var objects.\n") ;

   double d_njets_pt45_eta24(0.) ;
   cut_var cv_njets( d_njets_pt45_eta24, 6 ) ;
   cv_njets.set_hist_pars( "njets", "Njets, pt>45, |eta|<2.4", 21, -0.5, 20.5 ) ;
   cut_vars.emplace_back( cv_njets ) ;
   is_2d_nm1_var_val = false ; is_2d_nm1_var.push_back( is_2d_nm1_var_val ) ;

   double d_pfht_pt40_eta24(0.) ;
   cut_var cv_pfht( d_pfht_pt40_eta24, 500. ) ;
   cv_pfht.set_hist_pars( "pfht", "PFHT, jet pt>40, |eta|<2.4", 100, 0., 4000. ) ;
   cut_vars.emplace_back( cv_pfht ) ;
   is_2d_nm1_var_val = false ; is_2d_nm1_var.push_back( is_2d_nm1_var_val ) ;

   double d_nbtag_csv85_pt30_eta24(0.) ;
   cut_var cv_nbtag( d_nbtag_csv85_pt30_eta24, 1 ) ;
   cv_nbtag.set_hist_pars( "nbtag", "Nbtag, CSV>0.85, jet pt>30, |eta|<2.4", 11, -0.5, 10.5 ) ;
   cut_vars.emplace_back( cv_nbtag ) ;
   is_2d_nm1_var_val = false ; is_2d_nm1_var.push_back( is_2d_nm1_var_val ) ;

   cut_var cv_nbtag2( d_nbtag_csv85_pt30_eta24, 2 ) ;
   cv_nbtag2.set_hist_pars( "nbtag2", "Nbtag, CSV>0.85, jet pt>30, |eta|<2.4", 11, -0.5, 10.5 ) ;
   cut_vars.emplace_back( cv_nbtag2 ) ;
   is_2d_nm1_var_val = false ; is_2d_nm1_var.push_back( is_2d_nm1_var_val ) ;

   double d_nleptons(0.) ;
// cut_var cv_nleptons( d_nleptons, 0 ) ;
// cv_nleptons.use_le_in_cut() ;
// cv_nleptons.set_hist_pars( "nleptons", "Nleptons (e or mu)", 5, -0.5, 4.5 ) ;
// cut_vars.emplace_back( cv_nleptons ) ;
// is_2d_nm1_var_val = false ; is_2d_nm1_var.push_back( is_2d_nm1_var_val ) ;

   double d_pfht7p_pt30_eta24(0.) ;
   cut_var cv_pfht7p( d_pfht7p_pt30_eta24, 200. ) ;
   cv_pfht7p.set_hist_pars( "pfht7p", "PFHT, jets 7+, jet pt>30, |eta|<2.4", 100, 0., 1000. ) ;
   if ( use_pfht7p ) {
      cut_vars.emplace_back( cv_pfht7p ) ;
      is_2d_nm1_var_val = true ; is_2d_nm1_var.push_back( is_2d_nm1_var_val ) ;
   }

   double d_ntop1b(0.) ;
   cut_var cv_ntop1b( d_ntop1b, 2 ) ;
   cv_ntop1b.set_hist_pars( "ntop1b", "Ntoptag, only 1 btag, CSV>0.85", 6, -0.5, 5.5 ) ;
   cut_vars.emplace_back( cv_ntop1b ) ;
   is_2d_nm1_var_val = false ; is_2d_nm1_var.push_back( is_2d_nm1_var_val ) ;

   double d_ntop1bpt200(0.) ;
   cut_var cv_ntop1bpt200( d_ntop1bpt200, 2 ) ;
   cv_ntop1bpt200.set_hist_pars( "ntop1bpt200", "Ntoptag, only 1 btag, CSV>0.85, pt>200", 6, -0.5, 5.5 ) ;
   cut_vars.emplace_back( cv_ntop1bpt200 ) ;
   is_2d_nm1_var_val = false ; is_2d_nm1_var.push_back( is_2d_nm1_var_val ) ;

   double d_ntop1bnot3prong(0.) ;
   cut_var cv_ntop1bnot3prong( d_ntop1bnot3prong, 1 ) ;
   cv_ntop1bnot3prong.set_hist_pars( "ntop1bnot3prong", "Ntoptag, only 1 btag, CSV>0.85, not 3-prong", 6, -0.5, 5.5 ) ;
   cut_vars.emplace_back( cv_ntop1bnot3prong ) ;
   is_2d_nm1_var_val = false ; is_2d_nm1_var.push_back( is_2d_nm1_var_val ) ;

   double d_njetsextra_pt30_eta24(0.) ;
   cut_var cv_njetsextra( d_njetsextra_pt30_eta24, 5 ) ;
   cv_njetsextra.set_hist_pars( "njetsextra", "Njets extra, pt>30, |eta|<2.4", 21, -0.5, 20.5 ) ;
   cut_vars.emplace_back( cv_njetsextra ) ;
   is_2d_nm1_var_val = true ; is_2d_nm1_var.push_back( is_2d_nm1_var_val ) ;

   double d_pfhtextra_pt30_eta24(0.) ;
   cut_var cv_pfhtextra( d_pfhtextra_pt30_eta24, 200. ) ;
   cv_pfhtextra.set_hist_pars( "pfhtextra", "PFHT, extra jets, jet pt>30, |eta|<2.4", 100, 0., 4000. ) ;
   if ( !use_pfht7p ) {
      cut_vars.emplace_back( cv_pfhtextra ) ;
      is_2d_nm1_var_val = true ; is_2d_nm1_var.push_back( is_2d_nm1_var_val ) ;
   }


   printf("\n\n") ;
   vector<TH1F*> hists_all ;
   for ( unsigned int ci = 0 ; ci < cut_vars.size() ; ci++ ) {
      printf("Creating histogram for %s\n", cut_vars[ci].get_name() ) ;
      hists_all.emplace_back( cut_vars[ci].create_hist( "all" ) ) ;
   } // ci

   printf("\n\n") ;
   vector<TH1F*> hists_nm1 ;
   for ( unsigned int ci = 0 ; ci < cut_vars.size() ; ci++ ) {
      printf("Creating nminus1 histogram for %s\n", cut_vars[ci].get_name() ) ;
      hists_nm1.emplace_back( cut_vars[ci].create_hist( "nm1" ) ) ;
   } // ci

   TH2F* hist_2d_nm1(0x0) ;
   if ( use_pfht7p ) {
      hist_2d_nm1 = create_2d_hist( cv_pfht7p, cv_njetsextra, "nm1" ) ;
   } else {
      hist_2d_nm1 = create_2d_hist( cv_pfhtextra, cv_njetsextra, "nm1" ) ;
   }

   printf("\n\n") ;
   vector<TH1F*> hists_cutflow ;
   for ( unsigned int ci = 0 ; ci < cut_vars.size() ; ci++ ) {
      char cuts_string[10000] ;
      sprintf( cuts_string, "cuts" ) ;
      for ( unsigned int cj = 0 ; cj < cut_vars.size() ; cj++ ) {
         if ( cj==ci ) continue ;
         char tmp_string[10000] ;
         sprintf( tmp_string, "%s_%s", cuts_string, cut_vars[cj].get_name() ) ;
         sprintf( cuts_string, "%s", tmp_string ) ;
         printf("  Creating cutflow hist %s : %s\n", cut_vars[ci].get_name(), cuts_string ) ;
         hists_cutflow.emplace_back( cut_vars[ci].create_hist( cuts_string ) ) ;
      } // cj
   } // ci

   printf("\n\n Done creating histograms.\n") ;

   int modnum = nentries/50 ;
   if ( modnum == 0 ) modnum = 1 ;


   printf("\n\n Right before the event loop.\n") ;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {

      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if ( jentry % modnum == 0 ) printf("  Event %9llu / %9llu  (%2.0f%%)\n", jentry, nentries, 100*(jentry*1.)/(nentries*1.) ) ;


      d_njets_pt45_eta24       = njets_pt45_eta24       ;
      d_nbtag_csv85_pt30_eta24 = nbtag_csv85_pt30_eta24 ;
      d_ntop1b                 = ntop1b                 ;
      d_ntop1bpt200            = ntop1bpt200            ;
      d_ntop1bnot3prong        = ntop1bnot3prong        ;
      d_ntop1bnot3prongpt200   = ntop1bnot3prongpt200   ;
      d_njetsextra_pt30_eta24  = njetsextra_pt30_eta24  ;
      d_nleptons               = nleptons               ;
      d_pfht_pt40_eta24        = pfht_pt40_eta24        ;
      d_pfht7p_pt30_eta24      = pfht7p_pt30_eta24      ;
      d_pfhtextra_pt30_eta24   = pfhtextra_pt30_eta24   ;


     //----  Apply baseline (hadronic trigger)

      //if ( njets_pt45_eta24 < 6 ) continue ;
      //if ( pfht_pt40_eta24 < 500 ) continue ;
      //if ( nbtag_csv85_pt30_eta24 < 1 ) continue ;


     //----  Fill histograms.

      int cfhi(0) ;
      for ( unsigned int ci = 0 ; ci < cut_vars.size() ; ci++ ) {
         //cut_vars[ci].passes_cut( true ) ;
         hists_all[ci] -> Fill( cut_vars[ci].get_val(), ds_weight ) ;
         bool pass_nm1(true) ;
         for ( unsigned int ci2 = 0 ; ci2 < cut_vars.size() ; ci2++ ) {
            if ( ci2 == ci ) continue ;
            if ( ! cut_vars[ci2].passes_cut() ) { pass_nm1 = false ; break ; }
         } // ci2
         if ( pass_nm1 ) {
            hists_nm1[ci] -> Fill( cut_vars[ci].get_val(), ds_weight ) ;
         }
         bool pass_cutflow(true) ;
         for ( unsigned int cj = 0 ; cj < cut_vars.size() ; cj++ ) {
            if ( cj==ci ) continue ;
            if ( ! cut_vars[cj].passes_cut() ) pass_cutflow = false ;
            if ( pass_cutflow ) {
               hists_cutflow[cfhi] -> Fill( cut_vars[ci].get_val(), ds_weight ) ;
            }
            cfhi ++ ;
         } // cj
      } // ci

      bool pass_2d_nm1(true) ;
      for ( unsigned int ci = 0 ; ci < cut_vars.size() ; ci++ ) {
         if ( is_2d_nm1_var[ci] ) continue ;
         if ( ! cut_vars[ci].passes_cut() ) { pass_2d_nm1 = false ; break ; }
      } // ci
      if ( pass_2d_nm1 ) {
         if ( use_pfht7p ) {
            hist_2d_nm1 -> Fill( cv_pfht7p.get_val(), cv_njetsextra.get_val(), ds_weight ) ;
         } else {
            hist_2d_nm1 -> Fill( cv_pfhtextra.get_val(), cv_njetsextra.get_val(), ds_weight ) ;
         }
      }


   } // jentry

   printf("\n\n" ) ;
   gDirectory -> ls() ;

   printf("\n\n" ) ;
   saveHist( hist_file_name, "h*" ) ;

   printf("\n\n" ) ;


}
