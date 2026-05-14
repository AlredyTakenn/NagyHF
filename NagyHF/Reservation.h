#pragma once
#include <chrono>
#include <string>
#include "Guest.h"
#include "Room.h"
#include "Serializable.h"
class Reservation: public Serializable
{
private:
	std::chrono::year_month_day timeFrom;
	std::chrono::year_month_day timeTo;
	bool here;
	Room* reservedRoom;
	unsigned guestCount;
	Guest* guests;
	unsigned extraServicesCount;
	std::string* extraServices;

public:
	Reservation();
	Reservation(std::chrono::year_month_day pfrom, std::chrono::year_month_day pto, Guest* pguest, unsigned pguestcount, std::string* pextraservices, unsigned pextraservicescount, Room* proom);
	Reservation(const Reservation& other);

	std::chrono::year_month_day GetTimeFrom() const;
	std::chrono::year_month_day GetTimeTo() const;
	const Guest* GetGuests() const;
	const std::string* GetExtraServices() const;
	const unsigned GetGuestCount() const;
	Room* GetReservedRoom() const;
	bool GetHere() const;
	unsigned GetExtraServicesCount() const;

	void SetTimeFrom(std::chrono::year_month_day pfrom);
	void SetTimeTo(std::chrono::year_month_day pto);
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

	void serialize(std::ostream& os) const;
	void deserialize(std::istream& is);

	~Reservation();

};

