#include <iostream>
#include "file.h"
#include "fs.h"
#include "part.h"


using namespace std;

Partition *partition;

int main() {

	cout << "Test started" << endl;

	partition = new Partition((char *)"p1.ini");

	cout << "Kreirana particija" << endl;

	FS::mount(partition);

	cout << "Montirana particija" << endl;


	FS::unmount();

	cout << "Demontirana particija p1" << endl;


	cout << endl;
	cout << "Citanje i ispis jednog klastera" << endl;

	partition->readCluster(0, emptyCluster);
	for (int i = 0; i < 2048; i++) {
		cout << hex << (int)emptyCluster[i] << ',';
	}

	char ende;
	cin >> ende;

	return 0;
}