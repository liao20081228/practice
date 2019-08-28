#include<iostream>
#include<typeinfo>

int main(void)
{
	const int n=10;
	auto x =n;
	auto y= &n;

	std::cout << typeid(x).name() <<std::endl;
	std::cout << typeid(y).name() <<std::endl;

	
	return 0;
}
