#include "Reservation.h"
#include "Guest.h"

Reservation::Reservation(chrono::year_month_day pfrom, chrono::year_month_day pto, Guest* pguest, unsigned pguestcount, std::string* pextraservices, unsigned pextraservicescount, Room* proom)
	:timeFrom(pfrom), timeTo(pto), guestCount(pguestcount), extraServicesCount(pextraservicescount), reservedRoom(proom), here(false)
{
	guests = new Guest[guestCount];
	for (unsigned i = 0; i < guestCount; i++)
	{
		guests[i] = pguest[i];
	}
}
