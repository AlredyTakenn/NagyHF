#pragma once
#include "Room.h"
class FamilyRoom :
    public Room
{
private:
	unsigned numberOfChildBeds;
public:
	FamilyRoom(unsigned pnum, unsigned pbed, double pprice, std::string* pextra,unsigned pextracount, unsigned pchildBeds);
	FamilyRoom(const FamilyRoom& other);

	double CalculatePrice() const override;

	FamilyRoom& operator=(const FamilyRoom& other);

	void serialize(std::ostream& os) const;
	void deserialize(std::istream& is);

	~FamilyRoom();
};

