/*************************************************************************
    > File Name: const1.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月10日 星期一 23时05分52秒
 ************************************************************************/
#include<myhead_cpp.h>/*myhead.h is a headfile defined in /usr/include*/
#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
#define MAX 100
#define max(x,y) ((x)>(y)?(x):(y))
int  main()
{
	const int a=100;
	cout<<"a"<<a<<endl;
	int b;
	const int c=b;
	cout<<"b="<<b<<endl;
	return 0;
}
