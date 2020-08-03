#pragma once

#include "part.h"
#include "fs.h"
#include <list>


typedef struct {
	char fname[FNAMELEN];
	char ext[FEXTLEN];
	char emptySlot;
	ClusterNo indexCluster;
	unsigned long size;
} Entry;



class RootDir {
public:

	RootDir(Partition *part);
	~RootDir();

	FileCnt loadDir();
	char storeDir();
	char resetDir();

	FileCnt getDirSize() {
		return dir.size();
	}

	char doesExist(char* fname);
	char addEntry(char* fname, ClusterNo cluster);
	char updateEntry(char* fname, unsigned long size);
	char deleteEntry(char* fname);

	ClusterNo getIndex(char* fname);
	unsigned long getSize(char* fname);

private:

	int parseName(char *fname, char* &name, char* &ext);

	Partition *partition;
	unsigned long numOfEntries;
	std::list<Entry> dir;

};