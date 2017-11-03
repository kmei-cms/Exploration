


#include "histio.c"

   void set_style_1d( TH1F* hp, int style_ind, const char* xtitle ) ;
   void set_style_2d( TH2F* hp, const char* xtitle, const char* ytitle ) ;
   TH1F* get_hist_1d( const char* hname ) ;
   TH2F* get_hist_2d( const char* hname ) ;

 //--------------------

   void draw_rpv1( const char* file1 = "outputfiles/rpv-analysis2-rpv_350.root",
                   const char* file2 = "outputfiles/rpv-analysis2-rpv_650.root",
                   const char* tag1 = "350",
                   const char* tag2 = "650" ) {

      gDirectory -> Delete( "h*" ) ;

      gSystem -> Exec( "mkdir -p outputfiles-rpv" ) ;

      gStyle -> SetPadBottomMargin( 0.15 ) ;
      gStyle -> SetPadLeftMargin( 0.15 ) ;
      gStyle -> SetOptTitle(0) ;

      loadHist( file1, tag1 ) ;
      loadHist( file2, tag2 ) ;

      gDirectory -> ls() ;

      TCanvas* can1 = (TCanvas*) gDirectory->FindObject( "can1" ) ;
      if ( can1 == 0x0 ) can1 = new TCanvas( "can1", "", 900, 700 ) ;

      char hname_pre[100] ;
      char hname[100] ;
      char xtitle[100] ;
      char ytitle[100] ;
      char fname[1000] ;

      TH1F* hp1 ;
      TH1F* hp2 ;
      TH2F* hp2d ;
      TLegend* legend ;




    //------------

      sprintf( hname_pre, "h_top_pt" ) ;
      sprintf( xtitle, "Top pt" ) ;

      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp1 = get_hist_1d( hname ) ; set_style_1d( hp1, 1, xtitle ) ;
      sprintf( hname, "%s_%s", hname_pre, tag2 ) ; hp2 = get_hist_1d( hname ) ; set_style_1d( hp2, 2, xtitle ) ;

      legend = new TLegend( 0.70, 0.60, 0.85, 0.80 ) ;
      legend -> AddEntry( hp1, tag1 ) ;
      legend -> AddEntry( hp2, tag2 ) ;

      hp1->Draw() ;
      hp2->Draw("same") ;
      legend -> Draw() ;

      can1 -> SaveAs( "outputfiles-rpv/pt-top.pdf" ) ;


    //------------

      sprintf( hname_pre, "h_stop_pt" ) ;
      sprintf( xtitle, "stop pt" ) ;

      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp1 = get_hist_1d( hname ) ; set_style_1d( hp1, 1, xtitle ) ;
      sprintf( hname, "%s_%s", hname_pre, tag2 ) ; hp2 = get_hist_1d( hname ) ; set_style_1d( hp2, 2, xtitle ) ;

      legend = new TLegend( 0.70, 0.60, 0.85, 0.80 ) ;
      legend -> AddEntry( hp1, tag1 ) ;
      legend -> AddEntry( hp2, tag2 ) ;

      hp1->Draw() ;
      hp2->Draw("same") ;
      legend -> Draw() ;

      can1 -> SaveAs( "outputfiles-rpv/pt-stop.pdf" ) ;


    //------------

      sprintf( hname_pre, "h_chi_pt" ) ;
      sprintf( xtitle, "chi pt" ) ;

      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp1 = get_hist_1d( hname ) ; set_style_1d( hp1, 1, xtitle ) ;
      sprintf( hname, "%s_%s", hname_pre, tag2 ) ; hp2 = get_hist_1d( hname ) ; set_style_1d( hp2, 2, xtitle ) ;

      legend = new TLegend( 0.70, 0.60, 0.85, 0.80 ) ;
      legend -> AddEntry( hp1, tag1 ) ;
      legend -> AddEntry( hp2, tag2 ) ;

      hp1->Draw() ;
      hp2->Draw("same") ;
      legend -> Draw() ;

      can1 -> SaveAs( "outputfiles-rpv/pt-chi.pdf" ) ;



    //------------

      sprintf( hname_pre, "h_w_pt" ) ;
      sprintf( xtitle, "W pt" ) ;

      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp1 = get_hist_1d( hname ) ; set_style_1d( hp1, 1, xtitle ) ;
      sprintf( hname, "%s_%s", hname_pre, tag2 ) ; hp2 = get_hist_1d( hname ) ; set_style_1d( hp2, 2, xtitle ) ;

      legend = new TLegend( 0.70, 0.60, 0.85, 0.80 ) ;
      legend -> AddEntry( hp1, tag1 ) ;
      legend -> AddEntry( hp2, tag2 ) ;

      hp1->Draw() ;
      hp2->Draw("same") ;
      legend -> Draw() ;

      can1 -> SaveAs( "outputfiles-rpv/pt-w.pdf" ) ;



    //------------

      sprintf( hname_pre, "h_b_pt" ) ;
      sprintf( xtitle, "b pt" ) ;

      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp1 = get_hist_1d( hname ) ; set_style_1d( hp1, 1, xtitle ) ;
      sprintf( hname, "%s_%s", hname_pre, tag2 ) ; hp2 = get_hist_1d( hname ) ; set_style_1d( hp2, 2, xtitle ) ;

      legend = new TLegend( 0.70, 0.60, 0.85, 0.80 ) ;
      legend -> AddEntry( hp1, tag1 ) ;
      legend -> AddEntry( hp2, tag2 ) ;

      hp1->Draw() ;
      hp2->Draw("same") ;
      legend -> Draw() ;

      can1 -> SaveAs( "outputfiles-rpv/pt-b.pdf" ) ;




    //------------

      sprintf( hname_pre, "h_w_dh_pt" ) ;
      sprintf( xtitle, "W daughter (harder one) pt" ) ;

      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp1 = get_hist_1d( hname ) ; set_style_1d( hp1, 1, xtitle ) ;
      sprintf( hname, "%s_%s", hname_pre, tag2 ) ; hp2 = get_hist_1d( hname ) ; set_style_1d( hp2, 2, xtitle ) ;

      legend = new TLegend( 0.70, 0.60, 0.85, 0.80 ) ;
      legend -> AddEntry( hp1, tag1 ) ;
      legend -> AddEntry( hp2, tag2 ) ;

      hp1->Draw() ;
      hp2->Draw("same") ;
      legend -> Draw() ;

      can1 -> SaveAs( "outputfiles-rpv/pt-w-dh.pdf" ) ;



    //------------

      sprintf( hname_pre, "h_w_ds_pt" ) ;
      sprintf( xtitle, "W daughter (softer one) pt" ) ;

      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp1 = get_hist_1d( hname ) ; set_style_1d( hp1, 1, xtitle ) ;
      sprintf( hname, "%s_%s", hname_pre, tag2 ) ; hp2 = get_hist_1d( hname ) ; set_style_1d( hp2, 2, xtitle ) ;

      legend = new TLegend( 0.70, 0.60, 0.85, 0.80 ) ;
      legend -> AddEntry( hp1, tag1 ) ;
      legend -> AddEntry( hp2, tag2 ) ;

      hp1->Draw() ;
      hp2->Draw("same") ;
      legend -> Draw() ;

      can1 -> SaveAs( "outputfiles-rpv/pt-w-ds.pdf" ) ;





    //------------

      sprintf( hname_pre, "h_n_taggable_tops" ) ;
      sprintf( xtitle, "N taggable tops" ) ;

      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp1 = get_hist_1d( hname ) ; set_style_1d( hp1, 1, xtitle ) ;
      sprintf( hname, "%s_%s", hname_pre, tag2 ) ; hp2 = get_hist_1d( hname ) ; set_style_1d( hp2, 2, xtitle ) ;

      legend = new TLegend( 0.70, 0.60, 0.85, 0.80 ) ;
      legend -> AddEntry( hp1, tag1 ) ;
      legend -> AddEntry( hp2, tag2 ) ;

      hp1->SetNormFactor(1.) ;
      hp2->SetNormFactor(1.) ;

      gPad->SetGridy(1) ;
      hp1->Draw() ;
      hp2->Draw("same") ;
      legend -> Draw() ;
      can1->Update() ; can1->Draw() ;

      can1 -> SaveAs( "outputfiles-rpv/n-taggable-tops.pdf" ) ;


      gPad->SetGridy(0) ;

    //------------

      sprintf( hname_pre, "h_extra_njets" ) ;
      sprintf( xtitle, "N extra jets from hard scatter" ) ;

      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp1 = get_hist_1d( hname ) ; set_style_1d( hp1, 1, xtitle ) ;
      sprintf( hname, "%s_%s", hname_pre, tag2 ) ; hp2 = get_hist_1d( hname ) ; set_style_1d( hp2, 2, xtitle ) ;

      legend = new TLegend( 0.70, 0.60, 0.85, 0.80 ) ;
      legend -> AddEntry( hp1, tag1 ) ;
      legend -> AddEntry( hp2, tag2 ) ;

      hp1->Draw() ;
      hp2->Draw("same") ;
      legend -> Draw() ;

      can1 -> SaveAs( "outputfiles-rpv/n-extra-jets.pdf" ) ;





    //------------

      sprintf( hname_pre, "h_extra_jet_pt" ) ;
      sprintf( xtitle, "Extra jet pt" ) ;

      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp1 = get_hist_1d( hname ) ; set_style_1d( hp1, 1, xtitle ) ;
      sprintf( hname, "%s_%s", hname_pre, tag2 ) ; hp2 = get_hist_1d( hname ) ; set_style_1d( hp2, 2, xtitle ) ;

      legend = new TLegend( 0.70, 0.60, 0.85, 0.80 ) ;
      legend -> AddEntry( hp1, tag1 ) ;
      legend -> AddEntry( hp2, tag2 ) ;

      hp1->Draw() ;
      hp2->Draw("same") ;
      legend -> Draw() ;

      can1 -> SaveAs( "outputfiles-rpv/extra-jet-pt.pdf" ) ;






    //------------

      sprintf( hname_pre, "h_extra_lead_jet_rank" ) ;
      sprintf( xtitle, "Leading extra jet pt rank" ) ;

      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp1 = get_hist_1d( hname ) ; set_style_1d( hp1, 1, xtitle ) ;
      sprintf( hname, "%s_%s", hname_pre, tag2 ) ; hp2 = get_hist_1d( hname ) ; set_style_1d( hp2, 2, xtitle ) ;

      legend = new TLegend( 0.70, 0.60, 0.85, 0.80 ) ;
      legend -> AddEntry( hp1, tag1 ) ;
      legend -> AddEntry( hp2, tag2 ) ;

      hp1->Draw() ;
      hp2->Draw("same") ;
      legend -> Draw() ;

      can1 -> SaveAs( "outputfiles-rpv/extra-jet-lead-rank.pdf" ) ;





    //------------

      sprintf( hname_pre, "h_twostop_pt" ) ;
      sprintf( xtitle, "Pt of two stop system" ) ;

      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp1 = get_hist_1d( hname ) ; set_style_1d( hp1, 1, xtitle ) ;
      sprintf( hname, "%s_%s", hname_pre, tag2 ) ; hp2 = get_hist_1d( hname ) ; set_style_1d( hp2, 2, xtitle ) ;

      legend = new TLegend( 0.70, 0.60, 0.85, 0.80 ) ;
      legend -> AddEntry( hp1, tag1 ) ;
      legend -> AddEntry( hp2, tag2 ) ;

      hp1->Draw() ;
      hp2->Draw("same") ;
      legend -> Draw() ;

      can1 -> SaveAs( "outputfiles-rpv/twostop-pt.pdf" ) ;














    //------------

      sprintf( xtitle, "Top pt" ) ;

      sprintf( hname_pre, "h_top_pt" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp1 = get_hist_1d( hname ) ; set_style_1d( hp1, 1, xtitle ) ;
      sprintf( hname_pre, "h_top_pt_taggable" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp2 = get_hist_1d( hname ) ; set_style_1d( hp2, 1, xtitle ) ;
      hp2 -> SetLineStyle(3) ;

      legend = new TLegend( 0.70, 0.60, 0.85, 0.80 ) ;
      legend -> AddEntry( hp1, "all" ) ;
      legend -> AddEntry( hp2, "taggable" ) ;

      hp1->Draw() ;
      hp2->Draw("same") ;
      legend -> Draw() ;


      sprintf( fname, "outputfiles-rpv/top-pt-taggable-%s.pdf", tag1 ) ;
      can1 -> SaveAs( fname ) ;



    //------------

      sprintf( xtitle, "Top pt" ) ;

      sprintf( hname_pre, "h_top_pt" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag2 ) ; hp1 = get_hist_1d( hname ) ; set_style_1d( hp1, 2, xtitle ) ;
      sprintf( hname_pre, "h_top_pt_taggable" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag2 ) ; hp2 = get_hist_1d( hname ) ; set_style_1d( hp2, 2, xtitle ) ;
      hp2 -> SetLineStyle(3) ;

      legend = new TLegend( 0.70, 0.60, 0.85, 0.80 ) ;
      legend -> AddEntry( hp1, "all" ) ;
      legend -> AddEntry( hp2, "taggable" ) ;

      hp1->Draw() ;
      hp2->Draw("same") ;
      legend -> Draw() ;

      sprintf( fname, "outputfiles-rpv/top-pt-taggable-%s.pdf", tag2 ) ;
      can1 -> SaveAs( fname ) ;





    //------------

      sprintf( xtitle, "cos(dphi) between the tops" ) ;

      sprintf( hname_pre, "h_toptop_cosdphi" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp1 = get_hist_1d( hname ) ; set_style_1d( hp1, 1, xtitle ) ;
      sprintf( hname_pre, "h_toptop_cosdphi_two_taggable_tops" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp2 = get_hist_1d( hname ) ; set_style_1d( hp2, 1, xtitle ) ;
      hp2 -> SetLineStyle(3) ;
      hp2 -> SetFillColor(kBlue-10) ;

      legend = new TLegend( 0.70, 0.60, 0.85, 0.80 ) ;
      legend -> AddEntry( hp1, "all" ) ;
      legend -> AddEntry( hp2, "2 taggable" ) ;

      hp1->Draw() ;
      hp2->Draw("same") ;
      hp2->Draw("same axis") ;
      legend -> Draw() ;

      sprintf( fname, "outputfiles-rpv/twotop-cosdphi-taggable-%s.pdf", tag1 ) ;
      can1 -> SaveAs( fname ) ;





    //------------

      sprintf( xtitle, "cos(dphi) between the tops" ) ;

      sprintf( hname_pre, "h_toptop_cosdphi" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag2 ) ; hp1 = get_hist_1d( hname ) ; set_style_1d( hp1, 2, xtitle ) ;
      sprintf( hname_pre, "h_toptop_cosdphi_two_taggable_tops" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag2 ) ; hp2 = get_hist_1d( hname ) ; set_style_1d( hp2, 2, xtitle ) ;
      hp2 -> SetLineStyle(3) ;
      hp2 -> SetFillColor(kRed-10) ;

      legend = new TLegend( 0.70, 0.60, 0.85, 0.80 ) ;
      legend -> AddEntry( hp1, "all" ) ;
      legend -> AddEntry( hp2, "2 taggable" ) ;

      hp1->Draw() ;
      hp2->Draw("same") ;
      hp2->Draw("same axis") ;
      legend -> Draw() ;

      sprintf( fname, "outputfiles-rpv/twotop-cosdphi-taggable-%s.pdf", tag2 ) ;
      can1 -> SaveAs( fname ) ;




    //------------

      sprintf( xtitle, "Reconstructed cos(dphi) between the tops" ) ;

      sprintf( hname_pre, "h_rec_toptop_cosdphi" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp1 = get_hist_1d( hname ) ; set_style_1d( hp1, 1, xtitle ) ;
      sprintf( hname_pre, "h_rec_toptop_cosdphi_two_taggable_tops" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp2 = get_hist_1d( hname ) ; set_style_1d( hp2, 1, xtitle ) ;
      hp2 -> SetLineStyle(3) ;
      hp2 -> SetFillColor(kBlue-10) ;

      legend = new TLegend( 0.70, 0.60, 0.85, 0.80 ) ;
      legend -> AddEntry( hp1, "all" ) ;
      legend -> AddEntry( hp2, "2 taggable" ) ;

      hp1->Draw() ;
      hp2->Draw("same") ;
      hp2->Draw("same axis") ;
      legend -> Draw() ;

      sprintf( fname, "outputfiles-rpv/twotop-rec-cosdphi-taggable-%s.pdf", tag1 ) ;
      can1 -> SaveAs( fname ) ;





    //------------

      sprintf( xtitle, "Reconstructed cos(dphi) between the tops" ) ;

      sprintf( hname_pre, "h_rec_toptop_cosdphi" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag2 ) ; hp1 = get_hist_1d( hname ) ; set_style_1d( hp1, 2, xtitle ) ;
      sprintf( hname_pre, "h_rec_toptop_cosdphi_two_taggable_tops" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag2 ) ; hp2 = get_hist_1d( hname ) ; set_style_1d( hp2, 2, xtitle ) ;
      hp2 -> SetLineStyle(3) ;
      hp2 -> SetFillColor(kRed-10) ;

      legend = new TLegend( 0.70, 0.60, 0.85, 0.80 ) ;
      legend -> AddEntry( hp1, "all" ) ;
      legend -> AddEntry( hp2, "2 taggable" ) ;

      hp1->Draw() ;
      hp2->Draw("same") ;
      hp2->Draw("same axis") ;
      legend -> Draw() ;

      sprintf( fname, "outputfiles-rpv/twotop-rec-cosdphi-taggable-%s.pdf", tag2 ) ;
      can1 -> SaveAs( fname ) ;




    //------------

      sprintf( xtitle, "cos(dphi) between the stops" ) ;

      sprintf( hname_pre, "h_stopstop_cosdphi" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp1 = get_hist_1d( hname ) ; set_style_1d( hp1, 1, xtitle ) ;
      sprintf( hname_pre, "h_stopstop_cosdphi_two_taggable_tops" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp2 = get_hist_1d( hname ) ; set_style_1d( hp2, 1, xtitle ) ;
      hp2 -> SetLineStyle(3) ;
      hp2 -> SetFillColor(kBlue-10) ;

      legend = new TLegend( 0.70, 0.60, 0.85, 0.80 ) ;
      legend -> AddEntry( hp1, "all" ) ;
      legend -> AddEntry( hp2, "2 taggable" ) ;

      hp1->Draw() ;
      hp2->Draw("same") ;
      hp2->Draw("same axis") ;
      legend -> Draw() ;

      sprintf( fname, "outputfiles-rpv/twostop-cosdphi-taggable-%s.pdf", tag1 ) ;
      can1 -> SaveAs( fname ) ;





    //------------

      sprintf( xtitle, "cos(dphi) between the stops" ) ;

      sprintf( hname_pre, "h_stopstop_cosdphi" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag2 ) ; hp1 = get_hist_1d( hname ) ; set_style_1d( hp1, 2, xtitle ) ;
      sprintf( hname_pre, "h_stopstop_cosdphi_two_taggable_tops" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag2 ) ; hp2 = get_hist_1d( hname ) ; set_style_1d( hp2, 2, xtitle ) ;
      hp2 -> SetLineStyle(3) ;
      hp2 -> SetFillColor(kRed-10) ;

      legend = new TLegend( 0.70, 0.60, 0.85, 0.80 ) ;
      legend -> AddEntry( hp1, "all" ) ;
      legend -> AddEntry( hp2, "2 taggable" ) ;

      hp1->Draw() ;
      hp2->Draw("same") ;
      legend -> Draw() ;

      sprintf( fname, "outputfiles-rpv/twostop-cosdphi-taggable-%s.pdf", tag2 ) ;
      can1 -> SaveAs( fname ) ;





    //------------

      sprintf( xtitle, "cos(thetasum) between the stops in 2stop CMF" ) ;

      sprintf( hname_pre, "h_stopstop_costhetasum_cmf" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp1 = get_hist_1d( hname ) ; set_style_1d( hp1, 1, xtitle ) ;
      sprintf( hname_pre, "h_stopstop_costhetasum_cmf_two_taggable_tops" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp2 = get_hist_1d( hname ) ; set_style_1d( hp2, 1, xtitle ) ;
      hp2 -> SetLineStyle(3) ;
      hp2 -> SetFillColor(kBlue-10) ;

      legend = new TLegend( 0.70, 0.60, 0.85, 0.80 ) ;
      legend -> AddEntry( hp1, "all" ) ;
      legend -> AddEntry( hp2, "2 taggable" ) ;

      hp1->Draw() ;
      hp2->Draw("same") ;
      hp2->Draw("same axis") ;
      legend -> Draw() ;

      sprintf( fname, "outputfiles-rpv/twostop-costhetasum-taggable-%s.pdf", tag1 ) ;
      can1 -> SaveAs( fname ) ;





    //------------

      sprintf( xtitle, "cos(thetasum) between the stops in 2stop CMF" ) ;

      sprintf( hname_pre, "h_stopstop_costhetasum_cmf" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag2 ) ; hp1 = get_hist_1d( hname ) ; set_style_1d( hp1, 2, xtitle ) ;
      sprintf( hname_pre, "h_stopstop_costhetasum_cmf_two_taggable_tops" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag2 ) ; hp2 = get_hist_1d( hname ) ; set_style_1d( hp2, 2, xtitle ) ;
      hp2 -> SetLineStyle(3) ;
      hp2 -> SetFillColor(kRed-10) ;

      legend = new TLegend( 0.70, 0.60, 0.85, 0.80 ) ;
      legend -> AddEntry( hp1, "all" ) ;
      legend -> AddEntry( hp2, "2 taggable" ) ;

      hp1->Draw() ;
      hp2->Draw("same") ;
      hp2->Draw("same axis") ;
      legend -> Draw() ;

      sprintf( fname, "outputfiles-rpv/twostop-costhetasum-taggable-%s.pdf", tag2 ) ;
      can1 -> SaveAs( fname ) ;






    //------------

      sprintf( xtitle, "cos(thetasum) between the tops in 2stop CMF" ) ;

      sprintf( hname_pre, "h_toptop_costhetasum_cmf" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp1 = get_hist_1d( hname ) ; set_style_1d( hp1, 1, xtitle ) ;
      sprintf( hname_pre, "h_toptop_costhetasum_cmf_two_taggable_tops" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp2 = get_hist_1d( hname ) ; set_style_1d( hp2, 1, xtitle ) ;
      hp2 -> SetLineStyle(3) ;
      hp2 -> SetFillColor(kBlue-10) ;

      legend = new TLegend( 0.70, 0.60, 0.85, 0.80 ) ;
      legend -> AddEntry( hp1, "all" ) ;
      legend -> AddEntry( hp2, "2 taggable" ) ;

      hp1->Draw() ;
      hp2->Draw("same") ;
      hp2->Draw("same axis") ;
      legend -> Draw() ;

      sprintf( fname, "outputfiles-rpv/twotop-costhetasum-taggable-%s.pdf", tag1 ) ;
      can1 -> SaveAs( fname ) ;





    //------------

      sprintf( xtitle, "cos(thetasum) between the tops in 2stop CMF" ) ;

      sprintf( hname_pre, "h_toptop_costhetasum_cmf" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag2 ) ; hp1 = get_hist_1d( hname ) ; set_style_1d( hp1, 2, xtitle ) ;
      sprintf( hname_pre, "h_toptop_costhetasum_cmf_two_taggable_tops" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag2 ) ; hp2 = get_hist_1d( hname ) ; set_style_1d( hp2, 2, xtitle ) ;
      hp2 -> SetLineStyle(3) ;
      hp2 -> SetFillColor(kRed-10) ;

      legend = new TLegend( 0.70, 0.60, 0.85, 0.80 ) ;
      legend -> AddEntry( hp1, "all" ) ;
      legend -> AddEntry( hp2, "2 taggable" ) ;

      hp1->Draw() ;
      hp2->Draw("same") ;
      hp2->Draw("same axis") ;
      legend -> Draw() ;

      sprintf( fname, "outputfiles-rpv/twotop-costhetasum-taggable-%s.pdf", tag2 ) ;
      can1 -> SaveAs( fname ) ;






    //------------

      sprintf( xtitle, "Reconstructed cos(thetasum) between the tops in reco CMF" ) ;

      sprintf( hname_pre, "h_rec_toptop_costhetasum_rec_cmf" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp1 = get_hist_1d( hname ) ; set_style_1d( hp1, 1, xtitle ) ;
      sprintf( hname_pre, "h_rec_toptop_costhetasum_rec_cmf_two_taggable_tops" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp2 = get_hist_1d( hname ) ; set_style_1d( hp2, 1, xtitle ) ;
      hp2 -> SetLineStyle(3) ;
      hp2 -> SetFillColor(kBlue-10) ;

      legend = new TLegend( 0.70, 0.60, 0.85, 0.80 ) ;
      legend -> AddEntry( hp1, "all" ) ;
      legend -> AddEntry( hp2, "2 taggable" ) ;

      hp1->Draw() ;
      hp2->Draw("same") ;
      hp2->Draw("same axis") ;
      legend -> Draw() ;

      sprintf( fname, "outputfiles-rpv/twotop-rec-costhetasum-taggable-%s.pdf", tag1 ) ;
      can1 -> SaveAs( fname ) ;





    //------------

      sprintf( xtitle, "Reconstructed cos(thetasum) between the tops in rec CMF" ) ;

      sprintf( hname_pre, "h_rec_toptop_costhetasum_rec_cmf" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag2 ) ; hp1 = get_hist_1d( hname ) ; set_style_1d( hp1, 2, xtitle ) ;
      sprintf( hname_pre, "h_rec_toptop_costhetasum_rec_cmf_two_taggable_tops" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag2 ) ; hp2 = get_hist_1d( hname ) ; set_style_1d( hp2, 2, xtitle ) ;
      hp2 -> SetLineStyle(3) ;
      hp2 -> SetFillColor(kRed-10) ;

      legend = new TLegend( 0.70, 0.60, 0.85, 0.80 ) ;
      legend -> AddEntry( hp1, "all" ) ;
      legend -> AddEntry( hp2, "2 taggable" ) ;

      hp1->Draw() ;
      hp2->Draw("same") ;
      hp2->Draw("same axis") ;
      legend -> Draw() ;

      sprintf( fname, "outputfiles-rpv/twotop-rec-costhetasum-taggable-%s.pdf", tag2 ) ;
      can1 -> SaveAs( fname ) ;






    //------------

      sprintf( xtitle, "Njets, pt>40, AK4" ) ;

      sprintf( hname_pre, "h_rec_njet40" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp1 = get_hist_1d( hname ) ; set_style_1d( hp1, 1, xtitle ) ;
      sprintf( hname_pre, "h_rec_njet40_ht450" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp2 = get_hist_1d( hname ) ; set_style_1d( hp2, 1, xtitle ) ;
      hp2 -> SetLineStyle(3) ;

      legend = new TLegend( 0.70, 0.60, 0.85, 0.80 ) ;
      legend -> AddEntry( hp1, "all" ) ;
      legend -> AddEntry( hp2, "HT>450" ) ;

      hp1->Draw() ;
      hp2->Draw("same") ;
      legend -> Draw() ;

      sprintf( fname, "outputfiles-rpv/njet40-ht450-%s.pdf", tag1 ) ;
      can1 -> SaveAs( fname ) ;






    //------------

      sprintf( xtitle, "Njets, pt>40, AK4" ) ;

      sprintf( hname_pre, "h_rec_njet40" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag2 ) ; hp1 = get_hist_1d( hname ) ; set_style_1d( hp1, 2, xtitle ) ;
      sprintf( hname_pre, "h_rec_njet40_ht450" ) ;
      sprintf( hname, "%s_%s", hname_pre, tag2 ) ; hp2 = get_hist_1d( hname ) ; set_style_1d( hp2, 2, xtitle ) ;
      hp2 -> SetLineStyle(3) ;

      legend = new TLegend( 0.70, 0.60, 0.85, 0.80 ) ;
      legend -> AddEntry( hp1, "all" ) ;
      legend -> AddEntry( hp2, "HT>450" ) ;

      hp1->Draw() ;
      hp2->Draw("same") ;
      legend -> Draw() ;

      sprintf( fname, "outputfiles-rpv/njet40-ht450-%s.pdf", tag2 ) ;
      can1 -> SaveAs( fname ) ;










    //------------

      sprintf( hname_pre, "h_drmax_wrt_top_axis_vs_top_pt_dpt20" ) ;
      sprintf( xtitle, "top pt" ) ;
      sprintf( ytitle, "max top daughter dR" ) ;

      sprintf( hname, "%s_%s", hname_pre, tag1 ) ; hp2d = get_hist_2d( hname ) ; set_style_2d( hp2d, xtitle, ytitle ) ;

      hp2d->Draw( "colz" ) ;
      gPad -> SetGridx(1) ;
      gPad -> SetGridy(1) ;

      sprintf( fname, "outputfiles-rpv/top-dau-drmax-vs-top-pt-%s.pdf", tag1 ) ;
      can1 -> SaveAs( fname ) ;


      sprintf( hname, "%s_%s", hname_pre, tag2 ) ; hp2d = get_hist_2d( hname ) ; set_style_2d( hp2d, xtitle, ytitle ) ;

      hp2d->Draw( "colz" ) ;
      gPad -> SetGridx(1) ;
      gPad -> SetGridy(1) ;

      sprintf( fname, "outputfiles-rpv/top-dau-drmax-vs-top-pt-%s.pdf", tag2 ) ;
      can1 -> SaveAs( fname ) ;




   } // draw_rpv1


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
      }

   } // set_style_1d

  //===========================================================================================

   void set_style_2d( TH2F* hp, const char* xtitle, const char* ytitle ) {

      if ( hp == 0x0 ) return ;

      hp -> SetXTitle( xtitle ) ;
      hp -> SetYTitle( ytitle ) ;

      hp -> SetTitleOffset( 1.1, "x" ) ;
      hp -> SetTitleOffset( 1.05, "y" ) ;
      hp -> SetTitleSize( 0.050, "x" ) ;
      hp -> SetTitleSize( 0.050, "y" ) ;


   } // set_style_2d

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

   TH2F* get_hist_2d( const char* hname ) {
      TH2F* rp = (TH2F*) gDirectory -> FindObject( hname ) ;
      if ( rp == 0x0 ) {
         printf("\n\n *** Can't find hist %s\n\n", hname ) ;
         gSystem -> Exit( -1 ) ;
      }
      return rp ;
   } // get_hist_2d

  //===========================================================================================




