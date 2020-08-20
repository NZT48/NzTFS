#include "rootdir.h"


RootDir::RootDir(Partition *part) {
	partition = part;
	dir = std::list<Entry>();
	numOfEntries = 0;
	loadDir();
}

RootDir::~RootDir() {
	storeDir();
	partition = nullptr;
	numOfEntries = 0;
	dir.clear();
}

FileCnt RootDir::loadDir() {
	char bufferOne[2048];
	char bufferEntries[2048];

	partition->readCluster(1, bufferOne);
	// Citamo prvo broj fajlova koji cuvamo kao prvi info u root diru
	memcpy(&numOfEntries, &bufferOne, sizeof(unsigned long));

	partition->readCluster(2, bufferEntries);

	if (numOfEntries != 0) {
		int j = 0; // iterator za prelazak sa jednog ulaza na drugi
		for (unsigned int i = 0; i < numOfEntries; i++) {
			Entry* ent = new Entry();
			memcpy(ent, &bufferEntries[j], 20 * sizeof(char));
			j += 32;
			dir.push_back(*ent);
		}
		numOfEntries = dir.size();
		return dir.size();
	} else
		return -1; // vraca u slucaju neuspeha
}

char RootDir::storeDir() {
	char bufferOne[2048];
	memset(bufferOne, 0, sizeof bufferOne);
	char bufferEntries[2048];
	memset(bufferEntries, 0, sizeof bufferEntries);

	// Cuvamo broj fajlova i pokazivac na klaster sa ulazima
	unsigned long ent2 = 2;
	memcpy(&bufferOne, &numOfEntries, sizeof(unsigned long));
	memcpy(&bufferOne, &ent2, sizeof(unsigned long));
	partition->writeCluster(1, bufferOne);

	//Cuvamo sve ulaze u fajlove u ovaj klaster
	if (numOfEntries != 0) {
		int j = 0; // iterator za prelazak sa jednog ulaza na drugi
		for (std::list<Entry>::iterator itd = dir.begin(); itd != dir.end(); itd++) {
			memcpy(&bufferEntries[j], &(*itd), 8 * sizeof(unsigned long));
			j += 32;
		}
	}
	else {
		//memset buffer entries sa nulama
		memset(bufferEntries, 0, sizeof bufferEntries);
	}
	partition->writeCluster(2, bufferEntries);

	return 1;
}

char RootDir::addEntry(char *fname, ClusterNo cluster) {
	
	char *name = new char[FNAMELEN]();
	char *ext = new char[FEXTLEN]();
	int ret = parseName(fname, name, ext);
	if (ret == 0) return 0;
	unsigned long size = 0;

	Entry *ent = new Entry();

	memcpy(&ent->fname, name, FNAMELEN);
	memcpy(&ent->ext, ext, FEXTLEN);
	memcpy(&ent->indexCluster, &cluster, sizeof(cluster));
	memcpy(&ent->size, &size, sizeof(size));

	numOfEntries++;
	dir.push_back(*ent);
	return 1;
}
 
char RootDir::doesExist(char* fname) {
	int ret = -1;

	char *name = new char[FNAMELEN]();
	char *ext = new char[FEXTLEN]();
	ret = parseName(fname, name, ext);
	if (ret == 0) return -1;


	for (auto const& i : dir) {
		ret = strncmp(i.fname, name, 8);
		if (ret == 0)
			return 1;
	}

	return 0;
}

char RootDir::resetDir() {
	numOfEntries = 0;
	dir.clear();
	return 1;
}

char RootDir::updateEntry(char* fname, unsigned long size) {
	int ret = -1;

	char *name = new char[FNAMELEN]();
	char *ext = new char[FEXTLEN]();
	ret = parseName(fname, name, ext);
	if (ret == 0) return 0;

	for (std::list<Entry>::iterator itd = dir.begin(); itd != dir.end(); itd++) {
		ret = strncmp(itd->fname, name,8);
		if (ret == 0) {
			itd->size = size;
			return 1;
		}
	}

	return 0;
}

char RootDir::deleteEntry(char* fname) {
	int ret = -1;

	char *name = new char[FNAMELEN]();
	char *ext = new char[FEXTLEN]();
	ret = parseName(fname, name, ext);
	if (ret == 0) return 0;

	for (std::list<Entry>::iterator itd = dir.begin(); itd != dir.end(); itd++) {
		ret = strncmp(itd->fname, name, 8);
		if (ret == 0) {
			dir.erase(itd);
			numOfEntries--;
			return 1;
		}
	}

	return 0;
}

ClusterNo RootDir::getIndex(char *fname) {
	int ret = -1;

	char *name = new char[FNAMELEN]();
	char *ext = new char[FEXTLEN]();
	ret = parseName(fname, name, ext);
	if (ret == 0) return 0;

	for (std::list<Entry>::iterator itd = dir.begin(); itd != dir.end(); itd++) {
		ret = strncmp(itd->fname, name, 8);
		if (ret == 0) {
			return itd->indexCluster;
		}
	}

	return -1;
}

unsigned long RootDir::getSize(char *fname) {
	int ret = -1;

	char *name = new char[FNAMELEN]();
	char *ext = new char[FEXTLEN]();
	ret = parseName(fname, name, ext);
	if (ret == 0) return 0;

	for (std::list<Entry>::iterator itd = dir.begin(); itd != dir.end(); itd++) {
		ret = strncmp(itd->fname, name, 8);
		if (ret == 0) {
			return itd->size;
		}
	}

	return -1;
}


int RootDir::parseName(char *fname, char* &name, char* &ext) {

	if (strlen(fname) > 15) {
		return 0;
	}

	int i = 0, j = 0;

	for (; fname[i] != '.' && j < 8; i++, j++) {
		name[j] = fname[i];
	}

	while (j < 8) {
		name[j] = ' ';
		j++;
	}
	name[j] = '\0';

	i++;

	for (j = 0; j < 3; i++, j++)
		ext[j] = fname[i];

	ext[j] = '\0';

	return 1;

}
