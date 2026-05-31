#include "ConsoleUI.h"
#include "AutomatedTest.h"

#include <iostream>
#include <chrono>
#include <limits>

using namespace std;

bool ConsoleUI::askRetry()
{
	char answer;
	cout << "Szeretne ujraprobalkozni? (i/n): ";
	cin >> answer;
	return (answer == 'i' || answer == 'I');
}

void ConsoleUI::handleNewGuest(Hotel& hotel)
{
	while (true)
	{
		string guestName, guestId;
		try
		{
			cout << "Adja meg a vendeg nevet also vonallal elvalasztva(_): ";
			cin >> guestName;
			cout << "Adja meg az igazolvanyszamat: ";
			cin >> guestId;
			hotel.RegisterGuest(guestName, guestId);
			cout << "Vendeg sikeresen regisztralva!\n";
			break;
		}
		catch (const std::invalid_argument& e) {
			cerr << "Ervenytelen parameter: " << e.what() << endl;
			if (!askRetry()) break;
		}
		catch (const std::logic_error& e) {
			cerr << "Hiba a muvelet soran: " << e.what() << endl;
			if (!askRetry()) break;
		}
	}
}

void ConsoleUI::handleNewReservation(Hotel& hotel)
{
	while (true)
	{
		string guestName, guestId;
		int startYear, startMonth, startDay, endYear, endMonth, endDay, roomNumber;
		try
		{
			cout << "Foglalas kezdete (ev honap nap, szokozzel elvalasztva, pl. 2025 05 10): ";
			if (!(cin >> startYear >> startMonth >> startDay)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				throw invalid_argument("Ervenytelen formatum a kezdo datumnal! Szamokat adj meg.");
			}
			chrono::year_month_day startDate = chrono::year(startYear) / startMonth / startDay;
			if (!startDate.ok()) {
				throw invalid_argument("Nem letezo naptari napot adtal meg kezdodatumkent!");
			}

			cout << "Foglalas vege (ev honap nap, szokozzel elvalasztva, pl. 2025 05 15): ";
			if (!(cin >> endYear >> endMonth >> endDay)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				throw invalid_argument("Ervenytelen formatum a vegdatumnal! Szamokat adj meg.");
			}
			chrono::year_month_day endDate = chrono::year(endYear) / endMonth / endDay;
			if (!endDate.ok()) {
				throw invalid_argument("Nem letezo naptari napot adtal meg vegdatumkent!");
			}

			cout << "Lefoglalni kivant szobaszam: ";
			if (!(cin >> roomNumber)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				throw invalid_argument("A szobaszam csak szam lehet!");
			}

			cout << "Vendeg neve (also vonallal): ";
			cin >> guestName;
			cout << "Vendeg igazolvanyszama: ";
			cin >> guestId;
			Guest newGuest(guestName, guestId);
			hotel.BookReservation(startDate, endDate, &newGuest, 1, nullptr, 0, roomNumber);
			break;
		}
		catch (const std::invalid_argument& e) {
			cerr << "Beviteli hiba: " << e.what() << endl;
			if (!askRetry()) break;
		}
		catch (const std::logic_error& e) {
			cerr << "Foglalas hiba: " << e.what() << endl;
			if (!askRetry()) break;
		}
	}
}

void ConsoleUI::handleCheckIn(Hotel& hotel)
{
	while (true)
	{
		string guestId;
		try {
			cout << "Adja meg az igazolvanyszamot a bejelentkezeshez: ";
			cin >> guestId;
			hotel.CheckIn(guestId);
			break;
		}
		catch (const std::invalid_argument& e) {
			cerr << "Keresesi hiba: " << e.what() << endl;
			if (!askRetry()) break;
		}
		catch (const std::logic_error& e) {
			cerr << "Bejelentkezesi hiba: " << e.what() << endl;
			if (!askRetry()) break;
		}
	}
}

void ConsoleUI::handleCheckOut(Hotel& hotel)
{
	while (true)
	{
		string guestId;
		try {
			cout << "Adja meg az igazolvanyszamot a kijelentkezeshez: ";
			cin >> guestId;
			hotel.GenerateInvoice(guestId);
			hotel.CheckOut(guestId);
			break;
		}
		catch (const std::invalid_argument& e) {
			cerr << "Keresesi hiba: " << e.what() << endl;
			if (!askRetry()) break;
		}
		catch (const std::logic_error& e) {
			cerr << "Kijelentkezesi hiba: " << e.what() << endl;
			if (!askRetry()) break;
		}
	}
}

