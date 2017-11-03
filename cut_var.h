#ifndef cut_var_h
#define cut_var_h

#include "TH1F.h"

   class cut_var {

      public:

         cut_var( double& val, double cut_val ) ;

         bool   passes_cut( bool do_print = false ) ;
         void   set_hist_pars( const char* name, const char* xtitle, int nbins, double xlow, double xhigh ) ;
         double get_val() { return _var_val ; } ;
         TH1F*  create_hist( const char* hname ) ;
         void   use_le_in_cut() { _use_ge_in_cut = false ; }
         const char* get_name() { return _hist_name ; }

         int    get_hist_nbins() { return _hist_nbins ; } ;
         double get_hist_xlow() { return _hist_xlow ; } ;
         double get_hist_xhigh() { return _hist_xhigh ; } ;
         const char* get_hist_name() { return _hist_name ; } ;
         const char* get_hist_xtitle() { return _hist_xtitle ; } ;

         double& _var_val ;
         double _cut_val ;
         bool   _use_ge_in_cut ;
         int    _hist_nbins ;
         double _hist_xlow ;
         double _hist_xhigh ;
         char   _hist_xtitle[100] ;
         char   _hist_name[100] ;
         char   _print_format[100] ;



   } ; // cut_var

  //------------

   cut_var::cut_var( double& val, double cut_val ) : _var_val(val), _cut_val(cut_val) {
      sprintf( _print_format, "%%.1f" ) ;
      _use_ge_in_cut = true ;
   }

  //------------

   void cut_var::set_hist_pars( const char* name, const char* xtitle, int nbins, double xlow, double xhigh ) {
      sprintf( _hist_name, "%s", name ) ;
      sprintf( _hist_xtitle, "%s", xtitle ) ;
      _hist_nbins = nbins ;
      _hist_xlow = xlow ;
      _hist_xhigh = xhigh ;
   }

  //------------

   TH1F* cut_var::create_hist( const char* name ) {
      char hname[100] ;
      sprintf( hname, "h_%s_%s", _hist_name, name ) ;
      TH1F* rv = new TH1F( hname, hname, _hist_nbins, _hist_xlow, _hist_xhigh ) ;
      rv -> SetXTitle( _hist_xtitle ) ;
      rv -> Sumw2() ;
      return rv ;
   } // create_hist

  //------------

   bool cut_var::passes_cut( bool do_print ) {
      bool rval = false ;
      if ( _use_ge_in_cut ) {
         if ( _var_val >= _cut_val ) rval = true ;
      } else {
         if ( _var_val <= _cut_val ) rval = true ;
      }
      if ( do_print ) {
         char format[1000] ;
         sprintf( format, " %s : %s %s %s : %s\n", _hist_xtitle, _print_format, _use_ge_in_cut?">=":"<=", _print_format, rval?"PASS":"fail" ) ;
         printf( format, _var_val, _cut_val ) ;
      }
      return rval ;
   } // passes_cut

  //------------

#endif // cut_var_h
