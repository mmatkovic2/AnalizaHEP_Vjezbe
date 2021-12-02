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
#include <THStack.h>
#include <TString.h>

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

void Analyzer::PlotHistogram(TString path){
	
	//dio kopiran iz h filea da se moze lakse mijenjat path
	TTree *tree = new TTree;
	
	TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(path);
	if (!f || !f->IsOpen())
		f = new TFile(path);
	TDirectory * dir = (TDirectory*)f->Get(path+":/ZZTree");
	dir->GetObject("candTree",tree);
	Init(tree);
	
	/*
	//zadatak1
	//crtamo dva odvojena platna, kopirani kod iz vj6zad2
	TCanvas* c = new TCanvas("c", "c", 2400, 1800);
	c->Divide(2,2);
	
	TH1F* histo11 = new TH1F("histo11", "Transversal Momentum", 200, 0, 150);
	TH1F* histo12 = new TH1F("histo12", "", 200, 0, 150);
	TH1F* histo13 = new TH1F("histo13", "", 200, 0, 150);
	TH1F* histo14 = new TH1F("histo14", "", 200, 0, 150);

	TH1F* histo21 = new TH1F("histo21", "Pseudorapidity", 100, -5, 5);
	TH1F* histo22 = new TH1F("histo22", "", 100, -5, 5);
	TH1F* histo23 = new TH1F("histo23", "", 100, -5, 5);
	TH1F* histo24 = new TH1F("histo24", "", 100, -5, 5);

	TH1F* histo31 = new TH1F("histo31", "Azimuth Angle", 100, -5, 5);
	TH1F* histo32 = new TH1F("histo32", "", 100, -5, 5);
	TH1F* histo33 = new TH1F("histo33", "", 100, -5, 5);
	TH1F* histo34 = new TH1F("histo34", "", 100, -5, 5);

	TH1F* histo41 = new TH1F("histo41", "Boosted Decision Tree", 40, 0, 10);
	TH1F* histo42 = new TH1F("histo42", "", 40, 0, 10);
	TH1F* histo43 = new TH1F("histo43", "", 40, 0, 10);
	TH1F* histo44 = new TH1F("histo44", "", 40, 0, 10);
	
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
		
		histo11->Fill(LepPt->at(2));
		histo12->Fill(LepPt->at(3));
		histo13->Fill(LepPt->at(0));
		histo14->Fill(LepPt->at(1));

		histo21->Fill(LepEta->at(2));
		histo22->Fill(LepEta->at(3));
		histo23->Fill(LepEta->at(0));
		histo24->Fill(LepEta->at(1));

		histo31->Fill(LepPhi->at(2));
		histo32->Fill(LepPhi->at(3));
		histo33->Fill(LepPhi->at(0));
		histo34->Fill(LepPhi->at(1));

		histo41->Fill(LepBDT->at(2));
		histo42->Fill(LepBDT->at(3));
		histo43->Fill(LepBDT->at(0));
		histo44->Fill(LepBDT->at(1));
	}
	
	c->cd(1);		// LepPt //----------------------------------------------------
	
	gPad->SetLeftMargin(0.15);
	
	histo11->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	histo11->GetYaxis()->SetTitle("no. of events");
	histo11->SetStats(0);
	histo11->SetLineColor(kGreen);
	histo11->SetLineWidth(4);
	histo11->Draw();
	
	histo12->SetLineColor(kRed);
	histo12->SetLineWidth(2);
	histo12->Draw("hist same");
	
	histo13->SetLineColor(kOrange);
	histo13->SetLineWidth(4);
	histo13->Draw("hist same");
	
	histo14->SetLineColor(kBlue);
	histo14->SetLineWidth(2);
	histo14->Draw("hist same");
	
	TLegend* legend1 = new TLegend(0.7,0.7,0.9,0.9);
	legend1->SetTextSize(0.03);
	legend1->AddEntry(histo11,"Decay lepton 1","l");
	legend1->AddEntry(histo12,"Decay lepton 2","l");
	legend1->AddEntry(histo13,"Decay lepton 3","l");
	legend1->AddEntry(histo14,"Decay lepton 4","l");
	legend1->Draw();

	c->cd(2);		// LepEta //----------------------------------------------------
	
	gPad->SetLeftMargin(0.15);
	
	histo21->GetXaxis()->SetTitle("#eta");
	histo21->GetYaxis()->SetTitle("no. of events");
	histo21->SetStats(0);
	histo21->SetLineColor(kGreen);
	histo21->SetLineWidth(4);
	histo21->Draw();
	
	histo22->SetLineColor(kRed);
	histo22->SetLineWidth(2);
	histo22->Draw("hist same");
	
	histo23->SetLineColor(kOrange);
	histo23->SetLineWidth(4);
	histo23->Draw("hist same");
	
	histo24->SetLineColor(kBlue);
	histo24->SetLineWidth(2);
	histo24->Draw("hist same");
	
	TLegend* legend2 = new TLegend(0.7,0.7,0.9,0.9);
	legend2->SetTextSize(0.03);
	legend2->AddEntry(histo21,"Decay lepton 1","l");
	legend2->AddEntry(histo22,"Decay lepton 2","l");
	legend2->AddEntry(histo23,"Decay lepton 3","l");
	legend2->AddEntry(histo24,"Decay lepton 4","l");
	legend2->Draw();
	
	c->cd(3);		// LepPhi //----------------------------------------------------
	
	gPad->SetLeftMargin(0.15);
	
	histo31->GetXaxis()->SetTitle("#phi (rad)");
	histo31->GetYaxis()->SetTitle("no. of events");
	histo31->SetStats(0);
	histo31->SetLineColor(kGreen);
	histo31->SetLineWidth(4);
	histo31->Draw();
	
	histo32->SetLineColor(kRed);
	histo32->SetLineWidth(2);
	histo32->Draw("hist same");
	
	histo33->SetLineColor(kOrange);
	histo33->SetLineWidth(4);
	histo33->Draw("hist same");
	
	histo34->SetLineColor(kBlue);
	histo34->SetLineWidth(2);
	histo34->Draw("hist same");
	
	TLegend* legend3 = new TLegend(0.7,0.7,0.9,0.9);
	legend3->SetTextSize(0.03);
	legend3->AddEntry(histo31,"Decay lepton 1","l");
	legend3->AddEntry(histo32,"Decay lepton 2","l");
	legend3->AddEntry(histo33,"Decay lepton 3","l");
	legend3->AddEntry(histo34,"Decay lepton 4","l");
	legend3->Draw();
	
	c->cd(4);		// LepBDT //----------------------------------------------------
	
	gPad->SetLeftMargin(0.15);

	histo41->GetXaxis()->SetTitle("BDT");
	histo41->GetYaxis()->SetTitle("no. of events");
	histo41->SetStats(0);
	histo41->SetLineColor(kGreen);
	histo41->SetLineWidth(4);
	histo41->Draw();
	
	histo42->SetLineColor(kRed);
	histo42->SetLineWidth(2);
	histo42->Draw("hist same");
	
	histo43->SetLineColor(kOrange);
	histo43->SetLineWidth(4);
	histo43->Draw("hist same");
	
	histo44->SetLineColor(kBlue);
	histo44->SetLineWidth(2);
	histo44->Draw("hist same");
	
	TLegend* legend4 = new TLegend(0.7,0.7,0.9,0.9);
	legend4->SetTextSize(0.03);
	legend4->AddEntry(histo41,"Decay lepton 1","l");
	legend4->AddEntry(histo42,"Decay lepton 2","l");
	legend4->AddEntry(histo43,"Decay lepton 3","l");
	legend4->AddEntry(histo44,"Decay lepton 4","l");
	legend4->Draw();
	
	c->SaveAs("Leptons_"+name+".png");
	*/
	
	/*
	//Zadatak2 - kopiran iz vjezbi6 zad 3 i modificiran
	TLorentzVector* lep1 = new TLorentzVector();
	TLorentzVector* lep2 = new TLorentzVector();
	TLorentzVector* lep3 = new TLorentzVector();
	TLorentzVector* lep4 = new TLorentzVector();
	TLorentzVector* Z1 = new TLorentzVector();
	TLorentzVector* Z2 = new TLorentzVector();
	TLorentzVector* Higgs = new TLorentzVector();
	
	TFile z2("/home/public/data/"+name+"/ZZ4lAnalysis.root"); 
	TH1F* histoCounter = (TH1F*)z2.Get("ZZTree/Counters");
	
	double w, contentbin;
	
	TCanvas* c = new TCanvas("c", "c", 900, 900);
	THStack* hs = new THStack("hs","Reconstructed mass");
	
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
		
		lep1->SetPtEtaPhiM(LepPt->at(0), LepEta->at(0), LepPhi->at(0), 0.0);
		lep2->SetPtEtaPhiM(LepPt->at(1), LepEta->at(1), LepPhi->at(1), 0.0);
		lep3->SetPtEtaPhiM(LepPt->at(2), LepEta->at(2), LepPhi->at(2), 0.0);
		lep4->SetPtEtaPhiM(LepPt->at(3), LepEta->at(3), LepPhi->at(3), 0.0);
			
		*Z1 = *lep1 + *lep2;
		*Z2 = *lep3 + *lep4;
		*Higgs = *Z1 + *Z2;
		
		contentbin = histoCounter->GetBinContent(40);
		w = (137.0 * 1000.0 * xsec * overallEventWeight) / contentbin;
		
		if(name == "ggH125")
			h1->Fill(Higgs->M(),w);
		else if(name == "qqZZ")
			h2->Fill(Higgs->M(),w);
	}
	
	gPad->SetLeftMargin(0.15);
	
	h2->GetXaxis()->SetTitle("m_{4l} (GeV)");
	h2->GetYaxis()->SetTitle("Events / 2GeV");
	h2->SetStats(0);
	h2->SetLineColor(kBlue);
	h2->SetFillColor(kBlue);
	hs->Add(h2);
	
	h1->GetXaxis()->SetTitle("m_{4l} (GeV)");
	h1->GetYaxis()->SetTitle("Events / 2GeV");
	h1->SetStats(0);
	h1->SetLineColor(kRed);
	h1->SetFillColor(kRed);
	hs->Add(h1);
	
	hs->Draw("hist");
	hs->GetXaxis()->SetTitle("m_{4l} (GeV)");
	hs->GetYaxis()->SetTitle("Events / 2GeV");
	
	TLegend* legend = new TLegend(0.7,0.8,0.9,0.9);
	legend->SetTextSize(0.03);
	legend->AddEntry(h1,"Signal","f");
	legend->AddEntry(h2,"Background","f");
	legend->Draw();
	
	c->SaveAs("CMSComparison.png");
	*/


	//zadatak3
	TLorentzVector* lep1 = new TLorentzVector();
	TLorentzVector* lep2 = new TLorentzVector();
	TLorentzVector* lep3 = new TLorentzVector();
	TLorentzVector* lep4 = new TLorentzVector();
	TLorentzVector* Z1 = new TLorentzVector();
	TLorentzVector* Z2 = new TLorentzVector();
	TLorentzVector* Higgs = new TLorentzVector();

	TFile* fnew = new TFile(path); 
	TH1F* histoCounter = (TH1F*)fnew->Get("ZZTree/Counters");

	double w, contentbin;
	double sigDiscriminant;
	double bcgDiscriminant;
	double constant = 70.0;

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
		
		lep1->SetPtEtaPhiM(LepPt->at(0), LepEta->at(0), LepPhi->at(0), 0.0);
		lep2->SetPtEtaPhiM(LepPt->at(1), LepEta->at(1), LepPhi->at(1), 0.0);
		lep3->SetPtEtaPhiM(LepPt->at(2), LepEta->at(2), LepPhi->at(2), 0.0);
		lep4->SetPtEtaPhiM(LepPt->at(3), LepEta->at(3), LepPhi->at(3), 0.0);

		*Z1 = *lep1 + *lep2;
		*Z2 = *lep3 + *lep4;
		*Higgs = *Z1 + *Z2;
		
		contentbin = histoCounter->GetBinContent(40);
		w = (137.0 * 1000.0 * xsec * overallEventWeight) / contentbin;
		
		if(path.Contains("ggH125"))
		{
			sigDiscriminant = 1 / (1 + p_QQB_BKG_MCFM / p_GG_SIG_ghg2_1_ghz1_1_JHUGen);
			histoSignal->Fill(sigDiscriminant,w);
		}
		else if(path.Contains("qqZZ"))
		{
			bcgDiscriminant = 1 / (1 + constant * p_QQB_BKG_MCFM / p_GG_SIG_ghg2_1_ghz1_1_JHUGen);
			histoBackground->Fill(bcgDiscriminant,w);
		}
	}
}


