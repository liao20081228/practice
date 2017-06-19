/*************************************************************************
    > File Name: externc.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月11日 星期二 14时36分15秒
 ************************************************************************/
#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
#ifdef __cplusplus
extern "C"
{
#endif
int add(int x,int y)
{
	return x+y;
}
#ifdef __cplusplus
}
#endif
int add(int x,int y,int z)
{
	return x+y+z;
}
double  add(double x,double y,double z)
{
	return x+y+z;
}
void func()
{
	cout<<"func no arg"<<endl;
}
void func(int idx)
{
	cout<<"idx="<<idx<<endl;
}
int  main()
{
	int x=1,y=2,z=3;
	double  a=0.1,b=0.2,c=0.3;
	cout<<"x+y="<<add(x,y)<<endl;
	cout<<"x+y+z="<<add(x,y,z)<<endl;
	cout<<"x+y+z="<<add(a,b,c)<<endl;
	func();
	func(10);
	return 0;
}
