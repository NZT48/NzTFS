#include "openfilestable.h"

OpenFilesTable::OpenFilesTable() {
	numOfOpen = 0;
	files = std::list<FCB *>();
}

OpenFilesTable::~OpenFilesTable() {

}

int OpenFilesTable::getNumOfOpen() {
	return numOfOpen;
}

char OpenFilesTable::isOpen(char *fname) {
	int ret = -1;

	char *name = new char[FNAMELEN]();
	char *ext = new char[FEXTLEN]();
	ret = parseName(fname, name, ext);
	if (ret == 0) return 0;

	for (auto const& i : files) {
		ret = strncmp(i->name, name, 8);
		if (ret == 0)
			return 1;
	}
	return 0;
	

}

char OpenFilesTable::addOpenFile(char *fname, char mode) {
	int ret = -1;

	char *name = new char[FNAMELEN]();
	char *ext = new char[FEXTLEN]();
	ret = parseName(fname, name, ext);
	if (ret == 0) return -1;

	if (!isOpen(fname)) {
		FCB *fcb = new FCB();
		memcpy(&fcb->name, name, FNAMELEN);
		fcb->rw->startRW(mode);
		fcb->mode = mode;
		fcb->cnt = 1;
		numOfOpen++;
		files.push_back(fcb);
	}
	else {
		for (std::list<FCB *>::iterator itd = files.begin(); itd != files.end(); itd++) {
			ret = strncmp((*itd)->name, name, 8);
			if (ret == 0) {
				(*itd)->cnt++;
				(*itd)->rw->startRW(mode);
				return 1;
			}
		}
	}

	return 1;
}


char OpenFilesTable::removeOpenFile(char *fname) {

	int ret = -1;

	char *name = new char[FNAMELEN]();
	char *ext = new char[FEXTLEN]();
	ret = parseName(fname, name, ext);
	if (ret == 0) return -1;


	for (std::list<FCB *>::iterator itd = files.begin(); itd != files.end(); itd++) {
		ret = strncmp((*itd)->name, name, 8);
		if (ret == 0) {
			(*itd)->rw->stopRW((*itd)->mode);
			if (--((*itd)->cnt) == 0) {
				files.erase(itd);
				numOfOpen--;
			}

			return 1;
		}
	}

	return 0;

}

int OpenFilesTable::parseName(char *fname, char* &name, char* &ext) {

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