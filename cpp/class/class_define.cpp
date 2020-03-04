#include<iostream>

class animal
{
private:
	int age;
	char name[100]={};
	
public:
	void action(void) const
	{
		std::cout << "action" << std::endl;
	}
protected:
	int leg;

};


int main(void)
{
	animal a();//认为是一个函数声明
	animal b{};
	return 0;
}
