#include<iostream>
#include<cmath>
int main()
{
	char fill;
	int radius;
	std::cout << "Enter the radius:";
	std::cin >> radius;
	std::cout << std::endl << "Enter in the character:";
	std::cin >> fill;
	std::cout << std::endl;

	for(int i = radius; i != -radius; --i)
	{
		for(int j = -radius; j != radius * 2; ++j)
		{ 
			if(std::sqrt(std::pow(i,2) + std::pow(j,2)) <=radius)
			{
				std::cout << fill;
			}
			else
			{
				std::cout << ' ';
			}
		}
		std::cout << std::endl;
	}
}