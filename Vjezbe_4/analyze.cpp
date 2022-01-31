#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "Analyzer.h"

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TApplication.h>

using namespace std;

int main()
{
	Analyzer *a;
	a = new Analyzer();

	a->ReadFile();
	a->ConvertTxtToRootFile();
	return 0;
}
