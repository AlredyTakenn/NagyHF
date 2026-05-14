#include "Room.h"

Room::Room(unsigned pnum, std::string ptype, unsigned pbed, double pprice, std::string* pextra, unsigned pextracount):
	roomNumber(pnum), roomType(ptype), numberOfBeds(pbed), roomBasePrice(pprice), extrasCount(pextracount)
{
	extras = new std::string[extrasCount];
	for (unsigned i = 0; i < extrasCount; i++)
	{
		extras[i] = pextra[i];
	}
}

Room::Room(const Room& other):
	roomNumber(other.roomNumber), roomType(other.roomType), numberOfBeds(other.numberOfBeds), roomBasePrice(other.roomBasePrice), extrasCount(other.extrasCount)
{
	extras = new std::string[extrasCount];
	for (unsigned i = 0; i < extrasCount; i++)
	{
		extras[i] = other.extras[i];
	}
}

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

void Room::serialize(std::ostream& os) const
{
	os << roomNumber << " " << numberOfBeds << " " << roomBasePrice << " ";
	os << extrasCount << " ";
	for (unsigned i = 0; i < extrasCount; i++)
	{
		os << extras[i] << " ";
	}
}

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
