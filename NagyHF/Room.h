#pragma once
#include <string>
#include "Serializable.h"
class Room : 
	public Serializable
{
private:
	std::string roomType;
	unsigned roomNumber;
	unsigned numberOfBeds;
	double roomBasePrice;
	unsigned extrasCount;
	std::string* extras;
public:
	Room(unsigned pnum,const std::string& ptype, unsigned pbed, double pprice, std::string* pextra, unsigned pextracount);
	Room(const Room& other);

	unsigned GetRoomNumber() const;
	std::string GetRoomType() const;
	unsigned GetNumberOfBeds() const;
	unsigned GetRoomBasePrice() const;
	const std::string* GetExtras() const;
	const unsigned GetExtrasCount() const;

	virtual double CalculatePrice() const = 0;
	Room& operator=(const Room& other);

	void serialize(std::ostream& os) const;
	void deserialize(std::istream& is);

	virtual ~Room();

};

