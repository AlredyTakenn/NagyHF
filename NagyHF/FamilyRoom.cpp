#include "FamilyRoom.h"

//Default konstruktor
FamilyRoom::FamilyRoom(): 
	numberOfChildBeds(0), Room(0, "Family", 0, 0, nullptr, 0)
{
}

//Paraméteres konstruktor
FamilyRoom::FamilyRoom(unsigned pnum, unsigned pbed, double pprice, std::string* pextra, unsigned pextracount, unsigned pchildBeds):
	Room(pnum, "Family", pbed, pprice, pextra, pextracount), numberOfChildBeds(pchildBeds)
{
}

//másoló konstruktor
FamilyRoom::FamilyRoom(const FamilyRoom& other)
	: Room(other), numberOfChildBeds(other.numberOfChildBeds)
{
}
unsigned FamilyRoom::GetNumberOfChildBeds() const
{
	return numberOfChildBeds;
}

//specializált napi ár kiszámító a családi szobára
double FamilyRoom::CalculatePrice() const
{
	double price = GetRoomBasePrice() * (1 + 0.1 * GetExtrasCount() + 0.05 * GetNumberOfBeds() - 0.02 * numberOfChildBeds);
	return price;
}

//értékadó operátor
FamilyRoom& FamilyRoom::operator=(const FamilyRoom& other)
{
	if(this == &other)
		return *this;
	Room::operator=(other);
	numberOfChildBeds = other.numberOfChildBeds;
	return *this;
}

//álltalános output streamre kiírás
void FamilyRoom::serialize(std::ostream& os) const
{
	os << GetRoomType() << " ";
	Room::serialize(os);
	os << numberOfChildBeds << std::endl;
}

//álltalános inputstreamről beolvasás
void FamilyRoom::deserialize(std::istream& is)
{
	Room::deserialize(is);
	is >> numberOfChildBeds;
}

FamilyRoom::~FamilyRoom()
{
}
