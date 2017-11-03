#ifndef utility_functions_h
#define utility_functions_h

#include "TLorentzVector.h"

double calcDPhi(double phi1, double phi2)
{
    double dphi = phi1 - phi2 ;
    if ( dphi >  3.14159265 ) dphi -= 2*3.14159265 ;
    if ( dphi < -3.14159265 ) dphi += 2*3.14159265 ;
    return dphi;
}

double calcDR( TLorentzVector& lv1, TLorentzVector& lv2 ) {
   double dphi = calcDPhi( lv1.Phi(), lv2.Phi() ) ;
   double deta = fabs( lv1.Eta() - lv2.Eta() ) ;
   return sqrt( dphi*dphi + deta*deta ) ;
}

#endif
