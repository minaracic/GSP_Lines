#pragma once
#include<string>
#include<regex>
#include<fstream>
#include<iostream>
#include<set>
#include"Lokacija.h"
#include"Linija.h"
using namespace std;

const regex stajalistaRegex("([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)");

class Stajaliste
{
private:
	int sifra, zona;
	string naziv;
	Lokacija lokacija;
public:
	Stajaliste() {}
	Stajaliste(int sifra,
		string naziv,
		double x,
		double y,
		int zona) 
		: sifra(sifra), naziv(naziv), lokacija(x, y), zona(zona) {}
	//TODO: Prebaci u .cpp, build ne radi 
	static vector<Stajaliste> parsiraj(const string &filePath)
	{
		ifstream stajalistaFile(filePath);
		string buffer;
		vector<Stajaliste> stajalista;
		while (getline(stajalistaFile, buffer))
		{
			smatch result;
			if (regex_match(buffer, result, stajalistaRegex))
			{
				int sifraStajalista = atoi(result.str(1).c_str());
				string naziv = result.str(2);
				double x = atof(result.str(3).c_str());
				double y = atof(result.str(4).c_str());
				int zona = atoi(result.str(5).c_str());

				Stajaliste stajaliste(sifraStajalista, naziv, x, y, zona);
				stajalista.push_back(stajaliste);
			}
			else
			{
				std::cout << "Greska prilikom parsiranja linije: " << buffer << endl;
			}
		}
		return stajalista;
	}

	bool operator<(const Stajaliste &other)const { return sifra < other.sifra; }
	bool operator==(const Stajaliste &other)const { return sifra == other.sifra; }

	int getSifra()const { return sifra; }
	int getZona()const { return zona; }
	string getNaziv()const { return naziv; }
	Lokacija getLokacija()const { return lokacija; }
};