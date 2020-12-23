#pragma once
//#include "Header.h"
#include <Wektor.h>
#include<iostream>
#include<fstream>
#include<string>
#include<math.h>
#include <iomanip>

class Macierz
{
public:

	float Mac[4][4] = { 0 };

	Macierz();
	Macierz(float wartosc);
	Macierz(float tablica[3][3]);
	Macierz(float tablica[4][4]);
	~Macierz();

	float get(int wiersz, int kolumna);
	void set(int wiersz, int kolumna, float wartosc);
	Macierz Wypisz(Macierz m);
	Macierz Jednostkowa();
	Macierz Transponowanie(Macierz m);
	Macierz Odwracanie(Macierz m);

	//friend std::ostream& operator<<(std::ostream& output, const Macierz& m1);
	Macierz& operator+=(const Macierz& right);
	Macierz& operator-=(const Macierz& right);
	Macierz& operator*=(const Macierz& right);
	Macierz& operator*=(const int & right);
	Macierz& operator=(const Macierz& right);

};

//std::ostream& operator<<(std::ostream& output, const Macierz& m1);
Macierz operator+(const Macierz &m1, const Macierz &m2);
Macierz operator-(const Macierz &m1, const Macierz &m2);
Macierz operator*(const Macierz &m1, const Macierz &m2);
Macierz operator*(const Macierz &m1, const int &f);
Wektor operator*(const Macierz &m1, const Wektor &w1);


std::ostream & operator<<(std::ostream & output, const Macierz & M)
{


	if (M.Mac[3][3] == NULL) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				
				if (j == 0) {
					output << std::left << std::setw(12) << M.Mac[i][j];
				}
				else {
					output << std::setw(12) << M.Mac[i][j];
				}

			
			}
		
			output << std::endl;
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
		
				if (j == 0) {
					output << std::left << std::setw(12) << M.Mac[i][j];
				}
				else {
					output << std::setw(12) << M.Mac[i][j];
				}
			}
			output << std::endl;
		}
	}


	return output;
}






float Mac[4][4] = { NULL };
double d = 0;

Macierz::Macierz()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Mac[i][j] = 0;
		}
	}
}

Macierz::Macierz(float wartosc)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Mac[i][j] = wartosc;
		}
	}
}


Macierz::Macierz(float tablica[3][3])
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			/*if (tablica[i][j] == NULL) {
				Mac[i][j] = 0;
			}
			else {*/
			Mac[i][j] = tablica[i][j];
			//}
		}
	}



}




Macierz::Macierz(float tablica[4][4])
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (tablica[i][j] == NULL) {
				Mac[i][j] = 0;
			}
			else {
				Mac[i][j] = tablica[i][j];
			}
		}
	}
}

Macierz::~Macierz()
{
}

float Macierz::get(int wiersz, int kolumna) {
	return Mac[wiersz][kolumna];
}

void Macierz::set(int wiersz, int kolumna, float wartosc) {
	Mac[wiersz][kolumna] = wartosc;
}

