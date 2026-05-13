#pragma once
#include "Container.h"
#include "Guest.h"
#include "Reservation.h"
#include "Room.h"
#include <string>
class Hotel
{
private:
	Container<Room*> roomList;
	Container<Guest> guestList;
	Container<Reservation> reservationList;
public:
	Hotel() = default;
	Hotel(const Hotel& other) = delete;
	Hotel& operator=(const Hotel& other) = delete;

	void AddRoom(Room* proom);
	void RegisterGuest(std::string pname, std::string pId);
	void BookReservation(std::chrono::year_month_day pfrom, std::chrono::year_month_day pto, Guest* pguests, unsigned pguestcount, std::string* pextraservices, unsigned pextraservicescount, unsigned requestedRoomNumber);

	void CheckIn(std::string searchGuestId);
	void CheckOut(std::string searchGuestId);
	void GenerateInvoice(std::string searchGuestId);

	~Hotel();
};

