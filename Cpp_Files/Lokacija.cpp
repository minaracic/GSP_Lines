#include "Lokacija.h"
#include<iomanip>
#include<math.h>

using namespace std;
ostream & operator<<(ostream & ot, const Lokacija & lokacija)
{
	return ot << setw(22) << "(" << lokacija.getX() << ", " << lokacija.getY() << ")";
}

double Lokacija::udaljenost(const Lokacija &lokacija1, const Lokacija &lokacija2)
{
	double x1 = lokacija1.getX();
	double x2 = lokacija2.getX();
	double y1 = lokacija1.getY();
	double y2 = lokacija2.getY();

	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
