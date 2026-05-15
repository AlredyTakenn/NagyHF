#pragma once
#include <string>
#include "Serializable.h"
class Room :				//Az álltalános szobát tároló class
	public Serializable
{
private:
	std::string roomType;		//szoba típus	
	unsigned roomNumber;		//szobaszám
	unsigned numberOfBeds;		//ágyak száma
	double roomBasePrice;		//alap ár egy napra
	unsigned extrasCount;		//szobához kapcsolódó extra szolgáltatások száma
	std::string* extras;		//szobához kapcsolódó extra szolgáltatások tömbjére mutató
public:
	//konstruktorok
	Room(unsigned pnum,const std::string& ptype, unsigned pbed, double pprice, std::string* pextra, unsigned pextracount);
	Room(const Room& other);

	//getterek
	unsigned GetRoomNumber() const;
	std::string GetRoomType() const;
	unsigned GetNumberOfBeds() const;
	unsigned GetRoomBasePrice() const;
	const std::string* GetExtras() const;
	const unsigned GetExtrasCount() const;

	//virtuális napi ár számoló
	virtual double CalculatePrice() const = 0;

	//értékadó operátor
	Room& operator=(const Room& other);

	void serialize(std::ostream& os) const;			//álltalános output streamre kiíró 
	void deserialize(std::istream& is);				//álltalános inputstreamről beolvasó

	virtual ~Room();

};

