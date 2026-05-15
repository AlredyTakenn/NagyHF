#include "Reservation.h"
#include "Guest.h"
using namespace std;

//default konstruktor
Reservation::Reservation()
	:timeFrom(std::chrono::year(1970) / 1 / 1), timeTo(std::chrono::year(1970) / 1 / 1),guests(nullptr), guestCount(0),extraServices(nullptr), extraServicesCount(0), reservedRoom(nullptr), here(false), lastReadRoomNumber(0)
{

}

//paraméteres konstruktor
Reservation::Reservation(const std::chrono::year_month_day& pfrom, const std::chrono::year_month_day& pto, Guest* pguest, unsigned pguestcount, std::string* pextraservices, unsigned pextraservicescount, Room* proom)
	:timeFrom(pfrom), timeTo(pto), guestCount(pguestcount), extraServicesCount(pextraservicescount), reservedRoom(proom), here(false), lastReadRoomNumber(0)
{
	guests = new Guest[guestCount];					//dinamikus vendég és extra szolgáltatás tömb
	for (unsigned i = 0; i < guestCount; i++)
	{
		guests[i] = pguest[i];
	}
	extraServices = new std::string[extraServicesCount];
	for (unsigned i = 0; i < extraServicesCount; i++)
	{
		extraServices[i] = pextraservices[i];
	}
}

//másoló konstruktor
Reservation::Reservation(const Reservation& other):
	timeFrom(other.timeFrom), timeTo(other.timeTo), guestCount(other.guestCount), extraServicesCount(other.extraServicesCount), reservedRoom(other.reservedRoom), here(other.here), lastReadRoomNumber(other.lastReadRoomNumber)
{
	guests = new Guest[guestCount];
	for (unsigned i = 0; i < guestCount; i++)
	{
		guests[i] = other.guests[i];
	}
	extraServices = new std::string[extraServicesCount];
	for (unsigned i = 0; i < extraServicesCount; i++)
	{
		extraServices[i] = other.extraServices[i];
	}
}

//Getterek
std::chrono::year_month_day Reservation::GetTimeFrom() const
{
	return timeFrom;
}

std::chrono::year_month_day Reservation::GetTimeTo() const
{
	return timeTo;
}

const Guest* Reservation::GetGuests() const
{
	return guests;
}

const std::string* Reservation::GetExtraServices() const
{
	return extraServices;
}

const unsigned Reservation::GetGuestCount() const
{
	return guestCount;
}

Room* Reservation::GetReservedRoom() const
{
	return reservedRoom;
}

bool Reservation::GetHere() const
{
	return here;
}

unsigned Reservation::GetExtraServicesCount() const
{
	return extraServicesCount;
}

unsigned Reservation::GetLastReadRoomNumber() const
{
	return lastReadRoomNumber;
}

//kiszámolja a foglalás hosszát napokban
unsigned Reservation::GetDuration() const
{
	chrono::sys_days from = timeFrom;
	chrono::sys_days to = timeTo;
	chrono::days duration = to - from;
	return duration.count();
}

//setterek
void Reservation::SetTimeFrom(const chrono::year_month_day& pfrom)
{
	timeFrom = pfrom;
}

void Reservation::SetTimeTo(const chrono::year_month_day& pto)
{
	timeTo = pto;
}

void Reservation::SetGuests(Guest* pguest, unsigned pguestcount)
{
	if (guests != nullptr)
	{
		delete[] guests;
	}
	guestCount = pguestcount;
	guests = new Guest[pguestcount];
	for (unsigned i = 0; i < pguestcount; i++)
	{
		guests[i] = pguest[i];
	}
}

void Reservation::SetExtraServices(std::string* pextraservices, unsigned pextraservicescount)
{
	if (extraServices != nullptr)
	{
		delete[] extraServices;
	}
	extraServicesCount = pextraservicescount;
	extraServices = new std::string[pextraservicescount];
	for (unsigned i = 0; i < pextraservicescount; i++)
	{
		extraServices[i] = pextraservices[i];
	}
}

