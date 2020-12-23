﻿#include "Header.h"
#include<iostream>
#include<fstream>
#include<string>
//#include "Wektor.h"
//#include "Macierz.h"
//#include <Wektor.h>
#include <cmath>

#define M_PI 3.14159265358979323846


GLuint ProgramMPGK::VAO;
GLuint ProgramMPGK::VBO;
GLuint ProgramMPGK::IBO;
GLuint ProgramMPGK::programZShaderami;
GLuint ProgramMPGK::vertexShaderId;
GLuint ProgramMPGK::fragmentShaderId;
GLint ProgramMPGK::zmiennaShader;
GLint ProgramMPGK::zmiennaObrShader;

using namespace std;


double rotate_y = 0;
double rotate_x = 0;



ProgramMPGK::ProgramMPGK(void) //konstruktor bez parametrow
{
	wysokoscOkna = 768;
	szerokoscOkna = 1024;
	polozenieOknaX = 100;
	polozenieOknaY = 100;
}

ProgramMPGK::ProgramMPGK(int wysokoscOkna, int szerokoscOkna, int polozenieOknaX, int polozenieOknaY) //konstruktor z parametrami
{
	this->wysokoscOkna = wysokoscOkna;
	this->szerokoscOkna = szerokoscOkna;
	this->polozenieOknaX = polozenieOknaX;
	this->polozenieOknaY = polozenieOknaY;
}

ProgramMPGK::~ProgramMPGK() //destruktor
{

}

void ProgramMPGK::stworzenieOkna(int argc, char** argv)
{
	glutInit(&argc, argv); //inicjalizacja
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); //tryb - glebokosc, dwa bufory(funkcja swap), tryb kolorow Red Green Blue Alpha
	glutInitWindowSize(szerokoscOkna, wysokoscOkna); //wielksoc okna
	glutInitWindowPosition(polozenieOknaX, polozenieOknaY); //polozenie
//	glutInitContextVersion(3, 3);  //ustawienie na sztywno wersji opengl
//	glutInitContextProfile(GLUT_CORE_PROFILE);  //profil starej wersji opengl
	glutCreateWindow("Zadanie0"); //Nazwa okna programu
}

void ProgramMPGK::inicjalizacjaGlew() //inicjalizacja GLEW i sprawdzenie czy nie zakonczyla sie bledem
{
	GLenum wynik = glewInit();
	if (wynik != GLEW_OK)
	{
		std::cerr << "Nie udalo sie zainicjalizowac GLEW. Blad: " << glewGetErrorString(wynik) << std::endl;
		system("pause");
		exit(1);
	}
}





void  ProgramMPGK::wyswietl()
{


	glEnable(GL_DEPTH_TEST); //wlacza sprawdzanie glebokosci oraz aktualizowanie bufora
	glDepthFunc(GL_LESS); //okresla funkcje porownujaca glebokosc kazdego kolejnego piksela z wartoscia przechowywana w buforze glebokosci (depth buffer)
	//GL_LESS - nadchodzaca wartosc jest mniejsza od przechowywanej 


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //czysci bufory do wczesniej ustawionych wartosci

	static GLfloat zmiana = 1.0f; //ustawienie stalej wielkosci
	//static GLfloat zmiana = 0.0f;  // zmienna statyczna

	//zmiana += 0.0005f; //ustalenie zmiany wielkosci obiektu rysowanego


	static GLfloat obrot = 1.57;
	obrot += 0.0005;

	glUniform1f(zmiennaShader, abs(sinf(zmiana))); //laduje dane do zmiennej typu uniform w "shaderze". ta funkcja ma rozne wersje, glUniform{1234}{if}
	glUniform1f(zmiennaObrShader, obrot);
	//{1234} oznacza odpowiednio 1,2,3,4 zmiany

	glEnableVertexAttribArray(0); //umozliwia przekazanie danych z bufora z glownego porgramu do atrybutu z "shadera". Dzieje sie to dzieki indeksowi podanemu tu jak i w samym
	//"shaderze"
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 4));
	//cout << "sizeof(GLfloat): " << sizeof(GLfloat) << endl << "sizeof(GLfloat)*8: " << sizeof(GLfloat) * 8 << endl;
	//okresla lokalizacje i format danych tablicy atrybutow (informuje potok-pipeline jak interpretowac dane z bufora)
	//pierwszy parametr to indeks, drugi to liczba komponentow (3 dla x y z)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glDrawElements(GL_TRIANGLES, 40, GL_UNSIGNED_INT, 0); //druga wartosc to ilosc rysowanych wierzcholkow

	//w opengl wszystko jest opisywane za pomoca prymitywow graficznych
	//gl points, gl lines, gl line strip, gl line loop, gl triangles, gl triangle strip, gl triangle fan
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glutSwapBuffers(); //swap buforow, jeden do rysowania drugi do wyswietlania
}