Macierz Macierz::Wypisz(Macierz m)
{
	/*for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << m.Mac[i][j] << "  ";
		}
		std::cout << std::endl;
	}
*/

//std::cout <<"------------" <<std::endl;
	if (m.Mac[3][3] == NULL) {
		std::cout << std::left << std::setw(12) << m.Mac[0][0] << std::setw(12) << m.Mac[0][1] << std::setw(12) << m.Mac[0][2] << std::endl;
		std::cout << std::left << std::setw(12) << m.Mac[1][0] << std::setw(12) << m.Mac[1][1] << std::setw(12) << m.Mac[1][2] << std::endl;
		std::cout << std::left << std::setw(12) << m.Mac[2][0] << std::setw(12) << m.Mac[2][1] << std::setw(12) << m.Mac[2][2] << std::endl;

	}
	else if (m.Mac[3][3] != NULL) {
		std::cout << std::left << std::setw(12) << m.Mac[0][0] << std::setw(12) << m.Mac[0][1] << std::setw(12) << m.Mac[0][2] << std::setw(12) << m.Mac[0][3] << std::endl;
		std::cout << std::left << std::setw(12) << m.Mac[1][0] << std::setw(12) << m.Mac[1][1] << std::setw(12) << m.Mac[1][2] << std::setw(12) << m.Mac[1][3] << std::endl;
		std::cout << std::left << std::setw(12) << m.Mac[2][0] << std::setw(12) << m.Mac[2][1] << std::setw(12) << m.Mac[2][2] << std::setw(12) << m.Mac[2][3] << std::endl;
		std::cout << std::left << std::setw(12) << m.Mac[3][0] << std::setw(12) << m.Mac[3][1] << std::setw(12) << m.Mac[3][2] << std::setw(12) << m.Mac[3][3] << std::endl;

	}
	else {
		std::cout << "Blad w trakcie wyswietlania macierzy" << std::endl;
	}
	//std::cout << std::left << std::setw(10) << "Name" << std::setw(10) << "Title"<< std::setw(10) << "Gross" << std::setw(10) << "Tax" << "Net\n";

	//std::cout << "------------"<< std::endl;
	return Macierz();
}

Macierz Macierz::Jednostkowa()
{
	//Macierz macierzJ[4][4];

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j) {
				Mac[i][j] = 1;
			}
			else {
				Mac[i][j] = 0;
			}

		}
	}


	//std::cout << Mac[0][0] << " " << Mac[0][1] << " " << Mac[0][2] << " " << Mac[0][3] << std::endl;
	return Mac;
}

Macierz Macierz::Transponowanie(Macierz m)
{
	Macierz mac2;
	if (m.Mac[3][3] == NULL) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				mac2.Mac[i][j] = m.Mac[j][i];
			}
		}
	}
	else if (m.Mac[3][3] != NULL) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				mac2.Mac[i][j] = m.Mac[j][i];
			}
		}
	}
	else {
		std::cout << "Blad w trakcie mnozenia macierzy" << std::endl;
	}










	return mac2.Mac;
}

