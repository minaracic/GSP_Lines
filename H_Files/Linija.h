#pragma once
#include<string>
#include "Smer.h"
using namespace std;
class Linija
{
	string sifra;
	string okretnica1, okretnica2;
	Smer smerA, smerB;
public:
	Linija() {}
	Linija(const string &sifra,
		const string &okretnica1, 
		const string &okretnica2, 
		const Smer &smerA, 
		const Smer &smerB)
		: sifra(sifra), okretnica1(okretnica1), okretnica2(okretnica2), smerA(smerA), smerB(smerB){}

	bool operator<(const Linija &other)const { return sifra < other.sifra; }
	Smer getSmerA() const{ return smerA; }
	Smer getSmerB() const { return smerB; }
	string getSifra()const { return sifra; }
	string getOkretnica1()const { return okretnica1; }
	string getOkretnica2()const { return okretnica2; }
	void setSifra(string novaSifra) { sifra = novaSifra; }
	
	
};