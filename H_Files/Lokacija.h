#pragma once
#include<iostream>
using namespace std;
class Lokacija 
{
private:
	double x, y;
public:
	Lokacija(){}
	Lokacija(double x, double y) :x(x), y(y) {}

	double getX()const { return x;}
	double getY()const { return y; }
	friend ostream& operator<<(ostream& ot, const Lokacija &lokacija);
	static double udaljenost(const Lokacija&, const Lokacija&);
};