#include "bitvector.h"
#include <iostream>

using namespace std;

int main() {

  BitVector *bv = new BitVector();

  bv->reset();


  /* Test za popunjen bit vektor */

  int cluster = bv->getFreeCluster();
  cout << cluster << endl;

  for(int i = 0; i < 17000; i++) {
    cluster = bv->getFreeCluster();
    if(cluster % 2355 == 0){
      bv->releaseCluster(cluster);
    }
  }
  cout << "end of getting" << endl;
  cout << bv->getFreeCluster() << endl;
  cout << bv->getFreeCluster() << endl;
  cout << bv->getFreeCluster() << endl;
  cout << bv->getFreeCluster() << endl;
  cout << bv->getFreeCluster() << endl;
  cout << bv->getFreeCluster() << endl;


  /* Test za ispisivanje bit vektora */

  bv->reset();

  cout << "Getting couple clusters" << endl;
  for(int i = 0; i < 2400; i++) {
    if(i % 140 == 0){
      cout <<  bv->getFreeCluster() << endl;
    }
  }

  cout << "Printing out bit vector" << endl;
  char *myBits = bv->getBitVector();
  for(int i = 0; i < 2048; i++ ){
    cout <<  hex << (int)myBits[i] << ',';
  }



  return 0;

}
