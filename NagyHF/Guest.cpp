#include "Guest.h"
#include <stdexcept>

Guest::Guest()
{

}

Guest::Guest(string pname, string pId):name(pname), Id(pId)
{
}

Guest::Guest(const Guest& other) :name(other.name), Id(other.Id)
{
}

string Guest::GetName() const
{
    return name;
}

string Guest::GetId() const
{
    return Id;
}

void Guest::SetName(string pname)
{
	if (pname.empty())
    {
        throw invalid_argument("A Név nem lehet üres.");
    }
    name = pname;
}

void Guest::SetId(string pId)
{
    Id = pId;
}