Macierz Macierz::Odwracanie(Macierz m)
{
	Macierz mac2;
	float determinant = 0;

	if (m.Mac[3][3] == NULL) {
		for (int i = 0; i < 3; i++) {
			determinant = determinant + (m.Mac[0][i] * (m.Mac[1][(i + 1) % 3] * m.Mac[2][(i + 2) % 3] - m.Mac[1][(i + 2) % 3] * m.Mac[2][(i + 1) % 3]));
		}
		if (determinant == 0) {
			std::cout << "Wyznacznik wynosi 0, nie mozna obliczyc macierzy odwrotnej" << std::endl;
			return mac2.Mac;
		}
		std::cout << "Wyznacznik: " << determinant << std::endl;
		//std::cout << "Macierz odwrotna" << std::endl;;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				mac2.Mac[i][j] = ((m.Mac[(j + 1) % 3][(i + 1) % 3] * m.Mac[(j + 2) % 3][(i + 2) % 3]) - (m.Mac[(j + 1) % 3][(i + 2) % 3] * m.Mac[(j + 2) % 3][(i + 1) % 3])) / determinant;
				//std::cout << ((m.Mac[(j + 1) % 3][(i + 1) % 3] * m.Mac[(j + 2) % 3][(i + 2) % 3]) - (m.Mac[(j + 1) % 3][(i + 2) % 3] * m.Mac[(j + 2) % 3][(i + 1) % 3])) / determinant << std::endl;
			}
		}
	}
	else if (m.Mac[3][3] != NULL) {
		std::cout << "Macierz 4x4" << std::endl;




		float determinant =
			m.Mac[0][3] * m.Mac[1][2] * m.Mac[2][1] * m.Mac[3][0] - m.Mac[0][2] * m.Mac[1][3] * m.Mac[2][1] * m.Mac[3][0] - m.Mac[0][3] * m.Mac[1][1] * m.Mac[2][2] * m.Mac[3][0] + m.Mac[0][1] * m.Mac[1][3] * m.Mac[2][2] * m.Mac[3][0] +
			m.Mac[0][2] * m.Mac[1][1] * m.Mac[2][3] * m.Mac[3][0] - m.Mac[0][1] * m.Mac[1][2] * m.Mac[2][3] * m.Mac[3][0] - m.Mac[0][3] * m.Mac[1][2] * m.Mac[2][0] * m.Mac[3][1] + m.Mac[0][2] * m.Mac[1][3] * m.Mac[2][0] * m.Mac[3][1] +
			m.Mac[0][3] * m.Mac[1][0] * m.Mac[2][2] * m.Mac[3][1] - m.Mac[0][0] * m.Mac[1][3] * m.Mac[2][2] * m.Mac[3][1] - m.Mac[0][2] * m.Mac[1][0] * m.Mac[2][3] * m.Mac[3][1] + m.Mac[0][0] * m.Mac[1][2] * m.Mac[2][3] * m.Mac[3][1] +
			m.Mac[0][3] * m.Mac[1][1] * m.Mac[2][0] * m.Mac[3][2] - m.Mac[0][1] * m.Mac[1][3] * m.Mac[2][0] * m.Mac[3][2] - m.Mac[0][3] * m.Mac[1][0] * m.Mac[2][1] * m.Mac[3][2] + m.Mac[0][0] * m.Mac[1][3] * m.Mac[2][1] * m.Mac[3][2] +
			m.Mac[0][1] * m.Mac[1][0] * m.Mac[2][3] * m.Mac[3][2] - m.Mac[0][0] * m.Mac[1][1] * m.Mac[2][3] * m.Mac[3][2] - m.Mac[0][2] * m.Mac[1][1] * m.Mac[2][0] * m.Mac[3][3] + m.Mac[0][1] * m.Mac[1][2] * m.Mac[2][0] * m.Mac[3][3] +
			m.Mac[0][2] * m.Mac[1][0] * m.Mac[2][1] * m.Mac[3][3] - m.Mac[0][0] * m.Mac[1][2] * m.Mac[2][1] * m.Mac[3][3] - m.Mac[0][1] * m.Mac[1][0] * m.Mac[2][2] * m.Mac[3][3] + m.Mac[0][0] * m.Mac[1][1] * m.Mac[2][2] * m.Mac[3][3];


		//std::cout << "Wyznacznik: " << determinant << std::endl;



		mac2.Mac[0][0] = m.Mac[1][2] * m.Mac[2][3] * m.Mac[3][1] - m.Mac[1][3] * m.Mac[2][2] * m.Mac[3][1] + m.Mac[1][3] * m.Mac[2][1] * m.Mac[3][2] - m.Mac[1][1] * m.Mac[2][3] * m.Mac[3][2] - m.Mac[1][2] * m.Mac[2][1] * m.Mac[3][3] + m.Mac[1][1] * m.Mac[2][2] * m.Mac[3][3];
		mac2.Mac[0][1] = m.Mac[0][3] * m.Mac[2][2] * m.Mac[3][1] - m.Mac[0][2] * m.Mac[2][3] * m.Mac[3][1] - m.Mac[0][3] * m.Mac[2][1] * m.Mac[3][2] + m.Mac[0][1] * m.Mac[2][3] * m.Mac[3][2] + m.Mac[0][2] * m.Mac[2][1] * m.Mac[3][3] - m.Mac[0][1] * m.Mac[2][2] * m.Mac[3][3];
		mac2.Mac[0][2] = m.Mac[0][2] * m.Mac[1][3] * m.Mac[3][1] - m.Mac[0][3] * m.Mac[1][2] * m.Mac[3][1] + m.Mac[0][3] * m.Mac[1][1] * m.Mac[3][2] - m.Mac[0][1] * m.Mac[1][3] * m.Mac[3][2] - m.Mac[0][2] * m.Mac[1][1] * m.Mac[3][3] + m.Mac[0][1] * m.Mac[1][2] * m.Mac[3][3];
		mac2.Mac[0][3] = m.Mac[0][3] * m.Mac[1][2] * m.Mac[2][1] - m.Mac[0][2] * m.Mac[1][3] * m.Mac[2][1] - m.Mac[0][3] * m.Mac[1][1] * m.Mac[2][2] + m.Mac[0][1] * m.Mac[1][3] * m.Mac[2][2] + m.Mac[0][2] * m.Mac[1][1] * m.Mac[2][3] - m.Mac[0][1] * m.Mac[1][2] * m.Mac[2][3];
		mac2.Mac[1][0] = m.Mac[1][3] * m.Mac[2][2] * m.Mac[3][0] - m.Mac[1][2] * m.Mac[2][3] * m.Mac[3][0] - m.Mac[1][3] * m.Mac[2][0] * m.Mac[3][2] + m.Mac[1][0] * m.Mac[2][3] * m.Mac[3][2] + m.Mac[1][2] * m.Mac[2][0] * m.Mac[3][3] - m.Mac[1][0] * m.Mac[2][2] * m.Mac[3][3];
		mac2.Mac[1][1] = m.Mac[0][2] * m.Mac[2][3] * m.Mac[3][0] - m.Mac[0][3] * m.Mac[2][2] * m.Mac[3][0] + m.Mac[0][3] * m.Mac[2][0] * m.Mac[3][2] - m.Mac[0][0] * m.Mac[2][3] * m.Mac[3][2] - m.Mac[0][2] * m.Mac[2][0] * m.Mac[3][3] + m.Mac[0][0] * m.Mac[2][2] * m.Mac[3][3];
		mac2.Mac[1][2] = m.Mac[0][3] * m.Mac[1][2] * m.Mac[3][0] - m.Mac[0][2] * m.Mac[1][3] * m.Mac[3][0] - m.Mac[0][3] * m.Mac[1][0] * m.Mac[3][2] + m.Mac[0][0] * m.Mac[1][3] * m.Mac[3][2] + m.Mac[0][2] * m.Mac[1][0] * m.Mac[3][3] - m.Mac[0][0] * m.Mac[1][2] * m.Mac[3][3];
		mac2.Mac[1][3] = m.Mac[0][2] * m.Mac[1][3] * m.Mac[2][0] - m.Mac[0][3] * m.Mac[1][2] * m.Mac[2][0] + m.Mac[0][3] * m.Mac[1][0] * m.Mac[2][2] - m.Mac[0][0] * m.Mac[1][3] * m.Mac[2][2] - m.Mac[0][2] * m.Mac[1][0] * m.Mac[2][3] + m.Mac[0][0] * m.Mac[1][2] * m.Mac[2][3];
		mac2.Mac[2][0] = m.Mac[1][1] * m.Mac[2][3] * m.Mac[3][0] - m.Mac[1][3] * m.Mac[2][1] * m.Mac[3][0] + m.Mac[1][3] * m.Mac[2][0] * m.Mac[3][1] - m.Mac[1][0] * m.Mac[2][3] * m.Mac[3][1] - m.Mac[1][1] * m.Mac[2][0] * m.Mac[3][3] + m.Mac[1][0] * m.Mac[2][1] * m.Mac[3][3];
		mac2.Mac[2][1] = m.Mac[0][3] * m.Mac[2][1] * m.Mac[3][0] - m.Mac[0][1] * m.Mac[2][3] * m.Mac[3][0] - m.Mac[0][3] * m.Mac[2][0] * m.Mac[3][1] + m.Mac[0][0] * m.Mac[2][3] * m.Mac[3][1] + m.Mac[0][1] * m.Mac[2][0] * m.Mac[3][3] - m.Mac[0][0] * m.Mac[2][1] * m.Mac[3][3];
		mac2.Mac[2][2] = m.Mac[0][1] * m.Mac[1][3] * m.Mac[3][0] - m.Mac[0][3] * m.Mac[1][1] * m.Mac[3][0] + m.Mac[0][3] * m.Mac[1][0] * m.Mac[3][1] - m.Mac[0][0] * m.Mac[1][3] * m.Mac[3][1] - m.Mac[0][1] * m.Mac[1][0] * m.Mac[3][3] + m.Mac[0][0] * m.Mac[1][1] * m.Mac[3][3];
		mac2.Mac[2][3] = m.Mac[0][3] * m.Mac[1][1] * m.Mac[2][0] - m.Mac[0][1] * m.Mac[1][3] * m.Mac[2][0] - m.Mac[0][3] * m.Mac[1][0] * m.Mac[2][1] + m.Mac[0][0] * m.Mac[1][3] * m.Mac[2][1] + m.Mac[0][1] * m.Mac[1][0] * m.Mac[2][3] - m.Mac[0][0] * m.Mac[1][1] * m.Mac[2][3];
		mac2.Mac[3][0] = m.Mac[1][2] * m.Mac[2][1] * m.Mac[3][0] - m.Mac[1][1] * m.Mac[2][2] * m.Mac[3][0] - m.Mac[1][2] * m.Mac[2][0] * m.Mac[3][1] + m.Mac[1][0] * m.Mac[2][2] * m.Mac[3][1] + m.Mac[1][1] * m.Mac[2][0] * m.Mac[3][2] - m.Mac[1][0] * m.Mac[2][1] * m.Mac[3][2];
		mac2.Mac[3][1] = m.Mac[0][1] * m.Mac[2][2] * m.Mac[3][0] - m.Mac[0][2] * m.Mac[2][1] * m.Mac[3][0] + m.Mac[0][2] * m.Mac[2][0] * m.Mac[3][1] - m.Mac[0][0] * m.Mac[2][2] * m.Mac[3][1] - m.Mac[0][1] * m.Mac[2][0] * m.Mac[3][2] + m.Mac[0][0] * m.Mac[2][1] * m.Mac[3][2];
		mac2.Mac[3][2] = m.Mac[0][2] * m.Mac[1][1] * m.Mac[3][0] - m.Mac[0][1] * m.Mac[1][2] * m.Mac[3][0] - m.Mac[0][2] * m.Mac[1][0] * m.Mac[3][1] + m.Mac[0][0] * m.Mac[1][2] * m.Mac[3][1] + m.Mac[0][1] * m.Mac[1][0] * m.Mac[3][2] - m.Mac[0][0] * m.Mac[1][1] * m.Mac[3][2];
		mac2.Mac[3][3] = m.Mac[0][1] * m.Mac[1][2] * m.Mac[2][0] - m.Mac[0][2] * m.Mac[1][1] * m.Mac[2][0] + m.Mac[0][2] * m.Mac[1][0] * m.Mac[2][1] - m.Mac[0][0] * m.Mac[1][2] * m.Mac[2][1] - m.Mac[0][1] * m.Mac[1][0] * m.Mac[2][2] + m.Mac[0][0] * m.Mac[1][1] * m.Mac[2][2];
		





		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				mac2.Mac[i][j] = mac2.Mac[i][j] / determinant;

			}
		}




		//std::cout << "====================" << std::endl;
		//for (int i = 0; i < 4; i++) {
		//	for (int j = 0; j < 4; j++) {
		//		std::cout << mac2.Mac[i][j] << " ";

		//	}
		//	std::cout << "\n";
		//}
		//std::cout << "====================" << std::endl;




	}
	else {
		std::cout << "Blad w trakcie obliczania wyznacznika macierzy" << std::endl;
	}


	return mac2.Mac;
}






