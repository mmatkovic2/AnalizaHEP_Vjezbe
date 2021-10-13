#include <iostream>

using namespace std;

class ElementaryParticle{
	public:
		string ime; 
		int masa;
		bool jeBozon;
		
		ElementaryParticle(string n, int m, bool b){
			ime = n;
			masa=m;
			jeBozon=b;
		}
		void printInfo(){
			cout << "Paricle name:" << ime << endl;
			cout << "Particle mass:" << masa << endl;
			cout << "Particle boson:" << endl;
			if (jeBozon==1)
				cout << "yes" << endl;
			else
				cout << "no" << endl;
		}

};

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
