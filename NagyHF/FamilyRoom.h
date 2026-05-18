#pragma once
#include "Room.h"
class FamilyRoom :						//Családi szoba, az általános szoba leszármazottja
    public Room
{
private:
	unsigned numberOfChildBeds;			//gyerekágyak száma
public:
	//konstruktorok
	FamilyRoom();
	FamilyRoom(unsigned pnum, unsigned pbed, double pprice, std::string* pextra,unsigned pextracount, unsigned pchildBeds);
	FamilyRoom(const FamilyRoom& other);

	unsigned GetNumberOfChildBeds() const;

	//kiszámolja a szoba árát egy napra
	double CalculatePrice() const override;

	//értékadó operátor
	FamilyRoom& operator=(const FamilyRoom& other);

	void serialize(std::ostream& os) const;			//általános outputstream kiirató függvény
	void deserialize(std::istream& is);				//álltalános inputstreamről beolvasó függvény

	~FamilyRoom();
};

