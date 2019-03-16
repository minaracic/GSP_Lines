#include "Mreza.h"
#include <fstream>
#include <regex>
#include<iostream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>

const regex linijeRegex("([^!]*)!([^!]*)!([^!]*)!");

set<string> Mreza::skupLinijaZajednickihStajalista(const Linija& linija) //proveri
{
	set<string> zajednickeLinije;
	Smer smerA = linija.getSmerA();
	Smer smerB = linija.getSmerB();

	vector<int> smerAStajalista = smerA.getSifreStajalista();
	vector<int> smerBStajalista = smerB.getSifreStajalista();

	for (int sifreStajalista : smerAStajalista)
	{
		set<string> linijeZaStajaliste = linijeIndexPoSifriStajalista[sifreStajalista];
		for (auto linijaStajalista : linijeZaStajaliste)
		{
			zajednickeLinije.insert(linijaStajalista);
		}
	}

	for (int sifreStajalista : smerBStajalista)
	{
		set<string> linijeZaStajaliste = linijeIndexPoSifriStajalista[sifreStajalista];
		for (auto linijaStajalista : linijeZaStajaliste)
		{
			zajednickeLinije.insert(linijaStajalista);
		}
	}
	return zajednickeLinije;
}


set<Linija> Mreza::getLinijeZaStajaliste(const int sifraStajalista)
{
	set<Linija> linijeRet;
	set<string> sifreLinijaZaStajaliste = linijeIndexPoSifriStajalista[sifraStajalista];
	for (auto sifraLinije : sifreLinijaZaStajaliste)
	{
		linijeRet.insert(linije[sifraLinije]);
	}
	return linijeRet;
}

Mreza Mreza::parsiraj(const string &dirPath)
{
	string buffer;
	string linijePath = dirPath + "_lines.txt";
	ifstream linijeFile(linijePath);

	if (!linijeFile.failbit)
	{
		cout << "Pogresno ime fajla! " ;
		exit(0);
	}

	set<Linija> linije;
	set<Stajaliste> stajalista;

	while (getline(linijeFile, buffer))
	{
		smatch result;
		if (regex_match(buffer, result, linijeRegex))
		{
			string sifraLinija = result.str(1);
			string okretnica1 = result.str(2);
			string okretnica2 = result.str(3);

			string smerAPath = dirPath + sifraLinija + "_dirA.txt";
			string smerBPath = dirPath + sifraLinija + "_dirB.txt";

			vector<Stajaliste> smerAStajalista = Stajaliste::parsiraj(smerAPath);
			vector<Stajaliste> smerBStajalista = Stajaliste::parsiraj(smerBPath);
			
			Smer smerA(smerAStajalista);
			Smer smerB(smerBStajalista);

			Linija linija(sifraLinija, okretnica1, okretnica2, smerA, smerB);
			linije.insert(linija);

			stajalista.insert(smerAStajalista.begin(), smerAStajalista.end());
			stajalista.insert(smerBStajalista.begin(), smerBStajalista.end());
		}
		else
		{
			std::cout << "Greska prilikom parsiranja mreze: " << buffer << endl;
		}
	}
	linijeFile.close();
	return Mreza(linije, stajalista);
}

Mreza Mreza::parsirajLiniju(const string& dirPath, string sifraLinije)
{
	string buffer;
	string linijePath = dirPath + "_lines.txt";
	ifstream linijeFile(linijePath);

	if (!linijeFile.failbit) 
	{
		cout << "Pogresno ime fajla! ";
		exit(1);
	}

	set<Linija> linije;
	set<Stajaliste> stajalista;

	while (getline(linijeFile, buffer))
	{
		smatch result;
		if (regex_match(buffer, result, linijeRegex))
		{
			string sifraLinija = result.str(1);
			string okretnica1 = result.str(2);
			string okretnica2 = result.str(3);

			if (sifraLinija != sifraLinije)
			{
				continue;
			}

			string smerAPath = dirPath + sifraLinija + "_dirA.txt";
			string smerBPath = dirPath + sifraLinija + "_dirB.txt";

			vector<Stajaliste> smerAStajalista = Stajaliste::parsiraj(smerAPath);
			vector<Stajaliste> smerBStajalista = Stajaliste::parsiraj(smerBPath);

			Smer smerA(smerAStajalista);
			Smer smerB(smerBStajalista);

			Linija linija(sifraLinija, okretnica1, okretnica2, smerA, smerB);
			linije.insert(linija);

			stajalista.insert(smerAStajalista.begin(), smerAStajalista.end());
			stajalista.insert(smerBStajalista.begin(), smerBStajalista.end());
		}
		else
		{
			std::cout << "Greska prilikom parsiranja mreze: " << buffer << endl;
		}
	}
	linijeFile.close();
	return Mreza(linije, stajalista);
}

