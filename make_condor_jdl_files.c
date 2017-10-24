
   void make_condor_jdl_files( const char* eos_dir="/store/group/lpcsusyhad/StealthStop/TreeMaker_ntuples/qcd", const char* fpat = "root" ) {


      printf("\n\n Will load files that match %s from eos dir %s\n\n", fpat, eos_dir ) ;


      char command[1000] ;
      sprintf( command, "eos root://cmseos.fnal.gov ls %s > eos-files.txt", eos_dir ) ;
      gSystem -> Exec( command ) ;


      char ds_name[100] ;
      sprintf( ds_name, "%s", gSystem->BaseName( eos_dir ) ) ;
      printf("\n\n Dataset name: %s\n\n", ds_name ) ;

      char group_name[100] ;
      sprintf( group_name, "%s-%s", ds_name, fpat ) ;
      printf("\n\n Group name: %s\n\n", group_name ) ;


      sprintf( command, "mkdir -p jdl-files/%s", group_name ) ;
      gSystem -> Exec( command ) ;

      sprintf( command, "mkdir -p log-files/%s", group_name ) ;
      gSystem -> Exec( command ) ;

      sprintf( command, "mkdir -p output-files/%s", group_name ) ;
      gSystem -> Exec( command ) ;

      sprintf( command, "mkdir -p log-files/%s/old", group_name ) ;
      gSystem -> Exec( command ) ;
      sprintf( command, "mv log-files/%s/*.* log-files/%s/old", group_name, group_name ) ;
      gSystem -> Exec( command ) ;

      sprintf( command, "mkdir -p output-files/%s/old", group_name ) ;
      gSystem -> Exec( command ) ;
      sprintf( command, "mv output-files/%s/*.* output-files/%s/old", group_name, group_name ) ;
      gSystem -> Exec( command ) ;



      std::ifstream ifs_files ;
      ifs_files.open( "eos-files.txt" ) ;
      while ( ifs_files.good() ) {
         TString tsline ;
         tsline.ReadLine( ifs_files ) ;
         if ( !ifs_files.good() ) break ;
         if ( tsline.Contains( fpat ) ) {
            char fname[10000] ;
            sprintf( fname, "%s/%s", eos_dir, tsline.Data() ) ;  
            TString jdl_file_name = tsline ;
            jdl_file_name.ReplaceAll( ".root", ".jdl" ) ;
            TString log_file_name = tsline ;
            log_file_name.ReplaceAll( ".root", ".log" ) ;
            TString out_file_name = tsline ;
            out_file_name.ReplaceAll( ".root", ".out" ) ;
            TString error_file_name = tsline ;
            error_file_name.ReplaceAll( ".root", ".error" ) ;
            char full_jdl_name[10000] ;
            sprintf( full_jdl_name, "jdl-files/%s/condor-%s", group_name, jdl_file_name.Data() ) ;
            printf ( "  jdl file: %s\n", full_jdl_name  ) ;
            char output_root_file[1000] ;
            sprintf( output_root_file, "topvars-%s", tsline.Data() ) ;
            FILE* ofp = fopen( full_jdl_name, "w" ) ;
            if ( ofp == 0x0 ) { printf("\n\n *** can't open file %s\n\n", full_jdl_name ) ; gSystem -> Exit( -1 ) ; }
            fprintf( ofp, "Universe   = vanilla\n" ) ;
            fprintf( ofp, "Executable = runtoptagger-condor-exec.tcsh\n") ;
            fprintf( ofp, "Transfer_Input_Files = cmssw-toptagger.tar.gz, opencv.tar.gz\n" ) ;
            fprintf( ofp, "Should_Transfer_Files = YES\n" ) ;
            fprintf( ofp, "WhenToTransferOutput = ON_EXIT\n" ) ;
            fprintf( ofp, "transfer_output_remaps = \"%s = output-files/%s/%s\"\n", output_root_file, group_name, output_root_file ) ;
            fprintf( ofp, "Arguments = %s/%s  %s skim\n", eos_dir, tsline.Data(), output_root_file ) ;
            fprintf( ofp, "Log    = log-files/%s/%s\n", group_name, log_file_name.Data() ) ;
            fprintf( ofp, "Output = log-files/%s/%s\n", group_name, out_file_name.Data() ) ;
            fprintf( ofp, "Error  = log-files/%s/%s\n", group_name, error_file_name.Data() ) ;
            fprintf( ofp, "Queue 1\n" ) ;
            fclose( ofp ) ;
         }
      } // reading files







   } // make_condor_jdl_files
