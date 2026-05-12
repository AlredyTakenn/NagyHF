#pragma once
#include <string>
using namespace std;
class Guest
{
private:
	string name;
	string Id;
public:
	Guest();
	Guest(string pname, string pId);
	Guest(const Guest& other);

	string GetName() const;
	string GetId() const;

	void SetName(string pname);
	void SetId(string pId);
};

