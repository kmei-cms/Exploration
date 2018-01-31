#ifndef ExploreBackground_h
#define ExploreBackground_h

#include <TH1D.h>
#include <TH2D.h>
#include <TEfficiency.h>

#include "NtupleClass.h"
//#include "samples.h"

#include <map>
#include <string>

class ExploreBackground : public NtupleClass {
public :
   std::map<std::string, TH1D*>  my_histos;
   std::map<std::string, TH2D*>  my_2d_histos;
   std::map<std::string, TEfficiency*>  my_efficiencies;

   ExploreBackground(TTree* tree) : NtupleClass(tree) {}

   void     Loop(std::string runtype, double weight, int maxevents = -1, bool isQuiet = false);
   virtual void     InitHistos();
   virtual void     WriteHistos();

};

#endif