bool Mreza::pripadaZoni(const Smer& smer, int zona) {

	const vector<int>& sifreStajalista = smer.getSifreStajalista();
	for (auto sifraStajalista : sifreStajalista) 
	{
		Stajaliste stajaliste = stajalista[sifraStajalista];
		if (stajaliste.getZona() == zona)
		{
			return true;
		}
	}
	return false;
}

string Mreza::rawOznakaLinije(string sifraLinije)
{
	int size = sifraLinije.size();
	string rawLinija = "";

	int i = 0;
	while (i < size)
	{
		if (sifraLinije[i] >= '0' && sifraLinije[i] <= '9')
		{
			rawLinija += sifraLinije[i];
		}
		i++;
	}
	return rawLinija;
}

bool Mreza::pripadaZoni(const Linija& linija, int zona) 
{
	Smer smerA = linija.getSmerA();
	Smer smerB = linija.getSmerB();
	return pripadaZoni(smerA, zona) || pripadaZoni(smerB, zona);
}

set<Linija> presekSkupova(const set<Linija>& a, const set<Linija>& b) {
	set<Linija> presek;
	for (auto linija : a) 
	{
		if (b.find(linija) != b.end()) 
		{
			presek.insert(linija);
		}
	}
	return presek;
}


void Mreza::dodajLinijuUIndexPoSifriStajalista(const Linija& linija) {

	vector<int> stajalistaSmerA = linija.getSmerA().getSifreStajalista();
	vector<int> stajalistaSmerB = linija.getSmerB().getSifreStajalista();
	set<int> svaStajalista;
	svaStajalista.insert(stajalistaSmerA.begin(), stajalistaSmerA.end());
	svaStajalista.insert(stajalistaSmerB.begin(), stajalistaSmerB.end());
	for (auto sifraStajalista : svaStajalista) 
	{
		linijeIndexPoSifriStajalista[sifraStajalista].insert(linija.getSifra()); 
	}

}

int Mreza::najmanjePresedanja(int stajaliste1, int stajaliste2)
{
	int brojStajalista = 0;
	Stajaliste stajalist1 = stajalista[stajaliste1];
	Stajaliste stajalist2 = stajalista[stajaliste2];

	set<int> svaStajalista;
	set<string> linijeKrozStajaliste;

	svaStajalista.insert(stajaliste1);

	while (1)
	{
		brojStajalista++;
		for (auto stajaliste : svaStajalista)
		{
			linijeKrozStajaliste.insert(linijeIndexPoSifriStajalista[stajaliste].begin(),
				linijeIndexPoSifriStajalista[stajaliste].end());
		}
		for (auto tekuci : linijeKrozStajaliste)
		{
				vector<int> smerA = linije[tekuci].getSmerA().getSifreStajalista();
				auto smerB = linije[tekuci].getSmerB().getSifreStajalista();

				svaStajalista.insert(smerA.begin(), smerA.end());
				svaStajalista.insert(smerB.begin(), smerB.end());

		}

		for (auto stajaliste : svaStajalista)
		{
			if (stajaliste == stajaliste2)
			{
				return brojStajalista;
				
			}
		}

	}

}

void Mreza::dodajStajalisteULiniju(Linija& linija, const Stajaliste & novoStajaliste, string smer)
{
	int sifraNovogStajalista = novoStajaliste.getSifra();
	string sifraLinije = linija.getSifra();

	if (smer == "A")
	{
		linije[sifraLinije].getSmerA().getSifreStajalista()[sifraNovogStajalista];
		linijeIndexPoSifriStajalista[sifraNovogStajalista].insert(sifraLinije);
	}
	else 
	{
		linije[sifraLinije].getSmerB().getSifreStajalista()[sifraNovogStajalista];
		linijeIndexPoSifriStajalista[sifraNovogStajalista].insert(sifraLinije);
	}
}

