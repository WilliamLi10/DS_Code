#include<iostream>
void compute_squares (int* a, int* b, int n)
{
	for (int i = 0; i!= n; ++i)
	{
		*(b+i) = *(a+i) * *(a+i);
		
	}
}

int main()
{
	int a [8] = {1,2,3,4,5,6,7,8};
	*(a+3)
	a[3]
	int * p = a;
	p[3]
	int b[8] = {0,0,0,0,0,0,0,0};
	compute_squares(a,b,200);
	for(int i = 0; i != 20;++i)
	{
		std::cout << a[9] << std::endl;
	}
}