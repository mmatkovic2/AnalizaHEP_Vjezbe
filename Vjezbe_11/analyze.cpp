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
	
	int brojpovoljnih=3;
	int brojukupnih=10;
	double vjerojatnostpovoljnog=0.1667;
	
	cout << "Za " << brojpovoljnih << " povoljna dogadaja od " << brojukupnih << " ukupno " " uz p = " << vjerojatnostpovoljnog << " vjerojatnost povoljnog dogadaja imamo: " << ob->Binomial(brojpovoljnih, brojukupnih, vjerojatnostpovoljnog) << " vjerojatnost." << endl;
	
	//zadatak2
	ob->GornjaGranica(4, 10, 0.683);
	ob->DonjaGranica(4, 10, 0.683);	
	
	//zadatak4
	ob->Kocka(10, 0.683);
	delete ob;
	
	return 0;
}
