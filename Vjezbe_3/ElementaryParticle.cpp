#include <iostream>
#include <cmath>
#include "ElementaryParticle.h"

using namespace std;

ElementaryParticle::ElementaryParticle(string n, int m, bool b, double p_x, double p_y, double p_z){
		ime = n;
		masa=m;
		jeBozon=b;
		px=p_x;
		py=p_y;
		pz=p_z;
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

void ElementaryParticle::Momentum(double kolx, double koly, double kolz){
	double moment;
	moment = sqrt(kolx*kolx+koly*koly);
	E = sqrt(kolx*kolx+koly+koly+kolz*kolz);
	cout << "Momentum of the particle is:" << moment << endl;
}

ElementaryParticle::ElementaryParticle(){
	ime = "";
	masa = 0.0;
	jeBozon = 0.0;
}

void ElementaryParticle::bosonDecay(ElementaryParticle* c1, ElementaryParticle* c2){
	if (jeBozon==0){
		cout << "Cestica koja se raspada nije boson, raspad nije moguc" << endl;
	}
	if (jeBozon=1){
		cout << "Cestica je bozon" << endl;
	}


}
