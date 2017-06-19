/*************************************************************************
    > File Name: reference.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月11日 星期二 12时56分09秒
 ************************************************************************/
#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
int  main()
{
	int a=10;
	int &refa=a;
	refa=20;
	cout<<"refa="<<refa<<endl;
	cout<<"a="<<a<<endl;
	cout<<endl;
	int b=30;
	refa=b;
	cout<<"refa="<<refa<<endl;
	cout<<"a="<<a<<endl;
	cout<<"b="<<b<<endl;
	return 0;
}
// 引用必须初始化，不能重复指向，不能为空，引用可做函数返返回值，对引用的操作 就是对原对象的操作
