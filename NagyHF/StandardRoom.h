#pragma once
#include "Room.h"
class StandardRoom :                //Alap szoba, az álltalános szoba leszármazottja
    public Room
{
public:
    //konstruktorok
    StandardRoom();
    StandardRoom(unsigned pnum, unsigned pbed, double pprice, std::string* pextra, unsigned pextracount);
    StandardRoom(const StandardRoom& other);

    //napi árat kiszámító függvény
    double CalculatePrice() const override;

    //értékadó operátor
	StandardRoom& operator=(const StandardRoom& other);

    void serialize(std::ostream& os) const;         //álltalános output streamre kiíró
    void deserialize(std::istream& is);             //álltalános input streamről beolvasó

    ~StandardRoom();
};

