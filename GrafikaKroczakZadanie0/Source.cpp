#include "Header.h"
#include<iostream>
#include<fstream>
#include<string>
#include <sstream>



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
/*
char **wczytajShaderTablica(const char *filePath) {
	char *content[200];
	int i = 0;
	ifstream fileStream(filePath, ios::in);

	if (!fileStream.is_open()) {
		cerr << "Nie mozna wczytac shadera " << filePath << ". Plik nie istnieje." << endl;
		system("pause");
	}

	char *line = "";
	while (!fileStream.eof()) {
		getline(fileStream, line);
		content[i] = line + "\n";
		i++;
		//content.append(line + "\n");
	}

	fileStream.close();

	return content;
}
*/


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
	GLfloat wierzcholki[] = {
		//wierzcholki nalezace do glownego kwadratu (1,2,3,4) - front - zolty
		-0.4f, -0.4f, 0.0f, 1.0f, //wierzcholek
		 1.0f,  1.0f, 0.0f, 1.0f, //kolor
		 0.4f, -0.4f, 0.0f, 1.0f, //wierzcholek
		 1.0f,  1.0f, 0.0f, 1.0f, //kolor
		-0.4f,  0.4f, 0.0f, 1.0f, //wierzcholek
		 1.0f,  1.0f, 0.0f, 1.0f, //kolor
		 0.4f,  0.4f, 0.0f, 1.0f, //wierzcholek
		 1.0f,  1.0f, 0.0f, 1.0f, //kolor
		 //drugi trojkat w prawym gornym rogu - nieuzywany do szescianu - brak odwolania w indeksyTab
		 0.6f,  0.6f, 0.0f, 1.0f, //wierzcholek
		 1.0f,  1.0f, 1.0f, 1.0f,  //kolor  
		 0.6f,  0.9f, 0.0f, 1.0f, //wierzcholek
		 1.0f,  1.0f, 1.0f, 1.0f,  //kolor  
		 0.9f,  0.6f, 0.0f, 1.0f, //wierzcholek
		 1.0f,  1.0f, 1.0f, 1.0f,  //kolor    
		 //wierzcholki lewego boku - czerwony
		-0.4f, -0.4f, 0.0f, 1.0f, //wierzcholek
		 1.0f,  0.0f, 0.0f, 1.0f, //kolor
		 -0.4f, 0.4f, 0.0f, 1.0f, //wierzcholek
	 	 1.0f,  0.0f, 0.0f, 1.0f, //kolor
		-0.4f,  -0.4f, 0.8f, 1.0f, //wierzcholek
		 1.0f,  0.0f, 0.0f, 1.0f, //kolor
		 -0.4f,  0.4f, 0.8f, 1.0f, //wierzcholek
		 1.0f,  0.0f, 0.0f, 1.0f, //kolor
		 //wierzcholki prawego boku - niebieski
		 0.4f, -0.4f, 0.0f, 1.0f, //wierzcholek
		 0.0f,  0.0f, 1.0f, 1.0f, //kolor
		 0.4f,  0.4f, 0.0f, 1.0f, //wierzcholek
		 0.0f,  0.0f, 1.0f, 1.0f, //kolor
		 0.4f,  0.4f, 0.8f, 1.0f, //wierzcholek
		 0.0f,  0.0f, 1.0f, 1.0f, //kolor
		 0.4f,  -0.4f, 0.8f, 1.0f, //wierzcholek
		 0.0f,  0.0f, 1.0f, 1.0f, //kolor
		 //wierzcholki dolnej scianki - zielony
		-0.4f, -0.4f, 0.0f, 1.0f, //wierzcholek
		 0.0f,  1.0f, 0.0f, 1.0f, //kolor
		 0.4f, -0.4f, 0.0f, 1.0f, //wierzcholek
		 0.0f,  1.0f, 0.0f, 1.0f, //kolor
		-0.4f, -0.4f, 0.8f, 1.0f, //wierzcholek
		 0.0f,  1.0f, 0.0f, 1.0f, //kolor
		 0.4f, -0.4f, 0.8f, 1.0f, //wierzcholek
		 0.0f,  1.0f, 0.0f, 1.0f, //kolor
		 //wierzcholki gornej scianki - biale
		-0.4f,  0.4f, 0.0f, 1.0f, //wierzcholek
		 1.0f,  1.0f, 1.0f, 1.0f, //kolor
		 0.4f,  0.4f, 0.0f, 1.0f, //wierzcholek
		 1.0f,  1.0f, 1.0f, 1.0f, //kolor
		-0.4f,  0.4f, 0.8f, 1.0f, //wierzcholek
		 1.0f,  1.0f, 1.0f, 1.0f, //kolor
		 0.4f,  0.4f, 0.8f, 1.0f, //wierzcholek
		 1.0f,  1.0f, 1.0f, 1.0f, //kolor 
		  //wierzcholki tylnej scianki - blekitny
		-0.4f, -0.4f, 0.8f, 1.0f, //wierzcholek
		 0.0f,  1.0f, 1.0f, 1.0f, //kolor
		 0.4f, -0.4f, 0.8f, 1.0f, //wierzcholek
		 0.0f,  1.0f, 1.0f, 1.0f, //kolor
		-0.4f,  0.4f, 0.8f, 1.0f, //wierzcholek
		 0.0f,  1.0f, 1.0f, 1.0f, //kolor
		 0.4f,  0.4f, 0.8f, 1.0f, //wierzcholek
		 0.0f,  1.0f, 1.0f, 1.0f, //kolor


	};

	
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(wierzcholki), wierzcholki, GL_STATIC_DRAW); //flaga stream draw, static, dynamic


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
	//int dlugosc = strlen(vertexShader);
	//cout << dlugosc << endl;

	//cout << vertexShaderString.find("\n");
	//string szukanaFraza = "\n";
	//size_t znalezionaPozycja = vertexShaderString.find(szukanaFraza);

	//string shaderStrArr[999];
	//int indexStart = 0;
	//int indexStop;
	//int i = 0;

	//do
	//{
	//	std::cout << "Fraza zostala odnaleziona na pozycji " << znalezionaPozycja << std::endl;
	//	znalezionaPozycja = vertexShaderString.find(szukanaFraza, znalezionaPozycja + szukanaFraza.size());
	//	//indexStop = znalezionaPozycja;
	//	indexStop = static_cast<int>(znalezionaPozycja);
	//	//cout << "znaleziona pozycja: " << znalezionaPozycja << "wartosc: " << vertexShaderString.substr(indexStart, indexStop);
	//	shaderStrArr[i] = vertexShaderString.substr(indexStart, indexStop);
	//	indexStart = indexStop - indexStart + 2;
	//	i++;
	//} while (znalezionaPozycja != std::string::npos);

	////cout << vertexShaderString.substr(0, 18) << endl << vertexShaderString.substr(19, 56);

	//for (int i = 0; i < 20; i++) {
	//	cout << shaderStrArr[i];
	//};
	//
	
	/*
	int i = 0;
	stringstream ssin(vertexShaderString);
	while (ssin.good() && i < 50) {
		ssin >> vertexShaderArr[i];
		++i;
	}
	for (i = 0; i < 50; i++) {
		cout << vertexShaderArr[i] << endl;
	}
	*/
	/////////////////////
