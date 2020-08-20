#define _CRT_SECURE_NO_WARNINGS

#include <cmath>
#include "kernelfile.h"

KernelFile::KernelFile(char* fnm, Partition *part, KernelFS *kfs, char m, unsigned long sz, ClusterNo index) {
	partition = part;
	fs = kfs;
	mode = m;
	size = sz;
	indexOne = index;
	fname = fnm;

	if (mode == 'w') {
		// Uzmemo adrese za nove klastere
		indexTwo = fs->bitVector->getFreeCluster();
		dataAdr = fs->bitVector->getFreeCluster();

		// Ocistimo lokalne bafere i sacuvajmo pozante adrese
		memset(buffOne, 0, sizeof buffOne);
		memset(buffTwo, 0, sizeof buffTwo);
		memset(buff, 0, sizeof buff);

		position = 0;

	} else if (mode == 'r') {
		partition->readCluster(indexOne, buffOne);
		
		memcpy(&indexTwo, &buffOne, sizeof(unsigned long));
		partition->readCluster(indexTwo, buffTwo);

		memcpy(&dataAdr, &buffTwo[0], sizeof(unsigned long));
		partition->readCluster(dataAdr, buff);

		position = 0;

	}
	else {

		partition->readCluster(indexOne, buffOne);
		memset(buffTwo, 0, sizeof buffTwo);
		memset(buff, 0, sizeof buff);

		unsigned long inTwo = (unsigned long)floor(((size) / ClusterSize) % 512);
		unsigned long inOne = (unsigned long)floor((size) / (512 * ClusterSize));
		position = size;


		memcpy(&indexTwo, &buffOne[inOne * 4], sizeof(unsigned long));
		if (indexTwo == 0) indexTwo = fs->bitVector->getFreeCluster();
		else 
			partition->readCluster(indexTwo, buffTwo);

		memcpy(&dataAdr, &buffTwo[inTwo * 4], sizeof(unsigned long));
		if(dataAdr == 0) dataAdr = fs->bitVector->getFreeCluster();
		else
			partition->readCluster(dataAdr, buff);
	}
}


KernelFile::~KernelFile(){ // zatvara fajl

	fs->rootDir->updateEntry(fname, size);
	fs->oft->removeOpenFile(fname);
	if (fs->oft->getNumOfOpen() == 0) fs->signalOpen();

	if (mode != 'r') {

		unsigned long inTwo = (unsigned long)floor(((position) / ClusterSize) % 512);
		unsigned long inOne = (unsigned long)floor((position) / (512 * ClusterSize));


		memcpy(&buffTwo[inTwo * 4], &dataAdr, sizeof(unsigned long));
		memcpy(&buffOne[inOne * 4], &indexTwo, sizeof(unsigned long));

		partition->writeCluster(indexOne, buffOne);
		partition->writeCluster(indexTwo, buffTwo);
		partition->writeCluster(dataAdr, buff);
	}


}

char KernelFile::write(BytesCnt cnt, char* buffer){
	if (mode == 'r') return 0;
	
	int ret = -1;

	for (unsigned long i = 0; i < cnt; i++) {
		buff[position % ClusterSize] = buffer[i];
		position++;

		if ((position % ClusterSize) == 0) {
			ret = store();
			if (ret == 0) return ret;
		}
	}

	size = position;
	return 1;

}

BytesCnt KernelFile::read(BytesCnt cnt, char* buffer){
	if (mode == 'w' || cnt < 0) { return 0; }

	int ret = -1;
	unsigned long rdCnt = 0;

	for (unsigned long i = 0; i < cnt; i++) {
		buffer[i] = buff[position % ClusterSize];
		position++;
		rdCnt++;

		if (position == size) break;
		if (position % ClusterSize == 0) {
			ret = loadNext();
			if (ret == 0) return ret;
		}

	}

	return rdCnt;
}

