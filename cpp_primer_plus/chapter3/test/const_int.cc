#include<iostream>
#include<climits>
int main(void)
{
	unsigned int  a=UINT_MAX;
	std::cout << a << std::endl;
	a+=1;
	std::cout << a << std::endl;
	a=0;
	std::cout << a << std::endl;
	a-=1;
	std::cout << a << std::endl;
	
	signed int  b=INT_MAX;
	std::cout << b << std::endl;
	b+=1;
	std::cout << b << std::endl;
	b=INT_MIN;
	std::cout << b << std::endl;
	b-=1;
	std::cout << b << std::endl;

	std::cout << sizeof(92233) << std::endl;

}