Linija Mreza::izbrisiStajalisteIzLinije(string sifraLinije, int sifraStajalistaIzbaci, string smerSifra)
{
	//linije[sifraLinije].getSmerA().getSifreStajalista().erase(sifraStajalistaIzbaci);
	Linija linija = linije[sifraLinije];
	Smer noviSmer;
	Smer stariSmer;
	vector<int> novaStajalista;
	vector<int> staraStajalista;
	int i = 0;

	if (smerSifra == "A")
	{
		novaStajalista = linija.getSmerA().getSifreStajalista();
		for (auto stajaliste : novaStajalista)
		{
			if (stajaliste == sifraStajalistaIzbaci)
			{
				continue;
			}
			novaStajalista[i++] = stajaliste;
		}
		i = 0;
		staraStajalista = linija.getSmerB().getSifreStajalista();
		for (auto stajaliste : staraStajalista)
		{
			novaStajalista[i++] = stajaliste;
		}

		linijeIndexPoSifriStajalista[sifraStajalistaIzbaci].erase(sifraLinije);
		return linija;
	//	return Linija(sifraLinije, linija.getOkretnica1(), linija.getOkretnica2(), novaStajalista, staraStajalista);
	}
	else
	{
		novaStajalista = linija.getSmerB().getSifreStajalista();
		for (auto stajaliste : novaStajalista)
		{
			if (stajaliste == sifraStajalistaIzbaci)
			{
				continue;
			}
			novaStajalista[i++] = stajaliste;
		}
		i = 0;
		staraStajalista = linija.getSmerA().getSifreStajalista();
		for (auto stajaliste : staraStajalista)
		{
			novaStajalista[i++] = stajaliste;
		}
	}
	
}

void Mreza::promeniSifruLinije(string staraSifraLinija, string novaSifraLinija)
{
	Linija novaLinija = linije[staraSifraLinija];

	novaLinija.setSifra(novaSifraLinija);
	linije.erase(staraSifraLinija);

	linije[novaSifraLinija] = novaLinija;

	//auto nodeHandler = linije.extract(staraSifraLinija);
}

bool Mreza::linijaProlaziKrozStajalista(const Linija& linija, const int stajaliste1, const int stajaliste2)
{
	Smer smerA = linija.getSmerA();
	Smer smerB = linija.getSmerB();

	vector<int> smerAStajalista = smerA.getSifreStajalista();
	vector<int> smerBStajalista = smerB.getSifreStajalista();
	
	bool flag1 = false;
	bool flag2 = false;
	for (int stajaliste : smerAStajalista)
	{
		if (stajaliste == stajaliste1)
		{
			flag1 = true;
		}
		if (stajaliste == stajaliste2)
		{
			flag2 = true;
		}
	}
	if (flag1 && flag2)
	{
		return true;
	}

	flag1 = false;
	flag2 = false;

	for (int stajaliste : smerBStajalista)
	{
		if (stajaliste == stajaliste1)
		{
			flag1 = true;
		}
		if (stajaliste == stajaliste2)
		{
			flag2 = true;
		}
	}
	
	if (flag1 && flag2)
	{
		return true;
	}

	return false;
}

Stajaliste Mreza::najblizeStajaliste(const Lokacija & lokacija)
{
	map<Stajaliste, double> razdaljine;

	for (auto stajaliste : stajalista)
	{
		pair<Stajaliste, double> par;
		Lokacija trenutnaLokacija = stajaliste.second.getLokacija();

		razdaljine[stajaliste.second];
		razdaljine[stajaliste.second] = Lokacija::udaljenost(lokacija, trenutnaLokacija);

	}
	auto min = *min_element(razdaljine.begin(), razdaljine.end(),
		[](pair<Stajaliste, double> parA, pair<Stajaliste, double> parB) {return parA.second < parB.second; });
	

	return min.first;
}

Stajaliste Mreza::najblizeStajalisteLinije(const Lokacija & lokacija, string sifraLinija)
{
	map<Stajaliste, double> razdaljine;
	Linija linija = linije[sifraLinija];

	vector<int> stajalistaSmerA = linija.getSmerA().getSifreStajalista();
	vector<int> stajalistaSmerB = linija.getSmerB().getSifreStajalista();

	for (auto sifraStajalista : stajalistaSmerA)
	{
		Stajaliste stajaliste = stajalista[sifraStajalista];
		Lokacija trenutnaLokacija = stajaliste.getLokacija();

		razdaljine[stajaliste];
		razdaljine[stajaliste] = Lokacija::udaljenost(lokacija, trenutnaLokacija);

	}

	for (auto sifraStajalista : stajalistaSmerB)
	{
		Stajaliste stajaliste = stajalista[sifraStajalista];
		Lokacija trenutnaLokacija = stajaliste.getLokacija();

		razdaljine[stajaliste];
		razdaljine[stajaliste] = Lokacija::udaljenost(lokacija, trenutnaLokacija);

	}
	auto min = *min_element(razdaljine.begin(), razdaljine.end(),
		[](pair<Stajaliste, double> parA, pair<Stajaliste, double> parB) {return parA.second < parB.second; });


	return min.first;
}


