/*************************************************************************
    > File Name: defaultparameter.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月11日 星期二 21时27分04秒
 ************************************************************************/
#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
int add(int x,int y=10,int z=10)
{
	return x+y+z;
}
int add(int x,int y)
{
	return x+y;
}
int  main()
{
	int x=10,y=20,z=30;
	//cout<<"x+y="<<add(x,y)<<endl;
	//cout<<"x+y+z"<<add(x,,z)<<endl;
	cout<<"x+y+z"<<add(x,y,z)<<endl;
	
	return 0;
}

