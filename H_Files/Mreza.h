#pragma once
#include<set>
#include<map>
#include"Linija.h"
#include"Stajaliste.h"
using namespace std;

class Mreza
{
private:
	map<string, Linija> linije;
	map<int, Stajaliste> stajalista;
	map<int, set<string>> linijeIndexPoSifriStajalista;

	set<Linija> getLinije(int zona);
	bool pripadaZoni(const Linija& linija, int zona);
	bool pripadaZoni(const Smer& smer, int zona);
	string rawOznakaLinije(string sifraLinije);

public:
	Mreza(){}
	Mreza(const set<Linija> &linije, const set<Stajaliste> &stajalista)
	{
		for (auto linija : linije) 
		{
			this->linije[linija.getSifra()] = linija;
			dodajLinijuUIndexPoSifriStajalista(linija);

		}
		for (auto stajaliste : stajalista) {
			this->stajalista[stajaliste.getSifra()] = stajaliste;
		}
	}
	static Mreza parsiraj(const string &fileName);
	static Mreza parsirajLiniju(const string &fileName, string sifraLinije);

	set<string> skupLinijaZajednickihStajalista(const Linija& linija);
	set<Linija> getLinijeZaStajaliste(const int sifraStajalista);
	set<Linija> getLinijeZaZonu(const set<int>& zone);
	set<Linija> getLinijeZaOznaku(const string oznakaLinije, bool manjeLinijeBool);
	set<Linija> getLinijeUOpsegu(const string donjaGranicaSifra, const string gornjaGranicaSifra);
	set<Linija> getLinijeZaBrojStajalista(const int brojStajalista, bool manjiBrojStajalista);
	string najviseZajednickihStajalista(string linijaSifra);
	bool linijaProlaziKrozStajalista(const Linija& linija, const int stajaliste1, const int stajaliste2);
	Stajaliste najblizeStajaliste(const Lokacija& lokacija);
	Stajaliste najblizeStajalisteLinije(const Lokacija& lokacija, string sifraLinija);
	map<pair<string, string>, int> brojZajednickihStajalista();
	set<Stajaliste> maxJednaStanica(const Stajaliste& stajaliste);
	void dodajLinijuUIndexPoSifriStajalista(const Linija& linija);
	int najmanjePresedanja(int stajaliste1, int stajaliste2);
	void dodajStajalisteULiniju(Linija& linija, const Stajaliste& novoStajaliste, string smer);
	Linija izbrisiStajalisteIzLinije(string sifraLinije, int sifraStajalistaIzbaci, string smer);
	void promeniSifruLinije(string staraSifraLinije, string novaSifraLinije);
	
	void ispisiLiniju(string sifraLinije);
	void ispisiStajalisteBezLinija(int sifraStajalista);
	void ispisiLinijeZaStajaliste(int sifraStajalista);
	void ispisiRawLiniju(string sifraLinije);

	Linija getLinija(string sifraLinija) { return linije[sifraLinija]; }
	map<string, Linija> &getLinije() { return linije; }
	Stajaliste getStajaliste(int sifraStajalista) { return stajalista[sifraStajalista]; }
};