#ifndef Analyzer_h
#define Analyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TF1.h>
#include <TGraphPainter.h>
#include<TGraphErrors.h>

// Header file for the classes stored in the TTree if any.
#include <vector>

using namespace std;

class Analyzer {
public :
   
   
   //Vjezbe 14, zad 1
   virtual void Fotoni();
   
   
};

#endif

#ifdef Analyzer_cxx

#endif // #ifdef Analyzer_cxx