Macierz & Macierz::operator+=(const Macierz & right)
{





	if (this->Mac[3][3] == NULL && right.Mac[3][3] == NULL) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				this->Mac[i][j] += right.Mac[i][j];
			}
		}
	}
	else if (this->Mac[3][3] != NULL && right.Mac[3][3] != NULL) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				this->Mac[i][j] += right.Mac[i][j];
			}
		}
	}
	else {
		std::cout << "Nie mozna dodawac z przypisaniem roznych macierzy" << std::endl;
	}

	return *this;








}

Macierz & Macierz::operator-=(const Macierz & right)
{





	if (this->Mac[3][3] == NULL && right.Mac[3][3] == NULL) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				this->Mac[i][j] -= right.Mac[i][j];
			}
		}
	}
	else if (this->Mac[3][3] != NULL && right.Mac[3][3] != NULL) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				this->Mac[i][j] -= right.Mac[i][j];
			}
		}
	}
	else {
		std::cout << "Nie mozna odejmowac z przypianiem roznych macierzy" << std::endl;
	}


	return *this;

}

Macierz & Macierz::operator*=(const Macierz & right)
{

	/*for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Mac[i][j] = this->Mac[i][j];
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
				this->Mac[i][j] = Mac[i][k] * right.Mac[k][j];
		}
	}
*/
	Macierz mac1 = this->Mac;

	//std::cout << "this->Mac -------------------------------------" << std::endl;
	//for (int i = 0; i < 4; i++) {
	//	for (int j = 0; j < 4; j++) {
	//		std::cout << this->Mac[i][j] << " ";

	//	}
	//	std::cout << "\n";
	//}
	//std::cout << "right.Mac -------------------------------------" << std::endl;
	//for (int i = 0; i < 4; i++) {
	//	for (int j = 0; j < 4; j++) {
	//		std::cout << right.Mac[i][j] << " ";

	//	}
	//	std::cout << "\n";
	//}
	//std::cout << "Mac1 -------------------------------------" << std::endl;


	//for (int i = 0; i < 4; i++) {
	//	for (int j = 0; j < 4; j++) {
	//		mac1.Mac[i][j] = 0;
	//		std::cout << mac1.Mac[i][j] << " ";

	//	}
	//	std::cout << "\n";
	//}

	//std::cout << "this->Mac -------------------------------------" << std::endl;
	//for (int i = 0; i < 4; i++) {
	//	for (int j = 0; j < 4; j++) {
	//		std::cout << this->Mac[i][j] << " ";

	//	}
	//	std::cout << "\n";
	//}
	//std::cout << "right.Mac -------------------------------------" << std::endl;
	//for (int i = 0; i < 4; i++) {
	//	for (int j = 0; j < 4; j++) {
	//		std::cout << right.Mac[i][j] << " ";

	//	}
	//	std::cout << "\n";
	//}
	//for (int i = 0; i < 4; i++) {
	//	for (int j = 0; j < 4; j++) {
	//		Mac[i][j] = this->Mac[i][j];
	//	}
	//}
	//Macierz mac2();


	//int i, j, k;
	//for (i = 0; i < 4; i++)
	//{
	//	for (j = 0; j < 4; j++)
	//	{
	//		Mac[i][j] = 0;
	//		/*for (k = 0; k < N; k++)
	//			Mac[i][j] += this->Mac[i][k] *right.Mac[k][j];*/
	//	}
	//}





	//std::cout << "thissssss-------------------------------------" << std::endl;


	//for (int i = 0; i < 4; i++) {
	//	for (int j = 0; j < 4; j++) {
	//		std::cout << this->Mac[i][j] << " ";

	//	}
	//	std::cout << "\n";
	//}std::cout << "rightttt-------------------------------------" << std::endl;


	//for (int i = 0; i < 4; i++) {
	//	for (int j = 0; j < 4; j++) {
	//		std::cout << right.Mac[i][j] << " ";

	//	}
	//	std::cout << "\n";
	//}

	//std::cout << "macccc1-------------------------------------" << std::endl;


	//for (int i = 0; i < 4; i++) {
	//	for (int j = 0; j < 4; j++) {
	//		std::cout << mac1.Mac[i][j] << " ";

	//	}
	//	std::cout << "\n";
	//}
	//std::cout << "-------------------------------------" << std::endl;



	int i, j, k;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			this->Mac[i][j] = 0;
			for (k = 0; k < 4; k++)
				this->Mac[i][j] += mac1.Mac[i][k] * right.Mac[k][j];
		}
	}


	//std::cout << "wynik -------------------------------------" << std::endl;


	//for (int i = 0; i < 4; i++) {
	//	for (int j = 0; j < 4; j++) {
	//		//mac1.Mac[i][j] = 0;
	//		std::cout << mac1.Mac[i][j] << " ";

	//	}
	//	std::cout << "\n";
	//}




	return *this;




}