void Analyzer::Drawing()
{
	TCanvas* c = new TCanvas("c", "c", 900, 900);
	c->Divide(2,2);
	
	gPad->SetLeftMargin(0.15);
	
	c->cd(1);		// KinematicDiscriminant
	
	histoSignal->Scale(1.0/histoSignal->Integral());
	histoSignal->GetXaxis()->SetTitle("D_{kin}");
	histoSignal->GetYaxis()->SetTitle("Events / 0.02");
	histoSignal->GetYaxis()->SetRangeUser(0, 1);
	histoSignal->SetStats(0);
	histoSignal->SetLineColor(kRed);
	histoSignal->SetLineWidth(3);
	histoSignal->Draw("hist");
											
	histoBackground->Scale(1.0/histoBackground->Integral());
	histoBackground->GetXaxis()->SetTitle("D_{kin}");
	histoBackground->GetYaxis()->SetTitle("Events / 0.02");
	histoBackground->GetYaxis()->SetRangeUser(0, 1);
	histoBackground->SetStats(0);
	histoBackground->SetLineColor(kBlue);
	histoBackground->SetLineWidth(3);
	histoBackground->Draw("hist same");
	
	TLegend* legend = new TLegend(0.7,0.8,0.9,0.9);
	legend->SetTextSize(0.03);
	legend->AddEntry(histoSignal,"Signal","l");
	legend->AddEntry(histoBackground,"Background","l");
	legend->Draw();
	
	
	c->SaveAs("Diskriminator.png");
}





