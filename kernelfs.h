#include "fs.h"

class KernelFS {
public:

    KernelFS();
    ~KernelFS();

    static char mount(Partition* partition); // montira particiju
    //vraca 0 u slucaju neuspeha ili 1 u slucaju uspeha

    static char unmount(); // demontira particiju
    //vraca 0 u slucaju neuspeha ili 1 u slucaju uspeha

    static char format(); // formatira particiju
    //vraca 0 u slucaju neuspeha ili 1 u slucaju uspeha

    static FileCnt readRootDir();
    // vraca -1 u slucaju neuspeha ili broj fajlova u slucaju uspeha

    static char doesExist(char* fname); // argument je naziv fajla sa apsolutnom putanjom

    static File* open(char* fname, char mode);

    static char deleteFile(char* fname);

private:

    struct fileElem {
        char *fname;
        char mode;
        ClusterNo firstCluster;
        BytesCnt size;
        int numOfReaders;
        int numOfWriters;
    }

    // Ili ovo iznad samo zamenim sa listom fajlova - File klase

    std::list<fileElem> openFiles;
    Char[ClusterSize] bufffer;
    Partition* partition;
    std::bitset<16384> bitVector;


    friend class KernelFile;


};
