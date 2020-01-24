KernelFS::KernelFS(){
    openFiles = new std::list<fileElem>();
    partition = nullptr;
}

KernelFS::~KernelFS(){

}

char KernelFS::mount(Partition* partition){
    if(partition == nullptr){
        this->partition = partition;
        return 1;
    } else {
        // Blokira se dok se montirana particija ne odblokira
        return 0;
    }
}

char KernelFS::unmount(){
    if(partition != nullptr){
        // Onaj ko demontira se blokira dok se ne zatvoresvi fajlovi sa date particije
        this->partition = nullptr;
        return 1;
    } else
        return 0;
}

char KernelFS::format(){
    // inicijalizuje bit vektor
    bitVector.reset();
    // buffer sadzri sve nule
    buffer = {0};
    int ret partition->writeCluster(0, buffer);
    // inicjalizuje root direktorijum
    // nit koja formatira se blokira dok se ne zatvore svi fajlovi
}

FileCnt KernelFS::readRootDir(){
    // citanje sadrzaja korenog dir -1 neuspeh
    // uspeh broj fajlova u direktorijumu - ukupan broj fajlova u listi
    int ret = partition->readCluster(1, buffer);
    if(ret == 0 ) return -1;
    else {

    }
}

char KernelFS::doesExist(char* fname){
    // ispitivanje postojanja zadatog fajla
    // 0 neuspeh, 1 uspeh

    // mogao bi da proverim da li ga imam u listi otvorenih
    // ako ne proverim na particiji da li je

}

File* KernelFS::open(char* fname, char mode){
    // otvaranja fajla sa zadatim nazivom
    // vraca pokazivac na objekat otvorenog fajla ili null ako nije uspelo
    // ako je neko drugi otvorio za upis, blokirati dok ga ovaj ne zatvori

    // ucitam u listu otvorenih

    return nullptr;
}

char KernelFS::deleteFile(char* fname){
    // brise pod uslovom da nije OTVOREN
    // 0 neuspeh, 1 - uspeh
    // osloboditi prostor u bit vektoru

}
