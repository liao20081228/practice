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
	int a[100],b[100],c[100];
	for (int i=0;i<100;++i)
	{
	  a[i]=rand()%100;
	  b[i]=rand()%100;
	  c[i]=rand()%100;
	}

	for (int i=0;i<100;i++)
		std::cout<<a[i]<<",";
	std::cout<<"\n";
	for (int i=0;i<100;i++)
		std::cout<<b[i]<<",";
	std::cout<<"\n";
	for (int i=0;i<100;i++)
		std::cout<<c[i]<<",";
	std::cout<<"\n";

	buble_down_sort(a,100);
	direct_insert_sort(b,100);
	binary_insert_sort(c,100);
	for (int i=0;i<100;i++)
		std::cout<<a[i]<<",";
	std::cout<<"\n";
	for (int i=0;i<100;i++)
		std::cout<<b[i]<<",";
	std::cout<<"\n";
	for (int i=0;i<100;i++)
		std::cout<<c[i]<<",";
	std::cout<<"\n";
	return 0;
}
