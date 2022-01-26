#define Analyzer_cxx
#include "Analyzer.h"
#include <TF1.h>
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TRandom.h>
#include <iostream>
#include <TMath.h>
#include <TLine.h>
#include <TString.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TRandom.h>
#include <TRandom3.h>

using namespace std;

void Analyzer::Fotoni(){
	TRandom3 *r3 = new TRandom3();

	TH1F *chisquare;
	chisquare = new TH1F("chi square", "chi square", 250, 0, 25);	
	
	TF1 *funcfita;
	funcfita = new TF1("funcfita", "[0]*exp(-x/[1])", 0.0, 300.0);
	funcfita->SetParName(0, "N_sm");
	funcfita->SetParameter(0, 200);
	funcfita->SetParName(1, "Gama");
	funcfita->FixParameter(1, 100);
	
	TH1F* histogram = new TH1F("histo", "histo", 200, 0, 700);
	for (int i=0; i<1000; i++){
		for(int j=0; j<100000; j++){
			histogram->Fill(r3->Exp(100));
		}
		
		for(int k=10; k<695; k=k+5){
			histogram->Fit("funcfita", "q", "", k-10, k+10);
			chisquare->Fill(funcfita->GetChisquare());
		}
		histogram->Reset();
	}
	chisquare->Scale(1.0/chisquare->Integral());
	
	gStyle->SetOptStat(0);
	TCanvas *c = new TCanvas("c", "c", 900, 900);
	gPad->SetLeftMargin(0.15);	
    	chisquare->GetXaxis()->SetTitle("chi^2");
    	chisquare->GetYaxis()->SetTitle("PDF");
    	chisquare->SetStats(0);
    	chisquare->SetLineColor(kBlue);
    	chisquare->Draw("histo");


	c->SaveAs("Z14_1.png");
		
}
