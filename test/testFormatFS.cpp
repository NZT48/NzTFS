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

	char res = FS::format();

	cout << "Formatirana particija sa rezultatom " << res << endl;

	FS::unmount();

	cout << "Demontirana particija p1" << endl;

	cout << "Test memset funkcije" << endl;

	// Ciscenje particije
	int numOfClusters = partition->getNumOfClusters();
	char emptyCluster[2048];
	memset(emptyCluster, 0, sizeof emptyCluster);
	for (int i = 0; i < 2048; i++) {
		cout << hex << (int)emptyCluster[i] << ',';
	}

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