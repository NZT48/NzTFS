#pragma once

#include "fs.h"
#include "bitvector.h"
#include "file.h"
#include "kernelfile.h"
#include "rootdir.h"
#include "openfilestable.h"
#include <windows.h>
#include <iostream>

#define signal(x) ReleaseSemaphore(x,1,NULL)
#define wait(x) WaitForSingleObject(x,INFINITE)

class KernelFS {
public:

    KernelFS();
    ~KernelFS();

    char mount(Partition* part); // montira particiju
    //vraca 0 u slucaju neuspeha ili 1 u slucaju uspeha

    char unmount(); // demontira particiju
    //vraca 0 u slucaju neuspeha ili 1 u slucaju uspeha

    char format(); // formatira particiju
    //vraca 0 u slucaju neuspeha ili 1 u slucaju uspeha

    FileCnt readRootDir();
    // vraca -1 u slucaju neuspeha ili broj fajlova u slucaju uspeha

    char doesExist(char* fname); // argument je naziv fajla sa apsolutnom putanjom

    File* open(char* fname, char mode);

    char deleteFile(char* fname);


private:

	void signalOpen() { signal(mutexOpen); }

	Partition *partition;
	BitVector *bitVector;
	RootDir *rootDir;
	OpenFilesTable *oft;

	bool formatting;

	HANDLE mutexPart;
	HANDLE mutexOpen;

    friend class KernelFile;

};
