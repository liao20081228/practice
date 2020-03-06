#include<iostream>
#include<string>
#include"custom_sem.hpp"
std::string& fun( std::string& a)
{
	return a;
}


int main()
{
	std::string a("i love you");
	fun(a)="test";
	std::cout <<(void*)a.c_str();
	a.clear();
	std::cout <<(void*)a.c_str();
	posix_sem c("test");
	c.post();
}