void ProgramMPGK::usun()//wywolywana w trakcie zamykania okna
{
	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
	glDeleteProgram(programZShaderami);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
	glDeleteVertexArrays(1, &VAO);
}

void ProgramMPGK::stworzenieVAO() //stworzenie vertex array object
{
	glGenVertexArrays(1, &VAO); //podaje ilosc i adres zmiennej statycznej
	glBindVertexArray(VAO); //powoduje ze obiekt staje sie aktualnie uzywanym obiektem
}


string wczytajShader(const char *filePath) {
	string content;
	ifstream fileStream(filePath, ios::in);

	if (!fileStream.is_open()) {
		cerr << "Nie mozna wczytac shadera " << filePath << ". Plik nie istnieje." << endl;
		system("pause");
	}

	string line = "";
	while (!fileStream.eof()) {
		getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}


void zapiszShader(string filePath, const char *testDest) {

	ofstream stream;

	stream.open(filePath);
	if (!stream) {
		cout << "Nie mozna otworzyc pliku" << endl;
		system("pause");
	}
	stream << testDest << endl;
	if (!stream) {
		cout << "Nie mozna zapisac shadera do pliku" << endl;
		system("pause");
	}

}

float naStopnie(float radiany) {
	float stopnie = 0;
	stopnie = radiany * 180 / M_PI;
	return stopnie;
}

float naRadiany(float stopnie) {
	float radiany;
	radiany = stopnie * M_PI / 180;
	return radiany;
}

void ProgramMPGK::stworzenieVBO() //tworzy bufor (na wierzcholki) i wypelnia go danymi
{
	//deklarujemy tablice na zmienne typu GLfloat i wstawiamy do niej X Y Z W kazdego wierzcholka oraz kolor - R G B A

	Wektor wektor;

	Wektor W1 = { -0.4f, -0.4f, 0.0f, 1.0f };
	Wektor W2 = { 0.4f, -0.4f, 0.0f, 1.0f };
	Wektor W3 = { -0.4f,  0.4f, 0.0f, 1.0f };
	Wektor W4 = { 0.4f,  0.4f, 0.0f, 1.0f };
	Wektor K1 = { 1.0f,  1.0f, 0.0f, 1.0f };

	Wektor W5 = { 0.6f,  0.6f, 0.0f, 1.0f };
	Wektor W6 = { 0.6f,  0.9f, 0.0f, 1.0f };
	Wektor W7 = { 0.9f,  0.6f, 0.0f, 1.0f };
	Wektor K2 = { 1.0f,  1.0f, 1.0f, 1.0f };

	Wektor W8 = { -0.4f, -0.4f, 0.0f, 1.0f };
	Wektor W9 = { -0.4f, 0.4f, 0.0f, 1.0f };
	Wektor W10 = { -0.4f,  -0.4f, 0.8f, 1.0f };
	Wektor W11 = { -0.4f,  0.4f, 0.8f, 1.0f };
	Wektor K3 = { 1.0f,  0.0f, 0.0f, 1.0f };

	Wektor W12 = { 0.4f, -0.4f, 0.0f, 1.0f };
	Wektor W13 = { 0.4f,  0.4f, 0.0f, 1.0f };
	Wektor W14 = { 0.4f,  0.4f, 0.8f, 1.0f };
	Wektor W15 = { 0.4f,  -0.4f, 0.8f, 1.0f };
	Wektor K4 = { 0.0f,  0.0f, 1.0f, 1.0f };

	Wektor W16 = { -0.4f, -0.4f, 0.0f, 1.0f };
	Wektor W17 = { 0.4f, -0.4f, 0.0f, 1.0f };
	Wektor W18 = { -0.4f, -0.4f, 0.8f, 1.0f };
	Wektor W19 = { 0.4f, -0.4f, 0.8f, 1.0f };
	Wektor K5 = { 0.0f,  1.0f, 0.0f, 1.0f };

	Wektor W20 = { -0.4f,  0.4f, 0.0f, 1.0f };
	Wektor W21 = { 0.4f,  0.4f, 0.0f, 1.0f };
	Wektor W22 = { -0.4f,  0.4f, 0.8f, 1.0f };
	Wektor W23 = { 0.4f,  0.4f, 0.8f, 1.0f };
	Wektor K6 = { 1.0f,  1.0f, 1.0f, 1.0f };

	Wektor W24 = { -0.4f, -0.4f, 0.8f, 1.0f };
	Wektor W25 = { 0.4f, -0.4f, 0.8f, 1.0f };
	Wektor W26 = { -0.4f,  0.4f, 0.8f, 1.0f };
	Wektor W27 = { 0.4f,  0.4f, 0.8f, 1.0f };
	Wektor K7 = { 0.0f,  1.0f, 1.0f, 1.0f };


	Wektor obiekty2[] = {
		W1,K1,W2,K1,W3,K1,W4,K1,
		W5,K2,W6,K2,W7,K2,
		W8,K3,W9,K3,W10,K3,W11,K3,
		W12,K4,W13,K4,W14,K4,W15,K4,
		W16,K5,W17,K5,W18,K5,W19,K5,
		W20,K6,W21,K6,W22,K6,W23,K6,
		W24,K7,W25,K7,W26,K7,W27,K7
	};

	vector <GLfloat> wierzcholkiV;

	for (int i = 0; i < sizeof(obiekty2) / sizeof(obiekty2[0]); i++) {
		for (int j = 0; j < 4; j++) {
			wierzcholkiV.push_back(obiekty2[i].get(j));
		}
	}


	//cout << "wektor sciana1: " << Sciana1 << endl;

	GLfloat wierzcholki3[9999];

	int k = 0;
	for (int i = 0; i < 54; i++) {
		for (int j = 0; j < 4; j++) {
			//wierzcholki3[j] = obiekty[i].getX;
			//cout << "i = " << i << " j = " << j <<" k = "<<k<< endl;
			if (j == 0) {
				wierzcholki3[k] = obiekty2[i].getX();
			}
			else if (j == 1) {
				wierzcholki3[k] = obiekty2[i].getY();
			}
			else if (j == 2) {
				wierzcholki3[k] = obiekty2[i].getZ();
			}
			else {
				wierzcholki3[k] = obiekty2[i].getW();
			}
			k++;
		}
	}






	//cout << "sizeof: " << sizeof(obiekty2) << endl;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//cout << "wierz size: " << wierz.size() << endl << "sizeof glfloat: " << sizeof(GLfloat) << endl;
	//cout << "sizeof obiekty2: " << sizeof(obiekty2)/15 << endl << "sizeof Wektor: " << sizeof(Wektor)/15 << endl;
	//glBufferData(GL_ARRAY_BUFFER, (sizeof(obiekty2)/15)*(sizeof(Wektor)/15), obiekty2, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, wierzcholkiV.size() * sizeof(GLfloat), &wierzcholkiV[0], GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(wierzcholki3), wierzcholki3, GL_STATIC_DRAW); //flaga stream draw, static, dynamic
	//przypisywanie i wyswietlanie



}

void ProgramMPGK::stworzenieIBO() //stworzenie bufora indeksow. indeksy odpowiadaja wierzcholkom z vbo
{
	//w indeksyTab podaje sie kolejne wierzcholki ktore beda rysowane. glowny kwadrat sklada sie z dwoch trojkatow + maly kwadrat w rogu

	/*GLuint indeksyTab[] = {
		0, 1, 2,
		1, 2, 3,
		//4, 5, 6,//
		//7, 8, 9//
		7,8,9,
		8,9,10,
		11,12,13,
		11,13,14,
		15,16,17,
		16,17,18
	};*/
	GLuint indeksyTab[] = {
		0, 1, 2,
		1, 2, 3,
		//4, 5, 6,//
		//7, 8, 9//
		7,8,9,
		8,9,10,
		11,12,13,
		11,13,14,
		15,16,17,
		16,17,18,
		19,20,21,
		20,21,22,
		23,24,25,
		24,25,26
	};


	//indeksy pozwalaja wielokrotne odwolywanie sie do danego wierzcholka
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeksyTab), indeksyTab, GL_STATIC_DRAW);
}
//w starszych wersjach opengl potok(pipeline) byl skonfigurowane na stale, obecnie samemu trzeba go skonfigurowac za pomoca "shaderow" (od opengl 3.3)
void ProgramMPGK::stworzenieProgramu()
{
	programZShaderami = glCreateProgram();

	if (programZShaderami == 0)
	{
		std::cerr << "Blad podczas tworzenia programu shaderow." << std::endl;
		system("pause");
		exit(1);
	}
	//dane do shaderow sa przekazywane za pomoca zmiennych globalnych (dla danego shadera) oznaczonych "in" i wyprowadzane "out"
	//version - 330= 3.3, core = brak kompatybilnosci wstecznej
	//GLSL jest jezykiem typowanym, nazwy zmiennych tworzy sie zgodnie z zasadami jezyka C
	//macierze sa ulozone w porzadku kolumny-wiersze
	//#version 330 core \n  zawsze musi byc \n w linijce okreslania wersji

	// ten kod w polaczeniu z klasa wczytajShader zastepuje oryginalny kod w kt�rym shadery znajduja sie bezposrednio w kodzie c++
	string vertexShaderString = wczytajShader("vertexShader");
	string fragmentShaderString = wczytajShader("fragmentShader");
	const char *vertexShader = vertexShaderString.c_str();
	const char *fragmentShader = fragmentShaderString.c_str();

	//Zapis shaderow do pliku
	//zapiszShader("vertexShaderKopia", vertexShader);
	//zapiszShader("fragmentShaderKopia", fragmentShader);

	//dodawnaie do programu shaderow
	vertexShaderId = dodanieDoProgramu(programZShaderami, vertexShader, GL_VERTEX_SHADER);
	fragmentShaderId = dodanieDoProgramu(programZShaderami, fragmentShader, GL_FRAGMENT_SHADER);

	//sprawdzanie linkowanie, tworzenie zmiennej czy linkowanie zakonczylo sie sukcesem (GL_LINK_STATUS)
	GLint linkowanieOK = 0;
	glLinkProgram(programZShaderami);
	glGetProgramiv(programZShaderami, GL_LINK_STATUS, &linkowanieOK);
	if (linkowanieOK == GL_FALSE) {
		//wydobywanie danych bledu z dziennika
		GLint dlugoscLoga = 0;
		glGetProgramiv(programZShaderami, GL_INFO_LOG_LENGTH, &dlugoscLoga);
		std::vector<GLchar> log(dlugoscLoga);
		glGetProgramInfoLog(programZShaderami, dlugoscLoga, NULL, &log[0]);
		std::cerr << "Blad podczas linkowania programu shaderow." << std::endl;
		for (std::vector<GLchar>::const_iterator i = log.begin(); i != log.end(); ++i)
			std::cerr << *i;
		std::cerr << std::endl;
		glDeleteProgram(programZShaderami);
		system("pause");
		exit(1);
	}

	GLint walidacjaOK = 0;
	glValidateProgram(programZShaderami);
	glGetProgramiv(programZShaderami, GL_VALIDATE_STATUS, &walidacjaOK);
	if (walidacjaOK == GL_FALSE) {
		GLint dlugoscLoga = 0;
		glGetProgramiv(programZShaderami, GL_INFO_LOG_LENGTH, &dlugoscLoga);
		std::vector<GLchar> log(dlugoscLoga);
		glGetProgramInfoLog(programZShaderami, dlugoscLoga, NULL, &log[0]);
		std::cerr << "Blad podczas walidacji programu shaderow." << std::endl;
		for (std::vector<GLchar>::const_iterator i = log.begin(); i != log.end(); ++i)
			std::cerr << *i;
		std::cerr << std::endl;
		glDeleteProgram(programZShaderami);
		system("pause");
		exit(1);
	}
	//program staje sie aktualnie uzywanym programem
	glUseProgram(programZShaderami);

	//odpytujemt program z shaderami o zmienna uniform. robimy to przy pomocy nazwy. zwraca indeks (-1 oznacza ze nie znalazl)
	zmiennaShader = glGetUniformLocation(programZShaderami, "zmianaShader");
	zmiennaObrShader = glGetUniformLocation(programZShaderami, "obrotShader");
	if (zmiennaShader == -1)
	{
		std::cerr << "Nie znalezion zmiennej uniform." << std::endl;
		system("pause");
		exit(1);
	}
}

