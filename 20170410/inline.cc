/*************************************************************************
    > File Name: inline.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月11日 星期二 20时35分15秒
 ************************************************************************/
#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
inline void func(){	cout<<"func inline"<<endl;}
int  main()
{
	func();
	return 0;
}
