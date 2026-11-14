#include<iostream>
#include<cstring>

using namespace std;

class Carte {
private:
	const int cod;
	char* titlu;
	int nrPagini;
public:
	static int nrCarti;

	Carte(int cod, const char* titlu, int nrPagini) :cod(cod) {
		nrCarti++;
		if (titlu != nullptr) {
			this->titlu = new char[strlen(titlu) + 1];
			strcpy_s(this->titlu, strlen(titlu) + 1, titlu);
		}
		else {
			this->titlu = nullptr;
		}
		this->nrPagini = nrPagini;
	}

	Carte(const Carte& copie) :cod(++nrCarti) {
		if (copie.titlu != nullptr) {
			this->titlu = new char[strlen(copie.titlu) + 1];
			strcpy_s(this->titlu, strlen(copie.titlu) + 1, copie.titlu);
		}
		else {
			this->titlu = nullptr;
		}
		this->nrPagini = copie.nrPagini;
	}

	char* getTitlu() {
		if (this->titlu == nullptr) {
			return nullptr;
		}
		char* copieTitlu = new char[strlen(this->titlu) + 1];
		strcpy_s(copieTitlu, strlen(this->titlu) + 1, this->titlu);
		return copieTitlu;
	}

	int getNrPagini() {
		return this->nrPagini;
	}

	void setNrPagini(int valoareNoua) {
		if (valoareNoua > 0) {
			this->nrPagini = valoareNoua;
		}
		else {
			throw exception();
		}
	}

	void operator+=(int paginiDeAdaugat) {
		this->nrPagini += paginiDeAdaugat;
	}

	bool operator<(const Carte& c) {
		return this->nrPagini < c.nrPagini;
	}

	friend ostream& operator<<(ostream& out, const Carte& c) {
		out << endl << "Cod carte: " << c.cod;
		out << endl << "Titlu: ";
		if (c.titlu != nullptr) {
			out << c.titlu;
		}
		else {
			out << "-";
		}
		out << endl << "Nr. pagini: " << c.nrPagini;
		return out;
	}

	~Carte() {
		cout << endl << "S-a apelat destructorul!";
		if (this->titlu != nullptr) {
			delete[] this->titlu;
		}
	}
};

int Carte::nrCarti = 0;

void main() {
	Carte c1(101, "Morometii", 450);
	cout << c1;

	Carte* c2 = new Carte(102, "Ion", 300);
	cout << *c2;

	Carte c3 = c1;
	cout << c3;

	char* titlu = c1.getTitlu();
	cout << endl << "Titlul cartii c1: " << titlu;
	delete[] titlu;

	c3.setNrPagini(500);
	cout << endl << "Noul nr. de pagini pentru c3: " << c3.getNrPagini();

	try {
		c3.setNrPagini(-10);
	}
	catch (...) {
		cout << endl << "Numarul de pagini trebuie sa fie pozitiv!";
	}

	(*c2) += 50;
	cout << endl << "Dupa += 50:";
	cout << *c2;

	if (*c2 < c1) {
		cout << endl << "Cartea c2 are mai putine pagini decat c1!";
	}
	else {
		cout << endl << "Cartea c1 are mai putine pagini decat c2!";
	}

	delete c2;

	cout << endl << "Numar carti: " << Carte::nrCarti;
}