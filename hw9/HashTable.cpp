#include"HashTable.h"
#include "query.h"
#include "movie_data.h"
#include<vector>
#include<string>
#include<list>
#include<iostream>

/*Generates 64 queries for each movie in the movie data array. It will then hash each query and find the correct bin
to put the movie data pointer in. If the bin is empty, then it will also set the query equal to the current query. It checks
the occupancy ratio on every iteration, and when it exceeds the max ratio, it will resize the table.*/
HashTable::HashTable(Movie_Data* AllMovies, int AllMoviesSize,int InitialSize, float TResizeRatio)
	:ResizeRatio(TResizeRatio),FilledSpaces(0),CurrentSize(InitialSize), UniqueMovies(AllMoviesSize)
{
	StorageTable = std::vector<std::pair<Query, std::list<Movie_Data*>>>(CurrentSize);
	for (int i = 0; i != UniqueMovies; ++i)
	{
		for (int j = 0; j != 64; ++j)
		{
			//std::cout << "Iteration " << i << ", " << j << std::endl;
			Query BaseQuery(AllMovies[i].GetTitle(), AllMovies[i].GetYearRelease(), AllMovies[i].GetRuntime(), AllMovies[i].GetGenreList(),
				AllMovies[i].GetActorList(), AllMovies[i].GetRoleList(), j);
			//std::cout << "Query made" << std::endl;
			int HashValue = abs(BaseQuery.HashThis());
			int TableIndex = HashValue % CurrentSize;
			//std::cout << "Hash made " << TableIndex << std::endl;
			int check = 0;
			while (StorageTable[TableIndex + check].second.size() != 0 && BaseQuery != StorageTable[TableIndex + check].first)
			{
				++check;
				if (check + TableIndex >= CurrentSize)
				{
					TableIndex = 0;
					check = 0;
				}
				//std::cout << TableIndex + check << std::endl;
			}
			if(StorageTable[TableIndex+check].second.size() == 0)
				StorageTable[TableIndex + check].first = BaseQuery;
			StorageTable[TableIndex + check].second.push_back(AllMovies + i);
			//std::cout << "Put into hash" << std::endl;
			++this->FilledSpaces;
			//std::cout << FilledSpaces/(float)CurrentSize  << " "  << " " <<StorageTable.size() << std::endl;
			if ((FilledSpaces /(float)CurrentSize) >= ResizeRatio)
			{
				//std::cout << "Resizing" << std::endl;
				ResizeThis();
			}
		}
	}
}
/*creates a new vector to hold temporarily hold the data, and then it will set the hashtable to a new vector with double the size.
It takes all the info in tmp, hashes it, and then puts it into the new hashtable.*/
void HashTable::ResizeThis()
{
	std::vector<std::pair<Query, std::list<Movie_Data*>>> tmp = StorageTable;
	CurrentSize *= 2;
	StorageTable.clear();
	StorageTable = std::vector<std::pair<Query, std::list<Movie_Data*>>>(CurrentSize);
	for (int i = 0; i != tmp.size(); ++i)
	{
		if (tmp[i].second.size() != 0)
		{
			int NewHashValue = abs(tmp[i].first.HashThis());
			int check = 0;
			int NewTableIndex = NewHashValue % CurrentSize;
			while (StorageTable[NewTableIndex + check].second.size() != 0 && tmp[i].first != StorageTable[NewTableIndex + check].first)
				++check;
			StorageTable[NewTableIndex + check].first = tmp[i].first;
			StorageTable[NewTableIndex + check].second = tmp[i].second;
		}
	}
	
}
/*a Query is passed in to look up in the table. It will hash the query, and find the correct location of the query movie data pointer list pair.
If it searches the entire hashtable without finding the correct query, the query is not inside the table and it will return an empty list.*/
std::list<Movie_Data*> HashTable::operator[](const Query& SearchQuery)
{
	int HashValue = abs(SearchQuery.HashThis());
	int check = 0;
	//std::cout << HashValue << std::endl;
	int TableIndex = HashValue % CurrentSize;
	int count = 0;
	while (count < CurrentSize && SearchQuery != StorageTable[TableIndex + check].first)
	{
		++check;
		if (check + TableIndex >= CurrentSize)
		{
			TableIndex = 0;
			check = 0;
		}
		++count;
	}
	if (count >= CurrentSize )
		return std::list<Movie_Data*>();
	else
	{
		return StorageTable[TableIndex + check].second;
	}
}