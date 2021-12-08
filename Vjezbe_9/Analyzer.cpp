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
	}
	
}

void Analyzer::Drawing()
{
	TCanvas* c = new TCanvas("c", "c", 900, 900);
	
	gPad->SetLeftMargin(0.15);
	gStyle->SetOptFit();

	funcfita->SetLineColor(kGreen);
	funcfita->SetTitle("Decay - maxlikelihood; #tau (s); N_a");
	funcfita->Draw();
	
	/*
	//za Zad1 imamo ovo, za zad2 u komentar stavljeno
	histoPodaci->SetLineColor(kRed);
	histoPodaci->SetTitle("Decay; t (s); number of atoms");
	histoPodaci->Draw("p E1 X0");
	histoPodaci->Fit(funcfita);
	*/

	c->SaveAs("Zadatak1Distribucija.png");
}
