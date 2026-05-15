#pragma once
#include <chrono>
#include <string>
#include "Guest.h"
#include "Room.h"
#include "Serializable.h"
class Reservation: public Serializable			//A foglalást tároló osztály
{
private:
	std::chrono::year_month_day timeFrom;		// érkezés dátuma
	std::chrono::year_month_day timeTo;			//távozás dátuma
	bool here;									//bejelentkezett-e már legalább egy vendég
	Room* reservedRoom;							//a lefoglalt szobára egy mutató
	unsigned guestCount;						//vendégek száma
	Guest* guests;								//vendégek tömbjére mutató
	unsigned extraServicesCount;				//foglaláshoz köthető extra szolgáltatások száma
	std::string* extraServices;					//foglaláshoz köthető extra szolgáltatások tömbjére mutató
	unsigned lastReadRoomNumber;				//fájlból beolvasáshoz szükséges segéd tagváltozó

public:
	Reservation();
	Reservation(const std::chrono::year_month_day& pfrom, const std::chrono::year_month_day& pto, Guest* pguest, unsigned pguestcount, std::string* pextraservices, unsigned pextraservicescount, Room* proom);
	Reservation(const Reservation& other);

	//getterek
	std::chrono::year_month_day GetTimeFrom() const;
	std::chrono::year_month_day GetTimeTo() const;
	const Guest* GetGuests() const;
	const std::string* GetExtraServices() const;
	const unsigned GetGuestCount() const;
	Room* GetReservedRoom() const;
	bool GetHere() const;
	unsigned GetExtraServicesCount() const;
	unsigned GetLastReadRoomNumber()const;
	unsigned GetDuration()const;				//kiszámolja hogy hány nap a foglalás

	//setterek
	void SetTimeFrom(const std::chrono::year_month_day& pfrom);
	void SetTimeTo(const std::chrono::year_month_day& pto);
	void SetGuests(Guest* pguest, unsigned pguestcount);
	void SetExtraServices(std::string* pextraservices, unsigned pextraservicescount);
	void SetReservedRoom(Room* proom);


	double Invoice() const;						//kiszámolja a teljes foglalás számláját
	void CheckIn();								//A here tagváltozó "setterei" csak más névvel
	void CheckOut();

	//foglalás végösszeget összehasonlító operátorok
	bool operator==(const Reservation& jobbop) const;
	bool operator<(const Reservation& jobbop) const;
	bool operator<=(const Reservation& jobbop) const;
	bool operator>(const Reservation& jobbop) const;
	bool operator>=(const Reservation& jobbop) const;
	
	//értékadó operátor
	Reservation& operator=(const Reservation& other);

	void serialize(std::ostream& os) const;		//Álltalános output streamre kiíró függvény
	void deserialize(std::istream& is);			//Álltalános inputstreamről beolvasó függvény

	~Reservation();

};

