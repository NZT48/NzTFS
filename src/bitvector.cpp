#include <iostream>
#include <string>
#include "bitvector.h"

BitVector::BitVector(Partition* part) {

    this->partition = part;
    int ret = partition->readCluster(0, bits);
    if(ret == 0){
        std::cout << "Error: Bit vector not read properly" << std::endl;
        exit(1);
    }
    nextFree = -1;

}

BitVector::~BitVector(){
    int ret = partition->writeCluster(0, bits);
    if(ret == 0){
        std::cout << "Error: Bit vector not write properly" << std::endl;
    }
}

char *BitVector::getBitVector(){
    return bits;
}

ClusterNo BitVector::getFreeCluster() {
	if (formated) formated = false;
	ClusterNo bytenum;
	ClusterNo bitnum;
	int ret = -1;

  if(nextFree == -1){
  	nextFree = 4;
    return 3;
  }

	ret = nextFree;
	bytenum = nextFree / 8;
	bitnum = nextFree % 8;
	bits[bytenum] &= ~(0x1 << bitnum);

	while (!(bits[bytenum] & (0x1 << bitnum))) { // dok ne nadje slobodan bit vrti
		nextFree = (nextFree + 1) % numOfClusters;
		bytenum = nextFree / 8;
		bitnum = nextFree % 8;
  }

	return ret;
}

void BitVector::releaseCluster(ClusterNo bitnum){
  if(bitnum <= numOfClusters && bitnum > 2) {
    ClusterNo bytenum = bitnum / 8;
    bitnum = bitnum % 8;
		bits[bytenum] |= (0x1 << bitnum); // oslobadjanje bita
	}
}


void BitVector::reset(){
	int i = 0;
	// postavlja sve na slobodne klastere
	while(i < ClusterSize){
		bits[i] = (char)0xff;
		i++;
	}

	// postavlja nulti, prvi i drugi klaster na zauzete
	bits[0] = (char)0xf8;
	formated = true;
	nextFree = 3;

}
