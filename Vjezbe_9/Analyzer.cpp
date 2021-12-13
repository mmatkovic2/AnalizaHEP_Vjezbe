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
#include <iostream>
#include <THStack.h>
#include <TString.h>
#include <TF1.h>
#include <cmath>

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
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}

void Analyzer::PlotHistogram(){
	
	TTree *tree = new TTree;
	TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/public/data/Lifetime/Lifetime.root");
	if (!f || !f->IsOpen()) {
        	f = new TFile("/home/public/data/Lifetime/Lifetime.root");
      	}
      	f->GetObject("Tree",tree);
	Init(tree);

	double tsuma, tau;
	//zadajemo parametre fita za zadatak 1
	//za zadatak2 ovo zakomentiramo
	//funcfita->SetParNames("N_{0}","#tau");
	//funcfita->SetParameters(100, 1);
	
	if (fChain == 0)
		return;
	Long64_t nentries = fChain->GetEntriesFast();
	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++)
	{
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0)
			break;
		nb = fChain->GetEntry(jentry);
		nbytes += nb;
		
		histoPodaci->Fill(t);
		tsuma += t;
	}
	tau = 1.0* tsuma / nentries;
	cout << "#tau = " << tau << endl;
}

void Analyzer::Drawing()
{
	TCanvas* c = new TCanvas("c", "c", 900, 900);
	
	gPad->SetLeftMargin(0.15);
	gStyle->SetOptFit();

	/*
	//za Zad1 imamo ovo, za zad2 u komentar stavljeno
	histoPodaci->SetLineColor(kRed);
	histoPodaci->SetTitle("Decay; t (s); number of atoms");
	histoPodaci->Draw("p E1 X0");
	histoPodaci->Fit(funcfita);
	*/

	//zad 4
	funcLN->SetLineColor(kRed);
	funcLN->SetTitle("Log likelihood; #tau (s); -2ln(L)");
	funcLN->Draw();
	//trazimo minimum ove funkcije sada, odnosno tocku x gdje se postize minimum
	cout << "Minimum funkcije likelihood je na polozaju tau = " << funcLN->GetMinimumX() << endl;

	//zad 5
	//imamo 3 vrijednosti Tau 
	//Tau za zad1 nastao fitanjem: Tau1=1.152+-0.041
	//Tau za zad3 nastao minimiziranjem -2lnL funkcije: Tau3=1.23506
	//Tau za zad4 nastao traženjem minimuma na grafu: Tau4=1.23506 

	//sigmu za max likelihood metodu (graf, zad 4) trazimo uz pomoc predavanja 8
	double yMin = funcLN->GetMinimum(); //trazimo koliki je minimum -2ln(L)
    	double x1 = funcLN->GetX(yMin + 1.0, 1.0, funcLN->GetMinimumX() - 0.0001); //trazimo x-eve
    	double x2 = funcLN->GetX(yMin + 1.0, funcLN->GetMinimumX() + 0.0001, 1.5); //gdje imamo y=min+1
	//sigma je samo razlika tau i x1 i x2	
	double sig1 = funcLN->GetMinimumX() - x1;
	double sig2 = x2 - funcLN->GetMinimumX();
	//ispis
	cout << "Sigma1 je:" << sig1 << endl;
	cout << "Sigma2 je:" << sig2 << endl;
	//rezultati ispisa su: sigma1 = 0.0382465; sigma2= 0.0398937
	//dakle, Tau4=1.235 +0.039 -0.038	
	

	c->SaveAs("Zadatak5lnL.png");
}
