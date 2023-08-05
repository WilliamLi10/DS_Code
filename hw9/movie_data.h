#ifndef __MOVIE_DATA_H__
#define __MOVIE_DATA_H__

#include<string>
#include<vector>


class Movie_Data {
public:
	//constructors
	Movie_Data()
		:Title(""),YearRelease(-1),Runtime(-1){}
	Movie_Data(std::string NTitle, int NYearRelease, int NRuntime, 
		std::vector<std::string>& NGenreList, std::vector<std::string>& NActorList, std::vector<std::string>& NRoleList)
		: Title(NTitle), YearRelease(NYearRelease), Runtime(NRuntime), GenreList(NGenreList), ActorList(NActorList), RoleList(NRoleList) {}
	//getter functions
	const std::string& GetTitle() const { return Title; }
	int GetYearRelease() const { return YearRelease; }
	int GetRuntime() const { return Runtime; }
	const std::vector<std::string>& GetGenreList() const { return GenreList; }
	const std::vector<std::string>& GetActorList() const { return ActorList; }
	const std::vector<std::string>& GetRoleList() const { return RoleList; }


private:
	std::string Title;
	int YearRelease;
	int Runtime;
	std::vector<std::string> GenreList;
	std::vector<std::string> ActorList;
	std::vector<std::string> RoleList;

};


#endif