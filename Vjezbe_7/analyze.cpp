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
	
	TString path;
	path = "/home/public/data/ggH125/ZZ4lAnalysis.root";
	ob->PlotHistogram(path);
	path = "/home/public/data/qqZZ/ZZ4lAnalysis.root";
	ob->PlotHistogram(path);

	ob->Drawing();
	delete ob;
	
	return 0;
}
