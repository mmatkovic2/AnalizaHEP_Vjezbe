#include <iostream>
#include <fstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TApplication.h>
#include <Analyzer.h>
#include <vector>
#include <TGraphPainter.h>
#include<TGraphErrors.h>

using namespace std;

int main()
{	
	Analyzer* ob;
	ob = new Analyzer();

	//ob->Loop();
	ob->Usporedba("Francuska", 164.7, 7.1);

	delete ob;
	
	return 0;
}
