#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class Product
{
	int id;
	char* name;
	char* description;
	double price;
	double* priceHistory;
	int nr_priceHistory;

public:


	//all getters
	int getid() { return this->id; }
	char* getname() { return this->name; }
	char* getdescription() { return this->description; }
	double getprice() { return this->price; }
	double* getpriceHistory() { return this->priceHistory; }
	int getnr_priceHistory() { return this->nr_priceHistory; }

	//all setters
	void setid(int id) { this->id = id; }
	void setname(char* name)
	{
		if (this->name != NULL)
			delete[] this->name;
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
	}
	void setdescription(char* description)
	{
		if (this->description != NULL)
			delete[] this->description;
		this->description = new char[strlen(description) + 1];
		strcpy(this->description, description);
	}
	void setnr_priceHistory(int nr_priceHistory) { this->nr_priceHistory = nr_priceHistory; }
	void setprice(double price)
	{
		
		double* newPriceHistory = new double[this->nr_priceHistory+1];
		for (int i = 0; i < this->nr_priceHistory; i++) {
			newPriceHistory[i] = this->priceHistory[i];
		}
		newPriceHistory[this->nr_priceHistory] = this->price;
		delete[] this->priceHistory;
		this->nr_priceHistory++;
		this->priceHistory = newPriceHistory;
		this->price = price;
	}		

	Product()
	{
		this->id = 0;
		this->price = 0;
		this->name = new char[strlen("necunoscut") + 1];
		strcpy(this->name, "necunoscut");
		this->description = new char[strlen("necunoscut") + 1];
		strcpy(this->description, "necunoscut");
		this->nr_priceHistory = 1;
		this->priceHistory = new double[this->nr_priceHistory];
		for (int i = 0; i < this->nr_priceHistory; i++)
			this->priceHistory[i] = 0;

	}

	Product(int id, const char* name, const char* description, double price, const double* priceHistory, int nr_priceHistory)
	{
		this->id = id;
		this->price = price;
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
		this->description = new char[strlen(description) + 1];
		strcpy(this->description, description);
		this->nr_priceHistory = nr_priceHistory;
		this->priceHistory = new double[this->nr_priceHistory];
		for (int i = 0; i < this->nr_priceHistory; i++)
			this->priceHistory[i] = priceHistory[i];

	}

	Product(const Product& p)
	{
		this->id = p.id;
		this->price = p.price;
		this->name = new char[strlen(p.name) + 1];
		strcpy(this->name, p.name);
		this->description = new char[strlen(p.description) + 1];
		strcpy(this->description, p.description);
		this->nr_priceHistory = p.nr_priceHistory;
		this->priceHistory = new double[this->nr_priceHistory];
		for (int i = 0; i < this->nr_priceHistory; i++)
			this->priceHistory[i] = p.priceHistory[i];
	}

	double getPriceAverage()
	{
		double sum = 0;
		for (int i = 0; i < this->nr_priceHistory; i++)
		{
			sum = sum + this->priceHistory[i] ;
		}
		sum = sum + this->price;
		return sum / (this->nr_priceHistory+1);
	}

	friend istream& operator >> (istream& in, Product& p);

	~Product()
	{
		if (this->name != NULL)
		{
			delete[] this->name;
			this->name = NULL;
		}
		if (this->description != NULL)
		{
			delete[] this->description;
			this->description = NULL;
		}
		if (this->priceHistory != NULL)
		{
			delete[] this->priceHistory;
			this->priceHistory = NULL;
		}
	}
};

istream& operator >> (istream& in, Product& p)
{
	char aux[100];
	cout << "Introduceti id: ";
	in >> p.id;
	cout << endl;
	cout << "Introduceti pretul: ";
	in >> p.price;
	cout << endl;
	cout << "Introduceti numele: ";
	in >> aux;
	p.name = new char[strlen(aux) + 1];
	strcpy(p.name, aux);
	cout << endl;
	cout << "Introduceti descrierea: ";
	in>>aux;
	p.name = new char[strlen(aux) + 1];
	strcpy(p.name, aux);
	cout << endl;
	cout << "Introduceti dimensiunea istoricului preturilor: ";
	in >> p.nr_priceHistory;
	p.priceHistory = new double[p.nr_priceHistory];
	for (int i = 0; i < p.nr_priceHistory; i++)
	{
		cout << endl;
		cout << "Introduceti pretul istoric " << i + 1 << ": ";
		in >> p.priceHistory[i];
	}
	return in;
}

int main()
{
	Product p;
	cin >> p;
	cout << "Media preturilor: " << p.getPriceAverage() << endl;

	Product p1(p);
	double newPrice;
	cout << "Introduceti un nou pret: ";
	cin >> newPrice;
	p1.setprice(newPrice);
	cout << "Media preturilor dupa actualizare: " << p1.getPriceAverage() << endl;

}