//	string vertexShaderArr[50];
	//char *array[10];
	//int i = 0;

	//array[i] = strtok(vertexShaderString, "/");

	//while (array[i] != NULL)
	//{
	//	array[++i] = strtok(NULL, "/");
	//}
	/////////////////////////
	//string vertexShaderArr = wczytajShaderTablica("vertexShader");
	//cout << *vertexShaderArr << endl;

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

GLuint ProgramMPGK::dodanieDoProgramu(GLuint programZShaderami, const GLchar * tekstShadera, GLenum typShadera)
{
	GLuint shader = glCreateShader(typShadera);

	// 35633 -> vertex shader, 35632 -> fragment shader
	const GLchar * typShaderaTekst = typShadera == 35633 ? "vertex" : "fragment";

	if (shader == 0) {
		std::cerr << "Blad podczas tworzenia " << typShaderaTekst << " shadera." << std::endl;
		//system("pause");
		exit(0);
	}

	string shaderArr[999];
	int shaderLen[999] = { 0 };
	int i;
	if (typShadera == 35633) {
		i = 0;
		string content;
		ifstream fileStream("vertexShader", ios::in);

		if (!fileStream.is_open()) {
			cout << "Nie mozna wczytac vertexShadera. Plik nie istnieje." << endl;
			system("pause");
		}

		string line = "";
		while (!fileStream.eof()) {
			getline(fileStream, line);
			content.append(line + "\n");
			shaderArr[i] = line+"\n";
			//cout << "dlugosc: "<<line.length() << endl;
			shaderLen[i] = line.length();
			//cout << shaderArr[i];
			i++;
		}

		fileStream.close();
		//cout << shaderArr[5];
		//cout << shaderLen[5];

	}
	else {
		i = 0;
		string content;
		ifstream fileStream("fragmentShader", ios::in);

		if (!fileStream.is_open()) {
			cout << "Nie mozna wczytac fragmentShadera. Plik nie istnieje." << endl;
			system("pause");
		}

		string line = "";
		while (!fileStream.eof()) {
			getline(fileStream, line);
			content.append(line + "\n");
			shaderArr[i] = line + "\n";
			//cout << shaderArr[i];
		}

		fileStream.close();
	}
	
	
	/*
	// =================== start counting numbers of lines
	string shaderTextAsString = tekstShadera;
	// function below working with: #include <algorithm>
	const int linesQuantity = count(shaderTextAsString.begin(), shaderTextAsString.end(), '\n');
	//cout << "linesQuantity" << linesQuantity << endl;
	//==================== end counting numbers of lines

	// _strdup converts const char * into char * which is requirement in strtok
	char * shaderText = _strdup(tekstShadera);

	//cout << "Shader text as char *: \n" << shaderText;
	const GLchar * shaderTextLines[999];
	GLint shaderTextLinesLength[999];
	char * line;
	// divide whole string by new line char
	line = strtok(shaderText, "\n");
	int shaderTextLineIndex = 0;
	string temp;
	temp = line;
	temp.append("\n");
	cout << temp;
	line = NULL;
	while (line != NULL) {
		//cout << line << endl;
		
		shaderTextLines[shaderTextLineIndex] = line;
		//cout << "line length: " << strlen(line) << endl;
		cout << shaderTextLines[shaderTextLineIndex];
		shaderTextLinesLength[shaderTextLineIndex] = strlen(line);
		shaderTextLineIndex++;
		// NULL as first arg means that function continues searching on the next char position
		line = strtok(NULL, "\n");
	}

	//for (int i = 0; i < 10; i++) {
	//	cout << "Shader line: " << i << ": " << shaderTextLines[i] << " | Length: " << shaderTextLinesLength[i] << endl;
	//}

	const GLchar * tekstShaderaTab[1];
	tekstShaderaTab[0] = tekstShadera;
	GLint dlugoscShadera[1];
	dlugoscShadera[0] = strlen(tekstShadera);
	*/

	const GLchar * tekstShaderaTab[1];
	tekstShaderaTab[0] = tekstShadera;
	GLint dlugoscShadera[1];
	dlugoscShadera[0] = strlen(tekstShadera);
	glShaderSource(shader, 1, tekstShaderaTab, dlugoscShadera);
	//glShaderSource(shader, 10, shaderTextLines, shaderTextLinesLength);

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
