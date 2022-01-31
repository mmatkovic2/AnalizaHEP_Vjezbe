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

void Analyzer::Osjetljivost(){
	TRandom3 *r3 = new TRandom3();

	double m_H, pVrijednost;
	int k=0;	
	
	TF1 *funcfita2;
	funcfita2 = new TF1("funcfita2", "[0]*exp(-x/[1])", 0.0, 700.0);
	funcfita2->SetParName(0, "N_sm");
	funcfita2->SetParameter(0, 200);
	funcfita2->SetParName(1, "Gama");
	funcfita2->FixParameter(1, 100);
	
	TH1F* histogram2 = new TH1F("histo2", "histo2", 200, 0, 700);
	TGraph *Pval = new TGraph();

	
	//setamo po svim masama Higgsa 10-690
	for (int i=10; i<690; i=i+5){
		m_H=i/1.0;
		//sada petlja po 10000 dogadaja
		for(int j=0; j<10000; j++){
			if(r3->Rndm()>(-1*(m_H-190.0)*(m_H-190.0) + 0.02))
				histogram2->Fill(r3->Exp(100)); //punjenje pozadine kao u zad 1
			else
				histogram2->Fill(r3->Gaus(m_H, 0.0236*m_H)); //punjenje signalnim podacima
		}
		histogram2->Fit(funcfita2, "q", "", i-10, i+10);
		pVrijednost = chisquare->Integral(chisquare->FindBin(funcfita2->GetChisquare()), 200);
		pVrijednost = pVrijednost/(chisquare->Integral());
		Pval->SetPoint(k, m_H, pVrijednost);
		histogram2->Reset();
		k++;
	}
	
	gStyle->SetOptStat(0);
	TCanvas *c2 = new TCanvas("c2", "c2", 1600, 900);
	gPad->SetLogy();	
    	Pval->GetXaxis()->SetTitle("m_{H}");
    	Pval->GetYaxis()->SetTitle("p-vrijednost");
    	Pval->SetTitle("P-value/m_{H}");
	Pval->Draw("AL*");


	c2->SaveAs("Z14_2.png");

}


