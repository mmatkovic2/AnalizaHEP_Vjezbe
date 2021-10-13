#include <iostream>

using namespace std;

class ElementaryParticle{
	public:
		string ime; 
		int masa;
		bool jeBozon;
		
		ElementaryParticle(string n, int m, bool b);
		void printInfo();

};

