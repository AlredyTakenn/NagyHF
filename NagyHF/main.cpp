#include <iostream>
#include <chrono>
#include <exception>
#include <string>

#include "Hotel.h"
#include "StandardRoom.h"
#include "FamilyRoom.h"
#include "LuxuryRoom.h"
#include "Reservation.h"
#include "Guest.h"
#include "AutomatedTest.h"

using namespace std;
using namespace std::chrono;

int main() {
	Hotel hotel;
	int user = 0;
	cout << "SZALLODAI SZOBAFOGLALO" << endl << endl;
	cout <<"1 - Uj vendeg regisztralasa" << endl
		<< "2 - Uj foglalas felvetele" << endl
		<< "3 - Bejelentkezes" << endl
		<< "4 - Kijelentkezes" << endl
		<< "5 - Szabad szoba keresese" << endl
		<< "6 - Fajlbol betoltes" << endl
		<< "7 - Fajlba mentes" << endl
		<< "-1 - Kilepes a programbol" << endl
		<< "-2 - Automatikus teszt" << endl;
	while (user != -1)
	{
		cout << "Kerlek add meg a menupont sorszamat: ";
		cin >> user;
		string nev, id, filename;
		int y1, m1, d1, y2, m2, d2, roomNum;
		switch (user)
		{
		default:
			cout << "Nem letezo menupont!" << endl << "Probald ujra!" << endl;
			break;
		case(1):
			cout << "Adja meg a vendeg nevet also vonallal elvalasztva(_): ";
			cin >> nev;
			cout << "Adja meg az igazolvanyszamat: ";
			cin >> id;
			try
			{
				hotel.RegisterGuest(nev, id);
				cout << "Vendeg sikeresen regisztralva!\n";
			}
			catch (const exception& e) {
				cerr << "Hiba: " << e.what() << endl;
			}
			break;
		case 2:
			cout << "Foglalas kezdete (ev honap nap, szokozzel elvalasztva, pl. 2025 05 10): ";
			cin >> y1 >> m1 >> d1;
			cout << "Foglalas vege (ev honap nap, szokozzel elvalasztva, pl. 2025 05 15): ";
			cin >> y2 >> m2 >> d2;
			cout << "Lefoglalni kivant szobaszam: ";
			cin >> roomNum;
			cout << "Vendeg neve (also vonallal): ";
			cin >> nev;
			cout << "Vendeg igazolvanyszama: ";
			cin >> id;
			try
			{
				// A menüből való egyszerűség kedvéért 1 vendéggel és extra szolgáltatások nélkül
				Guest vendeg(nev, id);
				hotel.BookReservation(year(y1) / m1 / d1, year(y2) / m2 / d2, &vendeg, 1, nullptr, 0, roomNum);
			}
			catch (const exception& e)
			{
				cerr << "Hiba a foglalasnal: " << e.what() << endl;
			}
			break;
		case 3:
			cout << "Adja meg az igazolvanyszamot a bejelentkezeshez: ";
			cin >> id;
			try {
				hotel.CheckIn(id);
			}
			catch (const exception& e) {
				cerr << "Hiba: " << e.what() << endl;
			}
			break;
		case 4:
			cout << "Adja meg az igazolvanyszamot a kijelentkezeshez: ";
			cin >> id;
			try {
				hotel.GenerateInvoice(id);
				hotel.CheckOut(id);
			}
			catch (const exception& e) {
				cerr << "Hiba: " << e.what() << endl;
			}
			break;
		case 5:
			cout << "Kereses kezdete (ev honap nap, szokozzel): ";
			cin >> y1 >> m1 >> d1;
			cout << "Kereses vege (ev honap nap, szokozzel): ";
			cin >> y2 >> m2 >> d2;
			try {
				hotel.SearchFreeRoom(year(y1) / m1 / d1, year(y2) / m2 / d2);
			}
			catch (const exception& e) {
				cerr << "Hiba: " << e.what() << endl;
			}
			break;
		case 6:
			cout << "Adja meg a betoltendo fajl nevet (pl. mentes.txt): ";
			cin >> filename;
			try {
				hotel.LoadFromFile(filename);
				cout << "Fajl sikeresen betoltve!\n";
			}
			catch (const exception& e) {
				cerr << "Hiba: " << e.what() << endl;
			}
			break;
		case 7:
			cout << "Adja meg a mentesi fajl nevet (pl. mentes.txt): ";
			cin >> filename;
			try {
				hotel.SaveToFile(filename);
				cout << "Fajl sikeresen kimentve!\n";
			}
			catch (const exception& e) {
				cerr << "Hiba: " << e.what() << endl;
			}
			break;

		case -1:
			cout << "Kilepes a programbol." << endl;
			break;

		case -2:
			cout << "\n>>> AUTOMATIKUS TESZT INDITASA <<<\n";
			AutomatedTest(hotel);
			break;
		};
	}
	return 0;
}