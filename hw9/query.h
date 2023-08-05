#ifndef __QUERY_H__
#define __QUERY_H__
#include<string>
#include<vector>
#include<string>
class Query {
public:
	Query();
	Query(std::string NTitle, int NYearRelease, int NRuntime,
		const std::vector<std::string>& NGenreList, const std::vector<std::string>& NActorList, const std::vector<std::string>& NRoleList, int NWildcards);
	int HashThis() const;
	bool operator==  (const Query& other) const;
	bool operator!= (const Query& other) const { return !(*this == other); } 
private:
	std::string Title;
	int YearRelease;
	int Runtime;
	std::vector<std::string> GenreList;
	std::vector<std::string> ActorList;
	std::vector<std::string> RoleList;
	int WildCards;

};


#endif