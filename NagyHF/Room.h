#pragma once
#include <string>
class Room
{
protected:
	unsigned roomNumber;
	std::string roomType;
	unsigned numberOfBeds;
	double roomBasePrice;
	std::string* extras;
	unsigned extrasCount;

public:
	Room(unsigned pnum, std::string ptype, unsigned pbed, double pprice, std::string* pextra, unsigned pextracount);
	Room(const Room& other);

	unsigned GetRoomNumber() const;
	std::string GetRoomType() const;
	unsigned GetNumberOfBeds() const;
	unsigned GetRoomBasePrice() const;
	const std::string* GetExtras() const;
	const unsigned GetExtrasCount() const;

	virtual double CalculatePrice() const = 0;
	Room& operator=(const Room& other);

	virtual ~Room();

};

