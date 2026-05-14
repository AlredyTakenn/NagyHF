#include "Guest.h"
#include <stdexcept>
using namespace std;
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

void Guest::serialize(std::ostream& os) const
{
    os << name << " " << Id << std::endl;
}

void Guest::deserialize(std::istream& is)
{
    string tempName, tempId;
    is >> tempName, tempId;

    SetName(tempName);
    SetId(tempId);
}
