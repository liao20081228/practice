#include<iostream>
void fun(int a)
{
	std::cout<< a << std::endl;
}


void fun(bool a)
{
	std::cout<< a << std::endl;

}
void fun(void* p)
{
	std::cout<< p << std::endl;

}

int main(void)
{
	fun(0);
	fun(NULL);
	fun(nullptr);
	return 0;
}
