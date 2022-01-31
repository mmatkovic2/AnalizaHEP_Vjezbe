#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>

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

void Analyzer::PlotHistogram()
{
	TCanvas* c = new TCanvas("c", "c", 1800, 900);
	c->Divide(2);
	
	TH1F* histo1 = new TH1F("histo1", "Transverzalni moment", 100, 0, 150);
	TH1F* histo2 = new TH1F("histo2", "Transverzalni momentum", 100, 0, 150);
	TH1F* histoH = new TH1F("histoH", "Transverzallni moment Higgsa", 100, 0, 150);
	
	TLorentzVector* Higgs = new TLorentzVector();
	
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
		//fillamo histograme transverzalnom kolicinom gibanja		
		histo1->Fill(pt1);
		histo2->Fill(pt2);
		
		//fillamo histogram Higgsa 
		Higgs->SetPxPyPzE(px1+px2, py1+py2, pz1+pz2, E1+E2);
		histoH->Fill(Higgs->Pt());
	}
	
	//prvi canvas
	c->cd(1);
	histo1->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	histo1->GetYaxis()->SetTitle("broj dogadaja N");
	histo1->SetLineColor(kBlue);
	histo1->SetFillColor(kBlue);
	histo1->SetStats(0);
	histo1->Draw();
	
	histo2->SetLineColor(kRed);
	histo2->SetLineWidth(3);
	histo2->Draw("hist same");
	
	TLegend* legend = new TLegend(0.6,0.8,0.9,0.9);
	legend->SetTextSize(0.03);
	legend->AddEntry(histo1,"Cestica raspada 1","f");
	legend->AddEntry(histo2,"Cestica raspada 2","l");
	legend->Draw();
	
	c->cd(2);
	histoH->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	histoH->GetYaxis()->SetTitle("Broj dogadaja N");
	histoH->SetLineColor(kGreen+2);
	histoH->SetFillColor(kGreen+2);
	histoH->SetStats(0);
	histoH->Draw();
	
	TLegend* legendH = new TLegend(0.1,0.8,0.45,0.9);
	legendH->SetTextSize(0.03);
	legendH->AddEntry(histoH, "Rekonstruirani Higgs", "f");
	legendH->Draw();	
	
	c->SaveAs("VJ4.pdf");
	c->SaveAs("VJ4.png");
	c->SaveAs("VJ4.root");
}
