#include<iostream>
#include<set>
#include "Mreza.h"
using namespace std;
const string fileName = "C:\\Users\\Mina\\Desktop\\Projekat\\data\\";

void main()
{
	Mreza mreza;

	int opcija;
	while (1)
	{
		system("cls");
		cout << "-----GLAVNI MENI-----" << endl;
		cout << "1. Parsiraj" << endl;
		cout << "2. Ispisi" << endl;
		cout << "3. Obradi" << endl;
		cout << "4. Filtriraj" << endl;
		cout << "5. Odredi" << endl;
		cout << "6. Kraj" << endl;
		cin >> opcija;
		if (opcija == 1)
		{
			system("cls");
			cout << "0. Nazad" << endl;
			cout << "1. Parsiraj mrezu" << endl;
			cout << "2. Parsiraj liniju" << endl;
			cin >> opcija;

			if (opcija == 0)
			{
				continue;
			}
			if (opcija == 1)
			{
				mreza = Mreza::parsiraj(fileName);
			}
			if (opcija == 2)
			{
				string sifraLinije;

				cout << "Unesi sifru linije za parsiranje: ";
				cin >> sifraLinije;

				mreza = Mreza::parsirajLiniju(fileName, sifraLinije);
			}
			else
			{
				continue;
			}
		}

		if (opcija == 2)
		{
			system("cls");
			cout << "0. Nazad" << endl;
			cout << "1. Ispisi sve podatke o linijama" << endl;
			cout << "2. Ispisi sve linije i stajalista" << endl;
			cout << "3. Ispisi sve linije i stajalista za odredjenu liniju" << endl;

			cin >> opcija;

			if (opcija == 1)
			{
				map<string, Linija> sveLinije = mreza.getLinije();
				for (auto linija : sveLinije)
				{
					mreza.ispisiRawLiniju(linija.first);
				}
				system("PAUSE");
			}
			if (opcija == 2)
			{
				map<string, Linija> sveLinije = mreza.getLinije();
				for (auto linija : sveLinije)
				{
					mreza.ispisiLiniju(linija.first);
				}
				system("PAUSE");
			}
			if (opcija == 3)
			{
				string sifraLinija;
				cout << "Linija? " << endl;
				cin >> sifraLinija;

				map<string, Linija> sveLinije = mreza.getLinije();
				for (auto linija : sveLinije)
				{
					if(linija.first == sifraLinija)
					mreza.ispisiLiniju(linija.first);
				}
				system("PAUSE");
			}
			else
			{
				continue;
			}
		}
		if (opcija == 3)
		{
			system("cls");
			cout << "0. Nazad" << endl;
			cout << "1. Promeni sifru linije" << endl;
			cout << "2. Dodaj stajaliste za odredjenu liniju i njen smer" << endl;
			cout << "3. Izbrisi liniju iz mreze" << endl;
			

			cin >> opcija;

			if (opcija == 1)
			{
				string staraSifra;
				cout << "Unesite sifru linije koju zelite da promenite: ";
				cin >> staraSifra;

				string novaSifra;
				cout << "Unesite novu sifru linije koju zelite da promenite: ";
				cin >> novaSifra;

				mreza.getLinije()[staraSifra].setSifra(novaSifra);
			}

			
		}
		if (opcija == 4)
		{
			system("cls");
			cout << "0. Nazad" << endl;
			cout << "1. Filtriraj po zoni 1" << endl;
			cout << "2. Filtriraj po zoni 1,2" << endl;
			cout << "3. Filtriraj po zoni 1, 2, 3" << endl;
			cout << "4. Filtriraj po oznakama manjim od zadatih" << endl;
			cout << "5. Filtriraj po oznakama vecih od zadatih" << endl;
			cout << "6. Filtriraj po oznakama izmedju zadatih" << endl;
			cout << "7. Filtriraj po broju stajalista manjim od zadatih" << endl;
			cout << "8. Filtriraj po broju stajalista vecim od zadatih" << endl;
			cin >> opcija;
			set<int> zone;
			if (opcija == 1)
			{
				zone.insert(1);
				for (auto linija : mreza.getLinijeZaZonu(zone))
				{
					mreza.ispisiRawLiniju(linija.getSifra());
				}
				system("PAUSE");
			}
			if (opcija == 2)
			{
				zone.insert(1);
				zone.insert(2);
				for (auto linija : mreza.getLinijeZaZonu(zone))
				{
					mreza.ispisiRawLiniju(linija.getSifra());
				}
				system("PAUSE");
				continue;
			}
			if (opcija == 3)
			{
				zone.insert(1);
				zone.insert(2);
				zone.insert(3);
				for (auto linija : mreza.getLinijeZaZonu(zone))
				{
					mreza.ispisiRawLiniju(linija.getSifra());
				}
				system("PAUSE");
				continue;
			}
			if (opcija == 4)
			{
				string sifraLinija;
				cout << "Oznaka? ";
				cin >> sifraLinija;

				auto linije = mreza.getLinijeZaOznaku(sifraLinija, true);
				for (auto linija : linije)
				{
					mreza.ispisiRawLiniju(linija.getSifra());
				}

				system("PAUSE");
				continue;
			}
			if (opcija == 5)
			{
				string sifraLinija;
				cout << "Oznaka? ";
				cin >> sifraLinija;

				auto linije = mreza.getLinijeZaOznaku(sifraLinija, false);
				for (auto linija : linije)
				{
					mreza.ispisiRawLiniju(linija.getSifra());
				}

				system("PAUSE");
				continue;
			}
			if (opcija == 6)
			{
				string sifraLinija1;
				string sifraLinija2;
				cout << "Oznaka1? ";
				cin >> sifraLinija1;

				cout << "Oznaka2? ";
				cin >> sifraLinija2;

				auto linije = mreza.getLinijeUOpsegu(sifraLinija1, sifraLinija2);
				for (auto linija : linije)
				{
					mreza.ispisiRawLiniju(linija.getSifra());
				}

				system("PAUSE");
				continue;
			}
			if (opcija == 7)
			{
				int brojStajalista;
				cout << "Broj stajalista? ";
				cin >> brojStajalista;

				auto linije = mreza.getLinijeZaBrojStajalista(brojStajalista, true);
				for (auto linija : linije)
				{
					mreza.ispisiRawLiniju(linija.getSifra());
				}

				system("PAUSE");
				continue;
			}
			if (opcija == 8)
			{
				int brojStajalista;
				cout << "Broj stajalista? ";
				cin >> brojStajalista;

				auto linije = mreza.getLinijeZaBrojStajalista(brojStajalista, false);
				for (auto linija : linije)
				{
					mreza.ispisiRawLiniju(linija.getSifra());
				}

				system("PAUSE");
				continue;
			}
			else
			{
				continue;
			}
		}
		if (opcija == 5) 
		{
			system("cls");
			cout << "0. Nazad" << endl;
			cout << "1. Skup linija sa kojima data linija ima zajednicka stajalista" << endl;
			cout << "2. Linija prolazi kroz dva data stajalista?" << endl;
			cout << "3. Data linija najvise zajadnickih stajalista? " << endl;
			cout << "4. Odredjivanje najblizeg stajalista u odnosu na datu lokaciju" << endl;
			cout << "5. Odredjivanje najblizeg stajalista(date linije) u odnosu na datu lokaciju " << endl;
			cout << "6. Odredjivanje parova linija i broja zajednickih stajalista" << endl;
			cout << "7. Odredjivanje linija koje prolaze kroz dato stajaliste" << endl;
			cout << "8. Odredjivanje svih mogucih stajalista do kojih je moguce stici uz voznju maks. jednu stanicu  " << endl;
			cout << "9. Odredjivanje najmanjeg broja presedanja " << endl;

			cin >> opcija;

			if (opcija == 1)
			{
				string linijaSifra;
				cout << "Linija? ";
				cin >> linijaSifra;
				
				Linija linija = mreza.getLinija(linijaSifra);
				
				for (auto tekuci : mreza.skupLinijaZajednickihStajalista(linija))
				{
					cout << tekuci << " " ;
				}

				cout << endl;
				system("PAUSE");

			}
			if (opcija == 2)
			{
				int sifraStajalista1;
				int sifraStajalista2;
				string sifraLinija;


				cout << "Sifra linije i stajalista? ";
				cin >> sifraLinija;
				cin >> sifraStajalista1 >> sifraStajalista2;

				Linija linija = mreza.getLinija(sifraLinija);
				cout << mreza.linijaProlaziKrozStajalista(linija, sifraStajalista1, sifraStajalista2);

				cout << endl;
				system("PAUSE");
			}

			if (opcija == 3)
			{
		
				string sifraLinija;

				cout << "Sifra linije? ";
				cin >> sifraLinija;

				cout << mreza.najviseZajednickihStajalista(sifraLinija);
				cout << endl;
				system("PAUSE");
			}

			if (opcija == 4)
			{
				double x;
				double y;

				cout << "Lokacija? ";
				cin >> x >> y;

				Lokacija lokacija(x, y);

				mreza.ispisiStajalisteBezLinija(mreza.najblizeStajaliste(lokacija).getSifra());
				cout << endl;
				system("PAUSE");
			}

			if (opcija == 5)
			{
				double x;
				double y;
				string sifraLinija;

				cout << "Lokacija? ";
				cin >> x >> y;

				cout << "Linija? ";
				cin >> sifraLinija;

				Lokacija lokacija(x, y);

				mreza.ispisiStajalisteBezLinija(mreza.najblizeStajalisteLinije(lokacija, sifraLinija).getSifra());
				cout << endl;
				system("PAUSE");
			}
			if (opcija == 6)
			{
				map<pair<string, string>, int> skup = mreza.brojZajednickihStajalista();
				for (auto parLinija : skup)
				{
					cout << "Par linija " << parLinija.first.first << " " << parLinija.first.second;
					cout << " ima " << parLinija.second << " zajednickih stajalista" << endl;
				}
				cout << endl;
				system("PAUSE");
			}
			if (opcija == 7)
			{
				//TODO: dodaj metode
			}

			if (opcija == 8)
			{
				//TODO: dodaj metode
			}

			if (opcija == 9)
			{
				int sifraStajalista1;
				cout << "Unesite sifru stajalista: ";
				cin >> sifraStajalista1;

				int sifraStajalista2;
				cout << "Unesite sifru stajalista: ";
				cin >> sifraStajalista2;

				int najmanjePreseda = mreza.najmanjePresedanja(sifraStajalista1, sifraStajalista2);
				cout << najmanjePreseda;
				system("PAUSE");

			}

		}
		if (opcija == 6) 
		{
			exit(1);
		}
	}
	cout << "";
	system("PAUSE");
}