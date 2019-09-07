#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cstdio>
#include"insert_sort/binary_insert_sort.hpp"
#include"insert_sort/direct_sort.hpp"
#include"exchang_sort/buble_sort.hpp"
int main(void)
{
	srand(time(NULL));
	int a[10],b[100],c[100];
	for (int i=0;i<10;++i)
	{
	  a[i]=rand()%10;
	  b[i]=rand()%10;
	  c[i]=rand()%10;
	}

	for (int i=0;i<10;i++)
		std::cout<<a[i]<<",";
	std::cout<<"\n";
	for (int i=0;i<10;i++)
		std::cout<<b[i]<<",";
	std::cout<<"\n";
	for (int i=0;i<10;i++)
		std::cout<<c[i]<<",";
	std::cout<<"\n";

	buble_down_sort(a,10);
	direct_insert_sort(b,10);
	binary_insert_sort(c,10);
	for (int i=0;i<10;i++)
		std::cout<<a[i]<<",";
	std::cout<<"\n";
	for (int i=0;i<10;i++)
		std::cout<<b[i]<<",";
	std::cout<<"\n";
	for (int i=0;i<10;i++)
		std::cout<<c[i]<<",";
	std::cout<<"\n";
	return 0;
}
