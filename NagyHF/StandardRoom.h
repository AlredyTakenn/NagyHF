#pragma once
#include "Room.h"
class StandardRoom :
    public Room
{
public:
    StandardRoom(unsigned pnum, unsigned pbed, double pprice, std::string* pextra, unsigned pextracount);
    StandardRoom(const StandardRoom& other);

    double CalculatePrice() const override;

	StandardRoom& operator=(const StandardRoom& other);

    ~StandardRoom();
};

