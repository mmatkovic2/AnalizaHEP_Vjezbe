#include <iostream>
#include <fstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TApplication.h>
#include <Analyzer.h>
#include <vector>

using namespace std;

int main()
{	
	Analyzer* ob;
	ob = new Analyzer();
	
	ob->PlotHistogram("ggH125");
	ob->PlotHistogram("qqZZ");	
	
	ob->Drawing();
	delete ob;
	
	return 0;
}
