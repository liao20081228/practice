#include<iostream>
#include<vector>

void fun(int a, int b)
{
	std::cout<< "call int a\n";
}

void fun( std::initializer_list<int> a, int b )
{
	std::cout<< "call std::initializer_list<int a\n";
}

int main(void)
{
	fun(1,2);
	fun({1,2},3);
	return 0;
}
