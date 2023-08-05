#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__
#include<vector>
#include<list>
#include<string>
#include<map>
#include"query.h"
#include"movie_data.h"

class HashTable {
public:
	//constructor used to make the hashtable
	HashTable(Movie_Data* AllMovies, int AllMoviesSize,int InitialSize, float ResizeRatio);
	//used to search for queries 
	std::list<Movie_Data*> operator[](const Query& SearchQuery);
private:
	float ResizeRatio;
	int FilledSpaces;
	int CurrentSize;
	int UniqueMovies;
	std::vector < std::pair<Query, std::list<Movie_Data*>>> StorageTable;
	//resize function
	void ResizeThis();

};

#endif