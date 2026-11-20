#include<iostream>
#include<cstring>

using namespace std;

class Film {
private:
	const int id;
	char* titlu;
	int durata;

public:
	static int nrFilme;

	Film() :id(++nrFilme) {
		this->titlu = new char[strlen("Film necunoscut") + 1];
		strcpy_s(this->titlu, strlen("Film necunoscut") + 1, "Film necunoscut");
		this->durata = 0;
	}

	Film(const char* titlu) :id(++nrFilme) {
		if (titlu != nullptr) {
			this->titlu = new char[strlen(titlu) + 1];
			strcpy_s(this->titlu, strlen(titlu) + 1, titlu);
		}
		else {
			this->titlu = new char[strlen("Film necunoscut") + 1];
			strcpy_s(this->titlu, strlen("Film necunoscut") + 1, "Film necunoscut");

		}

		this->durata = 0;
	}

	Film(const Film& copie) :id(++nrFilme) {
		if (copie.titlu != nullptr) {
			this->titlu = new char[strlen(copie.titlu) + 1];
			strcpy_s(this->titlu, strlen(copie.titlu) + 1, copie.titlu);
		}
		else {
			this->titlu = nullptr;
		}
		this->durata = copie.durata;
	}

	void operator=(const Film& copie) {

		if (this->titlu != nullptr) {
			delete[] this->titlu;
			this->titlu = nullptr;
		}

		if (copie.titlu != nullptr) {
			this->titlu = new char[strlen(copie.titlu) + 1];
			strcpy_s(this->titlu, strlen(copie.titlu) + 1, copie.titlu);
		}
		else {
			this->titlu = nullptr;
		}

		this->durata = copie.durata;
	}

	int getId() {
		return this->id;
	}

	void setTitlu(const char* titluNou) {
		if (titluNou != nullptr && strlen(titluNou) >= 2) {
			if (this->titlu != nullptr) {
				delete[] this->titlu;
				this->titlu = nullptr;
			}

			this->titlu = new char[strlen(titluNou) + 1];
			strcpy_s(this->titlu, strlen(titluNou) + 1, titluNou);
		}

		else {
			throw exception();
		}
	}
	void afisare() {
		cout << endl << "Id: " << this->id;
		cout << endl << "Titlu: ";
		if (this->titlu != nullptr) {
			cout << this->titlu;
		}
		else {
			cout << "-";
		}
		cout << endl << "Durata: " << this->durata;
	}

	void operator()(const char* titluNou) {
		this->setTitlu(titluNou);
	}

	~Film() {
		cout << endl << "S-a apelat destucrorul!";
		if (this->titlu != nullptr) {
			delete[] this->titlu;
		}
	}

};

int Film::nrFilme = 0;

void main() {
	Film film1;
	film1.afisare();

	Film film2("Titanic");
	film2.afisare();



	
}