void ConsoleUI::handleSearch(Hotel& hotel)
{
	while (true)
	{
		int startYear, startMonth, startDay, endYear, endMonth, endDay;
		try
		{
			cout << "Kereses kezdete (ev honap nap, szokozzel): ";
			if (!(cin >> startYear >> startMonth >> startDay)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				throw invalid_argument("Ervenytelen formatum a kezdo datumnal! Szamokat adj meg.");
			}
			chrono::year_month_day startDate = chrono::year(startYear) / startMonth / startDay;
			if (!startDate.ok()) {
				throw invalid_argument("Nem letezo naptari napot adtal meg kezdodatumkent!");
			}

			cout << "Kereses vege (ev honap nap, szokozzel): ";
			if (!(cin >> endYear >> endMonth >> endDay)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				throw invalid_argument("Ervenytelen formatum a vegdatumnal! Szamokat adj meg.");
			}
			chrono::year_month_day endDate = chrono::year(endYear) / endMonth / endDay;
			if (!endDate.ok()) {
				throw invalid_argument("Nem letezo naptari napot adtal meg vegdatumkent!");
			}

			hotel.SearchFreeRoom(startDate, endDate);
			break;
		}
		catch (const std::invalid_argument& e) {
			cerr << "Beviteli hiba: " << e.what() << endl;
			if (!askRetry()) break;
		}
		catch (const std::logic_error& e) {
			cerr << "Keresesi hiba: " << e.what() << endl;
			if (!askRetry()) break;
		}
	}
}

void ConsoleUI::handleLoading(Hotel& hotel)
{
	while (true)
	{
		string fileName;
		try {
			cout << "Adja meg a betoltendo fajl nevet (pl. mentes.txt): ";
			cin >> fileName;
			hotel.LoadFromFile(fileName);
			cout << "Fajl sikeresen betoltve!\n";
			break;
		}
		catch (const std::invalid_argument& e) {
			cerr << "Hibas bemenet: " << e.what() << endl;
			if (!askRetry()) break;
		}
		catch (const std::runtime_error& e) {
			cerr << "Fajlkezelesi hiba: " << e.what() << endl;
			if (!askRetry()) break;
		}
	}
}

void ConsoleUI::handleSaving(Hotel& hotel)
{
	while (true)
	{
		string fileName;
		try {
			cout << "Adja meg a mentesi fajl nevet (pl. mentes.txt): ";
			cin >> fileName;
			hotel.SaveToFile(fileName);
			cout << "Fajl sikeresen kimentve!\n";
			break;
		}
		catch (const std::invalid_argument& e) {
			cerr << "Hibas bemenet: " << e.what() << endl;
			if (!askRetry()) break;
		}
		catch (const std::runtime_error& e) {
			cerr << "Fajlkezelesi hiba: " << e.what() << endl;
			if (!askRetry()) break;
		}
	}
}

void ConsoleUI::run(Hotel& hotel)
{
	int menuChoice = 0;
	cout << "SZALLODAI SZOBAFOGLALO" << endl << endl;
	cout << "1 - Uj vendeg regisztralasa" << endl
		<< "2 - Uj foglalas felvetele" << endl
		<< "3 - Bejelentkezes" << endl
		<< "4 - Kijelentkezes" << endl
		<< "5 - Szabad szoba keresese" << endl
		<< "6 - Fajlbol betoltes" << endl
		<< "7 - Fajlba mentes" << endl
		<< "-1 - Kilepes a programbol" << endl
		<< "-2 - Automatikus teszt" << endl;

	while (menuChoice != -1)
	{
		cout << "\nKerlek add meg a menupont sorszamat: ";

		try
		{
			if (!(cin >> menuChoice))
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				throw invalid_argument("Ervenytelen bemenet! Kerlek egy szamot adj meg.");
			}

			switch (menuChoice)
			{
			default:
				cout << "Nem letezo menupont! Probald ujra!" << endl;
				break;
			case 1:
				handleNewGuest(hotel);
				break;
			case 2:
				handleNewReservation(hotel);
				break;
			case 3:
				handleCheckIn(hotel);
				break;
			case 4:
				handleCheckOut(hotel);
				break;
			case 5:
				handleSearch(hotel);
				break;
			case 6:
				handleLoading(hotel);
				break;
			case 7:
				handleSaving(hotel);
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
		catch (const std::invalid_argument& e)
		{
			cerr << "Hiba: " << e.what() << endl;
		}
	}
}
