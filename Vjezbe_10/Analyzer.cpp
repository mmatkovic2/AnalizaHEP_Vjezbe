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


	
	TGraphErrors *graph = new TGraphErrors(N, sila, a, silagreska, agreska);
	graph->SetTitle("Ovisnost a o F");
	//graph->GetXAxis()->SetTitle("F [N]");
	//graph->GetYAxis()->SetTitle("a [m/s2]");
	graph->Draw("AP");
	graph->Fit(funcfita);


	
	c->SaveAs("Zadatak1prvi.png");
}
