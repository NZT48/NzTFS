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

int main() {


	{
		FILE *f = fopen("ulaz.dat", "rb");
		if (f == 0) {
			cout << "GRESKA: Nije nadjen ulazni fajl 'ulaz.dat' u os domacinu!" << endl;
			system("PAUSE");
			return 0;//exit program
		}
		ulazBuffer = new char[32 * 1024];
		ulazSize = fread(ulazBuffer, 1, 32 * 1024, f);
		fclose(f);
	}


	partition = new Partition((char *)"p1.ini");

	cout << "Kreirana particija" << endl;

	FS::mount(partition);

	cout << " Montirana particija" << endl;

	FS::format();

	cout << " Formatirana particija" << endl;

	char filepath[] = "/fajl1.dat";
	File *f = FS::open(filepath, 'w');
	cout << " Kreiran fajl '" << filepath << "'" << endl; 
	f->write(ulazSize, ulazBuffer);
	cout << "Prepisan sadrzaj 'ulaz.dat' u '" << filepath << "'" << endl;
	delete f;
	cout <<  "zatvoren fajl '" << filepath << "'" << endl;


	f = FS::open(filepath, 'r');
	cout << " Otvoren za citanje fajl '" << filepath << "'" << endl;
	
	char c;
	int cnt = 0, cntC = 0;
	while (!f->eof()) {
	//for(int i = 0; i < 33000; i ++){
		f->read(1, &c);
		cout << c;
		cnt++;
	}
	cout <<  endl;
	cout << cnt << endl;



	cout << "Prepisan sadrzaj fajla  '" << filepath << "'" << endl;
	delete f;
	cout << "zatvoren fajl '" << filepath << "'" << endl;

	delete[] ulazBuffer;
	cout << "Kraj test primera!" << endl;


	char ende;
	cin >> ende;

	return 0;
}