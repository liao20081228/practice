#include<stdio.h>
void fun()
{}

int main(void)
{
	void (*a)()=&fun;
	int b=10;
	int* p=&b;


	printf("%p,%p",fun,&a);
	return 0;
}
