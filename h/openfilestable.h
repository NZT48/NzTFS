#pragma once

#include "part.h"
#include "fs.h"
#include "controlrw.h"
#include <list>


typedef struct FCB {
	ControlRW *rw;
	int cnt;
	char mode;
	char name[FNAMELEN];
	FCB() {
		rw = new ControlRW();
		cnt = 0;
	}
} FCB;



class OpenFilesTable {
public:
	
	OpenFilesTable();
	~OpenFilesTable();

	char isOpen(char *fname);
	char addOpenFile(char *fname, char mode);
	char removeOpenFile(char *fname);

	int getNumOfOpen(); 

private:

	int parseName(char *fname, char* &name, char* &ext);

	int numOfOpen;
	std::list<FCB*> files;

};
	