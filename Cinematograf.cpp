#include<iostream>
#include<cstring>

using namespace std;

class Cinematograf {
private:
	const int id;
	char* denumire;
	int nrSali;
	int* locuri;
public:
	static int nrCinematografe;
	Cinematograf() :id(++nrCinematografe) {
		this->denumire = new char[strlen("Cinema generic") + 1];
		strcpy_s(this->denumire, strlen("Cinema generic") + 1, "Cinema generic");
		this->nrSali = 0;
		this->locuri = nullptr;
	}

	Cinematograf(int id, const char* denumire, int nrSali, int* locuri) :id(id) {
		nrCinematografe++;
		this->denumire = new char[strlen(denumire) + 1];
		strcpy_s(this->denumire, strlen(denumire) + 1, denumire);
		this->nrSali = nrSali;
		this->locuri = new int[nrSali];
		for (int i = 0; i < this->nrSali; i++)
		{
			this->locuri[i] = locuri[i];
		}
		delete[] locuri;
	}

	Cinematograf(const Cinematograf& copie) :id(++nrCinematografe) {
		if (copie.denumire != nullptr) {
			this->denumire = new char[strlen(copie.denumire) + 1];
			strcpy_s(this->denumire, strlen(copie.denumire) + 1, copie.denumire);
		}
		else {
			this->denumire = nullptr;
		}
		this->nrSali = copie.nrSali;

		if (copie.locuri != nullptr) {
			this->locuri = new int[this->nrSali];
			for (int i = 0; i < this->nrSali; i++)
			{
				this->locuri[i] = copie.locuri[i];
			}
		}
		else {
			this->locuri = nullptr;
		}
	}

	char* getDenumire() {
		if (this->denumire == nullptr) {
			return nullptr;
		}
		char* copieDenumire = new char[strlen(this->denumire) + 1];
		strcpy_s(copieDenumire, strlen(this->denumire) + 1, this->denumire);
		return copieDenumire;
	}

	void setDenumire(const char* denumireNoua) {
		if (denumireNoua != nullptr && strlen(denumireNoua) >= 3) {
			if (this->denumire != nullptr) {
				delete[] this->denumire;
				this->denumire = nullptr;
			}
			this->denumire = new char[strlen(denumireNoua) + 1];
			strcpy_s(this->denumire, strlen(denumireNoua) + 1, denumireNoua);
		}
		else {
			throw exception();
		}
	}

	Cinematograf operator+(int locuriSalaNoua) {
		Cinematograf copie = *this;
		int* vNou = new int[copie.nrSali + 1];
		for (int i = 0; i < copie.nrSali; i++)
		{
			vNou[i] = copie.locuri[i];
		}
		vNou[copie.nrSali] = locuriSalaNoua;

		if (copie.locuri != nullptr) {
			delete[] copie.locuri;
		}
		copie.locuri = vNou;
		copie.nrSali++;

		return copie;
	}

	void operator-=(int nrSaliDeSters) {
		if (nrSaliDeSters <= 0 || nrSaliDeSters > this->nrSali) {
			throw exception();
		}

		int nrSaliNou = this->nrSali - nrSaliDeSters;
		int* vNou = nullptr;
		if (nrSaliNou > 0) {
			vNou = new int[nrSaliNou];
			for (int i = 0; i < nrSaliNou; i++)
			{
				vNou[i] = this->locuri[i];
			}
		}

		delete[] this->locuri;
		this->locuri = vNou;
		this->nrSali = nrSaliNou;
	}

	Cinematograf operator--(int) {
		Cinematograf copie = *this;
		for (int i = 0; i < this->nrSali; i++)
		{
			if (this->locuri[i] > 0) {
				this->locuri[i]--;
			}
		}
		return copie;
	}

	bool operator>(const Cinematograf& c) {
		int total1 = 0;
		for (int i = 0; i < this->nrSali; i++)
		{
			total1 += this->locuri[i];
		}
		int total2 = 0;
		for (int i = 0; i < c.nrSali; i++)
		{
			total2 += c.locuri[i];
		}
		return total1 > total2;
	}

	explicit operator int() {
		int total = 0;
		for (int i = 0; i < this->nrSali; i++)
		{
			total += this->locuri[i];
		}
		return total;
	}

	friend void operator<<(ostream& out, Cinematograf c) {
		out << endl << "Operator de afisare: ";
		out << endl << "Id: " << c.id;
		out << endl << "Denumire: " << c.denumire;
		out << endl << "Nr. sali: " << c.nrSali;
		if (c.locuri != nullptr && c.nrSali > 0) {
			out << endl << "Locuri pe sala: ";
			for (int i = 0; i < c.nrSali - 1; i++) {
				out << c.locuri[i] << ", ";
			}
			out << c.locuri[c.nrSali - 1];
		}
	}

	~Cinematograf() {
		cout << endl << "S-a apelat destructorul!";
		if (this->denumire != nullptr) {
			delete[] this->denumire;
		}
		if (this->locuri != nullptr) {
			delete[] this->locuri;
		}
	}
};

int Cinematograf::nrCinematografe = 0;

void main() {
	Cinematograf c1;
	cout << c1;

	int* locuri = new int[3] {120, 80, 200};
	Cinematograf* c2 = new Cinematograf(10, "Cinema City", 3, locuri);
	cout << *c2;

	Cinematograf c3 = *c2;
	cout << c3;

	char* denumire = c3.getDenumire();
	cout << endl << "Denumirea din getter: " << denumire;
	delete[] denumire;

	c3.setDenumire("Hollywood Multiplex");
	cout << c3;

	try {
		c3.setDenumire("AB");
	}
	catch (...) {
		cout << endl << "Denumire prea scurta!";
	}

	Cinematograf c4 = *c2 + 150;
	cout << c4;

	c4 -= 2;
	cout << c4;

	try {
		c4 -= 10;
	}
	catch (...) {
		cout << endl << "Nu se pot sterge atatea sali!";
	}

	Cinematograf c5 = c3--;
	cout << c5;
	cout << c3;

	if (*c2 > c4) {
		cout << endl << "Cinematograful c2 are mai multe locuri decat c4!";
	}
	else {
		cout << endl << "Cinematograful c4 are mai multe locuri decat c2!";
	}

	cout << endl << "Cast cinematograf -> int (total locuri): " << int(*c2);

	delete c2;

	cout << endl << "Numar cinematografe: " << Cinematograf::nrCinematografe;
}