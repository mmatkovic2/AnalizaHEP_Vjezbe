#define Analyzer_cxx
#include "Analyzer.h"
#include <TH1F.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <vector>
#include <TLorentzVector.h>
#include <iostream>

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
	TCanvas* c = new TCanvas("c", "c", 1800, 1800);
	c->Divide(2, 2);

	TH1F* h1 = new TH1F("h1", "LepP1", 100, 0, 150);
	TH1F* h2 = new TH1F("h2", "LepP2", 100, 0, 150);
	TH1F* h3 = new TH1F("h3", "LepP3", 100, 0, 150);
	TH1F* h4 = new TH1F("h4", "LepP4", 100, 0, 150);

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
		
		h1->Fill(LepPt->at(2));
		h2->Fill(LepPt->at(3));
		h3->Fill(LepPt->at(0));
		h4->Fill(LepPt->at(1));
		
	}

	//prvi od cetiri kanvasa, cd(1), gornji lijevi, p/noe
	c->cd(1);

	h1->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	h1->GetYaxis()->SetTitle("number of events");
	//h1->SetFillColor(kBlue);
	h1->SetStats(0);
	h1->SetLineColor(kBlue);
	h1->Draw();

	h2->SetLineColor(kRed);
	h2->SetLineWidth(2);
	h2->Draw("hist same");
	
	h3->SetLineColor(kGreen);
	h3->SetLineWidth(2);
	h3->Draw("hist same");
	
	h4->SetLineColor(kBlue);
	h4->SetLineWidth(2);
	h4->Draw("hist same");

	//svaki kanvas ima 4 velicine, h1-h4

	//postavljanje legende
	TLegend* legend = new TLegend(0.6,0.8,0.9,0.9);
	legend->SetTextSize(0.03);
	legend->AddEntry(h1,"Decay lepton 1","f");
	legend->AddEntry(h2,"Decay lepton 2","l");
	legend->AddEntry(h3,"Decay lepton 3","l");
	legend->AddEntry(h4,"Decay lepton 4","l");
	legend->Draw();
	
	c->SaveAs("LeptPt.png");
	
}
