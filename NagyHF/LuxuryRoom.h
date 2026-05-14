#pragma once
#include "Room.h"
class LuxuryRoom :
    public Room
{
private:
	bool hasJacuzzi;
	bool hasMassageChair;
public:
    LuxuryRoom(unsigned pnum, unsigned pbed, double pprice, std::string* pextra,unsigned pextracount, bool pjacuzzi, bool pmassageChair);
    LuxuryRoom(const LuxuryRoom& other);

    double CalculatePrice() const override;

    LuxuryRoom& operator=(const LuxuryRoom& other);

    void serialize(std::ostream& os) const;
    void deserialize(std::istream& is);

    ~LuxuryRoom();
};

