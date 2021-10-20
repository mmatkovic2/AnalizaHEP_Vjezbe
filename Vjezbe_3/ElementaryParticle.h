#include <iostream>
#include <cmath>

using namespace std;

class ElementaryParticle{
	public:
		string ime; 
		int masa;
		bool jeBozon;
		double px, py, pz, E;
		
		ElementaryParticle(string n, int m, bool b, double p_x, double p_y, double p_z);
		void printInfo();
		void Momentum(double kolx, double koly, double kolz);
		ElementaryParticle();
		void bosonDecay(ElementaryParticle* c1, ElementaryParticle* c2);

};
