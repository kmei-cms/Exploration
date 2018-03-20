
//
//   Note:  You need to load this in root with a "+" after the file name to compile it.
//          That is, do this
//
//             .L event_shape_bdt_example.c+
//
//          not this
//
//             .L event_shape_bdt_example.c
//
//   Owen
//

#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TLorentzVector.h"
#include "TMath.h"
#include "TSystem.h"

#include "bdt_350to650_fwm10_jmtev_top6.c"
#include "fisher_350to650_fwm10_jmtev_top6.c"
#include "fisher_350to650_fwm6_jmtev_top6_gt_v2.c"
#include "EventShapeVariables.c"
#include "get_cmframe_jets.c"

#ifdef __MAKECINT__
#pragma link C++ class vector<TLorentzVector>+;
#endif


#include <vector>
using std::vector ;

   void event_shape_bdt_example( const char* input_root_file, int max_evts = 100 ) {

      TChain* tt_in = new TChain( "PreSelection", "" ) ;

      printf("\n\n Adding %s to chain.\n", input_root_file ) ;
      int n_added = tt_in -> Add( input_root_file ) ;
      if ( n_added <= 0 ) { printf("\n\n *** No files match %s\n\n", input_root_file ) ; gSystem->Exit(-1) ; }
      printf("  Added %d files to chain.\n", n_added ) ;
      int n_entries = tt_in -> GetEntries() ;
      if ( n_entries <= 0 ) { printf("\n\n *** No entries in ntuple chain.\n\n" ) ; gSystem->Exit(-1) ; }
      printf("  Number of entries: %d\n\n", n_entries ) ;

      tt_in -> SetBranchStatus( "Jets", 1 ) ;

      vector<TLorentzVector> *Jets;
      TBranch     *b_Jets;
      Jets = 0 ;
      tt_in -> SetBranchAddress("Jets"    , &Jets    , &b_Jets      );




    //--- Setup the BDT reader

      std::vector<std::string> inputVarNames_top6 ;
      std::vector<double> bdtInputVals_top6 ;

      {
         std::string vname ;
         vname = "fwm2_top6" ; inputVarNames_top6.push_back( vname ) ;
         vname = "fwm3_top6" ; inputVarNames_top6.push_back( vname ) ;
         vname = "fwm4_top6" ; inputVarNames_top6.push_back( vname ) ;
         vname = "fwm5_top6" ; inputVarNames_top6.push_back( vname ) ;
         vname = "fwm6_top6" ; inputVarNames_top6.push_back( vname ) ;
         vname = "fwm7_top6" ; inputVarNames_top6.push_back( vname ) ;
         vname = "fwm8_top6" ; inputVarNames_top6.push_back( vname ) ;
         vname = "fwm9_top6" ; inputVarNames_top6.push_back( vname ) ;
         vname = "fwm10_top6" ; inputVarNames_top6.push_back( vname ) ;
         vname = "jmt_ev0_top6" ; inputVarNames_top6.push_back( vname ) ;
         vname = "jmt_ev1_top6" ; inputVarNames_top6.push_back( vname ) ;
         vname = "jmt_ev2_top6" ; inputVarNames_top6.push_back( vname ) ;

         for ( unsigned int i=0; i < inputVarNames_top6.size() ; i++ ) {
            bdtInputVals_top6.push_back( 0.5 ) ; //--- load vector with dummy values.
         } // i

      }

      ReadBDT_350to650_fwm10_jmtev_top6    read_bdt_350to650_fwm10_jmtev_top6( inputVarNames_top6 ) ;
      ReadFisher_350to650_fwm10_jmtev_top6 read_fisher_350to650_fwm10_jmtev_top6( inputVarNames_top6 ) ;






      std::vector<std::string> inputVarNames_top6_fwm6 ;
      std::vector<double> bdtInputVals_top6_fwm6 ;

      {
         std::string vname ;
         vname = "fwm2_top6" ; inputVarNames_top6_fwm6.push_back( vname ) ;
         vname = "fwm3_top6" ; inputVarNames_top6_fwm6.push_back( vname ) ;
         vname = "fwm4_top6" ; inputVarNames_top6_fwm6.push_back( vname ) ;
         vname = "fwm5_top6" ; inputVarNames_top6_fwm6.push_back( vname ) ;
         vname = "fwm6_top6" ; inputVarNames_top6_fwm6.push_back( vname ) ;
         vname = "jmt_ev0_top6" ; inputVarNames_top6_fwm6.push_back( vname ) ;
         vname = "jmt_ev1_top6" ; inputVarNames_top6_fwm6.push_back( vname ) ;
         vname = "jmt_ev2_top6" ; inputVarNames_top6_fwm6.push_back( vname ) ;

         for ( unsigned int i=0; i < inputVarNames_top6_fwm6.size() ; i++ ) {
            bdtInputVals_top6_fwm6.push_back( 0.5 ) ; //--- load vector with dummy values.
         } // i

      }

      ReadFisherG_350to650_fwm6_jmtev_top6_gt_v2 read_fisher_350to650_fwm6_jmtev_top6_gt_v2( inputVarNames_top6_fwm6 ) ;





      if ( max_evts > 0 && max_evts < n_entries ) n_entries = max_evts ;

      for ( Long64_t ei=0; ei<n_entries ; ei++ ) {

         tt_in -> GetEntry(ei ) ;


         std::vector<math::RThetaPhiVector> cm_frame_jets ;
         get_cmframe_jets( Jets, cm_frame_jets, 6 ) ;
         EventShapeVariables esv_top6( cm_frame_jets ) ;
         TVectorD eigen_vals_norm_top6 = esv_top6.getEigenValues() ;

         {
            int vi(0) ;
            bdtInputVals_top6.at(vi) = esv_top6.getFWmoment(2) ; vi++ ;
            bdtInputVals_top6.at(vi) = esv_top6.getFWmoment(3) ; vi++ ;
            bdtInputVals_top6.at(vi) = esv_top6.getFWmoment(4) ; vi++ ;
            bdtInputVals_top6.at(vi) = esv_top6.getFWmoment(5) ; vi++ ;
            bdtInputVals_top6.at(vi) = esv_top6.getFWmoment(6) ; vi++ ;
            bdtInputVals_top6.at(vi) = esv_top6.getFWmoment(7) ; vi++ ;
            bdtInputVals_top6.at(vi) = esv_top6.getFWmoment(8) ; vi++ ;
            bdtInputVals_top6.at(vi) = esv_top6.getFWmoment(9) ; vi++ ;
            bdtInputVals_top6.at(vi) = esv_top6.getFWmoment(10) ; vi++ ;
            bdtInputVals_top6.at(vi) = eigen_vals_norm_top6[0] ; vi++ ;
            bdtInputVals_top6.at(vi) = eigen_vals_norm_top6[1] ; vi++ ;
            bdtInputVals_top6.at(vi) = eigen_vals_norm_top6[2] ; vi++ ;
         }

         double bdt_val_350to650_fwm10_jmtev_top6 = read_bdt_350to650_fwm10_jmtev_top6.GetMvaValue( bdtInputVals_top6 ) ;
         double fisher_val_350to650_fwm10_jmtev_top6 = read_fisher_350to650_fwm10_jmtev_top6.GetMvaValue( bdtInputVals_top6 ) ;

         {
            int vi(0) ;
            bdtInputVals_top6_fwm6.at(vi) = esv_top6.getFWmoment(2) ; vi++ ;
            bdtInputVals_top6_fwm6.at(vi) = esv_top6.getFWmoment(3) ; vi++ ;
            bdtInputVals_top6_fwm6.at(vi) = esv_top6.getFWmoment(4) ; vi++ ;
            bdtInputVals_top6_fwm6.at(vi) = esv_top6.getFWmoment(5) ; vi++ ;
            bdtInputVals_top6_fwm6.at(vi) = esv_top6.getFWmoment(6) ; vi++ ;
            bdtInputVals_top6_fwm6.at(vi) = eigen_vals_norm_top6[0] ; vi++ ;
            bdtInputVals_top6_fwm6.at(vi) = eigen_vals_norm_top6[1] ; vi++ ;
            bdtInputVals_top6_fwm6.at(vi) = eigen_vals_norm_top6[2] ; vi++ ;
         }

         double fisher_val_350to650_fwm6_jmtev_top6_gt_v2 = read_fisher_350to650_fwm6_jmtev_top6_gt_v2.GetMvaValue( bdtInputVals_top6_fwm6 ) ;




         printf(" =============== Count : %lld\n", ei ) ;
         printf("\n") ;
         printf("   AK4 jets:\n" ) ;
         for ( unsigned int rji=0; rji<Jets->size() ; rji ++ ) {
            printf("  %3d : Pt = %7.1f, Eta = %7.3f, Phi = %7.3f\n", rji, Jets->at(rji).Pt(), Jets->at(rji).Eta(), Jets->at(rji).Phi()) ;
         } // rji
         printf("\n") ;

         printf("\n CM frame, top 6 highest-p jets:\n") ;
         for ( unsigned int ji=0; ji<cm_frame_jets.size(); ji++ ) {
            printf("  %2d :  p,cos(theta),phi = (%7.1f, %7.3f, %7.3f)\n", ji,
              cm_frame_jets.at(ji).R(),
              cos(cm_frame_jets.at(ji).Theta()),
              cm_frame_jets.at(ji).Phi()
              ) ;
         } // ji
         printf("\n") ;
         printf("  fwm2 = %7.4f\n", esv_top6.getFWmoment(2) ) ;
         printf("  fwm3 = %7.4f\n", esv_top6.getFWmoment(3) ) ;
         printf("  fwm4 = %7.4f\n", esv_top6.getFWmoment(4) ) ;
         printf("  fwm5 = %7.4f\n", esv_top6.getFWmoment(5) ) ;
         printf("  fwm6 = %7.4f\n", esv_top6.getFWmoment(6) ) ;
         printf("  fwm7 = %7.4f\n", esv_top6.getFWmoment(7) ) ;
         printf("  fwm8 = %7.4f\n", esv_top6.getFWmoment(8) ) ;
         printf("  fwm9 = %7.4f\n", esv_top6.getFWmoment(9) ) ;
         printf("  fwm10= %7.4f\n", esv_top6.getFWmoment(10) ) ;
         printf("\n") ;
         printf("  jmt_ev0 = %7.4f\n", eigen_vals_norm_top6[0] ) ;
         printf("  jmt_ev1 = %7.4f\n", eigen_vals_norm_top6[1] ) ;
         printf("  jmt_ev2 = %7.4f\n", eigen_vals_norm_top6[2] ) ;
         printf("\n") ;

         printf("\n  BDT    output : %7.3f\n", bdt_val_350to650_fwm10_jmtev_top6 ) ;
         printf("\n  Fisher output : %7.3f\n", fisher_val_350to650_fwm10_jmtev_top6 ) ;
         printf("\n  Fisher output using fwm2-fwm6 and jmtevs : %7.3f\n", fisher_val_350to650_fwm6_jmtev_top6_gt_v2 ) ;

         printf("\n\n") ;

      } // ei




   } // event_shape_bdt_example

