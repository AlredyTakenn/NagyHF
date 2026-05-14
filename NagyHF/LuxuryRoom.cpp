#include "LuxuryRoom.h"

LuxuryRoom::LuxuryRoom():
	Room(0,"Luxury", 0,0,nullptr,0)
{
}

LuxuryRoom::LuxuryRoom(unsigned pnum, unsigned pbed, double pprice, std::string* pextra, unsigned pextracount, bool pjacuzzi, bool pmassageChair):
	Room(pnum, "Luxury", pbed, pprice, pextra, pextracount), hasJacuzzi(pjacuzzi), hasMassageChair(pmassageChair)
{

}

LuxuryRoom::LuxuryRoom(const LuxuryRoom& other):
	Room(other), hasJacuzzi(other.hasJacuzzi), hasMassageChair(other.hasMassageChair)
{
}

double LuxuryRoom::CalculatePrice() const
{
	double price = roomBasePrice * (1 + 0.15 * extrasCount + 0.15 * numberOfBeds + 0.3 * (hasJacuzzi + hasMassageChair));
	return price;
}

LuxuryRoom& LuxuryRoom::operator=(const LuxuryRoom& other)
{
	if (this == &other)
	{
		return *this;
	}

	Room::operator=(other);
	hasJacuzzi = other.hasJacuzzi;
	hasMassageChair = other.hasMassageChair;
	return *this;
}

void LuxuryRoom::serialize(std::ostream& os) const
{
	os << roomType << " ";
	Room::serialize(os);
	os << hasJacuzzi << " " << hasMassageChair << std::endl;
}

void LuxuryRoom::deserialize(std::istream& is)
{
	Room::deserialize(is);
	is >> hasJacuzzi >> hasMassageChair;
}

LuxuryRoom::~LuxuryRoom()
{
}
