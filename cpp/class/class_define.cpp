#include<iostream>

class animal
{
	int age;
	char name[100]={};
	
public:
	void action(void) const
	{
		std::cout << "action" << std::endl;
	}
};


int main(void)
{
	animal a();//认为是一个函数声明
	animal b{};
	return 0;
}
