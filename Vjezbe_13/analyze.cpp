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

	//Zadatak 1
	//ob->Loop();

	//Zadatak 2
	//ob->Usporedba("Francuska", 164.7, 7.1);
	ob->Usporedba("Nizozemska", 170.3, 7.5);
	//ob->Usporedba("Italija", 166.1, 6.5);

	delete ob;
	
	return 0;
}
