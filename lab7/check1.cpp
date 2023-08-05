#include<iostream>

int check1(int x, int y)
{
	if(x == 0 || y == 0)
	{
		return 1;
	}
	else
	{
		return check1(x - 1, y) + check1(x, y - 1);
	}
}



int main()
{
	std::cout << check1(2,1) << std::endl;
	std::cout << check1(2,2) << std::endl;
	std::cout << check1(0,0) << std::endl;
	std::cout << check1(3,5) << std::endl;
}