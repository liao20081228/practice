#include<iostream>
#include<string>

int main()
{
	char a[]="youaref";
	std::string b(a);
	std::cout <<a <<"\n";
	a[1]='c';
	std::cout <<a <<"\n";
}