//tworzymy zarowno vertexshader i fragmentshader
GLuint ProgramMPGK::dodanieDoProgramu(GLuint programZShaderami, const GLchar * tekstShadera, GLenum typShadera)
{

	/* WERSJA ROBOCZA
	GLuint shader = glCreateShader(typShadera);

	// 35633 -> vertex shader, 35632 -> fragment shader
	const GLchar * typShaderaTekst = typShadera == 35633 ? "vertex" : "fragment";
	//sprawdzamy czy zostaly poprawnie utworzone
	if (shader == 0) {
		std::cerr << "Blad podczas tworzenia " << typShaderaTekst << " shadera." << std::endl;
		system("pause");
		exit(0);
	}
	//
	//cout << shader << endl;
	cout << "-----------------------------------" << endl;

	string str(tekstShadera);
	cout << str << endl;

	int iloscLinii = count(str.begin(), str.end(), '\n');
	const int iloscLinii2 = iloscLinii;
	cout << "Ilosc linii " << iloscLinii << endl;


	const GLchar * tekstShaderaTab[1]; //ilosc linii w shaderze
//	const GLchar * tekstShaderaTab[iloscLinii2];
//	tekstShaderaTab[0] = tekstShadera;
	//tekstShaderaTab[0] = "ddd";
	//tekstShaderaTab[1] = "bbb";
	//cout << tekstShaderaTab[0] << endl;
	//cout << tekstShadera << endl;
//	int iloscZnakow = strlen(tekstShadera);
//	cout << "ilosc znakow " << iloscZnakow << '\n';



	//ifstream ifs(str.c_str());
	//int iloscLinii = count(str.begin(), str.end(), '\n');

	//cout << "Ilosc linii " << iloscLinii << endl;




	cout << "-----------------------------------" << endl;

	GLint dlugoscShadera[1];
	//dlugoscShadera[0] = strlen(tekstShadera);
	//dlugoscShadera[0] = iloscZnakow;

	//glShaderSource(shader, iloscLinii, tekstShaderaTab, dlugoscShadera);

	glShaderSource(shader, 1, tekstShaderaTab, dlugoscShadera); //
	//kompilujemy shader i tworzymy zmienna
	glCompileShader(shader);
	GLint kompilacjaOK = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &kompilacjaOK);
	if (kompilacjaOK == GL_FALSE)
	{
		GLint dlugoscLoga = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &dlugoscLoga);
		std::vector<GLchar> log(dlugoscLoga);
		glGetShaderInfoLog(shader, dlugoscLoga, NULL, &log[0]);
		std::cerr << std::endl;
		std::cerr << "Blad podczas kompilacji " << typShaderaTekst << " shadera." << std::endl;
		std::cerr << std::endl;
		std::cerr << "log: ";
		for (std::vector<GLchar>::const_iterator i = log.begin(); i != log.end(); ++i)
			std::cerr << *i;
		std::cerr << std::endl;




		glDeleteShader(shader);
		system("pause");
		exit(1);
	}
	//dodajemy skopilowany shader do programu
	glAttachShader(programZShaderami, shader);
	return shader;
	*/
	GLuint shader = glCreateShader(typShadera);

	// 35633 -> vertex shader, 35632 -> fragment shader
	const GLchar * typShaderaTekst = typShadera == 35633 ? "vertex" : "fragment";
	//sprawdzamy czy zostaly poprawnie utworzone
	if (shader == 0) {
		std::cerr << "Blad podczas tworzenia " << typShaderaTekst << " shadera." << std::endl;
		//system("pause");
		exit(0);
	}

	const GLchar * tekstShaderaTab[1];
	tekstShaderaTab[0] = tekstShadera;
	GLint dlugoscShadera[1];
	dlugoscShadera[0] = strlen(tekstShadera);
	glShaderSource(shader, 1, tekstShaderaTab, dlugoscShadera);
	//kompilujemy shader i tworzymy zmienna
	glCompileShader(shader);
	GLint kompilacjaOK = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &kompilacjaOK);
	if (kompilacjaOK == GL_FALSE)
	{
		GLint dlugoscLoga = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &dlugoscLoga);
		std::vector<GLchar> log(dlugoscLoga);
		glGetShaderInfoLog(shader, dlugoscLoga, NULL, &log[0]);
		std::cerr << std::endl;
		std::cerr << "Blad podczas kompilacji " << typShaderaTekst << " shadera." << std::endl;
		std::cerr << std::endl;
		std::cerr << "log: ";
		for (std::vector<GLchar>::const_iterator i = log.begin(); i != log.end(); ++i)
			std::cerr << *i;
		std::cerr << std::endl;
		glDeleteShader(shader);
		system("pause");
		exit(1);
	}
	//dodajemy skopilowany shader do programu
	glAttachShader(programZShaderami, shader);
	return shader;
}

