#define _CRT_SECURE_NO_WARNINGS

#include"fs.h"
#include"file.h"
#include"part.h"

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<windows.h>
#include<ctime>

using namespace std;

Partition *partition;

char *ulazBuffer;
int ulazSize;

static char threadName1[] = "Nit1";
static char threadName2[] = "Nit2";



int main() {


	{
		FILE *f = fopen("ulaz.dat", "rb");
		if (f == 0) {
			cout << "GRESKA: Nije nadjen ulazni fajl 'ulaz.dat' u os domacinu!" << endl;
			system("PAUSE");
			return 0;//exit program
		}
		ulazBuffer = new char[32 * 1024 * 1024];
		ulazSize = fread(ulazBuffer, 1, 32 * 1024 * 1024, f);
		fclose(f);
	}


	partition = new Partition((char *)"p1.ini");

	cout << "Kreirana particija" << endl;

	FS::mount(partition);

	cout << " Montirana particija" << endl;

	FS::format();

	cout << " Formatirana particija" << endl;

	{
		char filepath[] = "/fajl1.dat";
		File *f = FS::open(filepath, 'w');
		cout << " Kreiran fajl '" << filepath << "'" << endl;
		f->write(ulazSize, ulazBuffer);
		cout << "Prepisan sadrzaj 'ulaz.dat' u '" << filepath << "'" << endl;
		delete f;
		cout << "zatvoren fajl '" << filepath << "'" << endl;
	}


	{
		File *src, *dst;
		char filepath[] = "/fajl1.dat";
		src = FS::open(filepath, 'r');
		src->seek(src->getFileSize() / 2);//pozicionira se na pola fajla
		cout << threadName1 << ": Otvoren fajl '" << filepath << "' i pozicionirani smo na polovini" << endl; 
		char filepath1[] = "/fajll5.dat";
		dst = FS::open(filepath1, 'w');
		cout << threadName1 << ": Otvoren fajl '" << filepath1 << "'" << endl;
		char c;
		while (!src->eof()) {
			src->read(1, &c);
			dst->write(1, &c);
		}
		cout << threadName1 << ": Prepisana druga polovina '" << filepath << "' u '" << filepath1 << "'" << endl; 
		delete dst;
		cout << threadName1 << ": Zatvoren fajl '" << filepath1 << "'" << endl; 
		delete src;
		 cout << threadName1 << ": Zatvoren fajl '" << filepath << "'" << endl; 
	}

	{
		File *src, *dst;
		char filepath[] = "/fajl1.dat";
		while ((src = FS::open(filepath, 'r')) == 0) {
			cout << threadName2 << ":Neuspesno otvoren fajl '" << filepath << "'" << endl;
			Sleep(1); // Ceka 1 milisekundu
		}
		cout << threadName2 << ": Otvoren fajl '" << filepath << "'" << endl; 
		char filepath1[] = "/fajl2.dat";
		dst = FS::open(filepath1, 'w');
		cout << threadName2 << ": Otvoren fajl '" << filepath1 << "'" << endl;
		char c;
		while (!src->eof()) {
			src->read(1, &c);
			dst->write(1, &c);
		}
		cout << threadName2 << ": Prepisan fajl '" << filepath << "' u '" << filepath1 << "'" << endl; 
		delete dst;
		cout << threadName2 << ": Zatvoren fajl '" << filepath1 << "'" << endl;
		delete src;
		cout << threadName2 << ": Zatvoren fajl '" << filepath << "'" << endl; 

	}


	{
		char filepath[] = "/fajl2.dat";
		File *f = FS::open(filepath, 'r');
		cout << threadName2 << ": Otvoren fajl " << filepath << "" << endl;
		delete f;
		cout << threadName2 << ": Zatvoren fajl " << filepath << "" << endl;
	}

	{
		char filepath[] = "/fajl2.dat";
		File *f = FS::open(filepath, 'r');
		cout << threadName2 << ": Otvoren fajl " << filepath << "" << endl;
		ofstream fout("izlaz1.dat", ios::out | ios::binary);
		char *buff = new char[f->getFileSize()];
		f->read(f->getFileSize(), buff);
		fout.write(buff, f->getFileSize());
		cout << threadName2 << ": Upisan '" << filepath << "' u fajl os domacina 'izlaz1.dat'" << endl;
		delete[] buff;
		fout.close();
		delete f;
		cout << threadName2 << ": Zatvoren fajl " << filepath << "" << endl;
	}

	{
		char copied_filepath[] = "/fajll5.dat";
		File *copy = FS::open(copied_filepath, 'r');
		BytesCnt size = copy->getFileSize();
		 cout << threadName2 << ": Otvoren fajl '" << copied_filepath << "' i dohvacena velicina" << endl; 
		delete copy;
		 cout << threadName2 << ": Zatvoren fajl '" << copied_filepath << "'" << endl; 
		File *src, *dst;
		char filepath[] = "/fajl1.dat";
		src = FS::open(filepath, 'r');
		src->seek(0);//pozicionira se na pola fajla
		 cout << threadName2 << ": Otvoren fajl '" << filepath << "' i pozicionirani smo na polovini" << endl; 
		char filepath1[] = "/fajl25.dat";
		dst = FS::open(filepath1, 'w');
		 cout << threadName2 << ": Otvoren fajl '" << filepath1 << "'" << endl; 
		char c; BytesCnt cnt = src->getFileSize() - size;
		while (!src->eof() && cnt-- > 0) {
			src->read(1, &c);
			dst->write(1, &c);
		}
		 cout << threadName2 << ": Prepisana druga polovina '" << filepath << "' u '" << filepath1 << "'" << endl; 
		delete dst;
		 cout << threadName2 << ": Zatvoren fajl '" << filepath1 << "'" << endl; 
		delete src;
		 cout << threadName2 << ": Zatvoren fajl '" << filepath << "'" << endl; 
	}

	{
		File *src, *dst;
		char filepath[] = "/fajl25.dat";
		dst = FS::open(filepath, 'a');
		cout << threadName1 << ": Otvoren fajl '" << filepath << "'" << endl; 
		char filepath1[] = "/fajll5.dat";
		src = FS::open(filepath1, 'r');
		cout << threadName1 << ": Otvoren fajl '" << filepath1 << "'" << endl; 
		char c;
		while (!src->eof()) {
			src->read(1, &c);
			dst->write(1, &c);
		}
		cout << threadName1 << ": Prepisana druga polovina '" << filepath << "' u '" << filepath1 << "'" << endl; 
		delete dst;
		 cout << threadName1 << ": Zatvoren fajl '" << filepath1 << "'" << endl; 
		delete src;
		 cout << threadName1 << ": Zatvoren fajl '" << filepath << "'" << endl; 
	}



	{
		char filepath[] = "/fajl25.dat";
		File *f = FS::open(filepath, 'r');
		 cout << threadName2 << ": Otvoren fajl " << filepath << "" << endl; 
		ofstream fout("izlaz2.dat", ios::out | ios::binary);
		char *buff = new char[f->getFileSize()];
		f->read(f->getFileSize(), buff);
		fout.write(buff, f->getFileSize());
		 cout << threadName2 << ": Upisan '" << filepath << "' u fajl os domacina 'izlaz2.dat'" << endl; 
		delete[] buff;
		fout.close();
		delete f;
		 cout << threadName2 << ": Zatvoren fajl " << filepath << "" << endl; 
	}

	{
		FS::unmount();
		 cout << threadName2 << ": Demontirana particija p1" << endl; 
	}

	delete[] ulazBuffer;
	cout << "Kraj test primera!" << endl;


	char ende;
	cin >> ende;

	return 0;
}