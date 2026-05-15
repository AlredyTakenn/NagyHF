#include "Hotel.h"
#include "StandardRoom.h"
#include "FamilyRoom.h"
#include "LuxuryRoom.h"
#include <stdexcept>
#include <fstream>

//szobabetöltõ segédfüggvény
void Hotel::LoadRooms(std::istream& is)
{
	std::string type;			//szoba típusra változó
	is >> type;
	Room* temp = nullptr;		//álltalános szobára muatató
	if (type == "Standard")		//Ha standard szoba akkor a temp egy új standard szobára mutat
	{
		temp = new StandardRoom();

	}
	else if (type == "Family")	//Ha családi szoba akkor a temp egy új családi szobára mutat
	{
		temp = new FamilyRoom();
	}
	else if (type == "Luxury")	//Ha luxus szoba akkor a temp egy luxus szobára mutat
	{
		temp = new LuxuryRoom();
	}
	if (temp != nullptr)		//ha sikerült beolvasni egy létezõ szobatípust akkor beolvass a maradék adatot és hozzáadja a listához
	{
		temp->deserialize(is);
		roomList.add(temp);
	}
	else
	{
		throw std::invalid_argument("Hiba: Nincs ilyen szobatípus: " + type);
	}
}

//vendégbetöltõ segédfüggvény
void Hotel::LoadGuests(std::istream& is)
{
	Guest temp;
	temp.deserialize(is);
	guestList.add(temp);
}

//foglalás betöltõ segédfüggvény
void Hotel::LoadReservations(std::istream& is)
{
	Reservation temp;
	temp.deserialize(is);										//beolvasásnál csak a szoba számát tudjuk ezért kell lekérdezni a szoba listából a szám alapján
	unsigned targetRoomNum = temp.GetLastReadRoomNumber();
	Room* linkedRoom = nullptr;
	for (unsigned i = 0; i < roomList.getElementCount(); i++) 
	{
		if (roomList[i]->GetRoomNumber() == targetRoomNum) 
		{
			linkedRoom = roomList[i];
			break;
		}
	}
	if (linkedRoom != nullptr) 
	{
		temp.SetReservedRoom(linkedRoom);
		reservationList.add(temp);
	}
}

//új szoba hozzáadása a dinamikus tömbbe
void Hotel::AddRoom(Room* proom)
{
	roomList.add(proom);
}

//új vendég hozzáadása a dinamikus tömbbe
void Hotel::RegisterGuest(const std::string& pname, const std::string& pId)
{
	Guest newGuest(pname, pId);
	guestList.add(newGuest);
}

//új foglalás hozzáadása a dinamikus tömbbe
void Hotel::BookReservation(const std::chrono::year_month_day& pfrom,const std::chrono::year_month_day& pto, Guest* pguests, unsigned pguestcount, std::string* pextraservices, unsigned pextraservicescount, unsigned requestedRoomNumber)
{
	if (pfrom > pto)
	{
		throw std::invalid_argument("Hiba: A távozás idõpontja nem lehet korábban mint az érkezésé!");
	}
	Room* foundRoom = nullptr;
	for (unsigned i = 0; i < roomList.getElementCount(); i++)
	{
		if (roomList[i]->GetRoomNumber() == requestedRoomNumber)
		{
			foundRoom = roomList[i];
			break;
		}
	}
	if (foundRoom == nullptr)
	{
		throw std::invalid_argument("Hiba: Nem létezik ilyen szobaszám a szállodában!");
	}
	for (unsigned i = 0; i < reservationList.getElementCount(); i++)			//végig megy a foglalásokon
	{
		if (reservationList[i].GetReservedRoom()->GetRoomNumber() == requestedRoomNumber)		//ha valaminek egyezik a szobaszáma a foglalandó szobával akkor megnézi hogy van-e átfedés a két foglalás idõpontja között
		{
			if (pfrom < reservationList[i].GetTimeTo() && pto > reservationList[i].GetTimeFrom())
			{
				throw std::logic_error("Hiba: Erre az idõszakra foglalt a szoba!");
			}
		}
	}
	Reservation newRes(pfrom, pto, pguests, pguestcount, pextraservices, pextraservicescount, foundRoom);
	reservationList.add(newRes);
	std::cout << "Sikeres foglalás a(z)" << requestedRoomNumber << ". szobára!" << std::endl;
}

//bejelentkezés
void Hotel::CheckIn(const std::string& searchGuestId)
{
	bool foundReservation = false;
	for (unsigned i = 0; i < reservationList.getElementCount(); i++)		//minden foglalásnak végig nézi a vendég listáját hogy egyezik-e az igazolványszám
	{
		const Guest* currentGuests = reservationList[i].GetGuests();
		for (unsigned j = 0; j < reservationList[i].GetGuestCount(); j++) 
		{
			if (currentGuests[j].GetId() == searchGuestId)					//ha megvan a vendég megnézi hogy bejelentkezett-e már
			{
				foundReservation = true; 
				if (reservationList[i].GetHere() == true) 
				{
					throw std::logic_error("Hiba: A vendég már bejelentkezett!");
				}
				else 
				{
					reservationList[i].CheckIn();
					std::cout << "Sikeres bejelentkezes!" << std::endl;
					return;
				}
			}
		}
	}
	if (!foundReservation) {
		throw std::invalid_argument("Hiba: Nincs foglalas a megadott igazolvanyszammal!");
	}
}

