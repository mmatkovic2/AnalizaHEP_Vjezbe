//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Dec  8 12:03:07 2021 by ROOT version 6.24/06
// from TTree Tree/Lifetime decay data
// found on file: /home/public/data/Lifetime/Lifetime.root
//////////////////////////////////////////////////////////

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
   
   //zadatak 1
   virtual double Factorial(int broj);
   virtual double Binomial(int r, int N, double p);
   
   //zadatak 2
   virtual double GornjaGranica(int m1, int N1, double C);
   virtual double DonjaGranica(int m2, int N2, double C);

   //Zadatak 4
   virtual void Kocka(int N, double C);
   
};

#endif

#ifdef Analyzer_cxx

#endif // #ifdef Analyzer_cxx
