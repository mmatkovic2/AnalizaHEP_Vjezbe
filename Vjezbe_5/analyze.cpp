#include <iostream>
#include <fstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TApplication.h>
#include <Analyzer.h>

using namespace std;

int main()
{	
	Analyzer* ob;
	ob = new Analyzer();
	
	ob->PlotHistogram();
	
	delete ob;
	
	return 0;
}
