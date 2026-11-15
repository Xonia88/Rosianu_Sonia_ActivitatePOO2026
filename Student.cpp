#include<iostream>
#include<cstring>

using namespace std;

class Student {
private:
	const int nrMatricol;
	char* nume;
	int nrNote;
	int* note;
public:
	static int nrStudenti;
	Student() :nrMatricol(++nrStudenti) {
		this->nume = new char[strlen("Student anonim") + 1];
		strcpy_s(this->nume, strlen("Student anonim") + 1, "Student anonim");
		this->nrNote = 0;
		this->note = nullptr;
	}

	Student(int nrMatricol, const char* nume, int nrNote, int* note) :nrMatricol(nrMatricol) {
		nrStudenti++;
		this->nume = new char[strlen(nume) + 1];
		strcpy_s(this->nume, strlen(nume) + 1, nume);
		this->nrNote = nrNote;
		this->note = new int[nrNote];
		for (int i = 0; i < this->nrNote; i++)
		{
			this->note[i] = note[i];
		}
		delete[] note;
	}

	Student(const Student& copie) :nrMatricol(++nrStudenti) {
		if (copie.nume != nullptr) {
			this->nume = new char[strlen(copie.nume) + 1];
			strcpy_s(this->nume, strlen(copie.nume) + 1, copie.nume);
		}
		else {
			this->nume = nullptr;
		}
		this->nrNote = copie.nrNote;

		if (copie.note != nullptr) {
			this->note = new int[this->nrNote];
			for (int i = 0; i < this->nrNote; i++)
			{
				this->note[i] = copie.note[i];
			}
		}
		else {
			this->note = nullptr;
		}
	}

	void operator=(const Student& copie) {
		if (this->nume != nullptr) {
			delete[] this->nume;
			this->nume = nullptr;
		}

		if (copie.nume != nullptr) {
			this->nume = new char[strlen(copie.nume) + 1];
			strcpy_s(this->nume, strlen(copie.nume) + 1, copie.nume);
		}
		else {
			this->nume = nullptr;
		}

		this->nrNote = copie.nrNote;

		if (this->note != nullptr) {
			delete[] this->note;
			this->note = nullptr;
		}

		if (copie.note != nullptr) {
			this->note = new int[this->nrNote];
			for (int i = 0; i < this->nrNote; i++)
			{
				this->note[i] = copie.note[i];
			}
		}
		else {
			this->note = nullptr;
		}
	}

	int getNrNote() {
		return this->nrNote;
	}

	void setNrNote(int valoareNoua) {
		if (valoareNoua >= 0) {
			this->nrNote = valoareNoua;
		}
		else {
			throw exception();
		}
	}

	void setNote(int* vNote, int dim) {
		setNrNote(dim);

		if (this->note != nullptr) {
			delete[] this->note;
			this->note = nullptr;
		}

		if (vNote != nullptr) {
			this->note = new int[this->nrNote];
			for (int i = 0; i < this->nrNote; i++)
			{
				this->note[i] = vNote[i];
			}

			delete[] vNote;
		}
		else {
			this->note = nullptr;
		}
	}

	int& operator[](int index) {
		if (index >= 0 && index < this->nrNote) {
			return this->note[index];
		}
		else {
			throw exception();
		}
	}

	Student operator++(int) {
		Student copie = *this;
		for (int i = 0; i < this->nrNote; i++)
		{
			if (this->note[i] < 10) {
				this->note[i]++;
			}
		}

		return copie;
	}

	bool operator!() {
		for (int i = 0; i < this->nrNote; i++)
		{
			if (this->note[i] < 5) {
				return true;
			}
		}
		return false;
	}

	explicit operator float() {
		if (this->nrNote == 0) {
			return 0;
		}
		float suma = 0;
		for (int i = 0; i < this->nrNote; i++)
		{
			suma += this->note[i];
		}
		return suma / this->nrNote;
	}

	friend void operator<<(ostream& out, Student s) {
		out << endl << "Operator de afisare: ";
		out << endl << "Nr. matricol: " << s.nrMatricol;
		out << endl << "Nume: " << s.nume;
		out << endl << "Nr. note: " << s.nrNote;
		if (s.note != nullptr && s.nrNote > 0) {
			out << endl << "Note: ";
			for (int i = 0; i < s.nrNote - 1; i++) {
				out << s.note[i] << ", ";
			}
			out << s.note[s.nrNote - 1];
		}
	}

	~Student() {
		cout << endl << "S-a apelat destructorul!";
		if (this->nume != nullptr) {
			delete[] this->nume;
		}
		if (this->note != nullptr) {
			delete[] this->note;
		}
	}
};

int Student::nrStudenti = 0;

void main() {
	Student s1;
	cout << s1;

	int* note = new int[4] {9, 4, 7, 10};
	Student* s2 = new Student(1001, "Popescu Ana", 4, note);
	cout << *s2;

	Student s3 = *s2;
	cout << s3;

	s1 = *s2;
	cout << s1;

	s3.setNote(new int[3] {8, 6, 9}, 3);
	cout << s3;

	try {
		s3.setNrNote(-2);
	}
	catch (...) {
		cout << endl << "Valoare negativa!";
	}

	cout << endl << "Nota de pe pozitia 1: " << (*s2)[1];
	(*s2)[1] = 5;
	cout << endl << "Nota modificata: " << (*s2)[1];

	try {
		cout << endl << (*s2)[10];
	}
	catch (...) {
		cout << endl << "Index invalid!";
	}

	if (!s1) {
		cout << endl << "Studentul are cel putin o nota sub 5!";
	}
	else {
		cout << endl << "Studentul nu are note sub 5!";
	}

	Student s4 = s1++;
	cout << s4;
	cout << s1;

	cout << endl << "Cast student -> float (media): " << float(*s2);

	delete s2;

	cout << endl << "Numar studenti: " << Student::nrStudenti;
}