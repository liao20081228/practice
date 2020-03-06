#include<iostream>
#include<string>
const std::string& fun(const std::string& a)
{
	return a;
}


int main()
{
	std::string a("i love you");
	std::string b(fun(a));
	b="test";
	std::cout << a;
	std::cout << b;
}
