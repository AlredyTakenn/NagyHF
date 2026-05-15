#include "StandardRoom.h"

//default konstruktor
StandardRoom::StandardRoom():
	Room(0,"Standard", 0,0,nullptr,0)
{
}

//paraméteres konstruktor
StandardRoom::StandardRoom(unsigned pnum, unsigned pbed, double pprice, std::string* pextra, unsigned pextracount):
	Room(pnum, "Standard", pbed, pprice, pextra, pextracount)
{
}

//másoló konstruktor
StandardRoom::StandardRoom(const StandardRoom& other):
	Room(other)
{
}

//nai ár kiszámító
double StandardRoom::CalculatePrice() const
{
	double price = GetRoomBasePrice() + GetExtrasCount() * GetRoomBasePrice() * 0.1 + (GetNumberOfBeds() > 2 ? GetNumberOfBeds() - 2 : 0) * GetRoomBasePrice * 0.05;
	return price;
}

//értékadó operátor
StandardRoom& StandardRoom::operator=(const StandardRoom& other)
{
	if (this == &other)
	{
		return *this;
	}
	
	Room::operator=(other);
	return *this;
}

//álltalános output streamre kiíró
void StandardRoom::serialize(std::ostream& os) const
{
	os << GetRoomType << " ";
	Room::serialize(os);
	os << std::endl;
}

//álltalános input streamről beolvasó
void StandardRoom::deserialize(std::istream& is)
{
	Room::deserialize(is);
}

StandardRoom::~StandardRoom()
{

}
