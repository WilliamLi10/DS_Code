#include<vector>
#include<iostream>


int main()
{
	std::vector<int> vec = {43,12,2,1,34,25,89,76,10};
	int count = 0;
	for(int i = 0; i != vec.size(); ++i)
	{
		if(vec[i]%2 == 0)
			count += 1;
	}
	std::cout << count << std::endl;
}