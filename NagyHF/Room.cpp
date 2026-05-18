#include "Room.h"

//paraméteres konstruktor
Room::Room(unsigned pnum,const std::string& ptype, unsigned pbed, double pprice, std::string* pextra, unsigned pextracount):
	roomNumber(pnum), roomType(ptype), numberOfBeds(pbed), roomBasePrice(pprice), extrasCount(pextracount)
{
	extras = new std::string[extrasCount];
	for (unsigned i = 0; i < extrasCount; i++)
	{
		extras[i] = pextra[i];
	}
	if (pprice < 0.0) {
		throw std::invalid_argument("Hiba: A szoba ara nem lehet negativ!");
	}
}

//másoló konstruktor
Room::Room(const Room& other):
	roomNumber(other.roomNumber), roomType(other.roomType), numberOfBeds(other.numberOfBeds), roomBasePrice(other.roomBasePrice), extrasCount(other.extrasCount)
{
	extras = new std::string[extrasCount];
	for (unsigned i = 0; i < extrasCount; i++)
	{
		extras[i] = other.extras[i];
	}
}

//getterek
unsigned Room::GetRoomNumber() const
{
	return roomNumber;
}

std::string Room::GetRoomType() const
{
	return roomType;
}

unsigned Room::GetNumberOfBeds() const
{
	return numberOfBeds;
}

unsigned Room::GetRoomBasePrice() const
{
	return roomBasePrice;
}

const std::string* Room::GetExtras() const
{
	return extras;
}

const unsigned Room::GetExtrasCount() const
{
	return extrasCount;
}

//értékadó operátor
Room& Room::operator=(const Room& other)
{
	if (this == &other)
		return *this;

	roomNumber = other.roomNumber;
	roomType = other.roomType;
	numberOfBeds = other.numberOfBeds;
	roomBasePrice = other.roomBasePrice;
	extrasCount = other.extrasCount;

	delete[] extras;
	extras = new std::string[extrasCount];
	for (unsigned i = 0; i < extrasCount; i++)
	{
		extras[i] = other.extras[i];
	}

	return *this;
}

//általános output stremre kiíró
void Room::serialize(std::ostream& os) const
{
	os << roomNumber << " " << numberOfBeds << " " << roomBasePrice << " ";
	os << extrasCount << " ";
	for (unsigned i = 0; i < extrasCount; i++)
	{
		os << extras[i] << " ";
	}
}

//álltalános input streamről beolvasó
void Room::deserialize(std::istream& is)
{
	is >> roomNumber >> numberOfBeds >> roomBasePrice;
	unsigned newExtrasCount;
	is >> newExtrasCount;
	if (extras != nullptr)
	{
		delete[] extras;
	}
	extrasCount = newExtrasCount;
	extras = new std::string[extrasCount];
	for (unsigned i = 0; i < extrasCount; i++)
	{
		is >> extras[i];
	}
}

Room::~Room()
{
	delete[] extras;
}
