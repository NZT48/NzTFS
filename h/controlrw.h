#pragma once

#include <Windows.h>

#define signal(x) ReleaseSemaphore(x,1,NULL)
#define wait(x) WaitForSingleObject(x,INFINITE)

class ControlRW {
public:

	ControlRW();
	~ControlRW();

	void startRW(char mode);
	void stopRW(char mode);

	void startRead();
	void stopRead();
	void startWrite();
	void stopWrite();

private:

	HANDLE rw, freeToWrite;
	int numR, numOfThreads;
	HANDLE freeToDel;

};