#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TLorentzVector.h"
#include "TClassTable.h"
#include "TMath.h"
#include "TSystem.h"
#include "TH1F.h"

#include <fstream>


#ifdef __MAKECINT__
#pragma link C++ class vector<TLorentzVector>+;
#pragma link C++ class std::vector<bool>+;
#endif

#include <vector>
using std::vector ;
using std::string ;


   void skim_and_slim( TChain* tt_in,
                       const char* outfile = "outputfiles/skim-slim-test.root",
                       bool do_skim = true,
                       bool lepton_skim = true,
                       bool dilepton_skim = false,
                       const char* trigfile = "skim-slim-trigs.txt"
                       ) {





      printf("\n\n") ;
      //printf("  skim_and_slim : infile = %s\n", infile ) ;
      printf("  skim_and_slim : input tchain pointer = %p\n", tt_in ) ;
      printf("  skim_and_slim : outfile = %s\n", outfile ) ;
      printf("  skim_and_slim : do_skim = %s\n", (do_skim?"TRUE":"false") ) ;
      printf("  skim_and_slim : lepton_skim = %s\n", (lepton_skim?"TRUE":"false") ) ;
      printf("  skim_and_slim : dilepton_skim = %s\n", (dilepton_skim?"TRUE":"false") ) ;
      printf("  skim_and_slim : trigfile = %s\n", trigfile ) ;
      printf("\n\n") ;


      //bool verb(true) ;
      bool verb(false) ;


///   TChain* tt_in = new TChain( "TreeMaker2/PreSelection" ) ;

///   int n_added = tt_in -> Add( infile ) ;
///   printf("  Added %d files to chain.\n", n_added ) ;
///   int n_entries = tt_in -> GetEntries() ;
///   if ( n_entries <= 0 ) { printf("\n\n *** No entries in ntuple chain.\n\n" ) ; gSystem->Exit(-1) ; }
///   printf("  Number of entries: %d\n\n", n_entries ) ;








      TFile* tf_output = new TFile( outfile, "RECREATE" ) ;
      if ( tf_output == 0x0 ) { printf("\n\n *** bad output file: %s\n\n", outfile ) ; gSystem -> Exit(-1) ; }
      if ( ! tf_output -> IsOpen() ) { printf("\n\n *** bad output file: %s\n\n", outfile ) ; gSystem -> Exit(-1) ; }





     //--- Test if this is MC.
      TBranch* tb_test = tt_in -> FindBranch( "GenParticles" ) ;
      bool is_mc(false) ;
      if ( tb_test != 0x0 ) {
         is_mc = true ;
         printf("\n\n  Found GenParticles branch in input TTree.  Set is_mc to true.\n\n" ) ;
      } else {
         printf("\n\n  Did not find GenParticles branch in input TTree.  Set is_mc to false.\n\n" ) ;
      }




      tt_in -> SetBranchStatus( "*", 0 ) ;


      std::ifstream ifs ;
      ifs.open( "skim-slim-save-vars.txt" ) ;
      printf("\n\n") ;
      while ( ifs.good() ) {
         TString tsline ;
         tsline.ReadLine( ifs ) ;
         if ( !ifs.good() ) break ;
         printf("  Saving branch %s\n", tsline.Data() ) ;
         tt_in -> SetBranchStatus( tsline.Data(), 1 ) ;
      }
      ifs.close() ;
      printf("\n\n") ;


      vector< string > trig_names ;

      if ( !is_mc ) {
         ifs.open( trigfile ) ;
         if ( !ifs.good() ) {
            printf("  Bad or non-existant trigger file: %s\n", trigfile ) ;
            if ( !is_mc ) {
               printf("  Since this input file is data, I will stop now.\n") ;
               return ;
            }
         }
         while ( ifs.good() ) {
            TString tsline ;
            tsline.ReadLine( ifs ) ;
            if ( !ifs.good() ) break ;
            std::string tname( tsline.Data() ) ;
            printf("  Saving events passing %s\n", tname.c_str() ) ;
            trig_names.push_back( tname ) ;
         }
         ifs.close() ;
      }








      TTree* tt_out = tt_in -> CloneTree( 0 ) ;


     //--- Extra output histograms

      TH1F* h_njets_pt45_eta24 = new TH1F( "h_njets_pt45", "Njets, pt>45, |eta|<2.4", 11, -0.5, 10.5 ) ;





     //--- Branches from input for selection


      vector<TLorentzVector> *Jets;
      vector<double>         *Jets_bDiscriminatorCSV;
      vector<TLorentzVector> *Muons;
      vector<int>            *Muons_charge;
      vector<TLorentzVector> *Electrons;
      vector<int>            *Electrons_charge;
      vector<string>         *TriggerNames ;
      vector<int>            *TriggerPass ;

      UInt_t RunNum ;
      UInt_t LumiBlockNum ;
      ULong64_t EvtNum ;



      TBranch     *b_Jets;
      TBranch     *b_Jets_bDiscriminatorCSV;
      TBranch     *b_Muons;
      TBranch     *b_Muons_charge;
      TBranch     *b_Electrons;
      TBranch     *b_Electrons_charge;
      TBranch     *b_TriggerNames;
      TBranch     *b_TriggerPass;

      TBranch     *b_RunNum ;
      TBranch     *b_LumiBlockNum ;
      TBranch     *b_EvtNum ;





      Jets = 0 ;
      Jets_bDiscriminatorCSV = 0 ;
      Muons = 0 ;
      Muons_charge = 0 ;
      Electrons = 0 ;
      Electrons_charge = 0 ;
      TriggerNames = 0 ;
      TriggerPass = 0 ;

      RunNum = 0 ;
      LumiBlockNum = 0 ;
      EvtNum = 0 ;




      tt_in -> SetBranchStatus( "Jets", 1 ) ;
      tt_in -> SetBranchStatus( "Jets_bDiscriminatorCSV", 1 ) ;
      tt_in -> SetBranchStatus( "Muons", 1 ) ;
      tt_in -> SetBranchStatus( "Muons_charge", 1 ) ;
      tt_in -> SetBranchStatus( "Electrons", 1 ) ;
      tt_in -> SetBranchStatus( "Electrons_charge", 1 ) ;

      tt_in -> SetBranchStatus( "RunNum", 1 ) ;
      tt_in -> SetBranchStatus( "LumiBlockNum", 1 ) ;
      tt_in -> SetBranchStatus( "EvtNum", 1 ) ;




      tt_in -> SetBranchAddress("Jets"                             , &Jets                                 , &b_Jets                             );
      tt_in -> SetBranchAddress("Jets_bDiscriminatorCSV"           , &Jets_bDiscriminatorCSV               , &b_Jets_bDiscriminatorCSV           );
      tt_in -> SetBranchAddress("Muons"                            , &Muons                                , &b_Muons                            );
      tt_in -> SetBranchAddress("Muons_charge"                     , &Muons_charge                         , &b_Muons_charge                     );
      tt_in -> SetBranchAddress("Electrons"                        , &Electrons                            , &b_Electrons                        );
      tt_in -> SetBranchAddress("Electrons_charge"                 , &Electrons_charge                     , &b_Electrons_charge                 );

      tt_in -> SetBranchAddress("RunNum"             , &RunNum                 , &b_RunNum             );
      tt_in -> SetBranchAddress("LumiBlockNum"             , &LumiBlockNum                 , &b_LumiBlockNum             );
      tt_in -> SetBranchAddress("EvtNum"             , &EvtNum                 , &b_EvtNum             );




      if ( !is_mc ) {
         printf("\n Enabling reading TriggerNames and TriggerPass branches.\n\n") ;
         tt_in -> SetBranchStatus( "TriggerNames", 1 ) ;
         tt_in -> SetBranchStatus( "TriggerPass", 1 ) ;
         tt_in -> SetBranchAddress("TriggerNames"             , &TriggerNames                 , &b_TriggerNames             );
         tt_in -> SetBranchAddress("TriggerPass"             , &TriggerPass                 , &b_TriggerPass             );
      }













//   //--- New branches for output.
//    int ds_index = arg_ds_index ;
//    tt_out -> Branch( "ds_index", &ds_index, "ds_index/I" ) ;









     //--- Loop over events

      Long64_t nevts_ttree = tt_in -> GetEntries() ;
      printf("\n\n Number of events in input tree: %lld\n\n", nevts_ttree ) ;

      //////nevts_ttree = 1000 ; // *** testing.


      int modnum(1) ;
      if ( nevts_ttree > 0 ) modnum = nevts_ttree / 100 ;
      if ( modnum <= 0 ) modnum = 1 ;

      int nsave(0) ;


      for ( Long64_t ei=0; ei<nevts_ttree ; ei++ ) {

         Long64_t loadtree_rv = tt_in -> LoadTree( ei ) ;
         ////////printf("\n\n debug : LoadTree returns %lld\n\n", loadtree_rv ) ;

         Long64_t bytes = tt_in -> GetEntry(ei ) ;
         ////////printf("\n\n debug : bytes read? %lld\n\n", bytes ) ;

         if ( ei%modnum == 0 ) printf("   %9lld / %9lld\n", ei, nevts_ttree ) ;

         if ( verb ) {
            printf("\n") ;
            printf(" =============== Count : %lld, run=%10d, lumi=%10d, event=%10llu\n", ei, RunNum, LumiBlockNum, EvtNum ) ;
            printf("\n") ;
            printf("   AK4 jets:\n" ) ;
            for ( unsigned int rji=0; rji<Jets->size() ; rji ++ ) {
               printf("  %3d : Pt = %7.1f, Eta = %7.3f, Phi = %7.3f | CSV = %8.3f \n",
                  rji, Jets->at(rji).Pt(), Jets->at(rji).Eta(), Jets->at(rji).Phi(),
                  Jets_bDiscriminatorCSV->at(rji)
                  ) ;
            } // rji
            printf("\n") ;
         }


         int rec_njet_pt45(0) ;
         int rec_njet_pt30(0) ;
         float pfht_pt40_eta24(0.) ;
         int nbtag_csv50(0) ;
         int nbtag_csv85(0) ;
         int nleptons(0) ;

         ////////printf("\n\n debug : RunNum is %10d\n\n", RunNum ) ;
         ////////printf("\n\n debug : pointer to Jets_bDiscriminatorCSV is %p\n\n", Jets_bDiscriminatorCSV ) ;
         ////////printf("\n\n debug : pointer to Jets is %p\n\n", Jets ) ;
         for ( unsigned int rji=0; rji < Jets->size() ; rji++ ) {

               TLorentzVector jlv( Jets->at(rji) ) ;

               if ( jlv.Pt() > 30 && fabs(jlv.Eta())<2.4 ) rec_njet_pt30++ ;
               if ( jlv.Pt() > 45 && fabs(jlv.Eta())<2.4 ) rec_njet_pt45++ ;
               if ( jlv.Pt() > 40 && fabs(jlv.Eta())<2.4 ) pfht_pt40_eta24 += jlv.Pt() ;
               if ( Jets_bDiscriminatorCSV->at(rji) > 0.50 ) nbtag_csv50++ ;
               if ( Jets_bDiscriminatorCSV->at(rji) > 0.85 ) nbtag_csv85++ ;

         } // rji

         nleptons = Muons->size() + Electrons->size() ;

         if ( verb ) {
            printf("\n") ;
            printf(" rec_njet_pt45 : %2d\n", rec_njet_pt45 ) ;
            printf(" rec_njet_pt30 : %2d\n", rec_njet_pt30 ) ;
            printf(" nbtag_csv85   : %2d\n", nbtag_csv85 ) ;
            printf(" nleptons      : %2d\n", nleptons ) ;
            printf("\n") ;
         }

       //-- Pre skim histograms.
         h_njets_pt45_eta24 -> Fill( rec_njet_pt45 ) ;

         if ( do_skim ) {
            if ( dilepton_skim ) {
               if ( nbtag_csv85 < 2 ) continue ;
               if ( nleptons < 2 ) continue ;
            } else {
               if ( rec_njet_pt30 < 6 ) continue ;
               if ( nbtag_csv85 < 1 ) continue ;
               if ( lepton_skim ) {
                  if ( (Muons->size() + Electrons->size()) <= 0 ) continue ;
               }
            }
         }

       //-- check trigger if this is data.
         if ( !is_mc ) {
            if ( verb ) printf("\n  Number of trigger names in ntuple: %lu\n", TriggerNames->size() ) ;
            bool pass_trig(false) ;
            for ( unsigned int ti=0; ti<TriggerNames->size(); ti++ ) {
               TString tstn( TriggerNames->at(ti) ) ;
               if ( verb ) printf(" %3d : %50s\n", ti, TriggerNames->at(ti).c_str() ) ;
               for ( unsigned int tni=0; tni<trig_names.size(); tni++ ) {
                  if ( tstn.Contains( trig_names.at(tni).c_str() ) ) {
                     if ( verb ) printf(" %3d | %50s :  %s\n", ti, TriggerNames->at(ti).c_str(), (TriggerPass->at(ti)?"TRUE":"false") ) ;
                     if ( TriggerPass->at(ti) ) {
                        pass_trig = true ;
                        break ;
                     }
                  }
               } // tni
               if ( pass_trig ) break ;
            } // ti
            if ( verb ) printf("\n") ;
            if ( !pass_trig ) continue ;
         }

         if ( verb ) printf( "  Saved event %10lld : nbtag_csv85 = %d , nleptons = %d , rec_njet_pt30 = %d \n\n", ei, nbtag_csv85, nleptons, rec_njet_pt30 ) ;


         nsave ++ ;

         tt_out -> Fill() ;

      } // ei


      tt_out -> AutoSave() ;

      h_njets_pt45_eta24 -> Write() ;

      tf_output -> Close() ;

      printf("\n\n Done.\n") ;
      if ( nevts_ttree > 0 ) printf("  Saved %9d / %9lld  (%.4f)\n", nsave, nevts_ttree, (1.*nsave)/(1.*nevts_ttree) ) ;
      printf("  Created %s\n\n", outfile ) ;

   } // skim_subset


