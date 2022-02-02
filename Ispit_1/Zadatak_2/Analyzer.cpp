#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <TLegend.h>
#include <TGraph.h>

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

void Analyzer::LoopPozadina(){
	Init(background);

	histoB1 = new TH1F("histoB1", "Transverzalni Moment", 280, 0, 140);
	//vrtimo petlju za filanje podataka iz patha Background
	if (fChain == 0) return;


   	Long64_t nentries = fChain->GetEntriesFast();

   	Long64_t nbytes = 0, nb = 0;
   	for (Long64_t jentry=0; jentry<nentries;jentry++) {
      		Long64_t ientry = LoadTree(jentry);
      		if (ientry < 0) break;
      		nb = fChain->GetEntry(jentry);   nbytes += nb;
      		// if (Cut(ientry) < 0) continue;
		histoB1->Fill(ele_pt);
		histo2D->Fill(ele_pt, ele_pt);
   	}
}

void Analyzer::LoopSignal(){
	Init(signal);

	histoS1 = new TH1F("histoS1", "Transverzalni moment", 280, 0, 140);
	//vrtimo petlju za filanje podataka iz patha Background
	if (fChain == 0) return;

   	Long64_t nentries = fChain->GetEntriesFast();

   	Long64_t nbytes = 0, nb = 0;
   	for (Long64_t jentry=0; jentry<nentries;jentry++) {
      		Long64_t ientry = LoadTree(jentry);
      		if (ientry < 0) break;
      		nb = fChain->GetEntry(jentry);   nbytes += nb;
      		// if (Cut(ientry) < 0) continue;
		histoS1->Fill(ele_pt);
		histo2D->Fill(ele_pt, ele_pt);
   	}
}

void Analyzer::HistogramPlot(){
	//stvaramo canvas
	TCanvas* c = new TCanvas("c", "c", 1600, 900);
	c->Divide(2);
	c->cd(1);

	gPad->SetLeftMargin(0.15);	
	
	histoB1->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	histoB1->GetYaxis()->SetTitle("broj dogadaja");
	histoB1->SetStats(0);
	histoB1->SetLineColor(kBlue);
	histoB1->Draw();

	histoS1->SetLineColor(kRed);
	histoS1->Draw("same");

	c->cd(2);
	histo2D->GetXaxis()->SetTitle("p_{T} signalni (GeV/c)");
	histo2D->GetYaxis()->SetTitle("p_{T} background (GeV/c)");
	histo2D->SetStats(0);
	histo2D->Draw("COLZ");

	

	c->SaveAs("Zadatak2_ispit.png");

}