Macierz & Macierz::operator*=(const int & right)
{


	if (this->Mac[3][3] == NULL) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				this->Mac[i][j] *= right;
			}
		}
	}
	else if (this->Mac[3][3] != NULL) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				this->Mac[i][j] *= right;
			}
		}
	}
	else {
		std::cout << "Blad w trakcie mnozenia macierzy" << std::endl;
	}



	return *this;
}

Macierz & Macierz::operator=(const Macierz & M)
{


	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			this->Mac[i][j] = M.Mac[i][j];
		}
	}



	return *this;
}

//std::ostream & operator<<(std::ostream & output, const Macierz & M)
//{
//
//
//	if (M.Mac[3][3] == NULL) {
//		for (int i = 0; i < 3; i++) {
//			for (int j = 0; j < 3; j++) {
//				
//				if (j == 0) {
//					output << std::left << std::setw(12) << M.Mac[i][j];
//				}
//				else {
//					output << std::setw(12) << M.Mac[i][j];
//				}
//
//			
//			}
//		
//			output << std::endl;
//		}
//	}
//	else {
//		for (int i = 0; i < 4; i++) {
//			for (int j = 0; j < 4; j++) {
//		
//				if (j == 0) {
//					output << std::left << std::setw(12) << M.Mac[i][j];
//				}
//				else {
//					output << std::setw(12) << M.Mac[i][j];
//				}
//			}
//			output << std::endl;
//		}
//	}
//
//
//	return output;
//}