void Reservation::SetReservedRoom(Room* proom)
{
	reservedRoom = proom;
}

//kiszámolja a foglalás teljes összegét
double Reservation::Invoice() const
{
	double pricePerDay = reservedRoom->CalculatePrice();
	double totalPrice = pricePerDay * GetDuration() + pricePerDay*0.05*extraServicesCount;
	return totalPrice;
}

//speciális setterek a here változónak
void Reservation::CheckIn()
{
	here = true;
}

void Reservation::CheckOut()
{
	here = false;
}

//végösszeg összehasonlító operátorok
bool Reservation::operator==(const Reservation& jobbop) const
{
	double thisPrice = this->Invoice();
	double otherPrice = jobbop.Invoice();
	if (thisPrice == otherPrice)
	{
		return true;
	}
	return false;
}

bool Reservation::operator<(const Reservation& jobbop) const
{
	double thisPrice = this->Invoice();
	double otherPrice = jobbop.Invoice();
	if (thisPrice < otherPrice)
	{
		return true;
	}
	return false;
}

bool Reservation::operator<=(const Reservation& jobbop) const
{
	double thisPrice = this->Invoice();
	double otherPrice = jobbop.Invoice();
	if (thisPrice <= otherPrice)
	{
		return true;
	}
	return false;
}

bool Reservation::operator>(const Reservation& jobbop) const
{
	double thisPrice = this->Invoice();
	double otherPrice = jobbop.Invoice();
	if (thisPrice > otherPrice)
	{
		return true;
	}
	return false;
}

bool Reservation::operator>=(const Reservation& jobbop) const
{
	double thisPrice = this->Invoice();
	double otherPrice = jobbop.Invoice();
	if (thisPrice >= otherPrice)
	{
		return true;
	}
	return false;
}

//értékadó operátor
Reservation& Reservation::operator=(const Reservation& other)
{
	if (this == &other)
	{
		return *this;
	}

	timeFrom = other.timeFrom;
	timeTo = other.timeTo;
	guestCount = other.guestCount;
	extraServicesCount = other.extraServicesCount;
	reservedRoom = other.reservedRoom;
	here = other.here;

	if (guests != nullptr)
	{
		delete[] guests;
	}
	guests = new Guest[guestCount];
	for (unsigned i = 0; i < guestCount; i++)
	{
		guests[i] = other.guests[i];
	}

	if (extraServices != nullptr)
	{
		delete[] extraServices;
	}
	extraServices = new std::string[extraServicesCount];
	for (unsigned i = 0; i < extraServicesCount; i++)
	{
		extraServices[i] = other.extraServices[i];
	}

	return *this;
}

//álltalános output streamre kiíró
void Reservation::serialize(std::ostream& os) const
{
	os << timeFrom << " " << timeTo << " " << here << " " << reservedRoom->GetRoomNumber() << " ";
	os << guestCount << " ";
	for (unsigned i = 0; i < guestCount; i++)
	{
		guests[i].serialize(os);
	}
	os << extraServicesCount << " ";
	for (unsigned i = 0; i < extraServicesCount; i++)
	{
		os << extraServices[i] << " ";
	}
	os << endl;
}

//álltalános input streamről beolvasó
void Reservation::deserialize(std::istream& is)
{
	unsigned newGuestCount;
	is >> chrono::parse("%F", timeFrom);
	is >> chrono::parse("%F", timeTo);
	is >> here >> lastReadRoomNumber;
	is >> newGuestCount;
	delete[] guests;
	guestCount = newGuestCount;
	guests = new Guest[guestCount];
	for (unsigned i = 0; i < guestCount; i++)
	{
		guests[i].deserialize(is);
	}
	unsigned newExtraCount;
	is >> newExtraCount;
	delete[] extraServices;
	extraServicesCount = newExtraCount;
	extraServices = new std::string[extraServicesCount];
	for (unsigned i = 0; i < extraServicesCount; i++)
	{
		is >> extraServices[i];
	}
}

Reservation::~Reservation()
{
	delete[] guests;
	delete[] extraServices;
}
