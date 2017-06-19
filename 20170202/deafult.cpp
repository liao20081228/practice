/*************************************************************************
    > File Name: deafult.cpp
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月04日 星期六 20时27分29秒
 ************************************************************************/

#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;

int add(int a=1,int y=2,int c=3)
{
	return a+y+c;
}
int main()
{
	cout<<add(11)<<add(10,5)<<endl;
}
