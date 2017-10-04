#define trig_eff_cxx
#include "trig_eff.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "histio.c"

char pname[100] ;

const char* mcname( int pdgid ) ;

double calcDr( double eta1, double eta2, double phi1, double phi2 ) ;

void add_overflows_to_last_bin( TH1F* hp ) ;

void trig_eff::Loop( int max_events, bool verb )
{

   gDirectory -> Delete( "h*" ) ;




   TH1F* h_rec_njet20 = new TH1F( "h_rec_njet20", "Njets, pt>20", 21, -0.5, 20.5 ) ;
   TH1F* h_rec_njet30 = new TH1F( "h_rec_njet30", "Njets, pt>30", 21, -0.5, 20.5 ) ;
   TH1F* h_rec_njet32 = new TH1F( "h_rec_njet32", "Njets, pt>32", 21, -0.5, 20.5 ) ;
   TH1F* h_rec_njet40 = new TH1F( "h_rec_njet40", "Njets, pt>40", 21, -0.5, 20.5 ) ;
   TH1F* h_rec_njet45 = new TH1F( "h_rec_njet45", "Njets, pt>45", 21, -0.5, 20.5 ) ;
   TH1F* h_rec_njet50 = new TH1F( "h_rec_njet50", "Njets, pt>50", 21, -0.5, 20.5 ) ;

   TH1F* h_rec_njet32_ht380 = new TH1F( "h_rec_njet32_ht380", "Njets, pt>32, HT>380", 21, -0.5, 20.5 ) ;

   TH1F* h_rec_njet40_ht450 = new TH1F( "h_rec_njet40_ht450", "Njets, pt>40, HT>450", 21, -0.5, 20.5 ) ;
   TH1F* h_rec_njet45_ht450 = new TH1F( "h_rec_njet45_ht450", "Njets, pt>45, HT>450", 21, -0.5, 20.5 ) ;
   TH1F* h_rec_njet50_ht450 = new TH1F( "h_rec_njet50_ht450", "Njets, pt>50, HT>450", 21, -0.5, 20.5 ) ;

   TH1F* h_rec_njet40_ht500 = new TH1F( "h_rec_njet40_ht500", "Njets, pt>40, HT>500", 21, -0.5, 20.5 ) ;
   TH1F* h_rec_njet45_ht500 = new TH1F( "h_rec_njet45_ht500", "Njets, pt>45, HT>500", 21, -0.5, 20.5 ) ;
   TH1F* h_rec_njet50_ht500 = new TH1F( "h_rec_njet50_ht500", "Njets, pt>50, HT>500", 21, -0.5, 20.5 ) ;

   TH1F* h_rec_njet40_ht550 = new TH1F( "h_rec_njet40_ht550", "Njets, pt>40, HT>550", 21, -0.5, 20.5 ) ;
   TH1F* h_rec_njet45_ht550 = new TH1F( "h_rec_njet45_ht550", "Njets, pt>45, HT>550", 21, -0.5, 20.5 ) ;
   TH1F* h_rec_njet50_ht550 = new TH1F( "h_rec_njet50_ht550", "Njets, pt>50, HT>550", 21, -0.5, 20.5 ) ;

   TH1F* h_rec_njet32_ht1100 = new TH1F( "h_rec_njet32_ht1100", "Njets, pt>32, HT>1100", 21, -0.5, 20.5 ) ;
   TH1F* h_rec_njet40_ht1100 = new TH1F( "h_rec_njet40_ht1100", "Njets, pt>40, HT>1100", 21, -0.5, 20.5 ) ;

   TH1F* h_rec_ht = new TH1F( "h_rec_ht", "HT", 80, 0., 4000. ) ;
   TH1F* h_rec_ht_njet32ge6 = new TH1F( "h_rec_ht_njet32ge6", "HT, Njet32>=6", 80, 0., 4000. ) ;
   TH1F* h_rec_ht_njet40ge6 = new TH1F( "h_rec_ht_njet40ge6", "HT, Njet40>=6", 80, 0., 4000. ) ;
   TH1F* h_rec_ht_njet45ge6 = new TH1F( "h_rec_ht_njet45ge6", "HT, Njet45>=6", 80, 0., 4000. ) ;
   TH1F* h_rec_ht_njet50ge6 = new TH1F( "h_rec_ht_njet50ge6", "HT, Njet50>=6", 80, 0., 4000. ) ;

   TH1F* h_rec_nbtag_csv80 = new TH1F( "h_rec_nbtag_csv80", "N btag, CSV>0.80", 6, -0.5, 5.5 ) ;
   TH1F* h_rec_nbtag_csv85 = new TH1F( "h_rec_nbtag_csv85", "N btag, CSV>0.85", 6, -0.5, 5.5 ) ;
   TH1F* h_rec_nbtag_csv90 = new TH1F( "h_rec_nbtag_csv90", "N btag, CSV>0.90", 6, -0.5, 5.5 ) ;

   TH1F* h_rec_nbtag_csv80_ht500_njet45ge6 = new TH1F( "h_rec_nbtag_csv80_ht500_njet45ge6", "N btag, CSV>0.80, HT>500, Njet45>=6", 6, -0.5, 5.5 ) ;
   TH1F* h_rec_nbtag_csv85_ht500_njet45ge6 = new TH1F( "h_rec_nbtag_csv85_ht500_njet45ge6", "N btag, CSV>0.85, HT>500, Njet45>=6", 6, -0.5, 5.5 ) ;
   TH1F* h_rec_nbtag_csv90_ht500_njet45ge6 = new TH1F( "h_rec_nbtag_csv90_ht500_njet45ge6", "N btag, CSV>0.90, HT>500, Njet45>=6", 6, -0.5, 5.5 ) ;


  //----------

   TH1F* h_gen_ele_pt = new TH1F( "h_gen_ele_pt", "Gen Electron pt", 90, 0., 300. ) ;
   TH1F* h_gen_mu_pt = new TH1F( "h_gen_mu_pt", "Gen Mu pt", 90, 0., 300. ) ;
   TH1F* h_ele_pt = new TH1F( "h_ele_pt", "Electron pt", 90, 0., 300. ) ;
   TH1F* h_mu_pt = new TH1F( "h_mu_pt", "Mu pt", 90, 0., 300. ) ;

   TH1F* h_gen_ele_eta24_pt = new TH1F( "h_gen_ele_eta24_pt", "Gen Electron pt, |eta|<2.4", 90, 0., 300. ) ;
   TH1F* h_gen_mu_eta24_pt = new TH1F( "h_gen_mu_eta24_pt", "Gen Mu pt, |eta|<2.4", 90, 0., 300. ) ;
   TH1F* h_ele_eta24_pt = new TH1F( "h_ele_eta24_pt", "Electron pt, |eta|<2.4", 90, 0., 300. ) ;
   TH1F* h_mu_eta24_pt = new TH1F( "h_mu_eta24_pt", "Mu pt, |eta|<2.4", 90, 0., 300. ) ;

   TH1F* h_gen_ele_eta = new TH1F( "h_gen_ele_eta", "Gen Electron pt", 100,-6.,6. ) ;
   TH1F* h_gen_mu_eta = new TH1F( "h_gen_mu_eta", "Gen Mu pt", 100,-6.,6. ) ;
   TH1F* h_ele_eta = new TH1F( "h_ele_eta", "Electron pt", 100,-6.,6. ) ;
   TH1F* h_mu_eta = new TH1F( "h_mu_eta", "Mu pt", 100,-6.,6. ) ;


   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();
   if ( max_events > 0 ) nentries = max_events ;

   Long64_t nbytes = 0, nb = 0;




   int n_missing_b(0) ;
   int n_sl_top(0) ;
   int n_sl_top_e_or_mu(0) ;
   int n_sl_top_e(0) ;
   int n_sl_top_mu(0) ;


   for (Long64_t jentry=0; jentry<nentries;jentry++) {

      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;


      if ( jentry % (nentries/10) == 0 ) printf("  Event %9llu / %9llu  (%2.0f%%)\n", jentry, nentries, 100*(jentry*1.)/(nentries*1.) ) ;




      if ( verb ) printf("\n\n =========== number %9llu : Run %9u , Lumi %9u , Event %9llu\n", jentry, RunNum, LumiBlockNum, EvtNum ) ;

      if ( verb ) printf("\n\n GenParticles: %lu\n", GenParticles->size() ) ;


      bool is_sl_top(false) ;
      bool is_sl_top_e_or_mu(false) ;
      bool is_sl_top_e(false) ;
      bool is_sl_top_mu(false) ;

      int first_ele_gpi(-1) ;
      int first_mu_gpi(-1) ;
      for ( unsigned int gpi=0; gpi < GenParticles->size() ; gpi++ ) {

         int spdgid = GenParticles_PdgId->at(gpi) ;
         int pdgid = abs( GenParticles_PdgId->at(gpi) ) ;
         int smomid = GenParticles_ParentId->at(gpi) ;
         int momid = abs( GenParticles_ParentId->at(gpi) ) ;
         int momidx = GenParticles_ParentIdx->at(gpi) ;

         if ( ( pdgid==11 || pdgid==13 || pdgid==15 ) && momid == 24 && GenParticles->at(gpi).Pt() > 3.  ) { is_sl_top = true ; }
         if ( ( pdgid==11 || pdgid==13 ) && momid == 24 && GenParticles->at(gpi).Pt() > 3.  ) { is_sl_top_e_or_mu = true ; }
         if ( ( pdgid==11 ) && momid == 24 && GenParticles->at(gpi).Pt() > 3. ) {
            is_sl_top_e = true ;
            if ( first_ele_gpi < 0 ) first_ele_gpi = gpi ;
         }
         if ( ( pdgid==13 ) && momid == 24 ) {
            is_sl_top_mu = true ;
            if ( first_mu_gpi < 0 ) first_mu_gpi = gpi ;
         }


         if ( verb ) {
            char pname[100] ;
            char mname[100] ;
            sprintf( pname, "%s", mcname( GenParticles_PdgId->at(gpi) ) ) ;
            sprintf( mname, "%s", mcname( GenParticles_ParentId->at(gpi) ) ) ;
            double eta = 99. ;
            if ( GenParticles->at(gpi).Pt() > 0 ) eta = GenParticles->at(gpi).Eta() ;
            double phi = GenParticles->at(gpi).Phi() ;
            double pt = GenParticles->at(gpi).Pt() ;
            printf("  %3u :  ID=%9d %10s : MomID=%9d %10s MomIdx=%3d status=%2d :  Pt = %7.1f , Eta = %6.3f, Phi = %6.3f,  px,py,pz,E = %6.1f, %6.1f, %6.1f,   %6.1f\n",
                gpi,
                GenParticles_PdgId->at(gpi), pname,
                GenParticles_ParentId->at(gpi), mname, GenParticles_ParentIdx->at(gpi),
                GenParticles_Status->at(gpi),
                GenParticles->at(gpi).Pt(),
                eta,
                phi,
                GenParticles->at(gpi).Px(),
                GenParticles->at(gpi).Py(),
                GenParticles->at(gpi).Pz(),
                GenParticles->at(gpi).E()
                ) ;

            printf("\n Triggers:\n") ;
            for ( int ti=0; ti<TriggerNames->size(); ti++ ) {
               printf("  %50s : %s\n", TriggerNames->at(ti).c_str(), (TriggerPass->at(ti)?"PASS":"fail") ) ;
            } // ti
         } // verbose?

      } // gpi

      if ( is_sl_top_e  && first_ele_gpi >= 0 ) h_gen_ele_pt -> Fill( GenParticles->at(first_ele_gpi).Pt() ) ;
      if ( is_sl_top_mu && first_mu_gpi  >= 0 ) h_gen_mu_pt  -> Fill( GenParticles->at(first_mu_gpi).Pt() ) ;

      if ( is_sl_top_e  && first_ele_gpi >= 0 && fabs( GenParticles->at(first_ele_gpi).Eta()) < 2.4 ) h_gen_ele_eta24_pt -> Fill( GenParticles->at(first_ele_gpi).Pt() ) ;
      if ( is_sl_top_mu && first_mu_gpi  >= 0 && fabs( GenParticles->at(first_mu_gpi).Eta()) < 2.4 ) h_gen_mu_eta24_pt  -> Fill( GenParticles->at(first_mu_gpi).Pt() ) ;

      if ( is_sl_top_e  && first_ele_gpi >= 0 ) h_gen_ele_eta -> Fill( GenParticles->at(first_ele_gpi).Eta() ) ;
      if ( is_sl_top_mu && first_mu_gpi  >= 0 ) h_gen_mu_eta  -> Fill( GenParticles->at(first_mu_gpi).Eta() ) ;

 ///  if ( is_sl_top_e  && first_ele_gpi >= 0 && GenParticles->at(first_ele_gpi).Pt() < 1 ) {
 ///     printf("\n\n Very low pt electron.\n\n") ;
 ///     for ( unsigned int gpi=0; gpi < GenParticles->size() ; gpi++ ) {
 ///        char pname[100] ;
 ///        char mname[100] ;
 ///        sprintf( pname, "%s", mcname( GenParticles_PdgId->at(gpi) ) ) ;
 ///        sprintf( mname, "%s", mcname( GenParticles_ParentId->at(gpi) ) ) ;
 ///        double eta = 99. ;
 ///        if ( GenParticles->at(gpi).Pt() > 0 ) eta = GenParticles->at(gpi).Eta() ;
 ///        double phi = GenParticles->at(gpi).Phi() ;
 ///        double pt = GenParticles->at(gpi).Pt() ;
 ///        printf("  %3u :  ID=%9d %10s : MomID=%9d %10s MomIdx=%3d status=%2d :  Pt = %7.1f , Eta = %6.3f, Phi = %6.3f,  px,py,pz,E = %6.1f, %6.1f, %6.1f,   %6.1f\n",
 ///            gpi,
 ///            GenParticles_PdgId->at(gpi), pname,
 ///            GenParticles_ParentId->at(gpi), mname, GenParticles_ParentIdx->at(gpi),
 ///            GenParticles_Status->at(gpi),
 ///            GenParticles->at(gpi).Pt(),
 ///            eta,
 ///            phi,
 ///            GenParticles->at(gpi).Px(),
 ///            GenParticles->at(gpi).Py(),
 ///            GenParticles->at(gpi).Pz(),
 ///            GenParticles->at(gpi).E()
 ///            ) ;
 ///     } // gpi
 ///  }

      if ( is_sl_top ) n_sl_top ++ ;

      if ( ! is_sl_top ) {

        //--- Use same definition of HT as used in HLT path.
         float pfht_pt40_eta26(0.) ;
         for ( unsigned int rji=0; rji < Jets->size() ; rji++ ) {
            TLorentzVector jlv( Jets->at(rji) ) ;
            if ( jlv.Pt() < 40 ) continue ;
            if ( fabs( jlv.Eta()) > 2.6 ) continue ;
            pfht_pt40_eta26 += jlv.Pt() ;
         }




       //--- Approximate a hadronic trigger

         int rec_njet_pt20(0) ;
         int rec_njet_pt30(0) ;
         int rec_njet_pt32(0) ;
         int rec_njet_pt40(0) ;
         int rec_njet_pt45(0) ;
         int rec_njet_pt50(0) ;

         for ( unsigned int rji=0; rji < Jets->size() ; rji++ ) {

               TLorentzVector jlv( Jets->at(rji) ) ;

               if ( jlv.Pt() > 20 ) rec_njet_pt20++ ;
               if ( jlv.Pt() > 30 ) rec_njet_pt30++ ;
               if ( jlv.Pt() > 32 ) rec_njet_pt32++ ;
               if ( jlv.Pt() > 40 ) rec_njet_pt40++ ;
               if ( jlv.Pt() > 45 ) rec_njet_pt45++ ;
               if ( jlv.Pt() > 50 ) rec_njet_pt50++ ;

         } // rji

         h_rec_njet20 -> Fill( rec_njet_pt20 ) ;
         h_rec_njet30 -> Fill( rec_njet_pt30 ) ;
         h_rec_njet32 -> Fill( rec_njet_pt32 ) ;
         h_rec_njet40 -> Fill( rec_njet_pt40 ) ;
         h_rec_njet45 -> Fill( rec_njet_pt45 ) ;
         h_rec_njet50 -> Fill( rec_njet_pt50 ) ;


         int rec_nbtag_csv80(0) ;
         int rec_nbtag_csv85(0) ;
         int rec_nbtag_csv90(0) ;

         for ( int ji=0; ji<Jets_bDiscriminatorCSV->size(); ji++ ) {
            if ( Jets_bDiscriminatorCSV->at(ji) > 0.80 ) rec_nbtag_csv80++ ;
            if ( Jets_bDiscriminatorCSV->at(ji) > 0.85 ) rec_nbtag_csv85++ ;
            if ( Jets_bDiscriminatorCSV->at(ji) > 0.90 ) rec_nbtag_csv90++ ;
         } // ji

         h_rec_nbtag_csv80 -> Fill( rec_nbtag_csv80 ) ;
         h_rec_nbtag_csv85 -> Fill( rec_nbtag_csv85 ) ;
         h_rec_nbtag_csv90 -> Fill( rec_nbtag_csv90 ) ;

         if ( pfht_pt40_eta26 > 380 ) h_rec_njet32_ht380 -> Fill( rec_njet_pt32 ) ;

         if ( pfht_pt40_eta26 > 450 ) h_rec_njet40_ht450 -> Fill( rec_njet_pt40 ) ;
         if ( pfht_pt40_eta26 > 450 ) h_rec_njet45_ht450 -> Fill( rec_njet_pt45 ) ;
         if ( pfht_pt40_eta26 > 450 ) h_rec_njet50_ht450 -> Fill( rec_njet_pt50 ) ;

         if ( pfht_pt40_eta26 > 500 ) h_rec_njet40_ht500 -> Fill( rec_njet_pt40 ) ;
         if ( pfht_pt40_eta26 > 500 ) h_rec_njet45_ht500 -> Fill( rec_njet_pt45 ) ;
         if ( pfht_pt40_eta26 > 500 ) h_rec_njet50_ht500 -> Fill( rec_njet_pt50 ) ;

         if ( pfht_pt40_eta26 > 550 ) h_rec_njet40_ht550 -> Fill( rec_njet_pt40 ) ;
         if ( pfht_pt40_eta26 > 550 ) h_rec_njet45_ht550 -> Fill( rec_njet_pt45 ) ;
         if ( pfht_pt40_eta26 > 550 ) h_rec_njet50_ht550 -> Fill( rec_njet_pt50 ) ;

         if ( HT > 1100 ) h_rec_njet40_ht1100 -> Fill( rec_njet_pt40 ) ;
         if ( HT > 1100 ) h_rec_njet32_ht1100 -> Fill( rec_njet_pt32 ) ;

         h_rec_ht -> Fill( pfht_pt40_eta26 ) ;
         if ( rec_njet_pt32 >= 6 ) h_rec_ht_njet32ge6 -> Fill( pfht_pt40_eta26 ) ;
         if ( rec_njet_pt40 >= 6 ) h_rec_ht_njet40ge6 -> Fill( pfht_pt40_eta26 ) ;
         if ( rec_njet_pt45 >= 6 ) h_rec_ht_njet45ge6 -> Fill( pfht_pt40_eta26 ) ;
         if ( rec_njet_pt50 >= 6 ) h_rec_ht_njet50ge6 -> Fill( pfht_pt40_eta26 ) ;

         if ( rec_njet_pt45 >= 6 && pfht_pt40_eta26 > 500 ) {
            h_rec_nbtag_csv80_ht500_njet45ge6 -> Fill( rec_nbtag_csv80 ) ;
            h_rec_nbtag_csv85_ht500_njet45ge6 -> Fill( rec_nbtag_csv85 ) ;
            h_rec_nbtag_csv90_ht500_njet45ge6 -> Fill( rec_nbtag_csv90 ) ;
         }

      } // not is_sl_top ?


      if ( is_sl_top_e_or_mu ) {

         n_sl_top_e_or_mu ++ ;

      }

      if ( is_sl_top_e ) {

         n_sl_top_e ++ ;

         if ( Electrons->size() > 0 ) {
            TLorentzVector tlv( Electrons->at(0) ) ;
            h_ele_pt -> Fill( tlv.Pt() ) ;
            if ( fabs(tlv.Eta()) < 2.4 ) h_ele_eta24_pt -> Fill( tlv.Pt() ) ;
            h_ele_eta -> Fill( tlv.Eta() ) ;
         } else {
            h_ele_pt -> Fill( -1. ) ;
            h_ele_eta24_pt -> Fill( -9. ) ;
            h_ele_eta -> Fill( -9. ) ;
         }

      }

      if ( is_sl_top_mu ) {

         n_sl_top_mu ++ ;

         if ( Muons->size() > 0 ) {
            TLorentzVector tlv( Muons->at(0) ) ;
            h_mu_pt -> Fill( tlv.Pt() ) ;
            h_mu_eta -> Fill( tlv.Eta() ) ;
         } else {
            h_mu_pt -> Fill( -1. ) ;
            h_mu_eta -> Fill( -9. ) ;
         }

      }

   } // jentry

   add_overflows_to_last_bin( h_ele_pt ) ;
   add_overflows_to_last_bin( h_mu_pt ) ;

   add_overflows_to_last_bin( h_rec_nbtag_csv80 ) ;
   add_overflows_to_last_bin( h_rec_nbtag_csv85 ) ;
   add_overflows_to_last_bin( h_rec_nbtag_csv90 ) ;

   add_overflows_to_last_bin( h_rec_nbtag_csv80_ht500_njet45ge6 ) ;
   add_overflows_to_last_bin( h_rec_nbtag_csv85_ht500_njet45ge6 ) ;
   add_overflows_to_last_bin( h_rec_nbtag_csv90_ht500_njet45ge6 ) ;


   printf("\n\n") ;
   gDirectory -> ls() ;
   printf("\n\n") ;

   printf(" Number and fraction of all-hadronic events : %lld / %llu  ((%.3f %%)\n\n",
      (nentries-n_sl_top), nentries, 100*(nentries-n_sl_top) / (1.*nentries) ) ;

   printf(" Number and fraction of SL top events                : %d / %llu  ((%.3f %%)\n\n",
      n_sl_top, nentries, 100*(n_sl_top) / (1.*nentries) ) ;

   printf(" Number and fraction of SL top events (e or mu only) : %d / %llu  ((%.3f %%)\n\n",
      n_sl_top_e_or_mu, nentries, 100*(n_sl_top_e_or_mu) / (1.*nentries) ) ;

   printf(" Number and fraction of SL top events (e only)       : %d / %llu  ((%.3f %%)\n\n",
      n_sl_top_e, nentries, 100*(n_sl_top_e) / (1.*nentries) ) ;

   printf(" Number and fraction of SL top events (mu only)      : %d / %llu  ((%.3f %%)\n\n",
      n_sl_top_mu, nentries, 100*(n_sl_top_mu) / (1.*nentries) ) ;

   saveHist( output_hist_file_name, "h*" ) ;


} // Loop


