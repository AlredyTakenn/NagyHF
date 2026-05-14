#include "Hotel.h"
#include "StandardRoom.h"
#include "FamilyRoom.h"
#include "LuxuryRoom.h"
#include <stdexcept>
#include <fstream>
void Hotel::LoadRooms(std::istream& is)
{
	std::string type;
	is >> type;
	Room* temp = nullptr;
	if (type == "Standard")
	{
		temp = new StandardRoom();

	}
	else if (type == "Family")
	{
		temp = new FamilyRoom();
	}
	else if (type == "Luxury")
	{
		temp = new LuxuryRoom();
	}
	if (temp != nullptr)
	{
		temp->deserialize(is);
		roomList.add(temp);
	}
	else
	{
		throw std::invalid_argument("Hiba: Nincs ilyen szobatípus: " + type);
	}
}

void Hotel::LoadGuests(std::istream& is)
{
	Guest* temp = new Guest();
	temp->deserialize(is);
	guestList.add(*temp);
}

void Hotel::LoadReservations(std::istream& is)
{
	Reservation* temp = new Reservation();
	temp->deserialize(is);
	reservationList.add(*temp);
}

void Hotel::AddRoom(Room* proom)
{
	roomList.add(proom);
}

void Hotel::RegisterGuest(std::string pname, std::string pId)
{
	Guest newGuest(pname, pId);
	guestList.add(newGuest);
}

void Hotel::BookReservation(std::chrono::year_month_day pfrom, std::chrono::year_month_day pto, Guest* pguests, unsigned pguestcount, std::string* pextraservices, unsigned pextraservicescount, unsigned requestedRoomNumber)
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
	for (unsigned i = 0; i < reservationList.getElementCount(); i++)
	{
		if (reservationList[i].GetReservedRoom()->GetRoomNumber() == requestedRoomNumber)
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

void Hotel::CheckIn(std::string searchGuestId)
{
	bool found = false;
	for (unsigned i = 0; i < reservationList.getElementCount(); i++)
	{
		const Guest* currentGuests = reservationList[i].GetGuests();
		const unsigned currentGuestCount = reservationList[i].GetGuestCount();

		for (unsigned j = 0; j < currentGuestCount; j++)
		{
			if (currentGuests[j].GetId() == searchGuestId && reservationList[i].GetHere() == false)
			{
				reservationList[i].CheckIn();
				std::cout << "Sikeres bejelentkezes!" << std::endl;
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
		throw std::invalid_argument("Hiba: Nincs foglalas a megadott igazolvanyszammal!");
	}
}

void Hotel::CheckOut(std::string searchGuestId)
{
	bool found = false;
	for (unsigned i = 0; i < reservationList.getElementCount(); i++)
	{
		const Guest* currentGuests = reservationList[i].GetGuests();
		const unsigned currentGuestCount = reservationList[i].GetGuestCount();
		for (unsigned j = 0; j < currentGuestCount; j++)
		{
			if (currentGuests[j].GetId() == searchGuestId && reservationList[i].GetHere() == true)
			{
				reservationList[i].CheckOut();
				std::cout << "Sikeres kijelentkezés!" << std::endl;
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
		throw std::invalid_argument("Hiba: Nincs foglalas a megadott igazolvanyszammal!");
	}
}

void Hotel::GenerateInvoice(std::string searchGuestId)
{
	bool found = false;
	for (unsigned i = 0; i < reservationList.getElementCount(); i++)
	{
		Reservation& currentRes = reservationList[i];

		const Guest* currentGuests = currentRes.GetGuests();
		const unsigned currentGuestCount = currentRes.GetGuestCount();

		for (unsigned j = 0; j < currentGuestCount; j++)
		{
			
			if (currentGuests[j].GetId() == searchGuestId && currentRes.GetHere() == true)
			{
				std::cout << "A(z) " << searchGuestId << " igazolványszámú vendég végszámlája:" << std::endl;

				double napiAr = currentRes.GetReservedRoom()->CalculatePrice();
				std::cout << "A tartózkodási idõ: " << (currentRes.Invoice() / napiAr) << " éjszaka." << std::endl;
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

void Hotel::SaveToFile(const std::string fileName) const
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

void Hotel::LoadFromFile(const std::string fileName)
{
	std::ifstream is(fileName);
	std::string tag;
	unsigned count;
	if (!is.is_open())
	{
		throw std::runtime_error("Hiba: A fájl megnyitása nem sikerült!");
	}
	while (!is.eof())
	{
		is >> tag >> count;
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
