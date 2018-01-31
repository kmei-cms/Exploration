IDIR       = .
ODIR       = obj
SDIR       = .

OPENCV_DIRECTORY=/uscms_data/d3/nstrobbe/SOFTWARE/opencv
TTDIR  = $(CMSSW_BASE)/src/TopTagger/
TTTDIR     = $(TTDIR)/TopTagger/test

CXX        = g++

CXXFLAGS  += -I. -I$(CMSSW_BASE)/src -std=c++0x
#CXXFLAGS  += -I. -I$(CMSSW_BASE)/src -std=c++0x -I$(LHAPDF_DATA_PATH)/../../include
## Optimization flag
CXXFLAGS += -g #-O3
## Enable the maximun warning
#CXXFLAGS += -Wall -Wextra -Weffc++ -g

## Include ROOT
CXXFLAGS  += $(shell root-config --cflags)

CXXDEPFLAGS = -MMD -MP

LD         = g++
LDFLAGS    =

LIBS       = $(shell root-config --glibs)
LIBSTOPTAGGER += -L$(TTTDIR) -lTopTagger
#LHAPDFLIB  = -L$(LHAPDF_DATA_PATH)/../../lib -lLHAPDF

#OBJS       = $(patsubst %, $(ODIR)/%, $(OBJ))


PROGRAMS = MyAnalysis MyAnalysisMultiFile AddTopVars AddTopVarsBatch MicroNtuple RunExploreTopTagger RunExploreEventSelection


all: mkobj $(PROGRAMS)

mkobj:
	@mkdir -p obj

$(ODIR)/%.o : $(SDIR)/%.C
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS)  -o $@ -c $<

$(ODIR)/%.o : $(SDIR)/%.c
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS)  -o $@ -c $<

$(ODIR)/%.o : $(SDIR)/%.cc
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS)  -o $@ -c $<

$(ODIR)/%.o : $(SDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS)  -o $@ -c $<

$(ODIR)/%.o : $(RSDIR)/%.C
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS)  -o $@ -c $<

$(ODIR)/%.o : $(RSDIR)/%.cc
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS)  -o $@ -c $<

$(ODIR)/%.o : $(RSDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS)  -o $@ -c $<

$(ODIR)/%.o : $(TTSDIR)/%.C
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS)  -o $@ -c $<

$(ODIR)/%.o : $(TTSDIR)/%.cc
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS)  -o $@ -c $<

$(ODIR)/%.o : $(TTSDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS)  -o $@ -c $<

MyAnalysis: $(ODIR)/MyAnalysis.o $(ODIR)/ExploreBackground.o $(ODIR)/NtupleClass.o $(ODIR)/Utility.o
	$(LD) $^ $(LIBSTOPTAGGER) $(LIBS) -o $@

MyAnalysisMultiFile: $(ODIR)/MyAnalysisMultiFile.o $(ODIR)/NtupleClass.o $(ODIR)/Utility.o
	$(LD) $^ $(LIBSTOPTAGGER) $(LIBS) -o $@

AddTopVars: $(ODIR)/AddTopVars.o $(ODIR)/NtupleClassAddTopVars.o
	$(LD) $^ $(LIBSTOPTAGGER) $(LIBS) -o $@

AddTopVarsBatch: $(ODIR)/AddTopVarsBatch.o $(ODIR)/NtupleClassAddTopVars.o
	$(LD) $^ $(LIBSTOPTAGGER) $(LIBS) -o $@


MicroNtuple: $(ODIR)/MicroNtuple.o $(ODIR)/NtupleClassMicroNtuple.o $(ODIR)/EventShapeVariables.o
	$(LD) $^ $(LIBSTOPTAGGER) $(LIBS) -o $@

RunExploreTopTagger: $(ODIR)/RunExploreTopTagger.o $(ODIR)/ExploreTopTagger.o $(ODIR)/NtupleClass.o $(ODIR)/Utility.o
	$(LD) $^ $(LIBSTOPTAGGER) $(LIBS) -o $@

RunExploreEventSelection: $(ODIR)/RunExploreEventSelection.o $(ODIR)/ExploreEventSelection.o $(ODIR)/NtupleClass.o $(ODIR)/Utility.o
	$(LD) $^ $(LIBSTOPTAGGER) $(LIBS) -o $@

clean:
	rm -f $(ODIR)/*.o $(ODIR)/*.so $(ODIR)/*.d $(PROGRAMS) core 
