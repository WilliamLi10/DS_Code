#include"query.h"
//checks for equality of all attributes of two query objects
bool Query::operator==(const Query& other) const
{
	if (this->Title != other.Title || this->Runtime != other.Runtime || this->YearRelease != other.YearRelease)
	{
		return false;
	}
	else if (this->GenreList.size() != other.GenreList.size() ||
		this->ActorList.size() != other.ActorList.size() || this->RoleList.size() != other.RoleList.size())
	{
		return false;
	}
	else
	{
		for (int i = 0; i != GenreList.size(); ++i)
		{
			if (this->GenreList[i] != other.GenreList[i])
				return false;
		}
		for (int i = 0; i != ActorList.size(); ++i)
		{
			if (this->ActorList[i] != other.ActorList[i])
				return false;
		}
		for (int i = 0; i != ActorList.size(); ++i)
		{
			if (this->ActorList[i] != other.ActorList[i])
				return false;
		}
		return true;
	}
}
/*Constructor used to make the query. Since the max value for wildcards is 64, it is represented by a 6 bit number. 1 represents wildcard and 0 represents no wildcard.
Each bit in the number corresponds to a different attribute in the query. If that bit is a 1, it is marked as a wildcard otherwise the attribute is set normally
using the data that is passed into the constructor.*/
Query::Query(std::string NTitle, int NYearRelease, int NRuntime,
	const std::vector<std::string>& NGenreList, const std::vector<std::string>& NActorList, const std::vector<std::string>& NRoleList, int NWildcards)
{
	WildCards = NWildcards;
	if ((WildCards & 0b000001) == 0)
		Title = NTitle;
	else
		Title = "0";
	if ((WildCards & 0b000010) == 0)
		YearRelease = NYearRelease;
	else
		YearRelease = 0;
	if ((WildCards & 0b000100) == 0)
		Runtime = NRuntime;
	else
		Runtime = 0;
	if ((WildCards & 0b001000) == 0)
		GenreList = NGenreList;
	if ((WildCards & 0b010000) == 0)
		ActorList = NActorList;
	if ((WildCards & 0b100000) == 0)
		RoleList = NRoleList;
}
/*It will combine all the attributes of the query into one giant string and then hash that string*/
int Query::HashThis() const
{
	std::string HashString = "";
	HashString += Title + std::to_string(YearRelease) + std::to_string(Runtime);
	if (GenreList.size() != 0)
	{
		for (int i = 0; i != GenreList.size(); ++i)
		{
			HashString += GenreList[i];
		}
	}
	else
	{
		HashString += '?';
	}
	if (RoleList.size() != 0)
	{
		for (int i = 0; i != RoleList.size(); ++i)
		{
			HashString += RoleList[i];
		}
	}
	else
	{
		HashString += '?';
	}
	if (ActorList.size() != 0)
	{
		for (int i = 0; i != ActorList.size(); ++i)
		{
			HashString += ActorList[i];
		}
	}
	else
	{
		HashString += '?';
	}
	unsigned int hash = 1315423911;
	for (unsigned int i = 0; i < HashString.length(); i++)
		hash ^= ((hash << 5) + HashString[i] + (hash >> 2));
	return hash;
	
}
//Default constructor for query called during initial creation of hashtable
Query::Query()
	:Title(""), YearRelease(-1), Runtime(-1) 
{
	ActorList.push_back("Uninitialized");
	GenreList.push_back("Uninitialized");
	RoleList.push_back("Uninitialized");
}