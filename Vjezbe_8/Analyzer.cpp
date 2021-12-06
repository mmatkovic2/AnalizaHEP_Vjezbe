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

void Analyzer::PlotHistogram(TString name){
	
	//dio kopiran iz h filea da se moze lakse mijenjat path, samo ime upisujemo
	TTree *tree = new TTree;
	
	TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/public/data/"+name+"/ZZ4lAnalysis.root");
	if (!f || !f->IsOpen())
		f = new TFile("/home/public/data/"+name+"/ZZ4lAnalysis.root");
	TDirectory * dir = (TDirectory*)f->Get("/home/public/data/"+name+"/ZZ4lAnalysis.root:/ZZTree");
	dir->GetObject("candTree",tree);
	Init(tree);
	
	//Zadatak 1 i zadatak 2 zajednicki dio
	//ponovno stvaramo vektore klase Lorentzvektor, za nase cestice
	TLorentzVector* lepton1 = new TLorentzVector();
	TLorentzVector* lepton2 = new TLorentzVector();
	TLorentzVector* lepton3 = new TLorentzVector();
	TLorentzVector* lepton4 = new TLorentzVector();
	TLorentzVector* Z1 = new TLorentzVector();
	TLorentzVector* Z2 = new TLorentzVector();
	TLorentzVector* Higgs = new TLorentzVector();
	//otvaramo file
	TFile fw("/home/public/data/"+name+"/ZZ4lAnalysis.root"); 
	TH1F* histoCounter = (TH1F*)fw.Get("ZZTree/Counters");
	//koristenje objekata klase TF1, generiramo funkcije iz zad 1 s parametrima A B C D M G
	//za zad 2 samo mijenjamo parametre i njihova imena za novu max like funkciju

	/* 
	//zadatak 1 	
	funcQ->SetParNames("A", "B", "C");
	funcBW->SetParNames("D", "#Gamma", "M");
	funcQBW->SetParNames("A", "B", "C", "D", "#Gamma", "M");
	funcQ->SetParameters(9.57, -0.1262, 0.0004926);
	funcBW->SetParameters(2580.0, 820.3, 124.6);
	funcQBW->SetParameters(9.57, -0.1262, 0.0004926, 2580.0, 820.3, 124.6);
	*/

	//zadatak 2
	funcMaxLike->SetParNames("A", "B", "C", "D_{Higgs}", "#Gamma_{Higgs}", "M_{Higgs}", "D_{Z}", "#Gamma_{Z}", "M_{Z}");
	funcMaxLike->SetParameters(-2.789, 0.04629, -0.0001112, 2720.0, 866.4, 124.5, 4737.0, 737.3, 90.83);

	//kopiramo dio iz prethodnih vjezbi
	double w, contentbin;
	
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
		// if (Cut(ientry) < 0) continue;
		
		lepton1->SetPtEtaPhiM(LepPt->at(0), LepEta->at(0), LepPhi->at(0), 0.0);
		lepton2->SetPtEtaPhiM(LepPt->at(1), LepEta->at(1), LepPhi->at(1), 0.0);
		lepton3->SetPtEtaPhiM(LepPt->at(2), LepEta->at(2), LepPhi->at(2), 0.0);
		lepton4->SetPtEtaPhiM(LepPt->at(3), LepEta->at(3), LepPhi->at(3), 0.0);
			
		*Z1 = *lepton1 + *lepton2;
		*Z2 = *lepton3 + *lepton4;
		*Higgs = *Z1 + *Z2;
		
		contentbin = histoCounter->GetBinContent(40);
		w = (137.0 * 1000.0 * xsec * overallEventWeight) / contentbin;
		
		if(name == "ggH125")
			histoSignal->Fill(Higgs->M(),w);
		else if(name == "qqZZ")
			histoBackground->Fill(Higgs->M(),w);
	}
}


void Analyzer::Drawing()
{
	TCanvas* c = new TCanvas("c", "c", 1800, 900);
	
	/*
	//Zad 1, dijeljenje canvasa na dva dijela
	c->Divide(2); //dijelimo canvas na lijevi i desni dio
	
	gPad->SetLeftMargin(0.15);
	gStyle->SetOptFit();

	c->cd(1);		// Lijevi dio, funkcije teorijskog modela
	
	funcQBW->SetTitle("Theoretical model; M (GeV); Events"); //crtamo
	funcQBW->SetLineColor(kRed); //teorijski 
	funcQBW->Draw(); //model
	funcQ->SetLineColor(kGreen); //po formuli
	funcQ->Draw("same"); //zadatka
	funcBW->SetLineColor(kBlue);
	funcBW->Draw("same");	

	TLegend* legend = new TLegend(0.5,0.8,0.9,0.9); //dodajemo legendu
	legend->SetTextSize(0.03);
	legend->AddEntry(funcQ,"Background Q","l");
	legend->AddEntry(funcBW,"Breit Wigner signal","l");
	legend->AddEntry(funcQBW,"Background + signal","l");
	legend->Draw();

	c->cd(2);	//desni dio canvasa, nas eksperimentalni fit, prethodne vjezbe	
	histoBackground->SetLineColor(kGreen);
	histoSignal->SetLineColor(kBlue);
	histoSignal->Add(histoBackground);
	
	histoSignal->Draw("p E1 X0");
	histoSignal->SetTitle("Reconstructed mass; M (GeV); Events");
	histoSignal->Fit(funcQBW);

	//c->SaveAs("Z1-Teorijski-eksp.png");
	*/


	//Zad 2, samo jedan canvas
	gPad->SetLeftMargin(0.15);
	gStyle->SetOptFit();
	
	funcMaxLike->SetLineColor(kGreen);
	funcMaxLike->Draw();

	histoSignal->SetLineColor(kRed);
	histoSignal->Add(histoBackground);
	
	histoSignal->SetTitle("Reconstructed mass; M (GeV); Events");
	histoSignal->Draw("p E1 X0");
	histoSignal->Fit(funcMaxLike);
	
	c->SaveAs("Z2MaxLike.png");
}





