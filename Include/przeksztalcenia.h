#pragma once
#include <Wektor.h>
#include <Macierz.h>
#include<iostream>
#include<fstream>
#include<string>
#include<math.h>
#include <iomanip>
#include <cmath>

#define M_PI 3.14159265358979323846

class Przeksztalcenia
{
public:

	float MacP[4][4] = { 0 };
	Macierz maciP;

	//Macierz maci;

	Przeksztalcenia();
	Przeksztalcenia(float wartosc);
	Przeksztalcenia(float tablica[3][3]);
	Przeksztalcenia(float tablica[4][4]);
	Przeksztalcenia(Macierz maci2);
	~Przeksztalcenia();


	Macierz Skalowanie2D(float w);   
	Macierz Skalowanie2D(float x, float y);
	Macierz Skalowanie2D(float w[2]);

	Macierz Obrot2D(float kat);

	Macierz Przesuniecie2D(float w);
	Macierz Przesuniecie2D(float x, float y);
	Macierz Przesuniecie2D(float w[2]);


	Macierz Skalowanie3D(float w);
	Macierz Skalowanie3D(float x, float y, float z);
	Macierz Skalowanie3D(float w[3]);

	Macierz Obrot3D(float kat, char os);

	Macierz Przesuniecie3D(float w);
	Macierz Przesuniecie3D(float x, float y, float z);
	Macierz Przesuniecie3D(float w[3]);

	float naRadiany(float stopnie);
	float naStopnie(float radiany);
};



using namespace std;
float Macie[4][4] = { NULL };
double d2 = 0;


std::ostream & operator<<(std::ostream & output, const Przeksztalcenia & M)
{


	if (M.MacP[3][3] == NULL) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {

				if (j == 0) {
					output << std::left << std::setw(12) << M.MacP[i][j];
				}
				else {
					output << std::setw(12) << M.MacP[i][j];
				}


			}

			output << std::endl;
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {

				if (j == 0) {
					output << std::left << std::setw(12) << M.MacP[i][j];
				}
				else {
					output << std::setw(12) << M.MacP[i][j];
				}
			}
			output << std::endl;
		}
	}


	return output;
}


Przeksztalcenia::Przeksztalcenia()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			MacP[i][j] = 0;
		}
	}
}

Przeksztalcenia::Przeksztalcenia(float wartosc)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			MacP[i][j] = wartosc;
		}
	}
}


Przeksztalcenia::Przeksztalcenia(float tablica[3][3])
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			/*if (tablica[i][j] == NULL) {
				Mac[i][j] = 0;
			}
			else {*/
			MacP[i][j] = tablica[i][j];
			//}
		}
	}



}




Przeksztalcenia::Przeksztalcenia(float tablica[4][4])
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (tablica[i][j] == NULL) {
				Macie[i][j] = 0;
			}
			else {
				Macie[i][j] = tablica[i][j];
			}
		}
	}
}


Przeksztalcenia::Przeksztalcenia(Macierz maci2)
{
	/*cout << "wypisuje macierz z przeksztalcen" << endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << maci2.Mac[i][j] << " ";
		}
		cout<<endl;
	}
	cout << "^^^ macierz z przeksztalcen" << endl;*/

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			/*if (tablica[i][j] == NULL) {
				Mac[i][j] = 0;
			}
			else {*/
			MacP[i][j] = maci2.Mac[i][j];
			//}
		}
	}
}




Przeksztalcenia::~Przeksztalcenia()
{
}




Macierz Przeksztalcenia::Skalowanie2D(float w) {
	Macierz maci;
	
	Macierz macJ = maci.Jednostkowa();
	macJ.set(0, 0, w);
	macJ.set(1, 1, w);
	macJ.set(3, 3, NULL);
	//cout << "macierz skalowania jeden float" << endl;
	//cout << macJ << endl;

	return macJ;
}

Macierz Przeksztalcenia::Skalowanie2D(float x, float y) {
	Macierz maci;
	Macierz macJ = maci.Jednostkowa();
	macJ.set(0, 0, x);
	macJ.set(1, 1, y);
	macJ.set(3, 3, NULL);
	//cout << "macierz skalowania float x i y" << endl;
	//cout << macJ << endl;

	return macJ;
}

Macierz Przeksztalcenia::Skalowanie2D(float w[2]) {
	Macierz maci;
	Macierz macJ = maci.Jednostkowa();
	macJ.set(0, 0, w[0]);
	macJ.set(1, 1, w[1]);
	macJ.set(3, 3, NULL);
	//cout << "macierz skalowania tablica x i y" << endl;
	//cout << macJ << endl;

	return macJ;
}


