/*************************************************************************
    > File Name: namespace.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月12日 星期三 09时02分27秒
 ************************************************************************/
#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
using std::string;
struct C 
{
	int a,b,c;
};
namespace  A
{
	int num =1000;
} /*  A */ 
namespace  B
{
	void displayA()
	{
		cout<<"a::num="<<A::num<<endl;
		cout<<"B::displayA"<<endl;
	}
} /*  B */ 
int  main()
{
	C c1;
	c1.a =10;
	B::displayA();
	return 0;
}
