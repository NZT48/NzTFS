#include <iostream>
#include "file.h"
#include "fs.h"
#include "part.h"
#include "openfilestable.h"


using namespace std;

Partition *partition;

int main() {

	cout << "Kreirana tabela" << endl;

	OpenFilesTable *rd = new OpenFilesTable();

	int ret = rd->addOpenFile("/test.xc", 432, 'r');

	if(ret == 1)
		cout << "Uspesno dodat entry test" << endl;
	else
		cout << "Neuspesno dodavanje" << endl;


	ret = rd->addOpenFile("/pera.pet", 3251, 'w');

	if (ret == 1)
		cout << "Uspesno dodat entry pera" << endl;
	else
		cout << "Neuspesno dodavanje" << endl;



	ret = rd->addOpenFile("/treci.st", 11, 's');

	if (ret == 1)
		cout << "Uspesno dodat entry treci" << endl;
	else
		cout << "Neuspesno dodavanje" << endl;


	ret = rd->isOpen("/test.xc");
	
	if (ret == 1)
		cout << "Pronadjen fajl sa nazivom /test" << endl;
	else
		cout << "Nije pronadjen fajl sa nazivom /test" << endl;

	ret = rd->isOpen("/treci.st");

	if (ret == 1)
		cout << "Pronadjen fajl sa nazivom /treci" << endl;
	else
		cout << "Nije pronadjen fajl sa nazivom /treci" << endl;



	ret = rd->removeOpenFile("/test.xc");
	if (ret == 1)
		cout << "Uspesno obrisan test.xc" << endl;
	else
		cout << "Neuspesno obrisan test.xc" << endl;


	ret = rd->isOpen("/test.xc");

	if (ret == 1)
		cout << "Pronadjen fajl sa nazivom test" << endl;
	else
		cout << "Nije pronadjen fajl sa nazivom test" << endl;

	cout << endl;


	delete rd;

	cout << "Direktorijum je obrisan" << endl;

	OpenFilesTable *rd2 = new OpenFilesTable();

	cout << "Direktorijum je ponovo kreiran i ucitan" << endl;

	ret = rd2->isOpen("/treci.st");

	if (ret == 1)
		cout << "Pronadjen fajl sa nazivom treci.st" << endl;
	else
		cout << "Nije pronadjen fajl sa nazivom treci.st" << endl;

	delete rd2;

	char ende;
	cin >> ende;

	return 0;
}