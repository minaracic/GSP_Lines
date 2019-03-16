#pragma once
#include"Stajaliste.h"

class Smer {
private:
	vector<int> sifreStajalista;
public:
	Smer() {}
	Smer(const vector<Stajaliste>& stajalista)
	{
		for (auto stajaliste : stajalista)
		{
			sifreStajalista.push_back(stajaliste.getSifra());
		}
	}

	int getBrojStajalista()const { return sifreStajalista.size(); }
	const vector<int>& getSifreStajalista()const{ return sifreStajalista; }
};