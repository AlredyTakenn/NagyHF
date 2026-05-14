#pragma once
#include "Container.h"
#include "Guest.h"
#include "Reservation.h"
#include "Room.h"
#include <string>
#include <iostream>

class Hotel
{
private:
	Container<Room*> roomList;
	Container<Guest> guestList;
	Container<Reservation> reservationList;
	void LoadRooms(std::istream& is);
	void LoadGuests(std::istream& is);
	void LoadReservations(std::istream& is);
public:
	Hotel() = default;
	Hotel(const Hotel& other) = delete;
	Hotel& operator=(const Hotel& other) = delete;

	void AddRoom(Room* proom);
	void RegisterGuest(const std::string& pname,const std::string& pId);
	void BookReservation(const std::chrono::year_month_day& pfrom, const std::chrono::year_month_day& pto, Guest* pguests, unsigned pguestcount, std::string* pextraservices, unsigned pextraservicescount, unsigned requestedRoomNumber);

	void CheckIn(const std::string& searchGuestId);
	void CheckOut(const std::string& searchGuestId);
	void GenerateInvoice(const std::string& searchGuestId);

	void SaveToFile(const std::string& fileName)const;
	void LoadFromFile(const std::string& fileName);
	~Hotel();
};

