#pragma once

#include "file.h"
#include "part.h"
#include "fs.h"
#include "kernelfs.h"


class KernelFile {
public:

	KernelFile(char *fname, Partition *partition, KernelFS *kfs, char mode, unsigned long size, ClusterNo indexOne);

    ~KernelFile(); // zatvaranje fajla

    char write(BytesCnt, char* buffer);

    BytesCnt read(BytesCnt, char* buffer);

    char seek(BytesCnt);

    BytesCnt filePos();

    char eof();

    BytesCnt getFileSize();

    char truncate();

private:

	int loadNext();
	int store();

	BytesCnt position;
	BytesCnt size;

	ClusterNo indexOne;
	ClusterNo indexTwo;
	ClusterNo dataAdr;
	
	char buffOne[ClusterSize];
	char buffTwo[ClusterSize];
	char buff[ClusterSize];

	char mode;
	char *fname;

	Partition *partition;
	KernelFS *fs;


	friend class KernelFS;

};
