#pragma once
#include "Room.h"
class LuxuryRoom :                  //Luxus szoba, az álltalános szoba leszármazottja
    public Room
{
private:
	bool hasJacuzzi;                //van-e jacuzzi
	bool hasMassageChair;           //van-e masszázs szék
public:
    //konstruktorok
    LuxuryRoom();
    LuxuryRoom(unsigned pnum, unsigned pbed, double pprice, std::string* pextra,unsigned pextracount, bool pjacuzzi, bool pmassageChair);
    LuxuryRoom(const LuxuryRoom& other);

    bool GetHasJacuzzi() const;
    bool GetHasMassageChair() const;

    //A szoba árát kiszámolja egy napra
    double CalculatePrice() const override;     

    //értékadó operátor
    LuxuryRoom& operator=(const LuxuryRoom& other);

    void serialize(std::ostream& os) const;      //Álltalános output streamre kiírás
    void deserialize(std::istream& is);          //Álltalános input streamről beolvasás

    ~LuxuryRoom();
};

