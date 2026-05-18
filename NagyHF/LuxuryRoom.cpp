#include "LuxuryRoom.h"

//default konstruktor
LuxuryRoom::LuxuryRoom():
	Room(0,"Luxury", 0,0,nullptr,0), hasMassageChair(false), hasJacuzzi(false)
{
}

//paraméteres konstruktor
LuxuryRoom::LuxuryRoom(unsigned pnum, unsigned pbed, double pprice, std::string* pextra, unsigned pextracount, bool pjacuzzi, bool pmassageChair):
	Room(pnum, "Luxury", pbed, pprice, pextra, pextracount), hasJacuzzi(pjacuzzi), hasMassageChair(pmassageChair)
{

}

//másoló konstruktor
LuxuryRoom::LuxuryRoom(const LuxuryRoom& other):
	Room(other), hasJacuzzi(other.hasJacuzzi), hasMassageChair(other.hasMassageChair)
{
}

bool LuxuryRoom::GetHasJacuzzi() const
{
	return hasJacuzzi;
}

bool LuxuryRoom::GetHasMassageChair() const
{
	return hasMassageChair;
}

//napi árat kiszámító függvény
double LuxuryRoom::CalculatePrice() const
{
	double price = GetRoomBasePrice() * (1 + 0.15 * GetExtrasCount() + 0.15 * GetNumberOfBeds() + 0.3 * (hasJacuzzi + hasMassageChair));
	return price;
}

//értékadó operátor
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

//álltalános output stremre kiíró
void LuxuryRoom::serialize(std::ostream& os) const
{
	os << GetRoomType() << " ";
	Room::serialize(os);
	os << hasJacuzzi << " " << hasMassageChair << std::endl;
}

//álltalános input streamről beolvasó
void LuxuryRoom::deserialize(std::istream& is)
{
	Room::deserialize(is);
	is >> hasJacuzzi >> hasMassageChair;
}

LuxuryRoom::~LuxuryRoom()
{
}
