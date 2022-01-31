#define Analyzer_cxx
#include "Analyzer.h"
#include<TH1F.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <TLegend.h>
#include <TGraph.h>

#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Tools.h"

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
   	}
}

void Analyzer::HistogramPlot(){
	//stvaramo canvas
	TCanvas* c = new TCanvas("c", "c", 900, 900);
	c->Divide(2,4);
	c->cd(1);

	gPad->SetLeftMargin(0.15);	
	
	histoB1->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	histoB1->GetYaxis()->SetTitle("broj dogadaja");
	histoB1->SetStats(0);
	histoB1->SetLineColor(kBlue);
	histoB1->Draw();

	histoS1->SetLineColor(kRed);
	histoS1->Draw("same");



	c->SaveAs("8_Distribucija.png");

}

void Analyzer::MVATraining(){
   TString outfileName( "TMVA.root" );
   TFile* outputFile = TFile::Open( outfileName, "RECREATE" );
   
   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile, "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );
   TMVA::DataLoader *dataloader = new TMVA::DataLoader("dataset");
   
   // Add variables //
   dataloader->AddVariable( "ele_pt", 'F' );
   dataloader->AddVariable( "ele_fbrem", 'F' );
   dataloader->AddVariable( "ele_ep", 'F' );
   dataloader->AddVariable( "ele_pfChargedHadIso", 'F' );
   dataloader->AddVariable( "ele_eelepout", 'F' );
   dataloader->AddVariable( "ele_gsfchi2", 'F' );

   
   // global event weights per tree (see below for setting event-wise weights)
   Double_t signalWeight     = 1.0;
   Double_t backgroundWeight = 1.0;
   
   // You can add an arbitrary number of signal or background trees
   dataloader->AddSignalTree( signal, signalWeight );
   dataloader->AddBackgroundTree( background, backgroundWeight );
   
   // Apply additional cuts on the signal and background samples (possibly not needed)
   TCut mycuts = ""; // for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
   TCut mycutb = ""; // for example: TCut mycutb = "abs(var1)<0.5";
   
   dataloader->PrepareTrainingAndTestTree( mycuts, mycutb, "nTrain_Signal=1000:nTrain_Background=1000:SplitMode=Random:NormMode=NumEvents:!V" );
   
   // Chose MVA method //
   //if (Use["BDT"])
   factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDT", "!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );
   
   // Train MVAs using the set of training events
   factory->TrainAllMethods();
   // Evaluate all MVAs using the set of test events
   factory->TestAllMethods();
   // Evaluate and compare performance of all configured MVAs
   factory->EvaluateAllMethods();
   
   // Save the output
   outputFile->Close();
   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVAClassification is done!" << std::endl;
   delete factory;
   delete dataloader;
}

void Analyzer::MVAPlot(){
   TFile* f = new TFile("TMVA.root");

    TGraph* graf_signal;
    TGraph* graf_pozadina;
    graf_signal = (TGraph*)f->Get("dataset/Method_BDT/BDT/MVA_BDT_S");
    graf_pozadina = (TGraph*)f->Get("dataset/Method_BDT/BDT/MVA_BDT_B");

    TH1F* histogram;
    histogram = (TH1F*)f->Get("dataset/Method_BDT/BDT/MVA_BDT_effBvsS");

    TCanvas* c = new TCanvas("c", "c", 1800, 900);
    c->Divide(2);
    gStyle->SetOptStat(0);

    c->cd(1);				
    graf_signal->SetTitle("Distribution of MVA results (BDT)");
    graf_signal->SetLineColor(kBlue);
    graf_pozadina->SetLineColor(kRed);
    graf_signal->Draw();
    graf_pozadina->Draw("same");

    TLegend* legenda = new TLegend(0.8, 0.82, 0.95, 0.92);
    legenda->AddEntry(graf_signal, "Signal", "l");
    legenda->AddEntry(graf_pozadina, "Background", "l");
    legenda->Draw();

    c->cd(2);				
    histogram->SetLineColor(kRed);
    cout << "Za 90 posto signalnih elektrona: " << histogram->Interpolate(0.9) * 100.0 << "%" << endl;
    histogram->Draw();
	
    c->SaveAs("MVA_BDT_zad4.png");
}
