/*************************************************************************
    > File Name: namespace2.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月10日 星期一 22时50分38秒
 ************************************************************************/
#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
int num=100;
namespace A
{
	int num=1000;
	void fun(int num)
	{
		cout<<"func 的num is"<<num<<endl;
		cout<<"A中的num是"<<A::num<<endl;
		cout<<"最外面的num是"<<num<<endl;
	}
} /* A */
void fun()
{
	cout<<"i am fun"<<endl;
}
int  main()
{
	A::fun(200);
	fun();
	return 0;
}
