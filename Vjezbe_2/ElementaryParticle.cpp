#include <iostream>
#include "ElementaryParticle.h"

using namespace std;

ElementaryParticle::ElementaryParticle(string n, int m, bool b){
		ime = n;
		masa=m;
		jeBozon=b;
}
void ElementaryParticle::printInfo(){
	cout << "Paricle name:" << ime << endl;			
	cout << "Particle mass:" << masa << endl;
	cout << "Particle boson:" << endl;
	if (jeBozon==1)
		cout << "yes" << endl;
	else
		cout << "no" << endl;
}


