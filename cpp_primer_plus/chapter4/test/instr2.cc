#include<iostream>
int main(void)
{
	const int size=20;
	char name[size]{};
	char dessert[size]{};
	std::cout << "enter your name: \n";
	std::cin.getline(name, size);
	std::cout << " enter you delicious" << std::endl;
	std::cin.getline(dessert, size);

	std::cout << "I have some delicious " << dessert << "for you, " << name << std::endl;
	std::cin.getline(name,size).getline(dessert,size);
	std::cout << "I have some delicious " << dessert << "for you, " << name << std::endl;
	return 0;
}
