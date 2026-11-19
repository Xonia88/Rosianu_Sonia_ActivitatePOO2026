#include<iostream>
#include<cstring>

using namespace std;

class Restaurant {
private:
	const int id;
	char* nume;
	float rating;
public:
	static int nrRestaurante;

	Restaurant() :id(++nrRestaurante) {
		this->nume = new char[strlen("Restaurant necunoscut") + 1];
		strcpy_s(this->nume, strlen("Restaurant necunoscut") + 1, "Restaurant necunoscut");
		this->rating = 0;
	}

	Restaurant(const char* nume) :id(++nrRestaurante) {
		if (nume != nullptr && strlen(nume) > 0) {
			this->nume = new char[strlen(nume) + 1];
			strcpy_s(this->nume, strlen(nume) + 1, nume);
		}
		else {
			this->nume = new char[strlen("Restaurant necunoscut") + 1];
			strcpy_s(this->nume, strlen("Restaurant necunoscut") + 1, "Restaurant necunoscut");
		}
		this->rating = 0;
	}

	Restaurant(const Restaurant& r) :id(++nrRestaurante) {
		this->nume = new char[strlen(r.nume) + 1];
		strcpy_s(this->nume, strlen(r.nume) + 1, r.nume);
		this->rating = r.rating;
	}

	Restaurant& operator=(const Restaurant& r) {
		if (this != &r) {
			if (this->nume != nullptr) {
				delete[] this->nume;
				this->nume = nullptr;
			}
			this->nume = new char[strlen(r.nume) + 1];
			strcpy_s(this->nume, strlen(r.nume) + 1, r.nume);
			this->rating = r.rating;
		}
		return *this;
	}

	int getId() {
		return this->id;
	}

	void setNume(const char* numeNou) {
		if (numeNou != nullptr && strlen(numeNou) >= 3) {
			if (this->nume != nullptr) {
				delete[] this->nume;
				this->nume = nullptr;
			}
			this->nume = new char[strlen(numeNou) + 1];
			strcpy_s(this->nume, strlen(numeNou) + 1, numeNou);
		}
		else {
			throw exception();
		}
	}

	void afisare() {
		cout << endl << "Id: " << this->id;
		cout << endl << "Nume: " << this->nume;
		cout << endl << "Rating: " << this->rating;
	}

	void operator()(const char* numeNou) {
		this->setNume(numeNou);
	}

	~Restaurant() {
		if (this->nume != nullptr) {
			delete[] this->nume;
		}
	}
};

int Restaurant::nrRestaurante = 0;

void main() {
	Restaurant r1;
	r1.afisare();

	Restaurant r2("La Mama");
	r2.afisare();

	cout << endl << "Id-ul lui r2: " << r2.getId();

	r1.setNume("Caru' cu bere");
	r1.afisare();

	try {
		r1.setNume("AB");
	}
	catch (...) {
		cout << endl << "Nume invalid!";
	}

	r1 = r2;
	r1.afisare();

	r1 = r1;
	r1.afisare();

	r2("Hanul lui Manuc");
	r2.afisare();
	r1.afisare();

	Restaurant* r3 = new Restaurant("Zexe");
	r3->afisare();
	delete r3;

	cout << endl << "Numar restaurante: " << Restaurant::nrRestaurante;
}