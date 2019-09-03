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

	animal(int age);
	animal();
	~animal(void);
};


int main(void)
{
	animal a();
	return 0;
}
