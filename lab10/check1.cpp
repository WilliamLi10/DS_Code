void FindModes(const std::vector<int>& numbers,std::vector<int>& Modes)
{
	std::map<int,int> NumFreq;
	int maxcount = 0;
	for(int i = 0; i != numbers.size(); ++i)
	{
		if(NumFreq.find(numbers[i]) == NumFreq.end())
		{
			NumFreq[numbers[i]] = 1;
		}
		else
		{
			++NumFreq[numbers[i]];
		}
		if(NumFreq[numbers[i]] > maxcount)
		{
			maxcount = NumFreq[numbers[i]];
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