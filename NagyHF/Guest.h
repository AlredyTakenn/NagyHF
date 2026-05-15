#pragma once
#include <string>
#include "Serializable.h"
class Guest: public Serializable		//Vendég osztály
{
private:
	std::string name;					//Vendég neve
	std::string Id;						//Vendég igazolványszáma
public:
	//konstruktorok
	Guest();
	Guest(const std::string& pname, const std::string& pId);
	Guest(const Guest& other);

	//getterek
	std::string GetName() const;
	std::string GetId() const;

	//setterek
	void SetName(const std::string& pname);
	void SetId(const std::string& pId);

	void serialize(std::ostream& os) const override;		//Általános output streamre kiíró függvény
	void deserialize(std::istream& is) override;			//Általános input streamből beolvasó függvény
};

