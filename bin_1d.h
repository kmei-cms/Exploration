#ifndef bin_1d_h
#define bin_1d_h

   class bin_1d {

      public:

         bin_1d( const char* name, const char* short_description, const char* description, double& var, double min, double max ) ;
         bool in_bin() { return ( _var >= _min && _var <= _max ) ; }
         const char* get_name() { return _name ; }
         const char* get_short_description() { return _short_description ; }
         const char* get_description() { return _description ; }

         char _name[100] ;
         char _short_description[100] ;
         char _description[100] ;
         double& _var ;
         double _min ;
         double _max ;

   } ;

  //------------

   bin_1d::bin_1d( const char* name, const char* short_description, const char* description, double& var, double min, double max ) :
      _var(var), _min(min), _max(max) {
      sprintf( _name, "%s", name ) ;
      sprintf( _short_description, "%s", short_description ) ;
      sprintf( _description, "%s", description ) ;
   } ;

  //------------


#endif // bin_1d_h