string Mreza::najviseZajednickihStajalista(string linijaSifra)
{
	map<string, int> zajednickeLinije;
	Linija linija;

	linija = linije[linijaSifra];
	vector<int> stajalistaSmerA = linija.getSmerA().getSifreStajalista();
	vector<int> stajalistaSmerB = linija.getSmerB().getSifreStajalista();

	for (auto stajaliste : stajalistaSmerA)
	{
		set<string> linijeStajalista = linijeIndexPoSifriStajalista[stajaliste];
		for (string linijaStajalista : linijeStajalista)
		{
			auto iterator = zajednickeLinije.find(linijaStajalista);
			if (iterator == zajednickeLinije.end())
			{
				zajednickeLinije[linijaStajalista];
				zajednickeLinije[linijaStajalista] = 0;

			}
			else
			{
				zajednickeLinije[linijaStajalista]++;
			}
		}
	}
	for (auto stajaliste : stajalistaSmerB)
	{
		set<string> linijeStajalista = linijeIndexPoSifriStajalista[stajaliste];
		for (string linijaStajalista : linijeStajalista)
		{
			auto iterator = zajednickeLinije.find(linijaStajalista);
			if (iterator == zajednickeLinije.end())
			{
				zajednickeLinije[linijaStajalista];
				zajednickeLinije[linijaStajalista] = 0;

			}
			else
			{
				zajednickeLinije[linijaStajalista]++;
			}
		}
	}
	auto prviMax = max_element(zajednickeLinije.begin(), zajednickeLinije.end(), 
		[](pair<string, int> parA, pair<string, int> parB) {return parA.second < parB.second; });
	zajednickeLinije.erase(prviMax);
	auto drugiMax = *max_element(zajednickeLinije.begin(), zajednickeLinije.end(),
		[](pair<string, int> parA, pair<string, int> parB) {return parA.second < parB.second; });
	
	return drugiMax.first;
}

void Mreza::ispisiLiniju(string sifraLinije)
{
	cout << "Linija " << sifraLinije << " : " << endl;
	

	Linija linija;
	linija = linije[sifraLinije];

	vector<int> sifreStajalistaSmerA = linija.getSmerA().getSifreStajalista();
	vector<int> sifreStajalistaSmerB = linija.getSmerB().getSifreStajalista();

	cout << "  Stajalista za smer A : " << endl;
	for (int sifraStajalista : sifreStajalistaSmerA)
	{
		ispisiStajalisteBezLinija(sifraStajalista);
		ispisiLinijeZaStajaliste(sifraStajalista);
		cout << endl;

	}

	cout << "  Stajalista za smer B : " << endl;
	for (int sifraStajalista : sifreStajalistaSmerA)
	{
		ispisiStajalisteBezLinija(sifraStajalista);
		ispisiLinijeZaStajaliste(sifraStajalista);
		cout << endl;
	}
	

}

void Mreza::ispisiStajalisteBezLinija(int sifraStajalista)
{
	Stajaliste stajaliste = stajalista[sifraStajalista];

	cout << setw(6) << sifraStajalista;
	cout << setw(35) << stajaliste.getNaziv();
	cout << setw(22) << stajaliste.getLokacija();
	cout << setw(6) << stajaliste.getZona() << "\t";
}

void Mreza::ispisiLinijeZaStajaliste(int sifraStajalista)
{
	set<string> linijeZaStajaliste = linijeIndexPoSifriStajalista[sifraStajalista];
	cout << "{";
	for (string linijaZaStajaliste : linijeZaStajaliste)
	{
		cout << setw(5) <<linijaZaStajaliste;
	}
	cout << "}";
}

void Mreza::ispisiRawLiniju(string sifraLinije)
{
	Linija linija = linije[sifraLinije];

	cout << setw(7) << sifraLinije;
	cout << setw(35) << linija.getOkretnica1();
	cout << setw(35) << linija.getOkretnica2() << endl;

}

set<Linija> Mreza::getLinijeZaZonu(const set<int>& zone)
{
	set<Linija> linijeZone;
	bool initialized = false;
	for (auto zona : zone) 
	{
		if (!initialized) 
		{
			initialized = true;
			linijeZone = getLinije(zona);
		}
		else 
		{
			linijeZone = presekSkupova(linijeZone, getLinije(zona));
		}
	}
	return linijeZone;

}

