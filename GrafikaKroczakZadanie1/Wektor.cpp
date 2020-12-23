#include "Wektor.h"
#include<iostream>
#include<fstream>
#include<string>
#include<math.h>

using namespace std;



float Wek1, Wek2, Wek3, Wek4;
float WektorTab[] = { 0 };
float WekT3[3] = { 0 };
float WekT4[4] = { 0 };




Wektor::Wektor()
{
	Wek1 = Wek2 = Wek3 = Wek4 = 0;
}


Wektor::~Wektor()
{
}



Wektor::Wektor(float W)
{
	Wek1 = Wek2 = Wek3 = Wek4 = W;
}

Wektor::Wektor(float W1, float W2, float W3)
{
	Wek1 = W1;
	Wek2 = W2;
	Wek3 = W3;
	WekT3[0] = W1;
	WekT3[1] = W2;
	WekT3[2] = W3;
}


Wektor::Wektor(float W1, float W2, float W3, float W4)
{
	Wek1 = W1;
	Wek2 = W2;
	Wek3 = W3;
	Wek4 = W4;
	WekT4[0] = W1;
	WekT4[1] = W2;
	WekT4[2] = W3;
	WekT4[3] = W4;
}


Wektor::Wektor(float W[], int dlugosc)
{
	//float dlugosc = sizeof(W)/sizeof(W[0]);

	//cout << "dlugosc floata " << dlugosc;
	if (dlugosc == 3) {
		WekT3[0] = W[0];
		WekT3[1] = W[1];
		WekT3[2] = W[2];
		//cout << "dlugosc floata " << WekT3[0]<< " " << WekT3[1] << " " << WekT3[2];
	}
	else if (dlugosc == 4) {
		WekT4[0] = W[0];
		WekT4[1] = W[1];
		WekT4[2] = W[2];
		WekT4[3] = W[3];
		cout << "dlugosc floata " << WekT4[0] << " " << WekT4[1] << " " << WekT4[2] << " " << WekT4[3];
	}
	else {
		cout << "blad ";
	}


}


void Wektor::Przypisz(GLfloat WT[], int dlug, int calosc) {

	GLfloat WekT[999];
	int j = 0, k = 0;
	cout << "\nilosc linii " << dlug;
	cout << "\nilosc calosc " << calosc;
	int linie = calosc / sizeof(WT);
	cout << "\nilosc linii " << linie;


	/*
	cout << "\nCopy Array List is :"<<"\n";
	for (int i = 0; i < linie;i++) {
		cout << WT[i] << " ";
		j++;
		if (j == 4) {
			cout << "\n";
			j = 0;
			k++;
		}
		if(k == 4) {
			cout << "\n";
			k = 0;
		}
		}
	*/


	for (int i = 0; i < linie; i++) {
		WekT[i] = WT[i];
	}

	cout << "\nTablica w klasie Wektor :" << "\n";
	for (int i = 0; i < linie; i++) {
		cout << WekT[i] << " ";
		j++;
		if (j == 4) {
			cout << "\n";
			j = 0;
			k++;
		}
		if (k == 4) {
			cout << "\n";
			k = 0;
		}
	}


	//cout << "\nilosc wierzcholkow" << sizeof(WT) / sizeof(*WT) / 4;
	/*
	GLfloat WekT[999];
	int i, n;
	n = (sizeof(WT) / sizeof(*WT));
	cout << "\nLenght Array  is :";
	cout << n;

	for (i = 0; i < n; i++) {
		WekT[i] = WT[i];
	}
	cout << "\nCopy Array List is :";
	for (i = 0; i < n; i++) {
		cout << WekT[i] << " ";
	}
	*/
};



