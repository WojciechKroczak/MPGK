#pragma once
#include "Header.h"
class Wektor :
	public ProgramMPGK
{
public:
	float Wek1, Wek2, Wek3, Wek4;
	float WekT3[3] = { 0 };
	float WekT4[4] = { 0 };

	Wektor();
	~Wektor();
	Wektor(float W);
	Wektor(float W1, float W2, float W3);
	Wektor(float W1, float W2, float W3, float W4);
	Wektor(float W[], int dlugosc);

	//void Konstruktor(GLfloat W[]);
	//	void Konstruktor(float W[3]);
	void Przypisz(GLfloat WT[], int dlug, int calosc);
	Wektor Normalizacja(float x, float y, float z, float w);
	Wektor Normalizacja(Wektor W);
	float Skalarny(float x, float y, float z, float w, float x2, float y2, float z2, float w2);
	float Skalarny(Wektor W1, Wektor W2);
	//float Geometryczny(float x, float y, float z, float w, float x2, float y2, float z2, float w2);
	Wektor Wektorowy(float x, float y, float z, float w, float x2, float y2, float z2, float w2);
	Wektor Wektorowy(Wektor W1, Wektor W2);

	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setW(float w);

	float getX();
	float getY();
	float getZ();
	float getW();
	float get(int index);

	friend std::ostream& operator<<(std::ostream& output, const Wektor& W1);
	Wektor& operator+=(const Wektor& right);
	Wektor& operator-=(const Wektor& right);
	Wektor& operator*=(const Wektor& right);
	Wektor& operator=(const Wektor& right);
	//friend Wektor& operator+(const Wektor& W);
};

std::ostream& operator<<(std::ostream& output, const Wektor& W1);
Wektor operator+(const Wektor &w1, const Wektor &w2);
Wektor operator-(const Wektor &w1, const Wektor &w2);
Wektor operator*(const Wektor &w1, const Wektor &w2);

//Wektor& operator+(const Wektor& W);
//Wektor operator+=(const Wektor &w1, const Wektor &w2);


//Wektor operator-=(const Wektor &w1, const Wektor &w2);
//Wektor operator*(const Wektor &w1, const Wektor &w2);
//Wektor operator*=(const Wektor &w1, const Wektor &w2);