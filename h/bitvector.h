#pragma once
typedef unsigned long ClusterNo;

#include "part.h"

class BitVector {

public:

	friend class KernelFS;
	friend class KernelFile;

	BitVector(Partition* part);

	~BitVector();

	char* getBitVector();

	ClusterNo getFreeCluster();

	void releaseCluster(ClusterNo);

	void reset();

private:

	ClusterNo nextFree;
	ClusterNo numOfClusters = 16384;
	Partition* partition;

	bool formated = false;
	char bits[2048];

};