void ProgramMPGK::sprawdzenieWersji()
{
	std::cout << "Wersja GLEW: " << glewGetString(GLEW_VERSION) << std::endl;
	std::cout << "Wersja VENDOR: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Wersja REDERER: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Wersja GL: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "Wersja GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

int main(int argc, char** argv)
{
	ProgramMPGK obiektMPGK(786, 786, 100, 100);

	//Testy stopni i radianow
	cout << "5 radianow = " << naStopnie(5) << endl;
	cout << "5 stopni = " << naRadiany(5) << endl;

	Macierz maci;
	Wektor wekt;
	//Test 1.1
	cout << "Test 1.1" << endl;
	Macierz mac0;
	maci.Wypisz(mac0);
	//Test 1.2
	cout << endl << "Test 1.2" << endl;
	Macierz mac1(4);
	maci.Wypisz(mac1);
	//Test 1.3
	cout << endl << "Test 1.3" << endl;
	float mac2_f[4][4] = {
		{ 1,2,3,4 }, { 5,6,7,8 }, { 9,10,11,12 }, { 13,14,15,16 }
	};
	Macierz mac2(mac2_f);
	maci.Wypisz(mac2);

	//cout << "---------------" << endl;
	float mac2_f2[3][3] = {
		{ 1,2,3}, { 5,6,7 }, { 9,10,11 }
	};
	Macierz mac2f(mac2_f2);
	maci.Wypisz(mac2f);


	//Test 2.1
	cout << endl << "Test 2.1" << endl;
	Macierz mac21_1(4);
	Macierz mac21_2(8);
	cout << "Macierz 21_1 - same 4" << endl;
	maci.Wypisz(mac21_1);
	cout << "Macierz 21_2 - same 8" << endl;
	maci.Wypisz(mac21_2);;;
	cout << "Przypisanie tablicy" << endl;
	mac21_1 = mac21_2;
	cout << "Macierz 21_1 po przypisaniu" << endl;
	maci.Wypisz(mac21_1);
	//Test 2.2
	cout << endl << "Test 2.2" << endl;
	Macierz mac22_1(3);
	Macierz mac22_2(4);
	cout << "Macierz 22_1" << endl;
	maci.Wypisz(mac22_1);;
	cout << "Macierz 22_2" << endl;
	maci.Wypisz(mac22_2);;
	cout << "Dodawanie" << endl;
	Macierz mac22_3;
	mac22_3 = mac22_1 + mac22_2;
	maci.Wypisz(mac22_3);;
	Macierz mac22_4(1);
	mac22_4 = mac2f + mac22_2;

	//Test 2.3
	cout << endl << "Test 2.3" << endl;
	Macierz mac23_1(1);
	Macierz mac23_2(3);
	cout << "Macierz 23_1" << endl;
	maci.Wypisz(mac23_2);;
	cout << "Macierz 23_2" << endl;
	maci.Wypisz(mac23_2);
	cout << "Dodawanie z przypisaniem" << endl;
	mac23_1 += mac23_2;
	maci.Wypisz(mac23_1);
	//Test 2.4
	cout << endl << "Test 2.4" << endl;
	Macierz mac24_1(6);
	Macierz mac24_2(2);
	cout << "Macierz 24_1" << endl;
	maci.Wypisz(mac24_1);
	cout << "Macierz 24_2" << endl;
	maci.Wypisz(mac24_2);
	cout << "Odejmowanie" << endl;
	Macierz mac24_3;
	mac24_3 = mac24_1 - mac24_2;
	maci.Wypisz(mac24_3);
	//Test 2.5 
	cout << endl << "Test 2.5" << endl;
	Macierz mac25_1(9);
	Macierz mac25_2(7);
	cout << "Macierz 25_1" << endl;
	maci.Wypisz(mac25_1);
	cout << "Macierz 25_2" << endl;
	maci.Wypisz(mac25_2);
	cout << "Odejmowanie z przypisaniem" << endl;
	mac25_1 -= mac25_2;
	maci.Wypisz(mac25_2);
	//Test 2.6
	cout << endl << "Test 2.6" << endl;
	Macierz mac26_1(6);
	int mnoz1 = 5;
	cout << "Macierz 26_1" << endl;
	maci.Wypisz(mac26_1);
	cout << "Liczba mnozaca macierz" << endl;
	cout << mnoz1 << endl;
	cout << "Mnozenie macierzy przez liczbe calkowita" << endl;
	Macierz mac26_2;
	mac26_2 = mac26_1 * mnoz1;
	maci.Wypisz(mac26_2);
	//Test 2.7
	cout << endl << "Test 2.7" << endl;
	Macierz mac27_1(4);
	int mnoz2 = 3;
	cout << "Macierz 27_1" << endl;
	maci.Wypisz(mac27_1);;
	cout << "Liczba mnozaca macierz" << endl;
	cout << mnoz2 << endl;
	cout << "Mnozenie macierzy przez liczbe calkowita z przypisaniem" << endl;
	mac27_1 *= mnoz2;
	maci.Wypisz(mac27_1);
	//Test 2.8 
	cout << endl << "Test 2.8" << endl;
	Macierz mac28_1(3);
	Macierz mac28_2(4);
	mac28_1.set(0, 0, 9);
	mac28_2.set(0, 0, 2);
	cout << "Macierz 28_1" << endl;
	maci.Wypisz(mac28_1);
	cout << "Macierz 28_2" << endl;
	maci.Wypisz(mac28_2);
	cout << "Mnozenie macierzy" << endl;
	Macierz mac28_3;
	mac28_3 = mac28_1 * mac28_2;
	maci.Wypisz(mac28_3);
	//Test 2.9
	cout << endl << "Test 2.9" << endl;
	Macierz mac29_1(3);
	Macierz mac29_2(4);
	mac29_1.set(0, 0, 9);
	cout << "Macierz 29_1" << endl;
	maci.Wypisz(mac29_1);
	cout << "Macierz 29_2" << endl;
	maci.Wypisz(mac29_2);
	cout << "Mnozenie macierzy z przypisaniem" << endl;
	mac29_1 *= mac29_2;
	maci.Wypisz(mac29_1);

	//Test 2.10
	cout << endl << "Test 2.10" << endl;
	Macierz mac210(1);
	mac210.set(0, 0, 9);
	mac210.set(1, 0, 3);
	mac210.set(1, 3, 2);
	Wektor w28(3, 4, 5, 6);
	Wektor w29(3, 4, 5);
	Wektor wwynik(1);
	cout << "Macierz 210" << endl;
	maci.Wypisz(mac210);;
	cout << "Wektor 28" << endl;
	//cout << w28 << endl;
	cout << "Mnozenie macierzy przez wektor" << endl;
	wwynik = mac210 * w28;
	cout << "Wynik mnozenia" << endl;
	//cout << wwynik << endl;
	wwynik = mac210 * w29;
	//Test 2.11
	cout << endl << "Test 2.11" << endl;
	cout << mac210 << endl;

	//Test 3.1
	cout << endl << "Test 3.1" << endl;
	maci.Wypisz(mac1);;
	cout << "zmiana elementu na 1 miejscu na 9" << endl;
	mac1.set(0, 0, 9);
	maci.Wypisz(mac1);;
	cout << "pobranie elementu z 1 miejsca" << endl;
	cout << mac1.get(0, 0) << endl;
	//Test 3.2 
	cout << endl << "Test 3.2 TODO" << endl;
	Macierz macWypisz4(mac2_f);
	Macierz macWypisz3(mac2_f2);
	maci.Wypisz(macWypisz4);
	//Test 3.3
	cout << endl << "Test 3.3" << endl;
	Macierz macJ = maci.Jednostkowa();
	maci.Wypisz(macJ);;
	//Test 3.4 
	cout << endl << "Test 3.4" << endl;
	Macierz macT1(1);
	macT1.set(0, 0, 9);
	macT1.set(3, 0, 2);
	macT1.set(1, 2, 7);
	macT1.set(0, 3, 4);
	macT1.set(2, 3, 8);
	cout << "Macierz T1" << endl;
	maci.Wypisz(macT1);;
	Macierz macT2 = maci.Transponowanie(macT1);
	cout << "Macierz T1 Transponowana" << endl;
	maci.Wypisz(macT2);;
	cout << "Macierz T2" << endl;
	maci.Wypisz(mac2f);;
	Macierz macT3 = maci.Transponowanie(mac2f);
	cout << "Macierz T2 Transponowana" << endl;
	maci.Wypisz(macT3);;

	//Test 3.5 TODO
	cout << endl << "Test 3.5 TODO" << endl;
	cout << "Macierz 1 przed odwroceniem" << endl;
	float macTest[3][3] = {
		{1,0,3},{0,1,4},{0,0,1}
	};
	maci.Wypisz(macTest);
	Macierz mac3_5 = maci.Odwracanie(macTest);
	cout << "Macierz 1 po odwroceniu" << endl;
	maci.Wypisz(mac3_5);

	cout << "Mnozenie macierzy odwrocanej przez oryginalna" << endl;
	Macierz macMnoz;
	macMnoz = mac3_5 * macTest;
	maci.Wypisz(macMnoz);
	cout << "Macierz 1_1 przed odwroceniem" << endl;
	mac2f.set(0, 0, 4);
	maci.Wypisz(mac2f);
	Macierz mac3_5_1 = maci.Odwracanie(mac2f);
	cout << "Macierz 1_1 po odwroceniu" << endl;
	//cout << mac3_5_1 << endl;

	maci.Wypisz(mac3_5_1);

	float mac3_6f[4][4] = {
		{5,2,3,4},{5,5,3,8},{5,10,11,5},{5,14,15,16}
	};
	Macierz mac3_6(mac3_6f);
	cout << "Macierz 2 przed odwroceniem" << endl;
	maci.Wypisz(mac3_6);;
	Macierz mac3_7 = maci.Odwracanie(mac3_6);
	cout << "Macierz 2 po odwroceniu" << endl;
	maci.Wypisz(mac3_7);;
	//Macierz wektNorm2(6, 5, 4, 2);



	//cout << mac2[1][4] << endl;

	Macierz mac3[4][4] = {
		{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}
	};
	//cout << mac2 << endl;
	/*for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << mac2[i][j]<<" ";
		}
	}*/


	obiektMPGK.stworzenieOkna(argc, argv);
	obiektMPGK.inicjalizacjaGlew();
	obiektMPGK.sprawdzenieWersji();
	obiektMPGK.stworzenieVAO();
	obiektMPGK.stworzenieVBO();
	obiektMPGK.stworzenieIBO();
	obiektMPGK.stworzenieProgramu();
	glutDisplayFunc(obiektMPGK.wyswietl); //wywolywana przez petle glut w momencie kiedy konieczne jest odwiezenie obrazu
	glutIdleFunc(obiektMPGK.wyswietl); //wywolywane w przypadku bezczynnosci
	//glutSpecialFunc(specialKeys);

	glutCloseFunc(obiektMPGK.usun); //w momencie zamykania okna
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS); //po zamknieciu okna kontrola wraca do programu
	//domyslnie GLUT_ACTION_EXIT i natychmiastowe wyjscie z programu

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //ustaawia kolor tla RGBA, parametry w przedziale 0 do 1

	glutMainLoop(); //petla GLUT ktora nasluchuje czy nastapi jakies zdarzenie

	//system("pause");
	return 0;
}