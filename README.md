# NzTFS

#### File system implemented as a project for university course Operating systems 2
* File system properties:
	* Written in C++ 
	* Two level indexed allocation 
	* Bit vector for free space management
	* Multithreaded access supported

### Useful links:
-------------
* [Operating systems class website](http://os.etf.bg.ac.rs/)

### Structure of project:

```bash
.
├── files_for_test
│   ├── Napomena.txt
│   ├── Ulaz 0.5MB.jpg
│   ├── Ulaz 2MB.jpg
│   ├── ulaz 80KB.jpg
│   └── ulaz.txt
├── h
│   ├── bitvector.h
│   ├── controlrw.h
│   ├── file.h
│   ├── fs.h
│   ├── kernelfile.h
│   ├── kernelfs.h
│   ├── openfilestable.h
│   └── rootdir.h
├── partition
│   ├── part.h
│   ├── particija.lib
│   └── uputstvo_za_rad_sa_particijom.txt
├── public_test
│   ├── main.cpp
│   ├── nit1.cpp
│   ├── nit2.cpp
│   └── testprimer.h
├── README.md
├── resources
│   ├── disk1.dat
│   └── p1.ini
├── src
│   ├── bitvector.cpp
│   ├── controlrw.cpp
│   ├── file.cpp
│   ├── fs.cpp
│   ├── kernelfile.cpp
│   ├── kernelfs.cpp
│   ├── openfilestable.cpp
│   └── rootdir.cpp
└── test
    ├── testBasicDelete.cpp
    ├── testBasicRW.cpp
    ├── testBasicSeek.cpp
    ├── testBasicTruncate.cpp
    ├── testBitVector.cpp
    ├── testBitVectorPartition.cpp
    ├── testFormatFS.cpp
    ├── testOftFirst.cpp
    ├── testRootdirAdd.cpp
    ├── testRootdirFin.cpp
    ├── testRootdirLdSt.cpp
    ├── testSingleThread.cpp
    ├── testStruct.cpp
    └── testTemplate.cpp

```