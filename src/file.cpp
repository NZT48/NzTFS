#include "file.h"
#include "fs.h"
#include "kernelfile.h"

File::File() {
}

File::~File(){
    delete myImpl;
}

char File::write(BytesCnt Bcnt, char* buffer){
    return myImpl->write(Bcnt, buffer);
}

BytesCnt File::read(BytesCnt Bcnt, char* buffer){
    return myImpl->read(Bcnt, buffer);
}

char File::seek(BytesCnt Bcnt){
    return myImpl->seek(Bcnt);
}

BytesCnt File::filePos(){
    return myImpl->filePos();
}

char File::eof(){
    return myImpl->eof();
}

BytesCnt File::getFileSize(){
    return myImpl->getFileSize();
}

char File::truncate(){
    return myImpl->truncate();
}
