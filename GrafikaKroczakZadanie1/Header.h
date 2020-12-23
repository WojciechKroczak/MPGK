#pragma once

#include <string.h>
#include <math.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>

class ProgramMPGK
{
private:
	int wysokoscOkna;
	int szerokoscOkna;
	int polozenieOknaX;
	int polozenieOknaY;
	static GLuint VAO; //vertex array object, przechowuje identyfikator obiektu opengl. Przechowuje format danych wierzcholkow oraz bufory(VBO, IBO)
	static GLuint VBO; //vertex buffer object, przechowuje identyfikator bufora
	static GLuint IBO; //uchwyt do bufora na indeksy
	static GLuint programZShaderami;
	static GLuint vertexShaderId;
	static GLuint fragmentShaderId;
	//w powyzszych trzech przechowywane beda uchwyty do programu w ktorym laczone sa shadery oraz do obu shaderow
	static GLint zmiennaShader; //zmeinna typu uniform, roznica miedzy nimi a atrybutami polega na tym ze w przypadku tych ostatnich ladowane sa nowe
	//przy kazdym wywolaniu shadera a z pola uniform pozostaja niezmienione przez caly czas trwania programu shaderow
	//zmiennashader- zmienna do ktorej wstawimy uzyskana lokalizacje (w shaderze) zmiennej typu uniform
	static GLint zmiennaObrShader;

public: //konstruktory, tworzenie okna, inicjalizacja GLEW, metoda rysujaca
	ProgramMPGK(void);
	ProgramMPGK(int wysokoscOkna, int szerokoscOkna, int polozenieOknaX, int polozenieOknaY);
	~ProgramMPGK(void);
	void stworzenieOkna(int argc, char** argv);
	void inicjalizacjaGlew();
	static void wyswietl();
	static void usun();
	//bufory (3 ponizej)
	void stworzenieVAO();
	void stworzenieVBO();
	void stworzenieIBO();
	//metody odpowiedzialne za shadery
	void stworzenieProgramu();
	GLuint dodanieDoProgramu(GLuint programZShaderami, const char * tekstShadera, GLenum typShadera);
	//sprawdzenie wersji GLEW, karty graficznej, GL i GLSL
	void sprawdzenieWersji();
};
