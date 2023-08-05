#include<iostream>
#include<string>

void ReverseString(std::string& s, int i = 0)
{
	if(i >=s.size()/2)
	{
		return;
	}
	else
	{
		char tmp = s[i];
		s[i] = s[s.size()-1-i];
		s[s.size()-1-i] = tmp;
		ReverseString(s,i+1);
	}
}
int main()
{
	std::string reverse = "ThisIsEven";
	ReverseString(reverse);
	std::cout << reverse << std::endl;
}