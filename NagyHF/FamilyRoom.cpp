#include "FamilyRoom.h"

FamilyRoom::FamilyRoom(unsigned pnum, unsigned pbed, double pprice, std::string* pextra, unsigned pextracount, unsigned pchildBeds):
	Room(pnum, "Family", pbed, pprice, pextra, pextracount), numberOfChildBeds(pchildBeds)
{
}

FamilyRoom::FamilyRoom(const FamilyRoom& other)
	: Room(other), numberOfChildBeds(other.numberOfChildBeds)
{
}

double FamilyRoom::CalculatePrice() const
{
	double price = roomBasePrice * (1 + 0.1 * extrasCount + 0.05 * numberOfBeds - 0.02 * numberOfChildBeds);
	return price;
}

FamilyRoom& FamilyRoom::operator=(const FamilyRoom& other)
{
	if(this == &other)
		return *this;
	Room::operator=(other);
	numberOfChildBeds = other.numberOfChildBeds;
	return *this;
}

FamilyRoom::~FamilyRoom()
{
}
