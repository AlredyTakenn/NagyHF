#include "Guest.h"
#include <stdexcept>
using namespace std;
Guest::Guest()
{

}

Guest::Guest(const string& pname, const string& pId)
{
    SetName(pname);
    SetId(pId);
}

Guest::Guest(const Guest& other)
{
    SetName(other.name);
    SetId(other.Id);
}

string Guest::GetName() const
{
    return name;
}

string Guest::GetId() const
{
    return Id;
}

void Guest::SetName(const string& pname)
{
	if (pname.empty())
    {
        throw invalid_argument("A Név nem lehet üres.");
    }
    name = pname;
}

void Guest::SetId(const string& pId)
{
    if (pId.empty())
    {
        throw invalid_argument("Az igazolványszám nem lehet üres.");
    }
    Id = pId;
}

void Guest::serialize(std::ostream& os) const
{
    os << name << " " << Id << std::endl;
}

void Guest::deserialize(std::istream& is)
{
    string tempName, tempId;
    is >> tempName >> tempId;

    SetName(tempName);
    SetId(tempId);
}
