#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

class ElementaryParticle{
	public:
		string ime; 
		double masa;
		bool jeBozon;
		double px, py, pz, E;
		
		ElementaryParticle(string n, double m, bool b, double p_x, double p_y, double p_z);
		void printInfo();
		void Momentum(double kolx, double koly, double kolz);
		ElementaryParticle();
		void bosonDecay(ElementaryParticle* c1, ElementaryParticle* c2);

};
