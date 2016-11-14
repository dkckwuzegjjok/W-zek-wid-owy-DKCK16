#include <iostream>
using namespace std;

class Regal;
class Poziom;

class Przedmiot
{
	private:
		int id;
		string nazwa;
		string kolor;
		string ksztalt;
		string material;
		int wysokosc;
		int szerokosc;
		int start;
		int koniec;

	public:
		Poziom* poziom;

		Przedmiot(int id, string nazwa, string kolor, string ksztalt, string material, int wysokosc, int szerokosc, int start)
		{
			this->id=id;
			poziom = NULL;
			this->nazwa=nazwa;
			this->kolor=kolor;
			this->ksztalt=ksztalt;
			this->material=material;
			this->wysokosc=wysokosc;
			this->szerokosc=szerokosc;
			this->start=start;
			koniec=start+szerokosc;
		}

		int getId()
		{
			return id;
		}
		Poziom& getPoziom()
		{
			return *poziom;
		}
		string getNazwa()
		{
			return nazwa;
		}
		string getKolor()
		{
			return kolor;
		}
		string getKsztalt()
		{
			return ksztalt;
		}
		string getMaterial()
		{
			return material;
		}
		int getWysokosc()
		{
			return wysokosc;
		}
		int getSzerokosc()
		{
			return szerokosc;
		}
		int getStart()
		{
			return start;
		}
		int getEnd()
		{
			return koniec;
		}
		void changePoziom(Poziom& poziom)
		{
		    this->poziom = &poziom;
		}
};

class Poziom
{
	private:
		int id_poziom;
		int wysokosc;

	public:
		Regal* regal;

		Poziom(int id_poziom, int wysokosc)
		{
			this->id_poziom=id_poziom;
			this->wysokosc=wysokosc;
			cout<<"Tworze poziom"<<endl;
		}

};

class Regal
{
	private:
		static const int ilosc_poziomow = 3;
		int id_reg;
		int szerokosc;

	public:
		Poziom **poziomy;
		Regal(int id_reg, int szerokosc)
		{
			this->id_reg=id_reg;
			this->szerokosc=szerokosc;
			cout<<"Tworze regal"<<endl;

			poziomy = new Poziom*[ilosc_poziomow];
			for(int i=0; i<ilosc_poziomow; i++)
			{
				poziomy[i]=new Poziom(i,100*i);
				poziomy[i]->regal = this;
			}
		}

		int getId_reg()
		{
			return id_reg;
		}
		int getSzerokosc()
		{
			return szerokosc;
		}

};

class Magazyn
{
	private:
		static const int ilosc_regalow = 6;

	public:
		Regal **regaly;
		Magazyn()
		{
			cout<<"Tworze magazyn"<<endl;
			regaly = new Regal*[ilosc_regalow];
			for(int i=0; i<ilosc_regalow; i++)
			{
				regaly[i]=new Regal(i,1000);
			}
		}
};


int main()
{
	Przedmiot ob1(1, "skrzynia", "czerwony", "szescian", "drewno", 100, 100, 0);

	Magazyn magazyn;
    ob1.changePoziom(*(magazyn.regaly[2]->poziomy[1]));

	cout<<ob1.getNazwa()<<endl;
	cout<<ob1.getKolor()<<endl;
	cout<<ob1.getStart()<<endl;

	cout<<ob1.getEnd()<<endl;

	return 0;
}
