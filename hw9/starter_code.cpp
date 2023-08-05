/*
These two functions are not required for your program, but may be helpful!
The recursive function will generate every combination of 0/1 for 6 positions
in a vector. Whenever pos == 6, the vector is complete.

Hint: There are 6 different "fields" in a query, this may be useful in constructing
your hash table.
*/
#include<iostream>
#include<vector>
void permute_filters(int pos, std::vector<int> filter){
	if(pos == 6){
		//Add other code here if you want to use the completed vectors
		return;
	}

	filter.push_back(0);
	std::vector<int> filter_new = filter;
	filter_new.back() = 1;
	permute_filters(pos+1, filter_new);
	for (int i = 0; i != filter.size(); ++i)
	{
		std::cout << "Filter at index " << i << ": " <<filter[i] << std::endl;
	}
	permute_filters(pos+1, filter);
	for (int i = 0; i != filter_new.size(); ++i)
	{
		std::cout << "Filter_new at index " << i << ": " <<filter_new[i] << std::endl;
	}
}

//Driver function, feel free to modify to pass more arguments
void permute_filters(){
		permute_filters(0, std::vector<int>());
}


int main()
{
	int WildCardCount = 0b000000;

		for (int j = 0; j != 64; ++j)
		{
			int check = WildCardCount & (1 << (2 - 1));
			if (check == 0)
				std::cout << WildCardCount << std::endl;
			WildCardCount += 0b000001;
		}

	return 0;
}