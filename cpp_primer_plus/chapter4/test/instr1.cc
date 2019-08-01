#include<iostream>
int main(void)
{
	const int size=20;
	char name[size]{};
	char dessert[size]{};
	std::cout << "enter your name:" << std::endl;
	std::cin >> name;
	std::cout << " enter you delicious" << std::endl;
	std::cin >> dessert;

	std::cout << "I have some delicious " << dessert << "for you, " << name << std::endl;
	return 0;
}
