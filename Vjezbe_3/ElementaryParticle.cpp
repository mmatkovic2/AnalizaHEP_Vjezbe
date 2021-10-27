#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "ElementaryParticle.h"

using namespace std;

ElementaryParticle::ElementaryParticle(string n, double m, bool b, double p_x, double p_y, double p_z){
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
		srand(time(0));
		int k, k2, k3, k4;
		k=rand()/1000;
		if(k<214){
			c1->masa=80;
			c2->masa=80;
		}
		if(k>=214 && k<276){
			c1->masa=1.7;
			c2->masa=1.7;
		}
		if(k>=276 && k<302){
			c1->masa=91;
			c2->masa=91;
		}
		if(k>=302){
			c1->masa=4.1;
			c2->masa=.1;
		}
		k2=(rand()%400)-200;
		c1->px=k2;
		c2->px=px-k2;

		k3=(rand()%400)-200;
		c1->px=k3;
		c2->px=py-k3;

		k4=(rand()%400)-200;
		c1->px=k4;
		c2->px=pz-k4;
	}


}