//=================================================================================


const char* mcname( int pdgid ) {

   sprintf( pname, "" ) ;

   if ( pdgid == 1 ) sprintf( pname, "d" ) ;
   if ( pdgid == 2 ) sprintf( pname, "u" ) ;
   if ( pdgid == 3 ) sprintf( pname, "s" ) ;
   if ( pdgid == 4 ) sprintf( pname, "c" ) ;
   if ( pdgid == 5 ) sprintf( pname, "b" ) ;
   if ( pdgid == 6 ) sprintf( pname, "t" ) ;

   if ( pdgid == -1 ) sprintf( pname, "d-bar" ) ;
   if ( pdgid == -2 ) sprintf( pname, "u-bar" ) ;
   if ( pdgid == -3 ) sprintf( pname, "s-bar" ) ;
   if ( pdgid == -4 ) sprintf( pname, "c-bar" ) ;
   if ( pdgid == -5 ) sprintf( pname, "b-bar" ) ;
   if ( pdgid == -6 ) sprintf( pname, "t-bar" ) ;

   if ( pdgid == 11 ) sprintf( pname, "e-" ) ;
   if ( pdgid == 12 ) sprintf( pname, "nu_e" ) ;
   if ( pdgid == 13 ) sprintf( pname, "mu-" ) ;
   if ( pdgid == 14 ) sprintf( pname, "nu_mu" ) ;
   if ( pdgid == 15 ) sprintf( pname, "tau-" ) ;
   if ( pdgid == 16 ) sprintf( pname, "nu_tau" ) ;

   if ( pdgid == -11 ) sprintf( pname, "e+" ) ;
   if ( pdgid == -12 ) sprintf( pname, "nu_e-bar" ) ;
   if ( pdgid == -13 ) sprintf( pname, "mu+" ) ;
   if ( pdgid == -14 ) sprintf( pname, "nu_mu-bar" ) ;
   if ( pdgid == -15 ) sprintf( pname, "tau+" ) ;
   if ( pdgid == -16 ) sprintf( pname, "nu_tau-bar" ) ;

   if ( pdgid == 21 ) sprintf( pname, "gluon" ) ;
   if ( pdgid == 22 ) sprintf( pname, "photon" ) ;
   if ( pdgid == 23 ) sprintf( pname, "Z0" ) ;
   if ( pdgid == 24 ) sprintf( pname, "W+" ) ;
   if ( pdgid ==-24 ) sprintf( pname, "W-" ) ;
   if ( pdgid == 25 ) sprintf( pname, "h" ) ;
   if ( pdgid == 35 ) sprintf( pname, "H" ) ;
   if ( pdgid == 36 ) sprintf( pname, "a" ) ;


   if ( pdgid == 1000001 ) sprintf( pname, "~dL" ) ;
   if ( pdgid == 1000002 ) sprintf( pname, "~uL" ) ;
   if ( pdgid == 1000003 ) sprintf( pname, "~sL" ) ;
   if ( pdgid == 1000004 ) sprintf( pname, "~cL" ) ;
   if ( pdgid == 1000005 ) sprintf( pname, "~b1" ) ;
   if ( pdgid == 1000006 ) sprintf( pname, "~t1" ) ;

   if ( pdgid == -1000001 ) sprintf( pname, "~dL*" ) ;
   if ( pdgid == -1000002 ) sprintf( pname, "~uL*" ) ;
   if ( pdgid == -1000003 ) sprintf( pname, "~sL*" ) ;
   if ( pdgid == -1000004 ) sprintf( pname, "~cL*" ) ;
   if ( pdgid == -1000005 ) sprintf( pname, "~b1*" ) ;
   if ( pdgid == -1000006 ) sprintf( pname, "~t1*" ) ;

   if ( pdgid == 1000022 ) sprintf( pname, "~chi01" ) ;

   return pname ;


} // mcname

//=====================================================================

double calcDr( double eta1, double eta2, double phi1, double phi2 ) {

   double deta = fabs( eta1 - eta2 ) ;

   double dphi = phi1 - phi2 ;
   if ( dphi > 3.1415926 ) dphi -= 2*3.1415926 ;
   if ( dphi <-3.1415926 ) dphi += 2*3.1415926 ;

   return sqrt( dphi*dphi + deta*deta ) ;

} // calcDr

//=====================================================================

void add_overflows_to_last_bin( TH1F* hp ) {
   if ( hp == 0x0 ) return ;
   float last_bin = hp -> GetBinContent( hp->GetNbinsX() ) ;
   float overflow = hp -> GetBinContent( hp->GetNbinsX()+1 ) ;
   hp -> SetBinContent( hp->GetNbinsX(), last_bin + overflow ) ;
}

//=====================================================================









