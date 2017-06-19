/*************************************************************************
    > File Name: namespace1.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月10日 星期一 22时22分41秒
 ************************************************************************/
#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
namespace A
{
	void display()
	{
		cout<<"a::display"<<endl;
	}
} /* A */ 
int  main()
{
	A::display();
	return 0;
}
