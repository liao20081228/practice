/*************************************************************************
    > File Name: struct.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月12日 星期三 11时09分46秒
 ************************************************************************/
#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
using std::string;
struct A 
{
	void print()
	{
		cout<<x<<","<<y<<endl;
	}
	private:
	int x;
	int y;
};
int  main()
{
	A a;
	a.x=10;
	a.y=10;
	a.print();
	return 0;
}
