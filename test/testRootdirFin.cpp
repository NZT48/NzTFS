#include <iostream>
#include "file.h"
#include "fs.h"
#include "part.h"
#include "rootdir.h"


using namespace std;

Partition *partition;

int main() {

	cout << "Test started" << endl;

	partition = new Partition((char *)"p1.ini");

	cout << "Kreiran root dir" << endl;

	RootDir *rd = new RootDir(partition);

	rd->resetDir();

	int ret = rd->addEntry("/test.xc", 432);

	if(ret == 1)
		cout << "Uspesno dodat entry test" << endl;
	else
		cout << "Neuspesno dodavanje" << endl;


	ret = rd->addEntry("/pera.pet", 3251);

	if (ret == 1)
		cout << "Uspesno dodat entry pera" << endl;
	else
		cout << "Neuspesno dodavanje" << endl;



	ret = rd->addEntry("/treci.st", 11);

	if (ret == 1)
		cout << "Uspesno dodat entry treci" << endl;
	else
		cout << "Neuspesno dodavanje" << endl;


	ret = rd->doesExist("/pera.pet");
	
	if (ret == 1)
		cout << "Pronadjen fajl sa nazivom /pera" << endl;
	else
		cout << "Nije pronadjen fajl sa nazivom /pera" << endl;

	ret = rd->doesExist("/treci.st");

	if (ret == 1)
		cout << "Pronadjen fajl sa nazivom /treci" << endl;
	else
		cout << "Nije pronadjen fajl sa nazivom /treci" << endl;


	rd->updateEntry("/treci.st", 532);
	if (ret == 1)
		cout << "Uspesno apdejtovan size za treci /treci" << endl;
	else
		cout << "Neuspesno apdejtovan size za /treci" << endl;


	rd->deleteEntry("/test.xc");
	if (ret == 1)
		cout << "Uspesno obrisan test.xc" << endl;
	else
		cout << "Neuspesno obrisan test.xc" << endl;


	ret = rd->doesExist("/test.xc");

	if (ret == 1)
		cout << "Pronadjen fajl sa nazivom test" << endl;
	else
		cout << "Nije pronadjen fajl sa nazivom test" << endl;

	cout << endl;


	delete rd;

	cout << "Direktorijum je obrisan" << endl;

	RootDir *rd2 = new RootDir(partition);

	cout << "Direktorijum je ponovo kreiran i ucitan" << endl;

	ret = rd2->doesExist("/treci.st");

	if (ret == 1)
		cout << "Pronadjen fajl sa nazivom treci.st" << endl;
	else
		cout << "Nije pronadjen fajl sa nazivom treci.st" << endl;

	delete rd2;

	char ende;
	cin >> ende;

	return 0;
}