char KernelFile::seek(BytesCnt pos){

	unsigned long inOne = (unsigned long)floor((position) / (512 * ClusterSize));
	unsigned long nextTwo = (unsigned long)floor((pos / ClusterSize) % 512);
	unsigned long nextOne = (unsigned long)floor(pos / (512 * ClusterSize));


	if (nextOne != inOne) {
		memcpy(&indexTwo, &buffOne[nextOne * 4], sizeof(unsigned long));
		partition->readCluster(indexTwo, buffTwo);
	}


	memcpy(&dataAdr, &buffTwo[nextTwo * 4], sizeof(unsigned long));
	partition->readCluster(dataAdr, buff);

	position = pos;

	return 1;

}

BytesCnt KernelFile::filePos(){
	return position;
}

char KernelFile::eof(){
	if (position == size) {
		return 2;
	}
	else if (position < size && position >= 0) {
		return 0;
	}
	else
		return 1;
}

BytesCnt KernelFile::getFileSize(){
    return size;
}

char KernelFile::truncate(){
	char cluster[ClusterSize];
	memset(cluster, 0, sizeof cluster);
	unsigned long inTwo = (unsigned long)floor((position / ClusterSize) % 512);
	unsigned long inOne = (unsigned long)floor(position / (512 * ClusterSize));
	unsigned long nextTwo;
	unsigned long nextOne;
	unsigned long adr, iTwo = indexTwo;
	unsigned long zero = 0;


	// Brisanje vrednosti iz tekuceg klastera
	for (unsigned long i = position % 2048; i < 2048; i++) {
		memset(&buff[i], 0, 8);
	}

	// Brisanje svih narednih klastera
	for (unsigned long i = position + (2048 - position%2048); i < size; i += 2048) {
		nextTwo = (unsigned long)floor((i / ClusterSize) % 512);
		nextOne = (unsigned long)floor(i / (512 * ClusterSize));
		
		if (nextOne > inOne) {
			inOne = nextOne;
			partition->writeCluster(iTwo, cluster);
			fs->bitVector->releaseCluster(iTwo);
			memcpy(&iTwo, &buffOne[nextOne * 4], sizeof(unsigned long));
			memcpy(&buffOne[nextOne * 4], &zero, sizeof(unsigned long));
			partition->readCluster(iTwo, buffTwo);
		}

		memcpy(&adr, &buffTwo[nextTwo * 4], sizeof(unsigned long));
		fs->bitVector->releaseCluster(adr);
		memcpy(&buffTwo[nextTwo * 4], &zero,  sizeof(unsigned long));
		partition->writeCluster(adr, cluster);
	}
	
	size = position;
	return 1;

}

int KernelFile::loadNext() {

	unsigned long inOne = (unsigned long)floor((position - 1)/ (512 * ClusterSize));
	unsigned long nextTwo = (unsigned long)floor((position / ClusterSize) % 512);
	unsigned long nextOne = (unsigned long)floor(position / (512 * ClusterSize));

	if (nextOne > inOne) {
		memcpy(&indexTwo, &buffOne[nextOne*4], sizeof(unsigned long));
		partition->readCluster(indexTwo, buffTwo);
	}

	memcpy(&dataAdr, &buffTwo[nextTwo*4], sizeof(unsigned long));
	partition->readCluster(dataAdr, buff);
	
	return 1;
}


int KernelFile::store() {

	unsigned long inTwo = (unsigned long)floor(((position - 1) / ClusterSize) % 512);
	unsigned long inOne = (unsigned long)floor((position - 1) / (512 * ClusterSize));
	unsigned long nextOne = (unsigned long)floor(position / (512 * ClusterSize));

	// Sacuvamo data addr u memoriju i njegovu adresu u bafer 2
	partition->writeCluster(dataAdr, buff);
	memcpy(&buffTwo[inTwo*4], &dataAdr, sizeof(unsigned long));

	// uzmemo novi data adr i postavimo buff za podatke na 0
	dataAdr = fs->bitVector->getFreeCluster();
	memset(buff, 0, sizeof buff);

	// Ako smo dosli do kraja buffera two
	if (nextOne > inOne) {
		memcpy(&buffOne[inOne*4], &indexTwo, sizeof(unsigned long));
		partition->writeCluster(indexTwo, buffTwo);
		indexTwo = fs->bitVector->getFreeCluster();
		memset(buffTwo, 0, sizeof buffTwo);
	}

	return 1;
}