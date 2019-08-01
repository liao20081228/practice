#include<iostream>
int main(void)
{
	const int size=20;
	char name[size]{};
	char dessert[size]{};
	std::cin.get(name, size);
	std::cin.get();
	std::cin.get(dessert, size);
	std::cin.get();
	std::cout << "I have some delicious " << dessert << " for you, " << name << std::endl;
	std::cin.get(name,size).get();
	std::cin.get(dessert,size).get();
	std::cout << "I have some delicious " << dessert <<  " for you, " << name << std::endl;
	return 0;
}
