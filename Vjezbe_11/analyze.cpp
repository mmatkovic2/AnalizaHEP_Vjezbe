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
	
	int brojpovoljnih=7;
	int brojukupnih=20;
	double vjerojatnostpovoljnog=0.5;
	
	cout << "Za " << brojpovoljnih << " povoljna dogadaja od " << brojukupnih << " ukupno " " uz p = " << vjerojatnostpovoljnog << " vjerojatnost povoljnog dogadaja imamo: " << ob->Binomial(brojpovoljnih, brojukupnih, vjerojatnostpovoljnog) << " vjerojatnost." << endl;

	
	ob->GornjaGranica(1, 4, 0.687);
	ob->DonjaGranica(1, 4, 0.687);	
	
	delete ob;
	
	return 0;
}
