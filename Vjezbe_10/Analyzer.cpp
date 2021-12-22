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


void Analyzer::PlotHistogram(){

	//stvaramo canvas
	TCanvas *c = new TCanvas("c", "c", 900, 900);

	gPad->SetLeftMargin(0.15);
	gStyle->SetOptFit();
	
	//zadajemo parametre fita za zadatak 1
	//za zadatak2 ovo zakomentiramo
	funcfita = new TF1("funcfita", "x/[0]", 0.0, 6.0);
	funcfita->SetParName(0, "masa");
	funcfita->SetParameter(0, 0.1);

	
	//upisujemo podatke (data set) zadan u zadatku	
	const Int_t N=5; //velicina polja
	Double_t a[5]={9.8, 21.2, 34.5, 39.9, 48.5};
	Double_t agreska[5]={1.0, 1.9, 3.1, 3.9, 5.1};
	Double_t sila[5]={1.0, 2.0, 3.0, 4.0, 5.0};
	Double_t silagreska[5]={0.0, 0.0, 0.0, 0.0, 0.0};

	//zadatak3
	chisquare = new TF1("chi square", "(([0]-x*[1])*([0]-x*[1]))/([2]*[2])+ (([3]-x*[4])*([3]-x*[4]))/([5]*[5]) + (([6]-x*[7])*([6]-x*[7]))/([8]*[8]) + (([9]-x*[10])*([9]-x*[10]))/([11]*[11]) + (([12]-x*[13])*([12]-x*[13]))/([14]*[14])", 7, 15);
	for(int i=0; i<5*5; i=i+3)
	{
		chisquare->SetParameter(i, a[i/3]);
		chisquare->SetParameter(i+1, sila[i/3]);
		chisquare->SetParameter(i+2, agreska[i/3]);
	}
	
	/*
	TGraphErrors *graph = new TGraphErrors(N, sila, a, silagreska, agreska);
	graph->SetTitle("Ovisnost a o F");
	//graph->GetXAxis()->SetTitle("F [N]");
	//graph->GetYAxis()->SetTitle("a [m/s2]");
	graph->Draw("AP");
	graph->Fit(funcfita);
	*/

	chisquare->SetLineColor(kRed);
	chisquare->SetTitle("Xi kvadrat funkcija; #theta; Xi");
	chisquare->Draw();
	cout << "Minimum funkcije likelihood je na polozaju theta = " << chisquare->GetMinimumX() << endl;
	double yMin = chisquare->GetMinimum(); //trazimo koliki je minimum chisquare funkcije
    	double x1 = chisquare->GetX(yMin + 1.0, 7.0, chisquare->GetMinimumX() - 0.0001); //trazimo x-eve
    	double x2 = chisquare->GetX(yMin + 1.0, chisquare->GetMinimumX() + 0.0001, 13); //gdje imamo y=min+1
	//sigma je samo razlika tau i x1 i x2	
	double sig1 = chisquare->GetMinimumX() - x1;
	double sig2 = x2 - chisquare->GetMinimumX();
	cout << "Theta = " << chisquare->GetMinimumX() << "-" << sig1 << "+" << sig2 << endl; 
	cout << "Masa = " << 1/(chisquare->GetMinimumX()) << "+-" << sig1/(chisquare->GetMinimumX()*chisquare->GetMinimumX()) << endl; 
	
	//zadatak2
	double suma1=0.0;
	double suma2=0.0;
	double theta;	
	for(int j=0; j<5; j++)
	{
		suma1=suma1+sila[j]*a[j]/(agreska[j]*agreska[j]);
		suma2=suma2+(sila[j]/agreska[j])*(sila[j]/agreska[j]);	
	}
	theta=suma1/suma2;

	cout << "Analitickom metodom izracunata je masa: " << 1.0/theta << "i pripadajuca greska" << suma2/theta << endl;


	c->SaveAs("Zadatak4.png");
}
