#include "Header.h"
#include<iostream>
#include<fstream>
#include<string>
#include "Wektor.h"



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



void ProgramMPGK::stworzenieVBO() //tworzy bufor (na wierzcholki) i wypelnia go danymi
{
	//deklarujemy tablice na zmienne typu GLfloat i wstawiamy do niej X Y Z W kazdego wierzcholka oraz kolor - R G B A
	//GLfloat wierzcholki[] = {
	//	//wierzcholki nalezace do glownego kwadratu (1,2,3,4) - front - zolty
	//	-0.4f, -0.4f, 0.0f, 1.0f, //wierzcholek
	//	 1.0f,  1.0f, 0.0f, 1.0f, //kolor
	//	 0.4f, -0.4f, 0.0f, 1.0f, //wierzcholek
	//	 1.0f,  1.0f, 0.0f, 1.0f, //kolor
	//	-0.4f,  0.4f, 0.0f, 1.0f, //wierzcholek
	//	 1.0f,  1.0f, 0.0f, 1.0f, //kolor
	//	 0.4f,  0.4f, 0.0f, 1.0f, //wierzcholek
	//	 1.0f,  1.0f, 0.0f, 1.0f, //kolor
	//	 //drugi trojkat w prawym gornym rogu - nieuzywany do szescianu - brak odwolania w indeksyTab
	//	 0.6f,  0.6f, 0.0f, 1.0f, //wierzcholek
	//	 1.0f,  1.0f, 1.0f, 1.0f,  //kolor  
	//	 0.6f,  0.9f, 0.0f, 1.0f, //wierzcholek
	//	 1.0f,  1.0f, 1.0f, 1.0f,  //kolor  
	//	 0.9f,  0.6f, 0.0f, 1.0f, //wierzcholek
	//	 1.0f,  1.0f, 1.0f, 1.0f,  //kolor    
	//	 //wierzcholki lewego boku - czerwony
	//	-0.4f, -0.4f, 0.0f, 1.0f, //wierzcholek
	//	 1.0f,  0.0f, 0.0f, 1.0f, //kolor
	//	 -0.4f, 0.4f, 0.0f, 1.0f, //wierzcholek
	//	 1.0f,  0.0f, 0.0f, 1.0f, //kolor
	//	-0.4f,  -0.4f, 0.8f, 1.0f, //wierzcholek
	//	 1.0f,  0.0f, 0.0f, 1.0f, //kolor
	//	 -0.4f,  0.4f, 0.8f, 1.0f, //wierzcholek
	//	 1.0f,  0.0f, 0.0f, 1.0f, //kolor
	//	 //wierzcholki prawego boku - niebieski
	//	 0.4f, -0.4f, 0.0f, 1.0f, //wierzcholek
	//	 0.0f,  0.0f, 1.0f, 1.0f, //kolor
	//	 0.4f,  0.4f, 0.0f, 1.0f, //wierzcholek
	//	 0.0f,  0.0f, 1.0f, 1.0f, //kolor
	//	 0.4f,  0.4f, 0.8f, 1.0f, //wierzcholek
	//	 0.0f,  0.0f, 1.0f, 1.0f, //kolor
	//	 0.4f,  -0.4f, 0.8f, 1.0f, //wierzcholek
	//	 0.0f,  0.0f, 1.0f, 1.0f, //kolor
	//	 //wierzcholki dolnej scianki - zielony
	//	-0.4f, -0.4f, 0.0f, 1.0f, //wierzcholek
	//	 0.0f,  1.0f, 0.0f, 1.0f, //kolor
	//	 0.4f, -0.4f, 0.0f, 1.0f, //wierzcholek
	//	 0.0f,  1.0f, 0.0f, 1.0f, //kolor
	//	-0.4f, -0.4f, 0.8f, 1.0f, //wierzcholek
	//	 0.0f,  1.0f, 0.0f, 1.0f, //kolor
	//	 0.4f, -0.4f, 0.8f, 1.0f, //wierzcholek
	//	 0.0f,  1.0f, 0.0f, 1.0f, //kolor
	//	 //wierzcholki gornej scianki - biale
	//	-0.4f,  0.4f, 0.0f, 1.0f, //wierzcholek
	//	 1.0f,  1.0f, 1.0f, 1.0f, //kolor
	//	 0.4f,  0.4f, 0.0f, 1.0f, //wierzcholek
	//	 1.0f,  1.0f, 1.0f, 1.0f, //kolor
	//	-0.4f,  0.4f, 0.8f, 1.0f, //wierzcholek
	//	 1.0f,  1.0f, 1.0f, 1.0f, //kolor
	//	 0.4f,  0.4f, 0.8f, 1.0f, //wierzcholek
	//	 1.0f,  1.0f, 1.0f, 1.0f, //kolor 
	//	  //wierzcholki tylnej scianki - blekitny
	//	-0.4f, -0.4f, 0.8f, 1.0f, //wierzcholek
	//	 0.0f,  1.0f, 1.0f, 1.0f, //kolor
	//	 0.4f, -0.4f, 0.8f, 1.0f, //wierzcholek
	//	 0.0f,  1.0f, 1.0f, 1.0f, //kolor
	//	-0.4f,  0.4f, 0.8f, 1.0f, //wierzcholek
	//	 0.0f,  1.0f, 1.0f, 1.0f, //kolor
	//	 0.4f,  0.4f, 0.8f, 1.0f, //wierzcholek
	//	 0.0f,  1.0f, 1.0f, 1.0f, //kolor
	//};
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
	//cout << "W1 " << W1 << endl << "K1 " << K1 << endl;

	//cout << "W1.x: " << W1.getX() << " W1.y: " << W1.getY() << " W1.z: " << W1.getZ() << " W1.w: " << W1.getW() << endl;
	//float W1x = W1.getX();

	/*GLfloat Sciana1[] = {
		W1.getX(), W1.getY(), W1.getZ(), W1.getW(),
		K1.getX(), K1.getY(), K1.getZ(), K1.getW(),
		W2.getX(), W2.getY(), W2.getZ(), W2.getW(),
		K1.getX(), K1.getY(), K1.getZ(), K1.getW(),
		W3.getX(), W3.getY(), W3.getZ(), W3.getW(),
		K1.getX(), K1.getY(), K1.getZ(), K1.getW(),
		W4.getX(), W4.getY(), W4.getZ(), W4.getW(),
		K1.getX(), K1.getY(), K1.getZ(), K1.getW(),
	};

	GLfloat Sciana2[] = {
		W5.getX(), W5.getY(), W5.getZ(), W5.getW(),
		K2.getX(), K2.getY(), K2.getZ(), K2.getW(),
		W6.getX(), W6.getY(), W6.getZ(), W6.getW(),
		K2.getX(), K2.getY(), K2.getZ(), K2.getW(),
		W7.getX(), W7.getY(), W7.getZ(), W7.getW(),
		K2.getX(), K2.getY(), K2.getZ(), K2.getW(),
	};

	GLfloat Sciana3[] = {
		W8.getX(), W8.getY(), W8.getZ(), W8.getW(),
		K3.getX(), K3.getY(), K3.getZ(), K3.getW(),
		W9.getX(), W9.getY(), W9.getZ(), W9.getW(),
		K3.getX(), K3.getY(), K3.getZ(), K3.getW(),
		W10.getX(), W10.getY(), W10.getZ(), W10.getW(),
		K3.getX(), K3.getY(), K3.getZ(), K3.getW(),
		W11.getX(), W11.getY(), W11.getZ(), W11.getW(),
		K3.getX(), K3.getY(), K3.getZ(), K3.getW(),
	};

	GLfloat Sciana4[] = {
		W12.getX(), W12.getY(), W12.getZ(), W12.getW(),
		K4.getX(), K4.getY(), K4.getZ(), K4.getW(),
		W13.getX(), W13.getY(), W13.getZ(), W13.getW(),
		K4.getX(), K4.getY(), K4.getZ(), K4.getW(),
		W14.getX(), W14.getY(), W14.getZ(), W14.getW(),
		K4.getX(), K4.getY(), K4.getZ(), K4.getW(),
		W15.getX(), W15.getY(), W15.getZ(), W15.getW(),
		K4.getX(), K4.getY(), K4.getZ(), K4.getW(),
	};

	GLfloat Sciana5[] = {
		W16.getX(), W16.getY(), W16.getZ(), W16.getW(),
		K5.getX(), K5.getY(), K5.getZ(), K5.getW(),
		W17.getX(), W17.getY(), W17.getZ(), W17.getW(),
		K5.getX(), K5.getY(), K5.getZ(), K5.getW(),
		W18.getX(), W18.getY(), W18.getZ(), W18.getW(),
		K5.getX(), K5.getY(), K5.getZ(), K5.getW(),
		W19.getX(), W19.getY(), W19.getZ(), W19.getW(),
		K5.getX(), K5.getY(), K5.getZ(), K5.getW(),
	};

	GLfloat Sciana6[] = {
		W20.getX(), W20.getY(), W20.getZ(), W20.getW(),
		K6.getX(), K6.getY(), K6.getZ(), K6.getW(),
		W21.getX(), W21.getY(), W21.getZ(), W21.getW(),
		K6.getX(), K6.getY(), K6.getZ(), K6.getW(),
		W22.getX(), W22.getY(), W22.getZ(), W22.getW(),
		K6.getX(), K6.getY(), K6.getZ(), K6.getW(),
		W23.getX(), W23.getY(), W23.getZ(), W23.getW(),
		K6.getX(), K6.getY(), K6.getZ(), K6.getW(),
	};

	GLfloat Sciana7[] = {
		W24.getX(), W24.getY(), W24.getZ(), W24.getW(),
		K7.getX(), K7.getY(), K7.getZ(), K7.getW(),
		W25.getX(), W25.getY(), W25.getZ(), W25.getW(),
		K7.getX(), K7.getY(), K7.getZ(), K7.getW(),
		W26.getX(), W26.getY(), W26.getZ(), W26.getW(),
		K7.getX(), K7.getY(), K7.getZ(), K7.getW(),
		W27.getX(), W27.getY(), W27.getZ(), W27.getW(),
		K7.getX(), K7.getY(), K7.getZ(), K7.getW(),
	};*/

	//long lenS1 = sizeof(Sciana1);
	//long lenS2 = sizeof(Sciana2);
	//long lenS3 = sizeof(Sciana3);
	//long lenS4 = sizeof(Sciana4);
	//long lenS5 = sizeof(Sciana5);
	//long lenS6 = sizeof(Sciana6);
	//long lenS7 = sizeof(Sciana7);

	//long lenSum2 = lenS1 + lenS2;
	//long lenSum3 = lenSum2 + lenS3;
	//long lenSum4 = lenSum3 + lenS4;
	//long lenSum5 = lenSum4 + lenS5;
	//long lenSum6 = lenSum5 + lenS6;
	//long lenSum7 = lenSum6 + lenS7;
	//
	//long lenA = sizeof(Sciana1);
	//long lenB = sizeof(Sciana2);
	//long lenC = sizeof(Sciana3);
	//long lenD = sizeof(Sciana4);

	////int newArray[lenA + lenB + lenC + lenD + 1];

	//GLfloat wierzcholki3[9999] = {0};

	//memcpy(&wierzcholki3[0], Sciana1, lenA);
	//memcpy(&wierzcholki3[lenA], Sciana2, lenB);
	//memcpy(&wierzcholki3[lenA + lenB], Sciana3, lenC);
	//memcpy(&wierzcholki3[lenA + lenB + lenC], Sciana4, lenD);

	Wektor obiekty[] = {
		 { -0.4f, -0.4f, 0.0f, 1.0f },
		 { 1.0f,  1.0f, 0.0f, 1.0f },
		 { 0.4f, -0.4f, 0.0f, 1.0f },
		 { 1.0f,  1.0f, 0.0f, 1.0f },
		 { -0.4f,  0.4f, 0.0f, 1.0f },
		 { 1.0f,  1.0f, 0.0f, 1.0f },
		 { 0.4f,  0.4f, 0.0f, 1.0f },
		 { 1.0f,  1.0f, 0.0f, 1.0f },

		 { 0.6f,  0.6f, 0.0f, 1.0f },
		 { 1.0f,  1.0f, 1.0f, 1.0f },
		 { 0.6f,  0.9f, 0.0f, 1.0f },
		 { 1.0f,  1.0f, 1.0f, 1.0f },
		 { 0.9f,  0.6f, 0.0f, 1.0f },
		 { 1.0f,  1.0f, 1.0f, 1.0f },

		 { -0.4f, -0.4f, 0.0f, 1.0f },
		 { 1.0f, 0.0f, 0.0f, 1.0f },
		 { -0.4f, 0.4f, 0.0f, 1.0f },
		 { 1.0f, 0.0f, 0.0f, 1.0f },
		 { -0.4f, -0.4f, 0.8f, 1.0f },
		 { 1.0f, 0.0f, 0.0f, 1.0f },
		 { -0.4f, 0.4f, 0.8f, 1.0f },
		 { 1.0f, 0.0f, 0.0f, 1.0f },

		 { 0.4f, -0.4f, 0.0f, 1.0f },
		 { 0.0f,  0.0f, 1.0f, 1.0f },
		 { 0.4f,  0.4f, 0.0f, 1.0f },
		 { 0.0f,  0.0f, 1.0f, 1.0f },
		 { 0.4f,  0.4f, 0.8f, 1.0f },
		 { 0.0f,  0.0f, 1.0f, 1.0f },
		 { 0.4f,  -0.4f, 0.8f, 1.0f },
		 { 0.0f,  0.0f, 1.0f, 1.0f },

		 { -0.4f, -0.4f, 0.0f, 1.0f },
		  { 0.0f,  1.0f, 0.0f, 1.0f },
		 { 0.4f, -0.4f, 0.0f, 1.0f },
		  { 0.0f,  1.0f, 0.0f, 1.0f },
		 { -0.4f, -0.4f, 0.8f, 1.0f },
		  { 0.0f,  1.0f, 0.0f, 1.0f },
		 { 0.4f, -0.4f, 0.8f, 1.0f },
		 { 0.0f,  1.0f, 0.0f, 1.0f },

		 { -0.4f,  0.4f, 0.0f, 1.0f },
		 { 1.0f,  1.0f, 1.0f, 1.0f },
		 { 0.4f,  0.4f, 0.0f, 1.0f },
		 { 1.0f,  1.0f, 1.0f, 1.0f },
		 { -0.4f,  0.4f, 0.8f, 1.0f },
		 { 1.0f,  1.0f, 1.0f, 1.0f },
		 { 0.4f,  0.4f, 0.8f, 1.0f },
		 { 1.0f,  1.0f, 1.0f, 1.0f },

		 { -0.4f, -0.4f, 0.8f, 1.0f },
		 { 0.0f,  1.0f, 1.0f, 1.0f },
		 { 0.4f, -0.4f, 0.8f, 1.0f },
		 { 0.0f,  1.0f, 1.0f, 1.0f },
		 { -0.4f,  0.4f, 0.8f, 1.0f },
		 { 0.0f,  1.0f, 1.0f, 1.0f },
		 { 0.4f,  0.4f, 0.8f, 1.0f },
		 { 0.0f,  1.0f, 1.0f, 1.0f },
	};

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

	for (int i = 0; i < sizeof(obiekty2) / sizeof(obiekty[0]); i++) {
		for (int j = 0; j < 4; j++){
			wierzcholkiV.push_back(obiekty[i].get(j));
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



	/*GLfloat wierzcholki2[] = {

		W1.getX(), W1.getY(), W1.getZ(), W1.getW(),
		K1.getX(), K1.getY(), K1.getZ(), K1.getW(),
		W2.getX(), W2.getY(), W2.getZ(), W2.getW(),
		K1.getX(), K1.getY(), K1.getZ(), K1.getW(),
		W3.getX(), W3.getY(), W3.getZ(), W3.getW(),
		K1.getX(), K1.getY(), K1.getZ(), K1.getW(),
		W4.getX(), W4.getY(), W4.getZ(), W4.getW(),
		K1.getX(), K1.getY(), K1.getZ(), K1.getW(),

		W5.getX(), W5.getY(), W5.getZ(), W5.getW(),
		K2.getX(), K2.getY(), K2.getZ(), K2.getW(),
		W6.getX(), W6.getY(), W6.getZ(), W6.getW(),
		K2.getX(), K2.getY(), K2.getZ(), K2.getW(),
		W7.getX(), W7.getY(), W7.getZ(), W7.getW(),
		K2.getX(), K2.getY(), K2.getZ(), K2.getW(),

		W8.getX(), W8.getY(), W8.getZ(), W8.getW(),
		K3.getX(), K3.getY(), K3.getZ(), K3.getW(),
		W9.getX(), W9.getY(), W9.getZ(), W9.getW(),
		K3.getX(), K3.getY(), K3.getZ(), K3.getW(),
		W10.getX(), W10.getY(), W10.getZ(), W10.getW(),
		K3.getX(), K3.getY(), K3.getZ(), K3.getW(),
		W11.getX(), W11.getY(), W11.getZ(), W11.getW(),
		K3.getX(), K3.getY(), K3.getZ(), K3.getW(),

		W12.getX(), W12.getY(), W12.getZ(), W12.getW(),
		K4.getX(), K4.getY(), K4.getZ(), K4.getW(),
		W13.getX(), W13.getY(), W13.getZ(), W13.getW(),
		K4.getX(), K4.getY(), K4.getZ(), K4.getW(),
		W14.getX(), W14.getY(), W14.getZ(), W14.getW(),
		K4.getX(), K4.getY(), K4.getZ(), K4.getW(),
		W15.getX(), W15.getY(), W15.getZ(), W15.getW(),
		K4.getX(), K4.getY(), K4.getZ(), K4.getW(),

		W16.getX(), W16.getY(), W16.getZ(), W16.getW(),
		K5.getX(), K5.getY(), K5.getZ(), K5.getW(),
		W17.getX(), W17.getY(), W17.getZ(), W17.getW(),
		K5.getX(), K5.getY(), K5.getZ(), K5.getW(),
		W18.getX(), W18.getY(), W18.getZ(), W18.getW(),
		K5.getX(), K5.getY(), K5.getZ(), K5.getW(),
		W19.getX(), W19.getY(), W19.getZ(), W19.getW(),
		K5.getX(), K5.getY(), K5.getZ(), K5.getW(),

		W20.getX(), W20.getY(), W20.getZ(), W20.getW(),
		K6.getX(), K6.getY(), K6.getZ(), K6.getW(),
		W21.getX(), W21.getY(), W21.getZ(), W21.getW(),
		K6.getX(), K6.getY(), K6.getZ(), K6.getW(),
		W22.getX(), W22.getY(), W22.getZ(), W22.getW(),
		K6.getX(), K6.getY(), K6.getZ(), K6.getW(),
		W23.getX(), W23.getY(), W23.getZ(), W23.getW(),
		K6.getX(), K6.getY(), K6.getZ(), K6.getW(),

		W24.getX(), W24.getY(), W24.getZ(), W24.getW(),
		K7.getX(), K7.getY(), K7.getZ(), K7.getW(),
		W25.getX(), W25.getY(), W25.getZ(), W25.getW(),
		K7.getX(), K7.getY(), K7.getZ(), K7.getW(),
		W26.getX(), W26.getY(), W26.getZ(), W26.getW(),
		K7.getX(), K7.getY(), K7.getZ(), K7.getW(),
		W27.getX(), W27.getY(), W27.getZ(), W27.getW(),
		K7.getX(), K7.getY(), K7.getZ(), K7.getW(),
	};*/


	//cout << "sizeof: " << sizeof(obiekty2) << endl;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//cout << "wierz size: " << wierz.size() << endl << "sizeof glfloat: " << sizeof(GLfloat) << endl;
	//cout << "sizeof obiekty2: " << sizeof(obiekty2)/15 << endl << "sizeof Wektor: " << sizeof(Wektor)/15 << endl;
	//glBufferData(GL_ARRAY_BUFFER, (sizeof(obiekty2)/15)*(sizeof(Wektor)/15), obiekty2, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, wierzcholkiV.size()*sizeof(GLfloat), &wierzcholkiV[0], GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(wierzcholki3), wierzcholki3, GL_STATIC_DRAW); //flaga stream draw, static, dynamic
	//przypisywanie i wyswietlanie

//	wekt.Przypisz(wierzcholki, (sizeof(wierzcholki) / sizeof(*wierzcholki) / 4), sizeof(wierzcholki));

	//wekt.Konstruktor(wierzcholki);

	//float wynik = wekt.Normalizacja(5.0, 5.0, 5.0, 5.0);
	//cout << "wynik normalizacji: " << wynik;

	//float Wektor1[4] = { 5.0, 5.0, 5.0, 5.0 };
	//float Wektor2[4] = { 9.0, 9.0, 9.0, 9.0 };
	//float wynik = wekt.Normalizacja(Wektor1);
	//cout << "wynik normalizacji: " << wynik;

	//float wynik = wekt.Skalarny(Wektor1, Wektor2);
	//cout << "wynik skalara: " << wynik;


	//float wynik = wekt.Geometryczny(5.0, 5.0, 5.0, 5.0, 9.0, 9.0, 9.0, 9.0);
	//cout << "wynik geometr: " << wynik;

//	float Wektor1[4] = { 5.0, 5.0, 5.0,5.0};
//	float Wektor2[3] = { 5.0, 5.0, 5.0 };
//	Wektor w1(Wektor1, 4);

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


	//Testy
	Wektor wekt;

	Wektor wek1(3, 5, 6, 7);
	Wektor wek11(3, 5, 6, 7);
	Wektor wek12(3, 5, 6, 7);

	Wektor wek2(3, 9, 2, 7);
	Wektor wek21(3, 9, 2, 7);


	Wektor wek3, wek4;

	cout << "Test 2.8: " << wek1 << endl;

	wek3 = wek1 + wek2;
	cout << "Test 2.2: " << wek3 << endl;
	wek1 += wek2;
	cout << "Test 2.3: " << wek1 << endl;

	wek3 = wek11 - wek2;
	cout << "Test 2.4: " << wek3 << endl;
	wek11 -= wek21;
	cout << "Test 2.5: " << wek11 << endl;

	wek3 = wek12 * 2;
	cout << "Test 2.6: " << wek3 << endl;
	wek12 *= 2;
	cout << "Test 2.7: " << wek12 << endl;

	Wektor wekTest = { 0 };
	wekTest = wek12;
	cout << "Test 2.1: " << wekTest << endl;



	Wektor wektNorm = wekt.Normalizacja(6, 5, 4, 2);
	cout << "Test Normalizacji: " << wektNorm << endl;

	//float wektNorm2[4] = { 6,5,4,2 };
	Wektor wektNorm2(6, 5, 4, 2);
	Wektor wektNorm1 = wekt.Normalizacja(wektNorm2);
	cout << "Test Normalizacji_1: " << wektNorm1 << endl;

	//cout << "Test 3.3: ";
	float wynik = wekt.Skalarny(5.0, 5.0, 5.0, 5.0, 9.0, 9.0, 9.0, 9.0);
	cout << "Test iloczynu skalarnego: " << wynik << endl;;

	Wektor wektS1(5, 5, 5, 5);
	Wektor wektS2(9, 9, 9, 9);
	float wynik2 = wekt.Skalarny(wektS1, wektS2);
	cout << "Test iloczynu skalarnego_1: " << wynik2 << endl;


	Wektor wynikW = wekt.Wektorowy(0, 1, 5, 5, -1, 0, -2, 9);
	cout << "Test iloczynu wektorowego: " << wynikW << endl;;

	Wektor wektS3(0, 1, 5, 5);
	Wektor wektS4(-1, 0, -2, 9);
	Wektor wynikW2 = wekt.Wektorowy(wektS3, wektS4);
	//cout << "wekts3: " << wektS3 << endl;
	//cout << "wekts4: " << wektS4 << endl;
	cout << "Test iloczynu wektorowego_1: " << wynikW2 << endl;




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