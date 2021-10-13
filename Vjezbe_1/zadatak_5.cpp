#include <iostream>

using namespace std;

float mycube (double k)
{
	double cube;
	cube=k*k*k;
	return cube;
}

int main()
{
	// uvodni dio
	cout << "Hello World!" << endl;
	
	//definiranje varijabli 	
	double a;
	double kub;	

	//unos varijabli
	cout << "Upisi realan broj r: ";
	cin >> a;

	//racunanje kuba, i ispis u sljedecem redu
	kub = mycube(a);
	cout << endl;
	cout << "Vrijednost kuba unesenog broja je: " << kub; 
	return 0;
}
