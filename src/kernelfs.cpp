#pragma once

#include "kernelfs.h"

KernelFS::KernelFS(){
	partition = nullptr;
	bitVector = nullptr;
	formatting = false;
	mutexPart = CreateSemaphore(NULL, 1, 32, NULL);
	mutexOpen = CreateSemaphore(NULL, 1, 32, NULL);
}

KernelFS::~KernelFS(){

}

char KernelFS::mount(Partition* part) {
	wait(mutexPart);
	if (partition == nullptr) {
		partition = part;
		bitVector = new BitVector(partition);
		rootDir = new RootDir(partition);
		oft = new OpenFilesTable();
		return 1;
	}
	else
		return 0;
}

char KernelFS::unmount(){
	if (partition != nullptr) {
		wait(mutexOpen);
		partition = nullptr;
		delete rootDir;
		delete bitVector;
		delete oft;
		signal(mutexPart);
		signal(mutexOpen);
		return 1;
	}
	else {
		signal(mutexPart);
		return 0;
	}
}

char KernelFS::format(){
	wait(mutexOpen);
	formatting = true;
	char emptyCluster[2048];
	int ret = -1;

	// Ciscenje root dira
	rootDir->resetDir();


	// Ciscenje bit vektora
	bitVector->reset();
	char* bitCluster = bitVector->getBitVector();
	ret = partition->writeCluster(0, bitCluster);
	if (ret == 0) {
		signal(mutexOpen);
		return 0;
	}

	// Ciscenje particije
	int numOfClusters = partition->getNumOfClusters();
	memset(emptyCluster, 0, sizeof emptyCluster);
	for (int i = 1; i < numOfClusters; i++) {
		ret = partition->writeCluster(i, emptyCluster);
		if (ret == 0) {
			signal(mutexOpen);
			return 0;
		}
	}
	formatting = false;
	signal(mutexOpen);
	return 1;
}

FileCnt KernelFS::readRootDir(){
	return rootDir->getDirSize();
}

char KernelFS::doesExist(char* fname){
	return rootDir->doesExist(fname);;
}

File* KernelFS::open(char* fname, char mode){
	if (formatting) {
		return nullptr;
	}
	//wait(mutexFS);

	ClusterNo indexOne = 0;
	unsigned long size = 0;


	if (!rootDir->doesExist(fname)) { // Ne postoji u root Diru napravi novi entry sa imenom i novim index clusterom
		if (mode == 'a' || mode == 'r') {
			return 0; // fajl mora postojati da bi se koristili append ili read
		}
		indexOne = bitVector->getFreeCluster();
		rootDir->addEntry(fname, indexOne);
		if (oft->getNumOfOpen() == 0) wait(mutexOpen);
		oft->addOpenFile(fname, mode);

	} else { // Vec postoji u root diru
		if (oft->getNumOfOpen() == 0) wait(mutexOpen);
		oft->addOpenFile(fname, mode);
		indexOne = rootDir->getIndex(fname);
		size = rootDir->getSize(fname);
	}

	File* f = new File();
	f->myImpl = new KernelFile(fname, partition, this, mode, size, indexOne);


	return f;

}

char KernelFS::deleteFile(char* fname){

	ClusterNo indexOne = rootDir->getIndex(fname);
	unsigned long size = rootDir->getSize(fname);

	oft->removeOpenFile(fname);
	rootDir->deleteEntry(fname);

	char cluster[ClusterSize];
	memset(cluster, 0, sizeof cluster);
	char buffTwo[ClusterSize];
	memset(cluster, 0, sizeof buffTwo);
	char buffOne[ClusterSize];
	memset(buffOne, 0, sizeof buffOne);

	partition->readCluster(indexOne, buffOne);
	
	unsigned long position = 0;
	unsigned long inTwo = (unsigned long)floor((position / ClusterSize) % 512);
	unsigned long inOne = (unsigned long)floor(position / (512 * ClusterSize));
	unsigned long nextTwo;
	unsigned long nextOne;
	unsigned long adr, iTwo = 0;

	// Brisanje svih narednih klastera
	for (unsigned long i =0; i < size; i += 2048) {
		nextTwo = (unsigned long)floor((i / ClusterSize) % 512);
		nextOne = (unsigned long)floor(i / (512 * ClusterSize));

		if (nextOne > inOne) {
			inOne = nextOne;
			partition->writeCluster(iTwo, cluster);
			bitVector->releaseCluster(iTwo);
			memcpy(&iTwo, &buffOne[nextOne * 4], sizeof(unsigned long));
			memcpy(&buffOne[nextOne * 4], 0, sizeof(unsigned long));
			partition->readCluster(iTwo, buffTwo);
		}

		memcpy(&adr, &buffTwo[nextTwo * 4], sizeof(unsigned long));
		bitVector->releaseCluster(adr);
		memcpy(&buffTwo[nextTwo * 4], 0, sizeof(unsigned long));
		partition->writeCluster(adr, cluster);
	}

	bitVector->releaseCluster(indexOne);

	return 1;
}
