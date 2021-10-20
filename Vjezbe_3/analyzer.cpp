#include <iostream>
#include <cmath>
#include "ElementaryParticle.h"

using namespace std;

int main()
{
	ElementaryParticle HiggsBoson("Higgs Boson", 125, 1, 3.0, 4.0, 5.0);
	ElementaryParticle upkvark("up kvark", 173, 0, 3.0, 4.0, 5.0);
	ElementaryParticle* Zboson;
	Zboson= new ElementaryParticle("Z Boson", 91, 1, 3.0, 4.0, 5.0);
	
	ElementaryParticle* decayParticle_1;
	decayParticle_1 = new ElementaryParticle();
	ElementaryParticle* decayParticle_2;
	decayParticle_2 = new ElementaryParticle();


	//printamo informacije o imenu i masi cestice
	HiggsBoson.printInfo();
	upkvark.printInfo();
	//ZBoson.printInfo();
	Zboson->printInfo();

	//zadatak 1 - dajemo vrijednosti kolicine gibanja
	HiggsBoson.Momentum(HiggsBoson.px, HiggsBoson.py, HiggsBoson.pz);
	//zadatak2 - sudar dvije cestice, poziv funkcije bosondecay
	HiggsBoson.bosonDecay(decayParticle_1, decayParticle_2);	

	
	delete Zboson;

	return 0;
}
