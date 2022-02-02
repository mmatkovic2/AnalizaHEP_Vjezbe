#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "ElementaryParticle.h"

using namespace std;

int main()
{
	ElementaryParticle* objekt;
	objekt = new ElementaryParticle();

	//1 slucaj
	//objekt->CalculateIntegral(100000, 1.0, 3.0); 
	// za 10 000 dogadaja, rezultat je 17.8, za 100 000 rezultat je 18.06, analiticki je 	rezultat integrala 18, vidi se kako vecim brojem konvergira tocnom rjesenju
	
	//2 slucaj
	//objekt->CalculateIntegral(100000, 2.0, 6.0);
	// za 10 000 dogadaja rezultat integrala je 172.3, za 100 000 je rezultat 175.68, analiticki je 176, opet konvergira povecnjem broja dogadaja

	//3 slucaj
	objekt->CalculateIntegral(100000, 3.0, 7.0);	
	//za 10 000 dogadaja rezultat je 274.31, za 100000 276.54. tocno rjesenje je upravo 276	
	return 0;
}
