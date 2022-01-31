#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "Analyzer.h"

using namespace std;

void Analyzer::ReadFile(){
	
	ifstream fin ("Analysis.txt");

	string line;
	bool _skipFirstLine = true;

	if(fin.is_open()){
		while(getline(fin, line)){
			stringstream linestream(line);

			if(_skipFirstLine){
				_skipFirstLine=false;					
				continue;
			}
			
			linestream >> px1 >> py1 >> pz1 >> E1 >> px2 >> py2 >> pz2 >> E2;
		}
	}	

	fin.close();	
}

void Analyzer::ConvertTxtToRootFile(){
	bool skip = true;
	string line;
	//string name1, name2;
	double pt1, pt2;
	ifstream input ("Analysis.txt");

	TFile* output = output = TFile::Open("Analysis.root", "RECREATE"); //TFile::Open(name, option);  
	TTree* tree = new TTree("tree", "Converting .txt to .root"); //TTree tree (name, title); Tree -> columnar dataset; TTree consists of a list of independent columns (branches, TBranch class)

	//Branch(name, address, string describing the leaf list); leaf: name/type
	
	//tree->Branch("name1", &name1, "name1/S"); 
	tree->Branch("E1", &E1, "E1/D");
	tree->Branch("px1", &px1, "px1/D");
	tree->Branch("py1", &py1, "py1/D");
	tree->Branch("pz1", &pz1, "pz1/D");
	tree->Branch("pt1", &pt1, "pt1/D");
	//tree->Branch("name2", &name2, "name2/S");
	tree->Branch("E2", &E2, "E2/D");
	tree->Branch("px2", &px2, "px2/D");
	tree->Branch("py2", &py2, "py2/D");
	tree->Branch("pz2", &pz2, "pz2/D");
	tree->Branch("pt2", &pt2, "pt2/D");
	
	while(getline(input, line))
	{
		if(skip)
		{
			skip = false;
			continue;
		}
		stringstream linestream(line);
		linestream >> px1 >> py1 >> pz1 >> E1 >> px2 >> py2 >> pz2 >> E2;
		pt1 = sqrt(px1*px1 + py1*py1);
		pt2 = sqrt(px2*px2+py2*py2);
		tree->Fill();
	}

	tree->Print();
	tree->Write();
	input.close();
	delete output;
	
	
}

