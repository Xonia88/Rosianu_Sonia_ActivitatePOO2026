#include<iostream>
#include<cstring>

using namespace std;

class Farmacie {
private:
	const int cod;
	char* denumire;
	int nrMedicamente;
	float* preturi;
public:
	static int nrFarmacii;
	Farmacie() :cod(++nrFarmacii) {
		this->denumire = new char[strlen("Farmacie generala") + 1];
		strcpy_s(this->denumire, strlen("Farmacie generala") + 1, "Farmacie generala");
		this->nrMedicamente = 0;
		this->preturi = nullptr;
	}

	Farmacie(int cod, const char* denumire, int nrMedicamente, float* preturi) :cod(cod) {
		nrFarmacii++;
		this->denumire = new char[strlen(denumire) + 1];
		strcpy_s(this->denumire, strlen(denumire) + 1, denumire);
		this->nrMedicamente = nrMedicamente;
		this->preturi = new float[nrMedicamente];
		for (int i = 0; i < this->nrMedicamente; i++)
		{
			this->preturi[i] = preturi[i];
		}
		delete[] preturi;
	}

	Farmacie(const Farmacie& copie) :cod(++nrFarmacii) {
		if (copie.denumire != nullptr) {
			this->denumire = new char[strlen(copie.denumire) + 1];
			strcpy_s(this->denumire, strlen(copie.denumire) + 1, copie.denumire);
		}
		else {
			this->denumire = nullptr;
		}
		this->nrMedicamente = copie.nrMedicamente;

		if (copie.preturi != nullptr) {
			this->preturi = new float[this->nrMedicamente];
			for (int i = 0; i < this->nrMedicamente; i++)
			{
				this->preturi[i] = copie.preturi[i];
			}
		}
		else {
			this->preturi = nullptr;
		}
	}

	void operator=(const Farmacie& copie) {
		if (this->denumire != nullptr) {
			delete[] this->denumire;
			this->denumire = nullptr;
		}

		if (copie.denumire != nullptr) {
			this->denumire = new char[strlen(copie.denumire) + 1];
			strcpy_s(this->denumire, strlen(copie.denumire) + 1, copie.denumire);
		}
		else {
			this->denumire = nullptr;
		}

		this->nrMedicamente = copie.nrMedicamente;

		if (this->preturi != nullptr) {
			delete[] this->preturi;
			this->preturi = nullptr;
		}

		if (copie.preturi != nullptr) {
			this->preturi = new float[this->nrMedicamente];
			for (int i = 0; i < this->nrMedicamente; i++)
			{
				this->preturi[i] = copie.preturi[i];
			}
		}
		else {
			this->preturi = nullptr;
		}
	}

	int getNrMedicamente() {
		return this->nrMedicamente;
	}

	float* getPreturi() {
		if (this->preturi == nullptr) {
			return nullptr;
		}
		float* vPreturi = new float[this->nrMedicamente];
		for (int i = 0; i < this->nrMedicamente; i++)
		{
			vPreturi[i] = this->preturi[i];
		}
		return vPreturi;
	}

	void operator+=(float pretNou) {
		float* vNou = new float[this->nrMedicamente + 1];
		for (int i = 0; i < this->nrMedicamente; i++)
		{
			vNou[i] = this->preturi[i];
		}
		vNou[this->nrMedicamente] = pretNou;

		if (this->preturi != nullptr) {
			delete[] this->preturi;
		}
		this->preturi = vNou;
		this->nrMedicamente++;
	}

	bool operator==(const Farmacie& f) {
		return this->nrMedicamente == f.nrMedicamente;
	}

	Farmacie operator++() {
		for (int i = 0; i < this->nrMedicamente; i++)
		{
			this->preturi[i]++;
		}
		return *this;
	}

	float operator()() {
		float total = 0;
		for (int i = 0; i < this->nrMedicamente; i++)
		{
			total += this->preturi[i];
		}
		return total;
	}

	friend void operator<<(ostream& out, Farmacie f) {
		out << endl << "Operator de afisare: ";
		out << endl << "Cod: " << f.cod;
		out << endl << "Denumire: " << f.denumire;
		out << endl << "Nr. medicamente: " << f.nrMedicamente;
		if (f.preturi != nullptr && f.nrMedicamente > 0) {
			out << endl << "Preturi: ";
			for (int i = 0; i < f.nrMedicamente - 1; i++) {
				out << f.preturi[i] << " lei, ";
			}
			out << f.preturi[f.nrMedicamente - 1] << " lei.";
		}
	}

	friend void operator>>(istream& in, Farmacie& f);

	~Farmacie() {
		cout << endl << "S-a apelat destructorul!";
		if (this->denumire != nullptr) {
			delete[] this->denumire;
		}
		if (this->preturi != nullptr) {
			delete[] this->preturi;
		}
	}
};

void operator>>(istream& in, Farmacie& f) {
	cout << endl << "Denumire: ";
	char buffer[100];
	in >> buffer;

	if (f.denumire != nullptr) {
		delete[] f.denumire;
		f.denumire = nullptr;
	}
	f.denumire = new char[strlen(buffer) + 1];
	strcpy_s(f.denumire, strlen(buffer) + 1, buffer);

	cout << endl << "Nr. medicamente: ";
	in >> f.nrMedicamente;

	if (f.preturi != nullptr) {
		delete[] f.preturi;
		f.preturi = nullptr;
	}

	f.preturi = new float[f.nrMedicamente];
	for (int i = 0; i < f.nrMedicamente; i++) {
		cout << endl << "preturi[" << i << "]: ";
		in >> f.preturi[i];
	}
}

int Farmacie::nrFarmacii = 0;

void main() {
	Farmacie f1;
	cout << f1;

	float* preturi = new float[3] {12.5, 30, 8.5};
	Farmacie* f2 = new Farmacie(101, "Catena", 3, preturi);
	cout << *f2;

	float* vPreturi = f2->getPreturi();
	cout << endl << "Preturile din getter: ";
	for (int i = 0; i < f2->getNrMedicamente(); i++)
	{
		cout << vPreturi[i] << " lei, ";
	}
	delete[] vPreturi;

	f1 = *f2;
	cout << f1;

	(*f2) += 45;
	cout << *f2;

	if (f1 == *f2) {
		cout << endl << "Farmaciile au acelasi numar de medicamente!";
	}
	else {
		cout << endl << "Farmaciile au numar diferit de medicamente!";
	}

	++f1;
	cout << f1;

	cout << endl << "Valoarea totala a medicamentelor din f2: " << (*f2)();

	Farmacie f3;
	cin >> f3;
	cout << f3;

	delete f2;

	cout << endl << "Numar farmacii: " << Farmacie::nrFarmacii;
}