Wektor Wektor::Normalizacja(float x, float y, float z, float w) {
	//cout << "normalizacja w wektorze przed " << x << " " << y << " " << z << " " << w << endl;
	float px = x / sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0) + pow(w, 2.0));
	float py = y / sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0) + pow(w, 2.0));
	float pz = z / sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0) + pow(w, 2.0));
	float pw = w / sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0) + pow(w, 2.0));
	//cout << "normalizacja w wektorze po " << px << " " << py << " " << pz << " " << pw << endl;
	//float jednostkowy = px + py + pz + pw;
	//return jednostkowy;
	return Wektor(px, py, pz, pw);
};


Wektor Wektor::Normalizacja(Wektor W) {

	float px = W.Wek1 / sqrt(pow(W.Wek1, 2.0) + pow(W.Wek2, 2.0) + pow(W.Wek3, 2.0) + pow(W.Wek4, 2.0));
	float py = W.Wek2 / sqrt(pow(W.Wek1, 2.0) + pow(W.Wek2, 2.0) + pow(W.Wek3, 2.0) + pow(W.Wek4, 2.0));
	float pz = W.Wek3 / sqrt(pow(W.Wek1, 2.0) + pow(W.Wek2, 2.0) + pow(W.Wek3, 2.0) + pow(W.Wek4, 2.0));
	float pw = W.Wek4 / sqrt(pow(W.Wek1, 2.0) + pow(W.Wek2, 2.0) + pow(W.Wek3, 2.0) + pow(W.Wek4, 2.0));
	float jednostkowy = px + py + pz + pw;
	//cout << "normalizacja w wektorze " << px << " " << py << " " << pz << " " << pw << endl;
	//return jednostkowy;
	return Wektor(px, py, pz, pw);
};

float Wektor::Skalarny(float x, float y, float z, float w, float x2, float y2, float z2, float w2) {

	float skalar = x * x2 + y * y2 + z * z2 + w * w2;
	return skalar;
};


float Wektor::Skalarny(Wektor W1, Wektor W2) {

	float skalar = W1.Wek1 * W2.Wek1 + W1.Wek2 * W2.Wek2 + W1.Wek3 * W2.Wek3 + W1.Wek4 * W2.Wek4;
	return skalar;
};

Wektor Wektor::Wektorowy(float x, float y, float z, float w, float x2, float y2, float z2, float w2) {
	float px = y*z2 - z*y2;
	float py = z*x2 - x*z2;
	float pz = x*y2 - y*x2;
	float pw = 0;
	return Wektor(px, py, pz, pw);
};

Wektor Wektor::Wektorowy(Wektor u, Wektor v) {
//	cout << "u.Wek2: " << u.Wek1 << endl;
//	cout << "v.Wek3: " << v.Wek3 << endl;
	float px = u.Wek2*v.Wek3 - u.Wek3*v.Wek2;
	float py = u.Wek3*v.Wek1 - u.Wek1*v.Wek3;
	float pz = u.Wek1*v.Wek2 - u.Wek2*v.Wek1;
	float pw = 0;
	//cout << "px " << px << endl;
	return Wektor(px, py, pz, pw);
}

float Wektor::get(int index) {
	return WekT4[index];
}

void Wektor::setX(float x) {
	Wek1 = x;
};
void Wektor::setY(float y) {
	Wek2 = y;
};
void Wektor::setZ(float z) {
	Wek3 = z;
};
void Wektor::setW(float w) {
	Wek4 = w;
};

float Wektor::getX() {
	return this->Wek1;
};
float Wektor::getY() {
	return this->Wek2;
};
float Wektor::getZ() {
	return this->Wek3;
};
float Wektor::getW() {
	return this->Wek4;
};

ostream& operator<<(ostream& output, const Wektor& W) {

	output << W.Wek1 << " " << W.Wek2 << " " << W.Wek3 << " " << W.Wek4;
	//output << W.WekT4[0] << " " << W.WekT4[1] << " " << W.WekT4[2] << " " << W.WekT4[3];
	return output;
};


