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

	cout <<  "Montirana particija" << endl; 

	FS::format();

	cout << "Formatirana particija" << endl;

	FS::unmount();

	cout << "Demontirana particija p1" << endl;

	char ende;
	cin >> ende;

	return 0;
}