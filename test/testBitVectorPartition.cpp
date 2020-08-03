#include <iostream>
#include "part.h"
#include "bitvector.h"


using namespace std;

Partition *partition;

int main() {
	cout << "Test started" << endl;

	partition = new Partition((char *)"p1.ini");

	cout << "Kreirana particija" << endl;

	BitVector *bv = new BitVector(partition);

	bv->reset();


	cout << "Getting couple clusters" << endl;
	for(int i = 0; i < 2400; i++) {
		if(i % 140 == 0){
			cout <<  bv->getFreeCluster() << endl;
		}
	}

	cout << "Printing out bit vector" << endl;
	char *myBits = bv->getBitVector();
	for(int i = 0; i < 2048; i++ ){
		cout <<  hex << (int)myBits[i] << ',';
	}


	cout << "Cuvanje bit vektora" << endl;

	delete bv;

	cout << "Citanje bit vektora sa diska" << endl;

	BitVector *nbv = new BitVector(partition);

	nbv->releaseCluster(6);

	cout << "Ispisivanje ponovo ucitanog bit vektora" << endl;

	myBits = nbv->getBitVector();
	for (int i = 0; i < 500; i++) {
		cout << hex << (int)myBits[i] << ',';
	}

	char ende;
	cin >> ende;

	return 0;
}