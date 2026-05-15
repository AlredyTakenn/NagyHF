#include "Guest.h"
#include <stdexcept>
using namespace std;

//default konstruktor
Guest::Guest()
{

}

//paraméteres skonstruktor
Guest::Guest(const std::string& pname, const std::string& pId) : name(pname), Id(pId)
{
    if (name.empty()) {
        throw std::invalid_argument("A Név nem lehet üres.");
    }
    if (Id.empty()) {
        throw std::invalid_argument("Az igazolványszám nem lehet üres.");
    }
}

//másoló konstruktor
Guest::Guest(const Guest& other):name(other.name), Id(other.Id)
{
}

//Getterek
string Guest::GetName() const
{
    return name;
}

string Guest::GetId() const
{
    return Id;
}

//Setterek
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

//álltalános output streamre kiírás
void Guest::serialize(std::ostream& os) const
{
    os << name << " " << Id << std::endl;
}

//álltalános inputstreamről beolvasás
void Guest::deserialize(std::istream& is)
{
    string tempName, tempId;
    is >> tempName >> tempId;

    SetName(tempName);
    SetId(tempId);
}