Macierz Przeksztalcenia::Skalowanie3D(float w) {
	Macierz maci;

	Macierz macJ = maci.Jednostkowa();
	macJ.set(0, 0, w);
	macJ.set(1, 1, w);
	macJ.set(2, 2, w);
	//cout << "macierz skalowania jeden float" << endl;
	//cout << macJ << endl;

	return macJ;
}

Macierz Przeksztalcenia::Skalowanie3D(float x, float y, float z) {
	Macierz maci;
	Macierz macJ = maci.Jednostkowa();
	macJ.set(0, 0, x);
	macJ.set(1, 1, y);
	macJ.set(2, 2, z);


	return macJ;
}

Macierz Przeksztalcenia::Skalowanie3D(float w[3]) {
	Macierz maci;
	Macierz macJ = maci.Jednostkowa();
	macJ.set(0, 0, w[0]);
	macJ.set(1, 1, w[1]);
	macJ.set(2, 2, w[2]);


	return macJ;
}


Macierz Przeksztalcenia::Przesuniecie2D(float w) {
	Macierz maci;
	Macierz macJ = maci.Jednostkowa();
	macJ.set(0, 2, w);
	macJ.set(1, 2, w);
	macJ.set(3, 3, NULL);

	return macJ;
}

Macierz Przeksztalcenia::Przesuniecie2D(float x, float y) {
	Macierz maci;
	Macierz macJ = maci.Jednostkowa();
	macJ.set(0, 2, x);
	macJ.set(1, 2, y);
	macJ.set(3, 3, NULL);

	return macJ;
}

Macierz Przeksztalcenia::Przesuniecie2D(float w[2]) {
	Macierz maci;
	Macierz macJ = maci.Jednostkowa();
	macJ.set(0, 2, w[0]);
	macJ.set(1, 2, w[1]);
	macJ.set(3, 3, NULL);
	

	return macJ;
}


Macierz Przeksztalcenia::Przesuniecie3D(float w) {
	Macierz maci;

	Macierz macJ = maci.Jednostkowa();
	macJ.set(0, 3, w);
	macJ.set(1, 3, w);
	macJ.set(2, 3, w);
	//cout << "macierz skalowania jeden float" << endl;
	//cout << macJ << endl;

	return macJ;
}

Macierz Przeksztalcenia::Przesuniecie3D(float x, float y, float z) {
	Macierz maci;
	Macierz macJ = maci.Jednostkowa();
	macJ.set(0, 3, x);
	macJ.set(1, 3, y);
	macJ.set(2, 3, z);


	return macJ;
}

Macierz Przeksztalcenia::Przesuniecie3D(float w[3]) {
	Macierz maci;
	Macierz macJ = maci.Jednostkowa();
	macJ.set(0, 3, w[0]);
	macJ.set(1, 3, w[1]);
	macJ.set(2, 3, w[2]);


	return macJ;
}

Macierz Przeksztalcenia::Obrot2D(float kat)
{
	Macierz maci;
	Macierz macJ = maci.Jednostkowa();
	//float kat2 = kat * M_PI / 180;
	macJ.set(3, 3, NULL);
	float kat2 = naRadiany(kat);
	macJ.set(0, 0, cos(kat2));
	macJ.set(0, 1, -sin(kat2));
	macJ.set(1, 0, sin(kat2));
	macJ.set(1, 1, cos(kat2));
	return macJ;
}

Macierz Przeksztalcenia::Obrot3D(float kat, char os)
{
	Macierz maci;
	Macierz macJ = maci.Jednostkowa();
	//float kat2 = kat * M_PI / 180;
	float kat2 = naRadiany(kat);
	if (os == 'x') {
		//cout << "X" << endl;
		macJ.set(1, 1, cos(kat2));
		macJ.set(1, 2, -sin(kat2));
		macJ.set(2, 1, sin(kat2));
		macJ.set(2, 2, cos(kat2));
	}
	else if (os == 'y') {
		//cout << "y" << endl;
		macJ.set(0, 0, cos(kat2));
		macJ.set(0, 2, sin(kat2));
		macJ.set(2, 0, -sin(kat2));
		macJ.set(2, 2, cos(kat2));
	}
	else if (os == 'z') {
		//cout << "z" << endl;
		macJ.set(0, 0, cos(kat2));
		macJ.set(0, 1, -sin(kat2));
		macJ.set(1, 0, sin(kat2));
		macJ.set(1, 1, cos(kat2));
	}	
	else {
		cout << "Wybrano zla os obrotu" << endl;
	}
	return macJ;
}

float Przeksztalcenia::naStopnie(float radiany) {
	float stopnie = 0;
	stopnie = radiany * 180 / M_PI;
	return stopnie;
}

float Przeksztalcenia::naRadiany(float stopnie) {
	float radiany;
	radiany = stopnie * M_PI / 180;
	return radiany;
}