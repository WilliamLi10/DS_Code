#include<iostream>
#include<vector>
#include<map>
#include<list>
#include<string>
#include<map>
#include<vector>
#include<fstream>
#include "movie_data.h"
#include "query.h"
#include "HashTable.h"

int main()
{
	//creates default table size and resize ratio numbers
	int TableSize = 100;
	float ResizeRatio = 0.5;
	std::string command;
	//used for printing out actor names
	std::map<std::string, std::string> Actors;
	//used to initially store movie data information
	std::vector<Movie_Data> Data;
	//reads in all the information needed to create the hashtable
	while (true)
	{
		std::cin >> command;
		if (command == "table_size")
		{
			std::cin >> TableSize;
		}
		else if (command == "occupancy")
		{
			std::cin >> ResizeRatio;
		}
		else if (command == "movies")
		{
			std::ifstream inFile;
			std::string FileName;
			std::cin >> FileName;
			inFile.open(FileName);
			std::string Title;
			while (inFile >> Title)
			{
				int YearRelease;
				int Runtime;
				int GenreCount;
				int ActorCount;
				int RoleCount;
				std::vector<std::string> GenreList;
				std::vector<std::string> ActorList;
				std::vector<std::string> RoleList;
				inFile >> YearRelease >> Runtime >> GenreCount;
				for (int i = 0; i != GenreCount; ++i)
				{
					std::string Genre;
					inFile >> Genre;
					GenreList.push_back(Genre);
				}
				inFile >> ActorCount;
				for (int i = 0; i != ActorCount; ++i)
				{
					std::string Actor;
					inFile >> Actor;
					ActorList.push_back(Actor);
				}
				inFile >> RoleCount;
				for (int i = 0; i != RoleCount; ++i)
				{
					std::string Role;
					inFile >> Role;
					RoleList.push_back(Role);
				}
				Data.push_back(Movie_Data(Title, YearRelease, Runtime, GenreList, ActorList, RoleList));

			}
			//std::cout << Data.size() << std::endl;
		}
		else if (command == "actors")
		{
			std::ifstream inFile;
			std::string FileName;
			std::cin >> FileName;
			inFile.open(FileName);
			while (inFile)
			{
				std::string identifier;
				std::string Name;
				inFile >> identifier >> Name;
				Actors[identifier] = Name;
			}
			break;
		}
		else
		{
			std::cerr << "Invalid Input" << std::endl;
		}
	}
	//creates movie data array using the info read from the file. Pointers in the hashtable will point to this array.
	Movie_Data AllMovies[Data.size()];
	for (int i = 0; i != Data.size(); ++i)
	{
		AllMovies[i] = Data[i];
	}
	//create hashtable
	HashTable LookupTable(AllMovies, Data.size(),TableSize, ResizeRatio);
	//reads in queries and looks them up until a quit command is received
	while (std::cin >> command)
	{
		if (command == "query")
		{
			int WildCardCount = 0b000000;
			std::string Title;
			std::cin >> Title;
			if (Title == "?")
				WildCardCount += 0b000001;
			std::string YearReleaseRead;
			int YearRelease; 
			std::cin >> YearReleaseRead;
			if (YearReleaseRead == "?")
			{
				YearRelease = 0;
				WildCardCount += 0b000010;
			}
			else
			{
				YearRelease = std::stoi(YearReleaseRead);
			}
			int Runtime;
			std::string RuntimeRead;
			std::cin >> RuntimeRead;
			if (RuntimeRead == "?")
			{
				Runtime = 0;
				WildCardCount += 0b000100;
			}
			else
			{
				Runtime = std::stoi(RuntimeRead);
			}
			int GenreCount;
			int ActorCount;
			int RoleCount;
			std::vector<std::string> GenreList;
			std::vector<std::string> ActorList;
			std::vector<std::string> RoleList;
			std::cin >> GenreCount;
			if (GenreCount > 0)
			{
				for (int i = 0; i != GenreCount; ++i)
				{
					std::string Genre;
					std::cin >> Genre;
					GenreList.push_back(Genre);
				}
			}
			else
			{
				WildCardCount += 0b001000;
			}
			std::cin >> ActorCount;
			if (ActorCount > 0)
			{
				for (int i = 0; i != ActorCount; ++i)
				{
					std::string Actor;
					std::cin >> Actor;
					ActorList.push_back(Actor);
				}
			}
			else
			{
				WildCardCount += 0b010000;
			}
			std::cin >> RoleCount;
			if (RoleCount > 0)
			{
				for (int i = 0; i != RoleCount; ++i)
				{
					std::string Role;
					std::cin >> Role;
					RoleList.push_back(Role);
				}
			}
			else
			{
				WildCardCount += 0b100000;
			}
			//looks up and prints out results of query
			std::list<Movie_Data*> Movies = LookupTable[Query(Title, YearRelease, Runtime, GenreList, ActorList, RoleList,WildCardCount)];
			if (Movies.size() != 0)
			{
				std::cout << "Printing " << Movies.size() << " result(s):" << std::endl;
				for (std::list<Movie_Data*>::iterator i = Movies.begin(); i != Movies.end(); ++i)
				{
					std::cout << (*i)->GetTitle() << std::endl << (*i)->GetYearRelease() << std::endl << (*i)->GetRuntime() << std::endl;
					std::cout << (*i)->GetGenreList().size() << " ";
					for (int j = 0; j != (*i)->GetGenreList().size(); ++j)
					{
						std::cout << (*i)->GetGenreList()[j] << " ";
					}
					std::cout << std::endl;
					std::cout << (*i)->GetActorList().size() << " ";
					for (int j = 0; j != (*i)->GetActorList().size(); ++j)
					{
						std::cout << Actors[(*i)->GetActorList()[j]] << " (" <<(*i)->GetRoleList()[j] <<") ";
					}
					std::cout << std::endl;
				}
			}
			else
			{
				std::cout << "No results for query." << std::endl;
			}
		}
		else if (command == "quit")
		{
			break;
		}
		else
		{
			std::cerr << "Invalid Input" << std::endl;
		}
	}

	
}