#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "ElementaryParticle.h"

using namespace std;

int main()
{
	ElementaryParticle HiggsBoson("Higgs Boson", 125, 1, 3.0, 4.0, 5.0);
	ElementaryParticle upkvark("up kvark", 173, 0, 3.0, 4.0, 5.0);
	ElementaryParticle* Zboson;
	Zboson= new ElementaryParticle("Z Boson", 91, 1, 3.0, 4.0, 5.0);
	int i;	

	ElementaryParticle* decayParticle_1;
	decayParticle_1 = new ElementaryParticle();
	ElementaryParticle* decayParticle_2;
	decayParticle_2 = new ElementaryParticle();

	ofstream file ("Analysis.txt");
	file << "px1\tpy1\tpz1\tE1\tpx2\tpy2\tpz2\tE2" << endl;
	for(i=1; i<100; i++){

		srand(time(0));
		int d1, j1, d2, j2, d3, j3;
		d1=(rand()%200)-100;
		j1=rand()/100;
		d2=(rand()%200)-100;
		j2=rand()/100;
		d3=(rand()%200)-100;
		j3=rand()/100;
		HiggsBoson.px=d1+0.01*j1;
		HiggsBoson.py=d2+0.01*j2;
		HiggsBoson.pz=d3+0.01*j3;

		HiggsBoson.bosonDecay(decayParticle_1, decayParticle_2);
		file << decayParticle_1->px << "\t" << decayParticle_1->py << "\t" << decayParticle_1->pz << "\t" << "3\t";
		file << decayParticle_2->px << "\t" << decayParticle_2->py << "\t" << decayParticle_2->pz << "\t" << "3\t" << endl;
	}

	//printamo informacije o imenu i masi cestice
	//HiggsBoson.printInfo();
	upkvark.printInfo();
	//ZBoson.printInfo();
	Zboson->printInfo();

	//zadatak 1 - dajemo vrijednosti kolicine gibanja
	HiggsBoson.Momentum(HiggsBoson.px, HiggsBoson.py, HiggsBoson.pz);
	//zadatak2 - sudar dvije cestice, poziv funkcije bosondecay
	HiggsBoson.bosonDecay(decayParticle_1, decayParticle_2);	

	
	delete Zboson;
	delete decayParticle_1;
	delete decayParticle_2;

	return 0;
}
