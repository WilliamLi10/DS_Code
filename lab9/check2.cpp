#include<vector>
#include<iostream>
#include<map>
#include<fstream>
void FindModes(const std::vector<int>& numbers,std::vector<int>& Modes)
{
	std::map<int,int> NumFreq;
	int maxcount = 0;
	for(int i = 0; i != numbers.size(); ++i)
	{
		if(NumFreq.find(numbers[i]) == NumFreq.end())
		{
			NumFreq.insert(std::make_pair(numbers[i], 1));
		}
		else
		{
			++NumFreq.find(numbers[i])->second;
		}
		if(NumFreq.find(numbers[i])->second > maxcount)
		{
			maxcount = NumFreq.find(numbers[i])->second;
		}
	}
	for(std::map<int,int>::iterator i = NumFreq.begin(); i != NumFreq.end(); ++i)
	{
		if(i->second == maxcount)
		{
			Modes.push_back(i->first);
		}
	}

}

int main(int argc, char* argv[])
{
	std::vector<int> numbers = {19, 83, -12, 83, 65, 19, 45, -12, 45, 19, 45};
	std::vector<int> modes;
	FindModes(numbers,modes);
	for(int i = 0; i != modes.size(); ++i)
	{
		std::cout << modes[i] << std::endl;
	}
}