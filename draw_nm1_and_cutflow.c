
#include "histio.c"

   void draw_nm1_and_cutflow( const char* dsname = "rpv_stop_650", const char* hist_file_dir = "outputfiles", int fill_color=45 ,const char* histpat = "*",
                              const char* hist_file_prefix = "nm1-hists-" ) {

      gStyle -> SetPadRightMargin(0.02) ;

      gDirectory -> Delete( "h*" ) ;

      char command[1000] ;
      sprintf( command, "ls -1 %s/%s*%s*.root", hist_file_dir, hist_file_prefix, dsname ) ;
      TString histfile = gSystem -> GetFromPipe( command ) ;

      printf("\n\n ls returns:\n") ;
      printf(" %s \n\n", histfile.Data() ) ;
      printf("\n\n") ;

      TObjArray* toa = histfile.Tokenize( "\n" ) ;
      printf("\n\n Number of lines: %d\n\n", toa->GetEntries() ) ;

      if ( histfile.Contains( "QCD" ) ) {
         if ( toa->GetEntries() != 7 ) {
            printf("\n\n *** Detected QCD in ds name but did not find 7 files matching %s\n\n", dsname ) ;
            gSystem -> Exit(-1) ;
         }
         for ( int fi=0; fi<toa->GetEntries(); fi++ ) {
            TString this_file = ((TObjString*) toa->At(fi))->GetString() ;
            printf("  %2d : %s\n", fi, this_file.Data() ) ;
            if ( fi == 0 ) {
               loadHist( this_file, 0, "*", 0 ) ;
            } else {
               loadHist( this_file, 0, "*", 1 ) ;
            }
         } // fi
      } else {
         if ( toa->GetEntries() != 1 ) {
            printf("\n\n *** Not QCD and did not find only one file matching dsname = %s\n\n", dsname ) ;
            gSystem -> Exit(-1) ;
         }
         loadHist( histfile ) ;
      }


      TString dsname_no_wildcards = dsname ;
      dsname_no_wildcards.ReplaceAll("*","-") ;

      char output_dir[1000] ;
      sprintf( output_dir, "%s/nm1-plots-%s", hist_file_dir, dsname_no_wildcards.Data() ) ;
      printf("\n Output dir for plots: %s\n\n", output_dir ) ;

      sprintf( command, "mkdir -p %s\n", output_dir ) ;
      gSystem -> Exec( command ) ;




      TCanvas* can1 = (TCanvas*) gDirectory -> FindObject( "can1" ) ;
      if ( can1 == 0x0 ) can1 = new TCanvas( "can1", "", 900, 700 ) ;




      TRegexp re( histpat, kTRUE ) ;

      TList* list = gDirectory -> GetList() ;
      /////// printf("\n\n pointer from gDirectory->GetList() : %p\n\n", list ) ;

      printf("\n\n Number of histograms in list: %d\n\n", list->GetEntries() ) ;
      for ( int hi=0; hi<list->GetEntries(); hi++ ) {
         TH1* hp = (TH1*) list->At(hi) ;
         ////// printf("  %s\n", hp->GetName() ) ;
         if ( ! hp->IsA()->InheritsFrom(TH1::Class()) ) {
            printf( " *** Not a histogram.\n" ) ;
            continue ;
         }
         if ( TString(hp->GetName()).Index(re) == -1 ) {
            ////// printf("  *** Does not match hist pattern: %s \n", histpat ) ;
            continue ;
         }
         TString tsfname( hp->GetName() ) ;
         tsfname.ReplaceAll( "h_", "plot-" ) ;
         char fname[1000] ;
         sprintf( fname, "%s/%s.pdf", output_dir, tsfname.Data() ) ;
         printf("  plot file name : %s\n", fname ) ;


         TText* label = new TText() ;
         label -> SetTextAlign( 33 ) ;


         hp -> SetFillColor( fill_color ) ;
         hp -> SetMinimum(0.) ;

         if ( hp -> IsA() -> InheritsFrom(TH2::Class()) ) {
            //hp -> SetMaximum( 500 ) ;
            hp -> Draw( "box" ) ;
            gPad->SetGridx(1) ;
            gPad->SetGridy(1) ;
         } else {
            hp -> Draw() ;
            gPad->SetGridy(0) ;
            gPad->SetGridx(1) ;
            hp -> Draw( "hist same" ) ;
            hp -> Draw( "same" ) ;
            hp -> Draw( "axis same" ) ;
            hp -> Draw( "axig same" ) ;
         }
         label -> DrawTextNDC( 0.85, 0.85, dsname_no_wildcards ) ;
         can1 -> Update() ; can1 -> Draw() ;
         can1 -> SaveAs( fname ) ;

      } // hi





   } // draw_nm1_and_cutflow




