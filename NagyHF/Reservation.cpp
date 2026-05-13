#include "Reservation.h"
#include "Guest.h"
using namespace std;

Reservation::Reservation(std::chrono::year_month_day pfrom, std::chrono::year_month_day pto, Guest* pguest, unsigned pguestcount, std::string* pextraservices, unsigned pextraservicescount, Room* proom)
	:timeFrom(pfrom), timeTo(pto), guestCount(pguestcount), extraServicesCount(pextraservicescount), reservedRoom(proom), here(false)
{
	guests = new Guest[guestCount];
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

Reservation::Reservation(const Reservation& other):
	timeFrom(other.timeFrom), timeTo(other.timeTo), guestCount(other.guestCount), extraServicesCount(other.extraServicesCount), reservedRoom(other.reservedRoom), here(other.here)
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

void Reservation::SetTimeFrom(chrono::year_month_day pfrom)
{
	timeFrom = pfrom;
}

void Reservation::SetTimeTo(chrono::year_month_day pto)
{
	timeTo = pto;
}

void Reservation::SetGuests(Guest* pguest, unsigned pguestcount)
{
	if (guests != nullptr)
	{
		delete[] guests;
	}
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

double Reservation::Invoice() const
{
	double pricePerDay = reservedRoom->CalculatePrice();
	chrono::sys_days from = timeFrom;
	chrono::sys_days to = timeTo;
	chrono::days duration = to - from;
	double totalPrice = pricePerDay * duration.count() + pricePerDay*0.05*extraServicesCount;
	return totalPrice;
}

void Reservation::CheckIn()
{
	here = true;
}

void Reservation::CheckOut()
{
	here = false;
}

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

Reservation::~Reservation()
{
	delete[] guests;
	delete[] extraServices;
}
