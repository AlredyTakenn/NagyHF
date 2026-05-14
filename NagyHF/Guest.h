#pragma once
#include <string>
#include "Serializable.h"
class Guest: public Serializable
{
private:
	std::string name;
	std::string Id;
public:
	Guest();
	Guest(const std::string& pname, const std::string& pId);
	Guest(const Guest& other);

	std::string GetName() const;
	std::string GetId() const;

	void SetName(const std::string& pname);
	void SetId(const std::string& pId);

	void serialize(std::ostream& os) const override;
	void deserialize(std::istream& is) override;
};

