#pragma once
#include <chrono>
#include <string>
#include "Guest.h"
#include "Room.h"
class Reservation
{
private:
	chrono::year_month_day timeFrom;
	chrono::year_month_day timeTo;
	Guest* guests;
	unsigned guestCount;
	std::string* extraServices;
	unsigned extraServicesCount;
	Room* reservedRoom;
	bool here;
public:
	Reservation(chrono::year_month_day pfrom, chrono::year_month_day pto, Guest* pguest, unsigned pguestcount, std::string* pextraservices, unsigned pextraservicescount, Room* proom);
	Reservation(const Reservation& other);

	chrono::year_month_day GetTimeFrom() const;
	chrono::year_month_day GetTimeTo() const;
	const Guest* GetGuests() const;
	const std::string* GetExtraServices() const;
	const unsigned GetGuestCount() const;
	Room* GetReservedRoom() const;
	bool GetHere() const;
	unsigned GetExtraServicesCount() const;

	void SetTimeFrom(chrono::year_month_day pfrom);
	void SetTimeTo(chrono::year_month_day pto);
	void SetGuests(Guest* pguest, unsigned pguestcount);
	void SetExtraServices(std::string* pextraservices, unsigned pextraservicescount);
	void SetReservedRoom(Room* proom);


	double Invoice() const;
	void CheckIn();
	void CheckOut();

	bool operator==(const Reservation& jobbop) const;
	bool operator<(const Reservation& jobbop) const;
	bool operator<=(const Reservation& jobbop) const;
	bool operator>(const Reservation& jobbop) const;
	bool operator>=(const Reservation& jobbop) const;

	Reservation& operator=(const Reservation& other);

	~Reservation();

};

