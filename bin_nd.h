#ifndef bin_nd_h
#define bin_nd_h

#include "bin_1d.h"

   class bin_nd {

      public:

         bin_nd( const char* name, const char* short_description, const char* description ) ;
         void add_1d_bin( bin_1d* bin ) ;
         bool in_bin() ;
         const char* get_name() { return _name ; }
         const char* get_short_description() { return _short_description ; }
         const char* get_description() { return _description ; }

         char _name[100] ;
         char _short_description[100] ;
         char _description[100] ;
         vector< bin_1d* > _bin_1d_objects ;

   } ;

  //------------

   bin_nd::bin_nd( const char* name, const char* short_description, const char* description ) {
      sprintf( _name, "%s", name ) ;
      sprintf( _short_description, "%s", short_description ) ;
      sprintf( _description, "%s", description ) ;
   } ;

  //------------

   void bin_nd::add_1d_bin( bin_1d* bin ) {
      _bin_1d_objects.push_back( bin ) ;
   }

  //------------

   bool bin_nd::in_bin() {
      bool ret_val(true) ;
      for ( unsigned int di=0; di<_bin_1d_objects.size(); di++ ) {
         if ( ! (_bin_1d_objects.at(di)->in_bin()) ) { ret_val = false ; break ; }
      }
      return ret_val ;
   }

  //------------


#endif // bin_nd_h


