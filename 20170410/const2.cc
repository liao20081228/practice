/*************************************************************************
    > File Name: const2.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月10日 星期一 23时12分46秒
 ************************************************************************/
#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
int  main()
{
	const int a=100;/* 常变量*/ 
	const int b=1000;/* 常变量*/ 
	// a=100;
	const int *p=&a;
	// *p=200;
	p=&b;
	int c=100;
	int *const q=&c;
	const int *const w=&a;
	// w=&a;
	// *w=200;
	return 0;
}
