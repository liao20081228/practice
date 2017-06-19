/*************************************************************************
    > File Name: reference2.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月11日 星期二 13时15分11秒
 ************************************************************************/
#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
void swap1(int x,int y)
{
	int temp=x;
	x=y;
	y=temp;
}
void swap2(int *pa,int *pb)
{
	int temp=*pa;
	*pa=*pb;
	*pb=temp;
}
void swap3(int &x,int &y)
{
	int temp=x;
	x=y;
	y=temp;
}
int arr[5]={0,1,2,3,4};
int &func(int x)
{
	return arr[x] ;
}
int &func2()
{
	int x=2;
	return x;
}
int *func3()
{
	int x=3;
	return &x;
}
int &func4()
{
	int *pa=new int(5);
	return * pa;
}
int  main()
{
	int a=10,b=20;
	cout<<"a="<<a<<" "<<"b="<<b<<endl;
	swap1(a,b);
	cout<<"a="<<a<<" "<<"b="<<b<<endl;
	swap2(&a,&b);
	cout<<"a="<<a<<" "<<"b="<<b<<endl;
	swap3(a,b);
	cout<<"a="<<a<<" "<<"b="<<b<<endl;
	cout<<"fun1="<<func(3)<<"fun2="<<func2()<<"func3="<<*func3()<<"func4="<<func4()<<endl;
	return 0;
}

