KernelFile::KernelFile(){

}

KernelFile::~KernelFile(){ // zatvara fajl
    // fajl se oslobadja za koriscenje od stran drugih niti

}

char KernelFile::write(BytesCnt cnt, char* buffer){
    // Upis u tekucu poziciju pos, zadati broj bajtova cnt
    // fajl se prosiruje upisom na kraj fajla ukoliko nije dostignuta max velicina
    // postition se pomera na kraj fajla
    // 0 - neuspeh, 1 - uspeh
}

BytesCnt KernelFile::read(BytesCnt cnt, char* buffer){
    // citanje sa tekuce pozicije, zadati broj bajtova cnt
    // tekuca pozicija se pomera na kraj procitanog dela
    // 0 - fajl zatvoren ili pozicija bila na kraju fajla
    // >0 - broj procitanih bajtova, cak i ako je manje procitano
}

char KernelFile::seek(BytesCnt pos){
    // pomeranje trekuce pozicije u fajlu
    // pozicija se racuna po rednom broju bajta u fajlu
    // zadaje se nova apsolutna pozicija
    // 1 - uspeh , 0 - neuspeh
}

BytesCnt KernelFile::filePos(){
    return position;
}

char KernelFile::eof(){
    // 0 - position nije na kraju fajla
    // 1 - greska
    // 2 - jeste na kraju fajla
}

BytesCnt KernelFile::getFileSize(){
    return size;
}

char KernelFile::truncate(){
    // brisanje od tekuce pozicije do kraja
    // 0 - neuspeh ili 1 uspeh
}
