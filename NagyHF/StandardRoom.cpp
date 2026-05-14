#include "StandardRoom.h"

StandardRoom::StandardRoom():
	Room(0,"Standard", 0,0,nullptr,0)
{
}
StandardRoom::StandardRoom(unsigned pnum, unsigned pbed, double pprice, std::string* pextra, unsigned pextracount):
	Room(pnum, "Standard", pbed, pprice, pextra, pextracount)
{
}

StandardRoom::StandardRoom(const StandardRoom& other):
	Room(other)
{
}

double StandardRoom::CalculatePrice() const
{
	double price = roomBasePrice + extrasCount * roomBasePrice * 0.1 + (numberOfBeds > 2 ? numberOfBeds - 2 : 0) * roomBasePrice * 0.05;
	return price;
}

StandardRoom& StandardRoom::operator=(const StandardRoom& other)
{
	if (this == &other)
	{
		return *this;
	}
	
	Room::operator=(other);
	return *this;
}

void StandardRoom::serialize(std::ostream& os) const
{
	os << roomType << " ";
	Room::serialize(os);
	os << std::endl;
}

void StandardRoom::deserialize(std::istream& is)
{
	Room::deserialize(is);
}

StandardRoom::~StandardRoom()
{

}
