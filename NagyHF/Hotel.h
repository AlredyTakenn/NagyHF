#pragma once
#include "Container.h"
#include "Guest.h"
#include "Reservation.h"
#include "Room.h"
#include <string>
#include <iostream>

class Hotel						//Az egész hotelt kezelő interface
{
private:
	Container<Room*> roomList;					//szobák dinamikus tömbje				
	Container<Guest> guestList;					//vendégek dinamikus tömbje
	Container<Reservation> reservationList;		//foglalások dinamikus tömbje
	void LoadRooms(std::istream& is);			//Szoba, vendég és foglalás betöltő segédfüggvények
	void LoadGuests(std::istream& is);
	void LoadReservations(std::istream& is);
public:
	//konstruktorok
	Hotel() = default;
	Hotel(const Hotel& other) = delete;
	Hotel& operator=(const Hotel& other) = delete;

	//Új szoba, vendég és foglalás felvétele
	void AddRoom(Room* proom);				
	void RegisterGuest(const std::string& pname, const std::string& pId);
	void BookReservation(const std::chrono::year_month_day& pfrom, const std::chrono::year_month_day& pto, Guest* pguests, unsigned pguestcount, std::string* pextraservices, unsigned pextraservicescount, unsigned requestedRoomNumber);

	//Ki- és bejelentkezés, végszámla kiállítás
	void CheckIn(const std::string& searchGuestId);
	void CheckOut(const std::string& searchGuestId);
	void GenerateInvoice(const std::string& searchGuestId);

	//A teljes hotel kimentése egy fájlba vagy onnan a feltöltése
	void SaveToFile(const std::string& fileName)const;
	void LoadFromFile(const std::string& fileName);

	~Hotel();
};