Macierz operator+(const Macierz & m1, const Macierz & m2)
{
	if (m1.Mac[3][3] == NULL && m2.Mac[3][3] == NULL) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				Mac[i][j] = m1.Mac[i][j] + m2.Mac[i][j];
			}
		}
	}
	else if (m1.Mac[3][3] != NULL && m2.Mac[3][3] != NULL) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				Mac[i][j] = m1.Mac[i][j] + m2.Mac[i][j];
			}
		}
	}
	else {
		std::cout << "Nie mozna dodawac roznych macierzy" << std::endl;
	}
	return Mac;
}

Macierz operator-(const Macierz & m1, const Macierz & m2)
{
	if (m1.Mac[3][3] == NULL && m2.Mac[3][3] == NULL) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				Mac[i][j] = m1.Mac[i][j] - m2.Mac[i][j];
			}
		}
	}
	else if (m1.Mac[3][3] != NULL && m2.Mac[3][3] != NULL) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				Mac[i][j] = m1.Mac[i][j] - m2.Mac[i][j];
			}
		}
	}
	else {
		std::cout << "Nie mozna odejmowac roznych macierzy" << std::endl;
	}
	return Mac;
}

Macierz operator*(const Macierz & m1, const Macierz & m2)
{

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Mac[i][j] = 0;
			for (int k = 0; k < 4; k++)
				Mac[i][j] += m1.Mac[i][k] * m2.Mac[k][j];
		}
	}




	return Mac;
}

