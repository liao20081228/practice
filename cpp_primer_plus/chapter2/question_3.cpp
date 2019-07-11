#include<iostream>
void fun1(void);
void fun2(void);
int main(void)
{
	fun1();
	fun1();
	fun2();
	fun2();
	return 0;
}

void fun1(void)
{
	
	std::cout << "three blind mice\n";
}

void fun2(void)
{
	std::cout << "see how they run\n";
}

void fun3(void)
{
	std::cout << "see how they run \n";
}
