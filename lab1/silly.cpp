#include<iostream>

int main()
{
	int product = 1;
	int num = 1;
	while (std::cin >> num){
		product *= num; 
	}
	std::cout << product;
}