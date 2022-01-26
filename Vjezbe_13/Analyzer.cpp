#define Analyzer_cxx
#include "Analyzer.h"
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

using namespace std;

void Analyzer::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Analyzer.C
//      root> Analyzer t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch

   TH1F *testStatistika;
   TH1F *podaci;
   TRandom *randomvisina;
   randomvisina = new TRandom();
	
   testStatistika = new TH1F("test statistika", "test statistika", 500, 160, 170);
   podaci = new TH1F("podaci", "podaci", 500, 160, 170); 

   double srednji_podaci=0.0;
   double sumarandom;
   double pvalue_postavljeni=0.005;	
   double pvalue_grafa;
   double zscore_postavljeni, zscore_grafa;


   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      //punimo histogram sa stvarnim mjerenjima i 
      podaci->Fill(height);
      srednji_podaci = srednji_podaci + height;
      // if (Cut(ientry) < 0) continue;
   }
   srednji_podaci=srednji_podaci/nentries;
   cout << "Srednji podaci: " << srednji_podaci << endl;

   for(int i=0; i<1000000; i++)
   {
	sumarandom=0.0;
	for(int j=0; j<100; j++)
	{
		sumarandom=sumarandom + randomvisina->Gaus(164.7, 7.1);
	}
	sumarandom=sumarandom/100;
	testStatistika->Fill(sumarandom);
   }
   //potrebno normalizirati funkciju; 
   testStatistika->Scale(1.0/testStatistika->Integral());

   //racunamo vrijednost pvaluea
   pvalue_grafa=testStatistika->Integral(testStatistika->FindBin(srednji_podaci), 500);

   //preracunato u sigmu
   zscore_postavljeni = TMath::Sqrt(2)*TMath::ErfcInverse(2*pvalue_postavljeni);
   zscore_grafa = TMath::Sqrt(2)*TMath::ErfcInverse(2*pvalue_grafa);

   //i ispisujemo
   cout << "Hipotezu H0 odbacujemo ako je pvalue manji od " << pvalue_postavljeni*100 << "% " << "odnosno " << zscore_postavljeni << " sigma" << endl;
   cout << "Za Hipotezu H0 smo dobili pvalue " << pvalue_grafa*100 << " % " << "odnosno " << zscore_grafa << " sigma" << endl;
    
    //crtamo graf
    TCanvas* c = new TCanvas("c", "c", 900, 900);
    gPad->SetLeftMargin(0.15);	
    testStatistika->GetXaxis()->SetTitle("test statistika");
    testStatistika->GetYaxis()->SetTitle("PDF - Francuska");
    testStatistika->SetStats(0);
    testStatistika->SetLineColor(kBlue);
    testStatistika->Draw("histo");

    //crtamo liniju srednje vrijednosti podataka na grafu
    TLine *line;
    line = new TLine(srednji_podaci, 0.0, srednji_podaci, 0.01);
    line->Draw(); 

    c->SaveAs("TestStatistika.png");
}

//zadatak 2
void Analyzer::Usporedba(TString ime, double srednja, double greska){
	
	TH1F *Spanjolska = new TH1F("", "", 500, 160, 175);
	TH1F *DrugaDrzava = new TH1F("", "", 500, 160, 175);

	TRandom *randomvisina;
   	randomvisina = new TRandom();	

	double sumaspanjolske, sumadruge;
	double t_spanjolske, t_druge;
	double srednja_data=167.85; //izracunata srednja vrijednost podataka iz zadatka 1 i prepisana
	double confidencelevel;

	for(int i=0; i<1000000; i++)
   	{
		sumaspanjolske=0.0;
		sumadruge=0.0;
		for(int j=0; j<100; j++)
		{
			sumaspanjolske = sumaspanjolske + randomvisina->Gaus(168.0, 7.0);
			sumadruge = sumadruge + randomvisina->Gaus(srednja, greska);
		}
		sumaspanjolske=sumaspanjolske/100;
		sumadruge=sumadruge/100;
		Spanjolska->Fill(sumaspanjolske);
		DrugaDrzava->Fill(sumadruge);
   	}
	Spanjolska->Scale(1.0/Spanjolska->Integral());
	DrugaDrzava->Scale(1.0/DrugaDrzava->Integral());

	//racunamo vrijednosti korisne za racune sa CL
	t_spanjolske=Spanjolska->Integral(Spanjolska->FindBin(srednja_data), 500);
	t_druge=DrugaDrzava->Integral(DrugaDrzava->FindBin(srednja_data), 500);

	if(ime=="Nizozemska"){
		//nizozemsku potrebno posebno izdvojiti jer se nalazi s "desne" strane spanjolske
		confidencelevel=1-((1-t_druge)/t_spanjolske);
		cout << "Odbijamo Nizozemsku sa confidence levelom " << confidencelevel*100 << "%." << endl;
	}
	else{
		confidencelevel=1-(t_druge/(1-t_spanjolske));
		cout << "Odbijamo " << ime << " sa confidence levelom " << confidencelevel*100 << "%." << endl; 
	}
	//Rezultati za confidence level:
	//Nizozemska: odbijamo sa confidence levelom od 99.9024%
	//Francuska: odbijamo sa confidence levelom od 99.9988%
	//Italija: odbijamo sa confidence levelom od 99.0848%
	
	//Crtamo distribuciju
	gStyle->SetOptStat(0);
	TCanvas *c1;
	c1 = new TCanvas("c1", "c1", 1600, 900);
	DrugaDrzava->SetTitle("H0 vs H1");
	Spanjolska->SetTitle("H0 vs H1");
	DrugaDrzava->GetXaxis()->SetTitle("visina");
    	DrugaDrzava->GetYaxis()->SetTitle("PDF");
	Spanjolska->GetXaxis()->SetTitle("visina");
    	Spanjolska->GetYaxis()->SetTitle("PDF");
	DrugaDrzava->SetLineColor(kBlue);
	Spanjolska->SetLineColor(kRed);

	Spanjolska->Draw("histo");
	DrugaDrzava->Draw("histo same");
	//Spanjolska->Draw("histo same");

	//crtanje linije podataka
	TLine *line1 = new TLine(srednja_data, 0., srednja_data, 0.018);
	line1->Draw();
	TLatex *text=new TLatex(srednja_data,-0.0016,"t_{podaci}");
	text->Draw();
	
	//legenda
	TLegend *legend=new TLegend(0.7,0.8,0.9,0.9);
	legend->AddEntry(Spanjolska, "Spanjolska", "f");
	legend->AddEntry(DrugaDrzava, ime, "f");
	legend->Draw();
	
	c1->SaveAs("Spanjolska_vs_"+ime+".png");
}