//kijelentkezés
void Hotel::CheckOut(const std::string& searchGuestId)
{
	bool foundReservation = false;
	for (unsigned i = 0; i < reservationList.getElementCount(); i++)		//minden foglalásnak végig nézi a vendég listáját hogy egyezik-e az igazolványszám
	{
		const Guest* currentGuests = reservationList[i].GetGuests();
		for (unsigned j = 0; j < reservationList[i].GetGuestCount(); j++)
		{
			if (currentGuests[j].GetId() == searchGuestId)					//ha megvan a vendég megnézi hogy kijelentkezett-e már
			{
				foundReservation = true;
				if (reservationList[i].GetHere() == false)
				{
					throw std::logic_error("Hiba: A vendég már kijelentkezett!");
				}
				else
				{
					reservationList[i].CheckOut();
					std::cout << "Sikeres kijelentkezés!" << std::endl;
					return;
				}
			}
		}
	}
	if (!foundReservation) {
		throw std::invalid_argument("Hiba: Nincs foglalas a megadott igazolvanyszammal!");
	}
}

//végszámla kiállítás az egész foglalásra
void Hotel::GenerateInvoice(const std::string& searchGuestId)
{
	bool found = false;
	for (unsigned i = 0; i < reservationList.getElementCount(); i++)	//megkeresi a foglalást az igazolványszám alapján
	{
		Reservation& currentRes = reservationList[i];

		const Guest* currentGuests = currentRes.GetGuests();
		const unsigned currentGuestCount = currentRes.GetGuestCount();

		for (unsigned j = 0; j < currentGuestCount; j++)
		{
			
			if (currentGuests[j].GetId() == searchGuestId && currentRes.GetHere() == true)		//csak akkor lehet számlát kiállítani ha a vendég még nem jelentkezett ki
			{
				std::cout << "A(z) " << searchGuestId << " igazolványszámú vendég végszámlája:" << std::endl;

				double napiAr = currentRes.GetReservedRoom()->CalculatePrice();
				std::cout << "A tartózkodási idõ: " << currentRes.GetDuration() << " éjszaka." << std::endl;
				std::cout << "A szoba ára/nap: " << napiAr << std::endl;

				std::cout << "Igénybevett szolgáltatások:" << std::endl;

				std::cout << "  (Szoba extrák):" << std::endl;
				const unsigned extrasCount = currentRes.GetReservedRoom()->GetExtrasCount();
				const std::string* roomExtras = currentRes.GetReservedRoom()->GetExtras();
				for (unsigned k = 0; k < extrasCount; k++) 
				{
					std::cout << "    - " << roomExtras[k] << std::endl;
				}

				std::cout << "  (Foglalás extrák):" << std::endl;
				const unsigned resExtrasCount = currentRes.GetExtraServicesCount();
				const std::string* resExtras = currentRes.GetExtraServices();
				for (unsigned k = 0; k < resExtrasCount; k++)
				{
					std::cout << "    - " << resExtras[k] << std::endl;
				}

				std::cout << "-----------------------------------" << std::endl;
				std::cout << "ÖSSZESEN FIZETENDÕ: " << currentRes.Invoice() << " HUF" << std::endl;

				found = true;
				break;
			}
		}
		if (found)
		{
			break;
		}
	}

	if (!found)
	{
		throw std::invalid_argument("Hiba: Nincs aktiv foglalas a megadott igazolvanyszammal!");
	}
}

//fájlba kiírás
void Hotel::SaveToFile(const std::string& fileName) const
{
	std::ofstream os(fileName);
	if (!os.is_open())
	{
		throw std::runtime_error("Hiba: A fájl megnyitása nem sikerült!");
	}
	os << "[ROOMS] " << roomList.getElementCount() << std::endl;
	for (unsigned i = 0; i < roomList.getElementCount(); i++)
	{
		roomList[i]->serialize(os);
	}
	os << "[GUESTS] " << guestList.getElementCount() << std::endl;
	for (unsigned i = 0; i < guestList.getElementCount(); i++)
	{
		guestList[i].serialize(os);
	}
	os << "[RESERVATIONS] " << reservationList.getElementCount() << std::endl;
	for (unsigned i = 0; i < reservationList.getElementCount(); i++)
	{
		reservationList[i].serialize(os);
	}
}

//fájlból beolvasás
void Hotel::LoadFromFile(const std::string& fileName)
{
	std::ifstream is(fileName);
	std::string tag;
	unsigned count;
	if (!is.is_open())
	{
		throw std::runtime_error("Hiba: A fájl megnyitása nem sikerült!");
	}
	while (is >> tag >> count)
	{
		
		if (tag == "[ROOMS]")
		{
			for (unsigned i = 0; i < count; i++)
			{
				LoadRooms(is);
			}
		}
		else if(tag == "[GUESTS]")
		{
			for (unsigned i = 0; i < count; i++)
			{
				LoadGuests(is);
			}
		}
		else if (tag == "[RESERVATIONS]")
		{
			for (unsigned i = 0; i < count; i++)
			{
				LoadReservations(is);
			}
		}
	}
}

Hotel::~Hotel()
{
	for (unsigned i = 0; i < roomList.getElementCount(); i++)
	{
		delete roomList[i];
	}
}
