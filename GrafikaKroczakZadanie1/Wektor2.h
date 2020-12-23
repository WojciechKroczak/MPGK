#pragma once
#include "Header.h"
class Wektor2 :
	public ProgramMPGK
{
public:
	Wektor2();
	~Wektor2();
	void Konstruktor(void);
	void Konstruktor(float W1, float W2, float W3);
	void Konstruktor(float W1, float W2, float W3, float W4);
	void Konstruktor(float W[2]);
	//	void Konstruktor(float W[3]);
	void Przypisz(GLfloat WT[]);
};

