#include<iostream>

int main(void)
{
	int b;
	b=10;
	
	int a=10;
	int c(10);
	int d{10};
	int e={10};
	int f={};
	int g={0};
	int h{};
	int i{0};
	std::cout << a<<b<<c<<d<<e<<f<<g<<h<<i << std::endl;
	i={20};
	std::cout << i << std::endl;

	return 0;
}
