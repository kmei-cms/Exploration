#define trig_eff_cxx
#include "trig_eff.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "histio.c"

char pname[100] ;

const char* mcname( int pdgid ) ;

double calcDr( double eta1, double eta2, double phi1, double phi2 ) ;

void trig_eff::Loop( int max_events, bool verb )
{

   bool skip_sl_top_events(true) ;

   int n_skipped(0) ;

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




   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();
   if ( max_events > 0 ) nentries = max_events ;

   Long64_t nbytes = 0, nb = 0;

   int n_missing_b(0) ;

   for (Long64_t jentry=0; jentry<nentries;jentry++) {

      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;


      if ( jentry % (nentries/10) == 0 ) printf("  Event %9llu / %9llu  (%2.0f%%)\n", jentry, nentries, 100*(jentry*1.)/(nentries*1.) ) ;




      if ( verb ) printf("\n\n =========== number %9llu : Run %9u , Lumi %9u , Event %9llu\n", jentry, RunNum, LumiBlockNum, EvtNum ) ;

      if ( verb ) printf("\n\n GenParticles: %lu\n", GenParticles->size() ) ;


      bool skip_event(false) ;
      for ( unsigned int gpi=0; gpi < GenParticles->size() ; gpi++ ) {

         int spdgid = GenParticles_PdgId->at(gpi) ;
         int pdgid = abs( GenParticles_PdgId->at(gpi) ) ;
         int smomid = GenParticles_ParentId->at(gpi) ;
         int momid = abs( GenParticles_ParentId->at(gpi) ) ;
         int momidx = GenParticles_ParentIdx->at(gpi) ;

         if ( skip_sl_top_events && ( ( pdgid==11 || pdgid==13 || pdgid==15 ) && momid == 24 ) ) { skip_event = true ; }

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
         } // verbose?

      } // gpi


      if ( skip_event ) {
         n_skipped ++ ;
         if ( verb ) printf("\n\n *** skipping event.\n\n") ;
         continue ;
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


      if ( HT > 380 ) h_rec_njet32_ht380 -> Fill( rec_njet_pt32 ) ;

      if ( HT > 450 ) h_rec_njet40_ht450 -> Fill( rec_njet_pt40 ) ;
      if ( HT > 450 ) h_rec_njet45_ht450 -> Fill( rec_njet_pt45 ) ;
      if ( HT > 450 ) h_rec_njet50_ht450 -> Fill( rec_njet_pt50 ) ;

      if ( HT > 500 ) h_rec_njet40_ht500 -> Fill( rec_njet_pt40 ) ;
      if ( HT > 500 ) h_rec_njet45_ht500 -> Fill( rec_njet_pt45 ) ;
      if ( HT > 500 ) h_rec_njet50_ht500 -> Fill( rec_njet_pt50 ) ;

      if ( HT > 550 ) h_rec_njet40_ht550 -> Fill( rec_njet_pt40 ) ;
      if ( HT > 550 ) h_rec_njet45_ht550 -> Fill( rec_njet_pt45 ) ;
      if ( HT > 550 ) h_rec_njet50_ht550 -> Fill( rec_njet_pt50 ) ;

      if ( HT > 1100 ) h_rec_njet40_ht1100 -> Fill( rec_njet_pt40 ) ;
      if ( HT > 1100 ) h_rec_njet32_ht1100 -> Fill( rec_njet_pt32 ) ;

      h_rec_ht -> Fill( HT ) ;
      if ( rec_njet_pt32 >= 6 ) h_rec_ht_njet32ge6 -> Fill( HT ) ;
      if ( rec_njet_pt40 >= 6 ) h_rec_ht_njet40ge6 -> Fill( HT ) ;
      if ( rec_njet_pt45 >= 6 ) h_rec_ht_njet45ge6 -> Fill( HT ) ;
      if ( rec_njet_pt50 >= 6 ) h_rec_ht_njet50ge6 -> Fill( HT ) ;



   } // jentry

   printf("\n\n") ;
   gDirectory -> ls() ;
   printf("\n\n") ;

   printf(" Skipped  %d / %llu  (%.3f %%)\n\n", n_skipped, nentries, 100*n_skipped/(1.*nentries) ) ;
   printf(" analyzed %lld / %llu  (%.3f %%)\n\n", (nentries-n_skipped), nentries, 100*(nentries-n_skipped)/(1.*nentries) ) ;

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

