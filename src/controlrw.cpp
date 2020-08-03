#include "controlrw.h"


void ControlRW::startRW(char mode) {
	if (mode == 'a' || mode == 'w') {
		startWrite();
	}
	else {
		startRead();
	}
}

void ControlRW::stopRW(char mode) {
	if (mode == 'a' || mode == 'w') {
		stopWrite();
	}
	else {
		stopRead();
	}
}


ControlRW::ControlRW() {
	rw = CreateSemaphore(NULL, 1, 10, NULL);
	freeToDel = CreateSemaphore(NULL, 0, 1, NULL);
	numR = 0;
	numOfThreads = 0;
}

ControlRW::~ControlRW() {
	CloseHandle(rw);
	CloseHandle(freeToDel);
}


void ControlRW::startRead() {
	if (++numR == 1)
		wait(rw);
	numOfThreads++;
}

void ControlRW::stopRead() {
	numOfThreads--;
	if (--numR == 0)
		signal(rw);
}

void ControlRW::startWrite() {
	wait(rw);
	numOfThreads++;
}

void ControlRW::stopWrite() {
	numOfThreads--;
	signal(rw);
}
