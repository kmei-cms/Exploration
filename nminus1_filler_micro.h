//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Nov  1 13:16:55 2017 by ROOT version 6.06/06
// from TChain micrott/
//////////////////////////////////////////////////////////

#ifndef nminus1_filler_micro_h
#define nminus1_filler_micro_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TSystem.h"

// Header file for the classes stored in the TTree if any.

class nminus1_filler_micro {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           njets_pt45_eta24;
   Float_t         pfht_pt40_eta24;
   Int_t           nbtag_csv85_pt30_eta24;
   Int_t           ntop1b;
   Int_t           ntop1bpt200;
   Int_t           ntop1bnot3prong;
   Int_t           ntop1bnot3prongpt200;
   Int_t           njetsextra_pt30_eta24;
   Float_t         pfht7p_pt30_eta24;
   Float_t         pfhtextra_pt30_eta24;
   Int_t           nleptons;

   // List of branches
   TBranch        *b_njets_pt45_eta24;   //!
   TBranch        *b_pfht_pt40_eta24;   //!
   TBranch        *b_nbtag_csv85_pt30_eta24;   //!
   TBranch        *b_ntop1b;   //!
   TBranch        *b_ntop1bpt200;   //!
   TBranch        *b_ntop1bnot3prong;   //!
   TBranch        *b_ntop1bnot3prongpt200;   //!
   TBranch        *b_njetsextra_pt30_eta24;   //!
   TBranch        *b_pfht7p_pt30_eta24;   //!
   TBranch        *b_pfhtextra_pt30_eta24;   //!
   TBranch        *b_nleptons;   //!

   nminus1_filler_micro( const char* sample_string = "rpv_stop_350_t3j_uds", const char* ntuple_dir = "micro-ntuples-v1", double lumi_times_xsec=1.);
   virtual ~nminus1_filler_micro();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   char    hist_file_name[1000] ;
   double ds_weight ;
};

#endif

#ifdef nminus1_filler_micro_cxx
nminus1_filler_micro::nminus1_filler_micro( const char* sample_string, const char* ntuple_dir, double lumi_times_xsec ) : fChain(0) 
{


   TChain* chain = new TChain( "micrott", "" ) ;
   char fpat[1000] ;
   sprintf( fpat, "%s/*%s*.root", ntuple_dir, sample_string ) ;
   printf("\n\n Loading files that match %s\n", fpat ) ;
   int n_added = chain -> Add( fpat ) ;
   if ( n_added <= 0 ) { printf("\n\n *** No files match %s\n\n", fpat ) ; gSystem->Exit(-1) ; }
   printf("  Added %d files to chain.\n", n_added ) ;
   int n_entries = chain -> GetEntries() ;
   if ( n_entries <= 0 ) { printf("\n\n *** No entries in ntuple chain.\n\n" ) ; gSystem->Exit(-1) ; }
   printf("  Number of entries: %d\n\n", n_entries ) ;

   ds_weight = lumi_times_xsec / n_entries ;
   printf("  Dataset weight : %.8f\n\n", ds_weight ) ;

   TTree* tree = chain ;
   Init(tree) ;

   gSystem -> Exec( "mkdir -p outputfiles" ) ;

   sprintf( hist_file_name, "outputfiles/nm1-micro-hists-%s.root", sample_string ) ;


}

nminus1_filler_micro::~nminus1_filler_micro()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t nminus1_filler_micro::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t nminus1_filler_micro::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void nminus1_filler_micro::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("njets_pt45_eta24", &njets_pt45_eta24, &b_njets_pt45_eta24);
   fChain->SetBranchAddress("pfht_pt40_eta24", &pfht_pt40_eta24, &b_pfht_pt40_eta24);
   fChain->SetBranchAddress("nbtag_csv85_pt30_eta24", &nbtag_csv85_pt30_eta24, &b_nbtag_csv85_pt30_eta24);
   fChain->SetBranchAddress("ntop1b", &ntop1b, &b_ntop1b);
   fChain->SetBranchAddress("ntop1bpt200", &ntop1bpt200, &b_ntop1bpt200);
   fChain->SetBranchAddress("ntop1bnot3prong", &ntop1bnot3prong, &b_ntop1bnot3prong);
   fChain->SetBranchAddress("ntop1bnot3prongpt200", &ntop1bnot3prongpt200, &b_ntop1bnot3prongpt200);
   fChain->SetBranchAddress("njetsextra_pt30_eta24", &njetsextra_pt30_eta24, &b_njetsextra_pt30_eta24);
   fChain->SetBranchAddress("pfht7p_pt30_eta24", &pfht7p_pt30_eta24, &b_pfht7p_pt30_eta24);
   fChain->SetBranchAddress("pfhtextra_pt30_eta24", &pfhtextra_pt30_eta24, &b_pfhtextra_pt30_eta24);
   fChain->SetBranchAddress("nleptons", &nleptons, &b_nleptons);
   Notify();
}

Bool_t nminus1_filler_micro::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void nminus1_filler_micro::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t nminus1_filler_micro::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   if ( entry > 0 ) return 1 ;
   return 1;
}
#endif // #ifdef nminus1_filler_micro_cxx
