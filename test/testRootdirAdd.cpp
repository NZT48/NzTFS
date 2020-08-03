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

	Entry *ent = new Entry();
	char fname1[FNAMELEN] = "/test";
	char ext1[FEXTLEN] = "tx";
	unsigned long index1 = 42142;
	unsigned long size1 = 241;

	memcpy(&ent->fname, &fname1, sizeof(fname1));
	memcpy(&ent->ext, &ext1, sizeof(ext1));
	memcpy(&ent->indexCluster, &index1, sizeof(index1));
	memcpy(&ent->size, &size1, sizeof(size1));

	int ret = rd->addEntry(ent);

	if(ret == 1)
		cout << "Uspesno dodat entry test" << endl;
	else
		cout << "Neuspesno dodavanje" << endl;


	Entry *ent2 = new Entry();
	char fname2[FNAMELEN] = "/pera";
	char ext2[FEXTLEN] = "tx";
	index1 = 3341;
	size1 = 2431;

	memcpy(&ent2->fname, &fname2, sizeof(fname1));
	memcpy(&ent2->ext, &ext2, sizeof(ext1));
	memcpy(&ent2->indexCluster, &index1, sizeof(index1));
	memcpy(&ent2->size, &size1, sizeof(size1));

	ret = rd->addEntry(ent2);

	if (ret == 1)
		cout << "Uspesno dodat entry pera" << endl;
	else
		cout << "Neuspesno dodavanje" << endl;


	Entry *ent3 = new Entry();
	char fname3[FNAMELEN] = "/treci";
	char ext3[FEXTLEN] = "st";
	index1 = 4214442;
	size1 = 1;

	memcpy(&ent3->fname, &fname3, sizeof(fname1));
	memcpy(&ent3->ext, &ext3, sizeof(ext1));
	memcpy(&ent3->indexCluster, &index1, sizeof(index1));
	memcpy(&ent3->size, &size1, sizeof(size1));

	ret = rd->addEntry(ent3);

	if (ret == 1)
		cout << "Uspesno dodat entry treci" << endl;
	else
		cout << "Neuspesno dodavanje" << endl;


	ret = rd->doesExist("/pera");
	
	if (ret == 1)
		cout << "Pronadjen fajl sa nazivom /pera" << endl;
	else
		cout << "Nije pronadjen fajl sa nazivom /pera" << endl;

	ret = rd->doesExist("/treci");

	if (ret == 1)
		cout << "Pronadjen fajl sa nazivom /treci" << endl;
	else
		cout << "Nije pronadjen fajl sa nazivom /treci" << endl;

	rd->storeDir();

	cout << "Direktorijum je sacuvan" << endl;

	rd->resetDir();

	cout << "Direktorijum je resetovan" << endl;

	ret = rd->doesExist("/test");

	if (ret == 1)
		cout << "Pronadjen fajl sa nazivom test" << endl;
	else
		cout << "Nije pronadjen fajl sa nazivom test" << endl;

	cout << endl;

	rd->loadDir();

	cout << "Direktorijum je ucitan" << endl;

	ret = rd->doesExist("/test");

	if (ret == 1)
		cout << "Pronadjen fajl sa nazivom test" << endl;
	else
		cout << "Nije pronadjen fajl sa nazivom test" << endl;

	char ende;
	cin >> ende;

	return 0;
}