#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "ElementaryParticle.h"

using namespace std;

//buduci je ovaj kod, radi brzine, kopiran sa prethodnih vjezbi, konstruktor se zove elementary particle a ne calculus. Ideja je ista, samo bi na preimenovanje svega i uredivanje makefilea trosio vrijeme pa je ostavljeno ovako

ElementaryParticle::ElementaryParticle(){
		cout << "Objekt uspjesno kreiran!" << endl;
}

void ElementaryParticle::CalculateIntegral(int N, double a, double b){
		
	srand(time(NULL));
	double broj1, broj2, decimala;
	double funkcijab, funkcijaa;
	double povrsina, postotak;	
	int counter=0;
	if(a>0.6666 || b<0.0)
	{
		for(int i=0; i<N; i++)
		{
			//generiramo brojeve 0 do f(b), y koordinata broja ;
			do {
			funkcijab = 3*b*b-2*b;
			broj1=rand()%10000;
			decimala=rand()%100;
			broj1=broj1+0.01*decimala;
			} while(broj1>funkcijab);

			//funkcijab;
			//generiramo brojeve a do b, x koordinata broja
			broj2=rand()/b-rand()/a;
			do {
			funkcijaa = 3*a*a-2*a;
			broj2=rand()%10000;
			decimala=rand()%100;
			broj2=broj2+0.01*decimala;
			} while(broj2>b || broj2<a);

			if (broj1 > broj2*broj2*3-2*broj2){
				counter++;
			}
			cout << counter << endl;
		}	
	}

	postotak=counter/100000.0;
	cout << postotak << endl;
	if (a>0.6666)
	{
		povrsina = (b-a)*(3*b*b-2*b)*(1-postotak);
	}

	if (b<0.0)
	{
		povrsina = (a-b)*(3*a*a-2*a*(-1))*(1-postotak);
	}
	cout << "Vrijednost integrala u granicama " << a << " do " << b << " je: " << povrsina << endl; 

	
}