set<Linija> Mreza::getLinijeZaOznaku(const string oznakaLinije, bool manjeLinijeBool)
{
	set<Linija> manjeLinije;
	set<Linija> veceLinije;

	int brojLinije = atoi(rawOznakaLinije(oznakaLinije).c_str());

	for (auto linija : linije)
	{
		string sifraLinija = linija.first;
	    string rawSifra = rawOznakaLinije(sifraLinija);

		int brojTrenutneLinije = atoi(rawSifra.c_str());

		if (brojTrenutneLinije > brojLinije)
		{
			veceLinije.insert(linija.second);
		}
		else
		{
			manjeLinije.insert(linija.second);
		}
	}
	
	if (manjeLinijeBool)
	{
		return manjeLinije;
	}

	return veceLinije;
}

set<Linija> Mreza::getLinijeUOpsegu(const string donjaGranicaSifra, const string gornjaGranicaSifra)
{
	set<Linija> linijeUOpsegu;
	int donjaGranica = atoi(rawOznakaLinije(donjaGranicaSifra).c_str());
	int gornjaGranica = atoi(rawOznakaLinije(gornjaGranicaSifra).c_str());

	for (auto linija : linije)
	{
		string sifraLinija = linija.first;
		string rawSifra = rawOznakaLinije(sifraLinija);

		int brojTrenutneLinije = atoi(rawSifra.c_str());

		if (brojTrenutneLinije > donjaGranica && brojTrenutneLinije < gornjaGranica)
		{
			linijeUOpsegu.insert(linija.second);
		}
	}
	return linijeUOpsegu;
}

set<Linija> Mreza::getLinijeZaBrojStajalista(const int brojStajalista, bool manjiBrojStajalista)
{
	set<Linija> skupLinija;
	int ukupnoStajalista = 0;

	for (auto linija : linije)
	{
		Smer smerA = linija.second.getSmerA();
		Smer smerB = linija.second.getSmerB();

		int brojStajalistaSmerA = smerA.getBrojStajalista();
		int brojStajalistaSmerB = smerB.getBrojStajalista();
		ukupnoStajalista = brojStajalistaSmerA + brojStajalistaSmerB;

		if (manjiBrojStajalista)
		{
			if (ukupnoStajalista < brojStajalista)
			{
				skupLinija.insert(linija.second);
			}
		}
		else
		{
			if (ukupnoStajalista > brojStajalista)
			{
				skupLinija.insert(linija.second);
			}
		}

	}

	return skupLinija;
}



set<Linija> Mreza::getLinije(int zona) {
	set<Linija> linijeZona;
	for (auto linijaEntry : linije)
	{
		if (pripadaZoni(linijaEntry.second, zona))
		{
			linijeZona.insert(linijaEntry.second);
		}
	}
	return linijeZona;

}


map<pair<string, string>, int> Mreza::brojZajednickihStajalista()
{
	map<pair<string, string>, int> paroviLinija;

	for(auto stajaliste : stajalista)
	{
		int sifraStajalista = stajaliste.second.getSifra();
		set<string> skupLinija = linijeIndexPoSifriStajalista[sifraStajalista];
		for (auto linijaPrva : skupLinija)
		{
			for (auto linijaDruga : skupLinija)
			{
				if (linijaPrva >= linijaDruga)
				{
					continue;
				}
				using parLinija = pair<string, string>;
				parLinija noviPar = make_pair(linijaPrva, linijaDruga);
				
				auto iterator = paroviLinija.find(noviPar);
				if (iterator == paroviLinija.end())
				{
					paroviLinija[noviPar] = 1;
				}
				else
				{
					paroviLinija[noviPar]++;
				}
			}
		}
	}

	return paroviLinija;

}

set<Stajaliste> Mreza::maxJednaStanica(const Stajaliste & stajaliste)
{
	set<Stajaliste> skupStajalista;
	set<string> skupLinija = linijeIndexPoSifriStajalista[stajaliste.getSifra()];

	for (auto linija : skupLinija)
	{
		vector<int> stajalistaSmerA = linije[linija].getSmerA().getSifreStajalista();
		vector<int> stajalistaSmerB = linije[linija].getSmerB().getSifreStajalista();

		for (auto iterator = stajalistaSmerA.begin(); iterator != stajalistaSmerA.end(); iterator++)
		{
			if (*iterator == stajaliste.getSifra() && (iterator+1)!= stajalistaSmerA.end())
			{
				skupStajalista.insert(stajalista[*(iterator + 1)]);
				continue;
			}
		}

		for (auto iterator = stajalistaSmerB.begin(); iterator != stajalistaSmerB.end(); iterator++)
		{
			if (*iterator == stajaliste.getSifra() && (iterator + 1) != stajalistaSmerB.end())
			{
				skupStajalista.insert(stajalista[*(iterator + 1)]);
				continue;
			}
		}
	}
	return skupStajalista;
}
