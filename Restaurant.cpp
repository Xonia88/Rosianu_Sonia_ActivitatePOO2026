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

	~Restaurant() {
		if (this->nume != nullptr) {
			delete[] this->nume;
		}
	}
};

int Restaurant::nrRestaurante = 0;

void main() {
	Restaurant r1;
	Restaurant r2("La Mama");
}