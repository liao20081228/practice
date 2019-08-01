#include<iostream>
int main(void)
{
	int a=10;
	std::cout << sizeof long (a) << std::endl;
	std::cout << sizeof((long )a) << std::endl;

	return 0;
}
