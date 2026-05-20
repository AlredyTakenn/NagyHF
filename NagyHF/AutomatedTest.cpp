#include "AutomatedTest.h"
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

using namespace std;
using namespace std::chrono;

void AutomatedTest(Hotel& hotel)
{
    cout << endl;
    cout << "SZALLODAI SZOBAFOGLALO AUTOMATIKUS TESZTJE" << endl;
    cout << endl << endl;

    // 1. TESZT: SZOBÁK ÉS VENDÉGEK REGISZTRÁCIÓJA
    cout << "[1. TESZT] Szobak es vendegek felvetele..." << endl;
    try {
        string stdExtras[] = { "Wifi", "Klima" };
        string famExtras[] = { "Wifi", "Klima", "Gyerekjatek" };
        string luxExtras[] = { "Wifi", "Klima", "Minibar", "Jakuzzi", "Masszazsagy" };

        // Szobák hozzáadása dinamikus memóriafoglalással
        hotel.AddRoom(new StandardRoom(101, 2, 20000.0, stdExtras, 2));
        hotel.AddRoom(new FamilyRoom(201, 4, 35000.0, famExtras, 3, 2));
        hotel.AddRoom(new LuxuryRoom(301, 2, 60000.0, luxExtras, 5, true, true));

        // Vendégek regisztrálása a rendszerbe
        hotel.RegisterGuest("Kovacs Aladar", "111111AA");
        hotel.RegisterGuest("Nagy Eszter", "222222BB");

        cout << " -> Szobak es vendegek sikeresen inicializalva." << endl;
    }
    catch (const exception& e) {
        cerr << " -> VARTATLAN HIBA: " << e.what() << endl;
    }
    cout << endl << "--------------------------------------------------" << endl << endl;


    // 2. TESZT: SZABAD SZOBA KERESÉSE KEZDETI ÁLLAPOTBAN

    cout << "[2. TESZT] Szabad szobak keresese kezdeti allapotban..." << endl;
    try {
        year_month_day tol = year(2026) / June / 10;
        year_month_day ig = year(2026) / June / 15;
        hotel.SearchFreeRoom(tol, ig);
    }
    catch (const exception& e) {
        cerr << " -> HIBA: " << e.what() << endl;
    }
    cout << endl << "--------------------------------------------------" << endl << endl;


    // 3. TESZT: SIKERES FOGLALÁS LÉTREHOZÁSA

    cout << "[3. TESZT] Foglalas letrehozasa..." << endl;
    try {
        year_month_day tol = year(2026) / June / 10;
        year_month_day ig = year(2026) / June / 15;

        Guest vendeg("Kovacs Aladar", "111111AA");
        string szolgaltatasok[] = { "Reggeli", "Parkolas" };

        hotel.BookReservation(tol, ig, &vendeg, 1, szolgaltatasok, 2, 101);
    }
    catch (const exception& e) {
        cerr << " -> HIBA: " << e.what() << endl;
    }
    cout << endl << "--------------------------------------------------" << endl << endl;


    // 4. TESZT: SZABAD SZOBA KERESÉSE FOGLALÁS UTÁN (A 101-es már nem szabad)

    cout << "[4. TESZT] Szabad szobak ellenorzese a foglalas utan..." << endl;
    try {
        year_month_day tol = year(2026) / June / 12;
        year_month_day ig = year(2026) / June / 14;
        hotel.SearchFreeRoom(tol, ig);
    }
    catch (const exception& e) {
        cerr << " -> HIBA: " << e.what() << endl;
    }
    cout << endl << "--------------------------------------------------" << endl << endl;


    // 5. TESZT: KIVÉTELKEZELÉS DEMONSTRÁLÁSA (Átfedő foglalás kísérlete)

    cout << "[5. TESZT] Hibakezeles: Rafoglalas tesztelese ugyanarra a szobara..." << endl;
    try {
        year_month_day tolAtfed = year(2026) / June / 12;
        year_month_day igAtfed = year(2026) / June / 17;

        Guest masikVendeg("Nagy Eszter", "222222BB");
        string szolgaltatasok[] = { "Vacsora" };

        cout << " -> Kiserlet egy mar foglalt szoba (101) lefoglalasara..." << endl;
        hotel.BookReservation(tolAtfed, igAtfed, &masikVendeg, 1, szolgaltatasok, 1, 101);
    }
    catch (const exception& e) {
        cerr << " -> ELKAPOTT VART LOGIKAI HIBA: " << e.what() << endl;
    }
    cout << endl << "--------------------------------------------------" << endl << endl;


    // 6. TESZT: BEJELENTKEZÉS, SZÁMLÁZÁS ÉS KIJELENTKEZÉS

    cout << "[6. TESZT] Bejelentkezes, szamlazas es kijelentkezes..." << endl;
    try {
        cout << " -> Bejelentkezes..." << endl;
        hotel.CheckIn("111111AA");

        try {
            cout << " -> Kiserlet ismetelt bejelentkezesre..." << endl;
            hotel.CheckIn("111111AA");
        }
        catch (const exception& e) {
            cerr << " -> ELKAPOTT VART HIBA (Dupla CheckIn): " << e.what() << endl;
        }

        cout << endl << " -> Vegszamla kiallitasa:" << endl;
        hotel.GenerateInvoice("111111AA");

        cout << endl << " -> Kijelentkezes..." << endl;
        hotel.CheckOut("111111AA");
    }
    catch (const exception& e) {
        cerr << " -> HIBA: " << e.what() << endl;
    }
    cout << endl << "--------------------------------------------------" << endl << endl;

    // 7. TESZT: OPERÁTOR TÚLTERHELÉS (Árösszehasonlítás)

    cout << "[7. TESZT] Foglalasok osszehasonlitasa operatorokkal..." << endl;
    try {
        StandardRoom olcsoSzoba(901, 2, 10000.0, nullptr, 0);
        LuxuryRoom dragaSzoba(902, 2, 80000.0, nullptr, 0, true, true);
        Guest tesztVendeg("Teszt Elek", "999999XX");

        year_month_day tol = year(2026) / July / 1;
        year_month_day ig = year(2026) / July / 5;

        Reservation f1(tol, ig, &tesztVendeg, 1, nullptr, 0, &olcsoSzoba);
        Reservation f2(tol, ig, &tesztVendeg, 1, nullptr, 0, &dragaSzoba);

        cout << " -> Alap foglalas ara: " << f1.Invoice() << " HUF" << endl;
        cout << " -> Luxus foglalas ara: " << f2.Invoice() << " HUF" << endl;

        if (f1 < f2) {
            cout << " -> SIKER: A kisebb mint (<) operator helyesen jelzett." << endl;
        }
        if (f2 > f1) {
            cout << " -> SIKER: A nagyobb mint (>) operator helyesen jelzett." << endl;
        }
    }
    catch (const exception& e) {
        cerr << " -> HIBA: " << e.what() << endl;
    }
    cout << endl << "--------------------------------------------------" << endl << endl;


    // 8. TESZT: ADATOK MENTÉSE ÉS BETÖLTÉSE FÁJLBÓL

    cout << "[8. TESZT] Fajlkezeles ellenorzese..." << endl;
    try {
        string fajlNev = "szalloda_mentes.txt";
        hotel.SaveToFile(fajlNev);
        cout << " -> Adatok sikeresen elmentve a '" << fajlNev << "' fajlba." << endl;

        Hotel ujHotel;
        ujHotel.LoadFromFile(fajlNev);
        cout << " -> Adatok sikeresen visszatoltve egy teljesen uj hotel objektumba." << endl;
    }
    catch (const exception& e) {
        cerr << " -> HIBA: " << e.what() << endl;
    }
    cout << endl;
    cout << "TESZTELES VEGE" << endl;
    cout << endl;
}