Macierz operator*(const Macierz & m1, const int & f)
{

	if (m1.Mac[3][3] == NULL) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				Mac[i][j] = m1.Mac[i][j] * f;
			}
		}
	}
	else if (m1.Mac[3][3] != NULL) {

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				Mac[i][j] = m1.Mac[i][j] * f;
			}
		}
	}
	else {
		std::cout << "Blad w trakcie mnozenia macierzy" << std::endl;
	}

	return Mac;
}

Wektor operator*(const Macierz & m1, const Wektor & w1)
{
	//std::cout << "---------------std::cout Z OBLICZEN----------------" << std::endl;
	//std::cout << "wektor" << std::endl;
	//for (int i = 0; i < 4; i++) {
	//	std::cout << w1.WekT4[i] << std::endl;
	//}
	//std::cout << "macierz m1" << std::endl;
	//for (int i = 0; i < 4; i++) {
	//	for (int j = 0; j < 4; j++) {
	//		std::cout << m1.Mac[i][j] << " ";
	//	}
	//	std::cout << std::endl;
	//}
	float px = NULL;
	float py = NULL;
	float pz = NULL;
	float pw = NULL;
	Wektor w2;
	if (m1.Mac[3][3] == NULL && w1.WekT4[3] == NULL) {
		//std::cout << "mozna mnozyc 3x3 i wektor 3" << std::endl;
		px = m1.Mac[0][0] * w1.Wek1 + m1.Mac[0][1] * w1.Wek2 + m1.Mac[0][2] * w1.Wek3;
		py = m1.Mac[1][0] * w1.Wek1 + m1.Mac[1][1] * w1.Wek2 + m1.Mac[1][2] * w1.Wek3;
		pz = m1.Mac[2][0] * w1.Wek1 + m1.Mac[2][1] * w1.Wek2 + m1.Mac[2][2] * w1.Wek3;
	}
	else if (m1.Mac[3][3] != NULL && w1.WekT4[3] != NULL) {
		//std::cout << "mozna mnozyc 4x4 i wektor 4" << std::endl;
		//for (int i = 0; i < 4; i++) {
		//	std::cout << m1.Mac[i][0] << " " << m1.Mac[i][1] << " " << m1.Mac[i][2] << " " << m1.Mac[i][3] << std::endl;
		//
		//	//px=m1.Mac[]

		//}
		px = m1.Mac[0][0] * w1.Wek1 + m1.Mac[0][1] * w1.Wek2 + m1.Mac[0][2] * w1.Wek3 + m1.Mac[0][3] * w1.Wek4;
		py = m1.Mac[1][0] * w1.Wek1 + m1.Mac[1][1] * w1.Wek2 + m1.Mac[1][2] * w1.Wek3 + m1.Mac[1][3] * w1.Wek4;
		pz = m1.Mac[2][0] * w1.Wek1 + m1.Mac[2][1] * w1.Wek2 + m1.Mac[2][2] * w1.Wek3 + m1.Mac[2][3] * w1.Wek4;
		pw = m1.Mac[3][0] * w1.Wek1 + m1.Mac[3][1] * w1.Wek2 + m1.Mac[3][2] * w1.Wek3 + m1.Mac[3][3] * w1.Wek4;
		//std::cout << "wektor wynikowy: " << px << " " << py << " " << pz << " " << pw << std::endl;

		w2.setX(px);
		w2.setY(py);
		w2.setZ(pz);
		w2.setW(pw);


	}
	else {
		std::cout << "Blad w trakcie mnozenia macierzy przez wektor" << std::endl;
	}

	//std::cout << "---------------KONIEC Z OBLICZEN----------------" << std::endl;

	return w2;

}
