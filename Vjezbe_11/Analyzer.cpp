#define Analyzer_cxx
#include "Analyzer.h"
#include <TH1F.h>
#include <TH2.h>
#include <TH2F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <vector>
#include <TLorentzVector.h>
#include <TColor.h>
#include <iostream>
#include <THStack.h>
#include <TString.h>
#include <TF1.h>
#include <cmath>
#include <TGraphPainter.h>
#include <TGraphErrors.h>
#include <stdlib.h>

using namespace std;

double Analyzer::Factorial(int broj){
	double factorial=1.0;
	
	if(broj==0)
		factorial=1.0;
	if(broj>0){
		for(int i=1; i<=broj; i++){
			factorial=factorial*i;
		}
	}
	
	return factorial;	
}

double Analyzer::Binomial(int r, int N, double p){
	double binomni;	

	binomni=(Factorial(N)/(Factorial(r)*Factorial(N-r)))*( pow(p,r)*pow(1-p,N-r));	
	return binomni;
}


//zadatak 2
double Analyzer::GornjaGranica(int m1, int N1, double C){
	double pplus=1.0;	
	double suma1=0.0, suma;
	
	
	while(suma<(1.0-C)/2.0){
		for (int r1 = m1+1; r1<=N1; r1++){
			suma1=suma1+Binomial(r1, N1, pplus);
		}	
		pplus=pplus-0.001;
		suma = 1-suma1;
		suma1=0.0;
	}		

	//cout << "Gornja granica je: " << pplus << endl;
	return pplus;
}

double Analyzer::DonjaGranica(int m2, int N2, double C){
	double pminus=1.0;	
	double suma1=0.0, suma=10.0;
	
	if(m2==0){
		return 0;
	}
	
	while(suma>(1.0-C)/2.0){
		for (int r1 = 0; r1< m2; r1++){
			suma1=suma1+Binomial(r1, N2, pminus);
		}	
		pminus=pminus-0.001;
		suma = 1-suma1;
		suma1=0.0;
	}		

	//cout << "Donja granica je: " << pminus << endl;
	return pminus;
}

//zadatak4
void Analyzer::Kocka(int N, double C){

	srand(time(NULL));
	int i, j;
	int brojac, brojpovoljnih=0;
	double pgornja, pdonja;

	for (i=0; i<1000; i++){
		brojac=0;
		for(j=0; j<N; j++){
			if((rand()%6+1)==6){
				brojac++;
			}	
		}
		pgornja=GornjaGranica(brojac, N, C);
		pdonja=DonjaGranica(brojac, N, C);

		if(pgornja>=(1.0/6.0) && pdonja<=(1.0/6.0)){
			brojpovoljnih++;
		}
					
	}

	cout << "Broj eksperimenata koji sadrze p u 10 bacanja u tocnom intervalu od " << C << " je: " << brojpovoljnih << endl;

	
}


