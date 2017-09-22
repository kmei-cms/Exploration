
#include "histio.c"

   TH1F* get_hist_1d( const char* hname ) ;
   void set_style_1d( TH1F* hp, int style_ind, const char* xtitle ) ;
   TH1F* shift_hist( TH1F* hp, float shift ) ;

   void draw_trig_eff() {

      gDirectory -> Delete( "h*" ) ;

      gStyle -> SetPadBottomMargin( 0.15 ) ;
      gStyle -> SetPadLeftMargin( 0.15 ) ;
      gStyle -> SetOptTitle(0) ;

      loadHist( "outputfiles/trig-eff-merged-rpv_stop_350_t3j_uds-plots.root", "rpv350" ) ;
      loadHist( "outputfiles/trig-eff-merged-rpv_stop_450_t3j_uds-plots.root", "rpv450" ) ;
      loadHist( "outputfiles/trig-eff-merged-rpv_stop_550_t3j_uds-plots.root", "rpv550" ) ;
      loadHist( "outputfiles/trig-eff-merged-rpv_stop_650_t3j_uds-plots.root", "rpv650" ) ;

      loadHist( "outputfiles/trig-eff-merged-stealth_stop_350_singlino_SYY-plots.root", "stealth_syy_350" ) ;
      loadHist( "outputfiles/trig-eff-merged-stealth_stop_350_singlino_SHuHd-plots.root", "stealth_shh_350" ) ;

      gDirectory -> ls( "h_rec_njet45_ht500*" ) ;


      TCanvas* can1 = new TCanvas( "can1", "", 900, 700 ) ;

      char hname_pre[100] ;
      char hname[100] ;
      char xtitle[100] ;
      char ytitle[100] ;
      char fname[1000] ;
      char tag1[100] ;
      char tag2[100] ;
      char tag3[100] ;
      char tag4[100] ;

      TH1F* hp1 ;
      TH1F* hp2 ;
      TH1F* hp3 ;
      TH1F* hp4 ;
      TLegend* legend ;



     //-----------

      TH1F* h_rec_njet45_ht500_rpv350          = get_hist_1d( "h_rec_njet45_ht500_rpv350" ) ;
      TH1F* h_rec_njet45_ht500_rpv450          = get_hist_1d( "h_rec_njet45_ht500_rpv450" ) ;
      TH1F* h_rec_njet45_ht500_rpv550          = get_hist_1d( "h_rec_njet45_ht500_rpv550" ) ;
      TH1F* h_rec_njet45_ht500_rpv650          = get_hist_1d( "h_rec_njet45_ht500_rpv650" ) ;
      TH1F* h_rec_njet45_ht500_stealth_syy_350 = get_hist_1d( "h_rec_njet45_ht500_stealth_syy_350" ) ;
      TH1F* h_rec_njet45_ht500_stealth_shh_350 = get_hist_1d( "h_rec_njet45_ht500_stealth_shh_350" ) ;

      TH1F* h_rec_njet45_rpv350          = get_hist_1d( "h_rec_njet45_rpv350" ) ;
      TH1F* h_rec_njet45_rpv450          = get_hist_1d( "h_rec_njet45_rpv450" ) ;
      TH1F* h_rec_njet45_rpv550          = get_hist_1d( "h_rec_njet45_rpv550" ) ;
      TH1F* h_rec_njet45_rpv650          = get_hist_1d( "h_rec_njet45_rpv650" ) ;
      TH1F* h_rec_njet45_stealth_syy_350 = get_hist_1d( "h_rec_njet45_stealth_syy_350" ) ;
      TH1F* h_rec_njet45_stealth_shh_350 = get_hist_1d( "h_rec_njet45_stealth_shh_350" ) ;


      float total_rpv350 = h_rec_njet45_rpv350 -> Integral() ;
      float total_rpv450 = h_rec_njet45_rpv450 -> Integral() ;
      float total_rpv550 = h_rec_njet45_rpv550 -> Integral() ;
      float total_rpv650 = h_rec_njet45_rpv650 -> Integral() ;

      float total_stealth_syy_350 = h_rec_njet45_stealth_syy_350 -> Integral() ;
      float total_stealth_shh_350 = h_rec_njet45_stealth_shh_350 -> Integral() ;

      float pass_rpv350 = h_rec_njet45_ht500_rpv350 -> Integral( 7, 21 ) ; // bin 7 is Njets = 6
      float pass_rpv450 = h_rec_njet45_ht500_rpv450 -> Integral( 7, 21 ) ; // bin 7 is Njets = 6
      float pass_rpv550 = h_rec_njet45_ht500_rpv550 -> Integral( 7, 21 ) ; // bin 7 is Njets = 6
      float pass_rpv650 = h_rec_njet45_ht500_rpv650 -> Integral( 7, 21 ) ; // bin 7 is Njets = 6

      float pass_stealth_syy_350 = h_rec_njet45_stealth_syy_350 -> Integral( 7, 21 ) ;
      float pass_stealth_shh_350 = h_rec_njet45_stealth_shh_350 -> Integral( 7, 21 ) ;

      float eff_val_rpv350 = pass_rpv350 / total_rpv350 ;
      float eff_val_rpv450 = pass_rpv450 / total_rpv450 ;
      float eff_val_rpv550 = pass_rpv550 / total_rpv550 ;
      float eff_val_rpv650 = pass_rpv650 / total_rpv650 ;
      float eff_val_stealth_syy_350 = pass_stealth_syy_350 / total_stealth_syy_350 ;
      float eff_val_stealth_shh_350 = pass_stealth_shh_350 / total_stealth_syy_350 ;

      printf(" Efficiency, rpv350 : %.3f\n", eff_val_rpv350 ) ;
      printf(" Efficiency, rpv450 : %.3f\n", eff_val_rpv450 ) ;
      printf(" Efficiency, rpv550 : %.3f\n", eff_val_rpv550 ) ;
      printf(" Efficiency, rpv650 : %.3f\n", eff_val_rpv650 ) ;
      printf(" Efficiency, stealth_syy_350 : %.3f\n", eff_val_stealth_syy_350 ) ;
      printf(" Efficiency, stealth_shh_350 : %.3f\n", eff_val_stealth_shh_350 ) ;



     //--------

      sprintf( tag1, "rpv350" ) ;
      sprintf( xtitle, "Njets, pt>40, AK4" ) ;

      sprintf( hname_pre, "h_rec_njet45" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp1 = get_hist_1d( hname ) ; set_style_1d( hp1, 1, xtitle ) ;
      sprintf( hname_pre, "h_rec_njet45_ht500" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp2 = get_hist_1d( hname ) ; set_style_1d( hp2, 1, xtitle ) ;
      hp2 -> SetLineStyle(2) ;

      legend = new TLegend( 0.70, 0.60, 0.85, 0.80 ) ;
      legend -> AddEntry( hp1, "all" ) ;
      legend -> AddEntry( hp2, "HT>500" ) ;

      hp1->Draw() ;
      hp2->Draw("same") ;
      legend -> Draw() ;

      sprintf( fname, "outputfiles/njet45-ht500-%s.pdf", tag1 ) ;
      can1 -> SaveAs( fname ) ;


     //--------

      sprintf( tag1, "rpv350" ) ;
      sprintf( xtitle, "HT" ) ;

      sprintf( hname_pre, "h_rec_ht" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp1 = get_hist_1d( hname ) ; set_style_1d( hp1, 1, xtitle ) ;
      sprintf( hname_pre, "h_rec_ht_njet45ge6" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp2 = get_hist_1d( hname ) ; set_style_1d( hp2, 1, xtitle ) ;
      hp2 -> SetLineStyle(2) ;

      legend = new TLegend( 0.40, 0.60, 0.85, 0.80 ) ;
      legend -> AddEntry( hp1, "all" ) ;
      legend -> AddEntry( hp2, "Njets >= 6 (pt>45)" ) ;

      hp1->Draw() ;
      hp2->Draw("same") ;
      legend -> Draw() ;

      sprintf( fname, "outputfiles/ht-njet45ge6-%s.pdf", tag1 ) ;
      can1 -> SaveAs( fname ) ;





     //--------

      sprintf( tag1, "rpv350" ) ;
      sprintf( tag2, "rpv450" ) ;
      sprintf( tag3, "rpv550" ) ;
      sprintf( tag4, "rpv650" ) ;
      sprintf( xtitle, "HT" ) ;

      sprintf( hname_pre, "h_rec_ht_njet45ge6" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp1 = get_hist_1d( hname ) ; set_style_1d( hp1, 1, xtitle ) ;
      sprintf( hname, "%s_%s", hname_pre, tag2 ) ; hp2 = get_hist_1d( hname ) ; set_style_1d( hp2, 2, xtitle ) ;
      sprintf( hname, "%s_%s", hname_pre, tag3 ) ; hp3 = get_hist_1d( hname ) ; set_style_1d( hp3, 3, xtitle ) ;
      sprintf( hname, "%s_%s", hname_pre, tag4 ) ; hp4 = get_hist_1d( hname ) ; set_style_1d( hp4, 4, xtitle ) ;
      hp1 -> SetLineStyle(1) ;
      hp2 -> SetLineStyle(1) ;
      hp3 -> SetLineStyle(1) ;
      hp4 -> SetLineStyle(1) ;

      hp1 -> SetNormFactor( 1. ) ;
      hp2 -> SetNormFactor( 1. ) ;
      hp3 -> SetNormFactor( 1. ) ;
      hp4 -> SetNormFactor( 1. ) ;

      legend = new TLegend( 0.70, 0.60, 0.85, 0.80 ) ;
      legend -> AddEntry( hp1, "350" ) ;
      legend -> AddEntry( hp2, "450" ) ;
      legend -> AddEntry( hp3, "550" ) ;
      legend -> AddEntry( hp4, "650" ) ;

      hp1->Draw() ;
      hp2->Draw("same") ;
      hp3->Draw("same") ;
      hp4->Draw("same") ;
      legend -> Draw() ;

      sprintf( fname, "outputfiles/ht-njet45ge6-mass-comp.pdf" ) ;
      can1 -> SaveAs( fname ) ;



     //--------

      sprintf( tag1, "rpv350" ) ;
      sprintf( tag2, "rpv450" ) ;
      sprintf( tag3, "rpv550" ) ;
      sprintf( tag4, "rpv650" ) ;
      sprintf( xtitle, "Njets, pt>40, AK4" ) ;

      TH1F* thp1 ;
      TH1F* thp2 ;
      TH1F* thp3 ;
      TH1F* thp4 ;
      sprintf( hname_pre, "h_rec_njet45_ht500" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; thp1 = get_hist_1d( hname ) ;
      sprintf( hname, "%s_%s", hname_pre, tag2 ) ; thp2 = get_hist_1d( hname ) ;
      sprintf( hname, "%s_%s", hname_pre, tag3 ) ; thp3 = get_hist_1d( hname ) ;
      sprintf( hname, "%s_%s", hname_pre, tag4 ) ; thp4 = get_hist_1d( hname ) ;
      hp1 = shift_hist( thp1, -0.09 ) ;
      hp2 = shift_hist( thp2, -0.03 ) ;
      hp3 = shift_hist( thp3,  0.03 ) ;
      hp4 = shift_hist( thp4,  0.09 ) ;
      set_style_1d( hp1, 1, xtitle ) ;
      set_style_1d( hp2, 2, xtitle ) ;
      set_style_1d( hp3, 3, xtitle ) ;
      set_style_1d( hp4, 4, xtitle ) ;

      hp1 -> SetLineStyle(1) ;
      hp2 -> SetLineStyle(1) ;
      hp3 -> SetLineStyle(1) ;
      hp4 -> SetLineStyle(1) ;

      hp1 -> SetNormFactor( 1. ) ;
      hp2 -> SetNormFactor( 1. ) ;
      hp3 -> SetNormFactor( 1. ) ;
      hp4 -> SetNormFactor( 1. ) ;

      legend = new TLegend( 0.70, 0.60, 0.85, 0.80 ) ;
      legend -> AddEntry( hp1, "350" ) ;
      legend -> AddEntry( hp2, "450" ) ;
      legend -> AddEntry( hp3, "550" ) ;
      legend -> AddEntry( hp4, "650" ) ;

      hp1->Draw() ;
      hp2->Draw("same") ;
      hp3->Draw("same") ;
      hp4->Draw("same") ;
      legend -> Draw() ;

      sprintf( fname, "outputfiles/njet45-ht500-mass-comp.pdf" ) ;
      can1 -> SaveAs( fname ) ;




   } // draw_trig_eff

  //===========================================================================================

   void set_style_1d( TH1F* hp, int style_ind, const char* xtitle ) {

      if ( hp == 0x0 ) return ;

      hp -> SetXTitle( xtitle ) ;

      hp -> SetLineWidth(3) ;
      hp -> SetTitleOffset( 1.1, "x" ) ;
      hp -> SetTitleSize( 0.050, "x" ) ;

      if ( style_ind == 1 ) {
         hp -> SetLineColor(4) ;
      } else if ( style_ind == 2 ) {
         hp -> SetLineColor(2) ;
      } else if ( style_ind == 3 ) {
         hp -> SetLineColor(8) ;
      } else if ( style_ind == 4 ) {
         hp -> SetLineColor(6) ;
      }

   } // set_style_1d

  //===========================================================================================

   TH1F* get_hist_1d( const char* hname ) {
      TH1F* rp = (TH1F*) gDirectory -> FindObject( hname ) ;
      if ( rp == 0x0 ) {
         printf("\n\n *** Can't find hist %s\n\n", hname ) ;
         gSystem -> Exit( -1 ) ;
      }
      return rp ;
   } // get_hist_1d

  //===========================================================================================

   TH1F* shift_hist( TH1F* hp, float shift ) {
      if ( hp == 0x0 ) { printf("\n\n *** null hp.\n\n" ) ; gSystem -> Exit(-1) ; }
      char hname[100] ;
      sprintf( hname, "%s_shift", hp->GetName() ) ;
      TH1F* rhp = new TH1F( hname, hp->GetTitle(), hp->GetNbinsX(),
              hp->GetXaxis()->GetBinLowEdge(1)+shift,
              hp->GetXaxis()->GetBinUpEdge(hp->GetNbinsX())+shift ) ;
      for ( int bi=1; bi<=hp->GetNbinsX(); bi++ ) {
         rhp -> SetBinContent( bi, hp->GetBinContent( bi ) ) ;
      }
      return rhp ;

   } // shift_hist

  //===========================================================================================
