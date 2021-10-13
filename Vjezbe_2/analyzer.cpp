#include <iostream>
#include "ElementaryParticle.h"

using namespace std;

int main()
{
	ElementaryParticle HiggsBoson("Higgs Boson", 125, 1);
	ElementaryParticle upkvark("up kvark", 173, 0);
	ElementaryParticle* Zboson;
	Zboson= new ElementaryParticle("Z Boson", 91, 1);
	

	HiggsBoson.printInfo();
	upkvark.printInfo();
	//ZBoson.printInfo();
	Zboson->printInfo();

	delete Zboson;

	return 0;
}
