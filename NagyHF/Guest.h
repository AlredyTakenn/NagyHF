#pragma once
#include <string>
class Guest
{
private:
	std::string name;
	std::string Id;
public:
	Guest();
	Guest(std::string pname, std::string pId);
	Guest(const Guest& other);

	std::string GetName() const;
	std::string GetId() const;

	void SetName(std::string pname);
	void SetId(std::string pId);
};

