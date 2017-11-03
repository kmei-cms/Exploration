
#include "load_qcd_ab_hists.c"

   TH1F* get_hist_1d( const char* hname ) ;

   void draw_analysis_bins( const char* sample = "rpv350" ) {

      gDirectory -> Delete("h*") ;

      gSystem -> Exec( "mkdir -p outputfiles/plots-analysis-bins" ) ;

      gStyle -> SetPadBottomMargin(0.25) ;
      gStyle -> SetPadRightMargin(0.30) ;

      TCanvas* can1 = (TCanvas*) gDirectory -> FindObject( "can1" ) ;
      if ( can1 == 0x0 ) {
         can1 = new TCanvas( "can1", "", 1000, 900 ) ;
      }
      can1 -> Clear() ;



      loadHist( "outputfiles/analysis-bin-hists-Qsum.root", "qcd" ) ;
      loadHist( "outputfiles/analysis-bin-hists-TT_Tune.root", "ttbar" ) ;

      loadHist( "outputfiles/analysis-bin-hists-rpv_stop_350.root", "rpv350" ) ;
      loadHist( "outputfiles/analysis-bin-hists-stealth_stop_350_singlino_SYY.root", "stealth_syy_350" ) ;
      loadHist( "outputfiles/analysis-bin-hists-stealth_stop_350_singlino_SHuHd.root", "stealth_shh_350" ) ;

      loadHist( "outputfiles/analysis-bin-hists-rpv_stop_450.root", "rpv450" ) ;
      loadHist( "outputfiles/analysis-bin-hists-stealth_stop_450_singlino_SYY.root", "stealth_syy_450" ) ;
      loadHist( "outputfiles/analysis-bin-hists-stealth_stop_450_singlino_SHuHd.root", "stealth_shh_450" ) ;

      loadHist( "outputfiles/analysis-bin-hists-rpv_stop_550.root", "rpv550" ) ;
      loadHist( "outputfiles/analysis-bin-hists-stealth_stop_550_singlino_SYY.root", "stealth_syy_550" ) ;
      loadHist( "outputfiles/analysis-bin-hists-stealth_stop_550_singlino_SHuHd.root", "stealth_shh_550" ) ;

      loadHist( "outputfiles/analysis-bin-hists-rpv_stop_650.root", "rpv650" ) ;
      loadHist( "outputfiles/analysis-bin-hists-stealth_stop_650_singlino_SYY.root", "stealth_syy_650" ) ;
      loadHist( "outputfiles/analysis-bin-hists-stealth_stop_650_singlino_SHuHd.root", "stealth_shh_650" ) ;

     //-----

////  loadHist( "outputfiles/analysis-bin-hists-4T_Tune.root", "tttt" ) ;
////  loadHist( "outputfiles/analysis-bin-hists-ttX-TTGJets.root", "ttX-TTGJets" ) ;
////  loadHist( "outputfiles/analysis-bin-hists-ttX-TTGamma.root", "ttX-TTGamma" ) ;
////  loadHist( "outputfiles/analysis-bin-hists-ttX-TTWJetsToQQ.root", "ttX-TTWJetsToQQ" ) ;
////  loadHist( "outputfiles/analysis-bin-hists-ttX-TTZToQQ.root", "ttX-TTZToQQ" ) ;

////  loadHist( "outputfiles/analysis-bin-hists-ttXX-Summer16_private.TTHH.root", "ttXX-TTHH" ) ;
////  loadHist( "outputfiles/analysis-bin-hists-ttXX-Summer16_private.TTWH.root", "ttXX-TTWH" ) ;
////  loadHist( "outputfiles/analysis-bin-hists-ttXX-Summer16_private.TTWW.root", "ttXX-TTWW" ) ;
////  loadHist( "outputfiles/analysis-bin-hists-ttXX-Summer16_private.TTWZ.root", "ttXX-TTWZ" ) ;
////  loadHist( "outputfiles/analysis-bin-hists-ttXX-Summer16_private.TTZH.root", "ttXX-TTZH" ) ;
////  loadHist( "outputfiles/analysis-bin-hists-ttXX-Summer16_private.TTZZ.root", "ttXX-TTZZ" ) ;

////  loadHist( "outputfiles/analysis-bin-hists-tttX-Summer16_private.TTTW.root", "tttX-TTTW" ) ;

      gDirectory -> ls() ;

      char hname[100] ;

      TH1F* h_qcd = get_hist_1d( "h_analysis_bins_qcd" ) ;
      TH1F* h_ttbar = get_hist_1d( "h_analysis_bins_ttbar" ) ;

//    TH1F* h_tttt = get_hist_1d( "h_analysis_bins_tttt" ) ;

//    TH1F* h_ttX_TTGJets     = get_hist_1d( "h_analysis_bins_ttX-TTGJets" ) ;
//    TH1F* h_ttX_TTGamma     = get_hist_1d( "h_analysis_bins_ttX-TTGamma" ) ;
//    TH1F* h_ttX_TTWJetsToQQ = get_hist_1d( "h_analysis_bins_ttX-TTWJetsToQQ" ) ;
//    TH1F* h_ttX_TTZToQQ     = get_hist_1d( "h_analysis_bins_ttX-TTZToQQ" ) ;
//    TH1F* h_ttXX_TTHH       = get_hist_1d( "h_analysis_bins_ttXX-TTHH" ) ;
//    TH1F* h_ttXX_TTWH       = get_hist_1d( "h_analysis_bins_ttXX-TTWH" ) ;
//    TH1F* h_ttXX_TTWW       = get_hist_1d( "h_analysis_bins_ttXX-TTWW" ) ;
//    TH1F* h_ttXX_TTWZ       = get_hist_1d( "h_analysis_bins_ttXX-TTWZ" ) ;
//    TH1F* h_ttXX_TTZH       = get_hist_1d( "h_analysis_bins_ttXX-TTZH" ) ;
//    TH1F* h_ttXX_TTZZ       = get_hist_1d( "h_analysis_bins_ttXX-TTZZ" ) ;
//    TH1F* h_tttX_TTTW       = get_hist_1d( "h_analysis_bins_tttX-TTTW" ) ;

      sprintf( hname, "h_analysis_bins_%s", sample ) ;
      TH1F* h_signal = get_hist_1d( hname ) ;




      h_qcd -> SetFillColor( 40 ) ;
      h_ttbar -> SetFillColor( 41 ) ;

//    h_tttt            -> SetFillColor( 42 ) ;
//    h_ttX_TTGJets     -> SetFillColor( 43 ) ;
//    h_ttX_TTGamma     -> SetFillColor( 44 ) ;
//    h_ttX_TTWJetsToQQ -> SetFillColor( 45 ) ;
//    h_ttX_TTZToQQ     -> SetFillColor( 46 ) ;
//    h_ttXX_TTHH       -> SetFillColor( 47 ) ;
//    h_ttXX_TTWH       -> SetFillColor( 48 ) ;
//    h_ttXX_TTWW       -> SetFillColor( 49 ) ;
//    h_ttXX_TTWZ       -> SetFillColor( 30 ) ;
//    h_ttXX_TTZH       -> SetFillColor( 31 ) ;
//    h_ttXX_TTZZ       -> SetFillColor( 32 ) ;
//    h_tttX_TTTW       -> SetFillColor( 33 ) ;

      h_signal -> SetLineColor(4) ;
      h_signal -> SetLineWidth(4) ;


      THStack* h_bg_stack = new THStack( "h_bg_stack", "" ) ;
//    h_bg_stack -> Add(h_ttXX_TTHH         ) ;
//    h_bg_stack -> Add(h_ttXX_TTWH         ) ;
//    h_bg_stack -> Add(h_ttXX_TTWW         ) ;
//    h_bg_stack -> Add(h_ttXX_TTWZ         ) ;
//    h_bg_stack -> Add(h_ttXX_TTZH         ) ;
//    h_bg_stack -> Add(h_ttXX_TTZZ         ) ;
//    h_bg_stack -> Add(h_tttX_TTTW         ) ;
//    h_bg_stack -> Add(h_tttt              ) ;
//    h_bg_stack -> Add(h_ttX_TTGJets       ) ;
//    h_bg_stack -> Add(h_ttX_TTGamma       ) ;
//    h_bg_stack -> Add(h_ttX_TTWJetsToQQ   ) ;
//    h_bg_stack -> Add(h_ttX_TTZToQQ       ) ;
      h_bg_stack -> Add( h_qcd ) ;
      h_bg_stack -> Add( h_ttbar ) ;

      h_bg_stack -> Draw( "hist" ) ;
      h_bg_stack -> Draw( "same" ) ;


      TLegend* legend = new TLegend( 0.80, 0.10, 0.95, 0.90 ) ;
      legend -> AddEntry( h_ttbar, "ttbar" ) ;
      legend -> AddEntry( h_qcd, "QCD" ) ;
//    legend -> AddEntry( h_ttX_TTZToQQ, "TTZ" ) ;
//    legend -> AddEntry( h_ttX_TTWJetsToQQ, "TTW" ) ;
//    legend -> AddEntry( h_ttX_TTGJets, "TTjgamma" ) ;
//    legend -> AddEntry( h_ttX_TTGamma, "TTgamma" ) ;
//    legend -> AddEntry( h_tttt, "TTTT" ) ;
//    legend -> AddEntry( h_tttX_TTTW, "TTTW" ) ;
//    legend -> AddEntry( h_ttXX_TTZZ, "TTZZ" ) ;
//    legend -> AddEntry( h_ttXX_TTZH, "TTZH" ) ;
//    legend -> AddEntry( h_ttXX_TTWZ, "TTWZ" ) ;
//    legend -> AddEntry( h_ttXX_TTWW, "TTWW" ) ;
//    legend -> AddEntry( h_ttXX_TTWH, "TTWH" ) ;
//    legend -> AddEntry( h_ttXX_TTZZ, "TTZZ" ) ;







      TH1* hp = h_bg_stack->GetHistogram() ;
      hp -> GetXaxis() -> LabelsOption("v") ;

      h_bg_stack -> Draw( "hist" ) ;
      h_bg_stack -> Draw( "same" ) ;

      h_signal -> Draw( "hist same" ) ;
      h_signal -> Draw( "same" ) ;

      gPad -> SetGridy(1) ;

      legend -> Draw() ;


      h_bg_stack -> SetMinimum( 0.5 ) ;

      char fname[1000] ;


      gPad -> SetLogy(1) ;

      sprintf( fname, "outputfiles/plots-analysis-bins/analysis-bins-plot-%s-logy.pdf", sample ) ;
      can1 -> Update() ; can1 -> Draw() ;
      can1 -> SaveAs( fname ) ;

      gPad -> SetLogy(0) ;

      sprintf( fname, "outputfiles/plots-analysis-bins/analysis-bins-plot-%s-liny-full.pdf", sample ) ;
      can1 -> Update() ; can1 -> Draw() ;
      can1 -> SaveAs( fname ) ;


      h_bg_stack -> SetMaximum( 1500 ) ;

      sprintf( fname, "outputfiles/plots-analysis-bins/analysis-bins-plot-%s-liny-zoom1.pdf", sample ) ;
      can1 -> Update() ; can1 -> Draw() ;
      can1 -> SaveAs( fname ) ;

      h_bg_stack -> SetMaximum( 500 ) ;

      sprintf( fname, "outputfiles/plots-analysis-bins/analysis-bins-plot-%s-liny-zoom2.pdf", sample ) ;
      can1 -> Update() ; can1 -> Draw() ;
      can1 -> SaveAs( fname ) ;


   }

  //===========================================================================================

   TH1F* get_hist_1d( const char* hname ) {
      TH1F* rp = (TH1F*) gDirectory -> FindObject( hname ) ;
      if ( rp == 0x0 ) {
         printf("\n\n *** Can't find hist %s\n\n", hname ) ;
         gDirectory->ls() ;
         gSystem -> Exit( -1 ) ;
      }
      return rp ;
   } // get_hist_1d

  //===========================================================================================