Wektor operator+(const Wektor &w1, const Wektor &w2)
{
	//cout << "operator +" << endl;
	Wek1 = w1.Wek1 + w2.Wek1;
	Wek2 = w1.Wek2 + w2.Wek2;
	Wek3 = w1.Wek3 + w2.Wek3;
	Wek4 = w1.Wek4 + w2.Wek4;
	//return Wektor(w1.Wek1 + w2.Wek1);
	return Wektor(Wek1, Wek2, Wek3, Wek4);
}

Wektor& Wektor::operator+=(const Wektor& W)
{
	this->Wek1 += W.Wek1;
	this->Wek2 += W.Wek2;
	this->Wek3 += W.Wek3;
	this->Wek4 += W.Wek4;
	return *this;
}

Wektor operator-(const Wektor &w1, const Wektor &w2)
{
	//cout << "operator -" << endl;

	Wek1 = w1.Wek1 - w2.Wek1;
	Wek2 = w1.Wek2 - w2.Wek2;
	Wek3 = w1.Wek3 - w2.Wek3;
	Wek4 = w1.Wek4 - w2.Wek4;
	//return Wektor(w1.Wek1 + w2.Wek1);
	return Wektor(Wek1, Wek2, Wek3, Wek4);
}

Wektor& Wektor::operator-=(const Wektor& W)
{
	/*cout << endl;
	cout << "Wektor: " << W.Wek1 << " " << W.Wek2 << " " << W.Wek3 << " " << W.Wek4 << endl;
	cout << "Wektor this: " << this->Wek1 << " " << this->Wek2 << " " << this->Wek3 << " " << this->Wek4 << endl;
	cout << endl;*/

	this->Wek1 -= W.Wek1;
	this->Wek2 -= W.Wek2;
	this->Wek3 -= W.Wek3;
	this->Wek4 -= W.Wek4;
	return *this;
}

Wektor operator*(const Wektor &w1, const Wektor &w2)
{
	//cout << "operator -" << endl;

	Wek1 = w1.Wek1 * w2.Wek1;
	Wek2 = w1.Wek2 * w2.Wek1;
	Wek3 = w1.Wek3 * w2.Wek1;
	Wek4 = w1.Wek4 * w2.Wek1;
	//return Wektor(w1.Wek1 + w2.Wek1);
	return Wektor(Wek1, Wek2, Wek3, Wek4);
}

Wektor& Wektor::operator*=(const Wektor& W)
{
	/*cout << endl;
	cout << "Wektor: " << W.Wek1 << " " << W.Wek2 << " " << W.Wek3 << " " << W.Wek4 << endl;
	cout << "Wektor this: " << this->Wek1 << " " << this->Wek2 << " " << this->Wek3 << " " << this->Wek4 << endl;
	cout << endl;*/

	this->Wek1 *= W.Wek1;
	this->Wek2 *= W.Wek1;
	this->Wek3 *= W.Wek1;
	this->Wek4 *= W.Wek1;
	return *this;
}

Wektor& Wektor::operator=(const Wektor& W)
{
	this->Wek1 = W.Wek1;
	this->Wek2 = W.Wek2;
	this->Wek3 = W.Wek3;
	this->Wek4 = W.Wek4;
	return *this;
}





//Wektor operator+=(const Wektor &w1, const Wektor &w2)
//{
//	cout << "operator += do zrobienia" << endl;
//	w1.Wek1 = w1.Wek1 + w2.Wek1;
//	Wek2 = w1.Wek2 + w2.Wek2;
//	Wek3 = w1.Wek3 + w2.Wek3;
//	Wek4 = w1.Wek4 + w2.Wek4;
//	return Wektor(w1.Wek1 + w2.Wek1);
//}

//Wektor& operator+(const Wektor& W) {
//	Wektor WekWynik;
//	WekWynik.Wek1 = Wek1 + W.Wek1;
//	WekWynik.Wek2 = Wek2 + W.Wek2;
//	WekWynik.Wek3 = Wek3 + W.Wek3;
//	WekWynik.Wek4 = Wek4 + W.Wek4;
//	return WekWynik;
//}