#include "LuxuryRoom.h"

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

LuxuryRoom::~LuxuryRoom()
{
}
