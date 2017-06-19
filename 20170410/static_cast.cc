/*************************************************************************
    > File Name: static_cast.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月11日 星期二 13时35分56秒
 ************************************************************************/
#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
int test(void)
{
	int a=10;
	double b=(double)a;
	cout<<"b="<<b<<endl;
	return 0;
}
int  main()
{
	int a=10;
	double b=static_cast<double>(a);
	cout<<"b="<<b<<endl;
	test();
	return 0;
}
