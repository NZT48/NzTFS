#include "file.h"

class KernelFile {
public:

    KernelFile();
    ~KernelFile(); // zatvaranje fajla

    char write(BytesCnt, char* buffer);
    BytesCnt read(BytesCnt, char* buffer);
    char seek(BytesCnt);
    BytesCnt filePos();
    char eof();
    BytesCnt getFileSize();
    char truncate();

private:

    BytesCnt position;
    BytesCnt size;

    int ThreadID;

};
