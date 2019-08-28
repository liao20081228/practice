#include<iostream>


namespace
{
	class bird
	{
		int wing;
		int leg;
		public:
		void eat(const char* food);
	};
}

namespace my
{
	class bird
	{
		int wing;
		int leg;
		public:
		void fly(const char* speed);
	};
}


void ::bird::eat(const char* food)
{
	std::cout << food << std::endl;
}

void my::bird::fly(const char* speed)
{
	std::cout << speed << std::endl; 
}
