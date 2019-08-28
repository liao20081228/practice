#include<iostream>

template<typename T>
auto fun(T n)
//auto fun(T n)->decltype(n)
{
	return n;
}

int main(void)
{
	fun<int>(10);
	fun(10);
	return 0;
}
