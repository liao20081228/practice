/*************************************************************************
    > File Name: string.cpp
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月04日 星期六 17时57分55秒
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

void test1()
{
	const char *pstr="hello,world";
	cout<<pstr<<endl;
	cout<<"length="<<strlen(pstr)<<endl;

	char *p1=(char *)malloc(strlen(pstr)+1);
	strcpy(p1,pstr);
	cout<<p1<<endl;
	cout<<"length="<<strlen(p1)<<endl;
   
	const char*pstr2="shenzhen";
	char *p2=(char *)malloc(strlen(pstr)+strlen(pstr2)+1);
	strcpy(p2,pstr);
	strcat(p2,pstr2);
	cout<<p2<<endl;
	cout<<"length="<<strlen(p2)<<endl;
}
void test2()
{
	string s1="hello,world";
	cout<<"s1:"<<s1<<s1.length()<<"   "<<s1.size()<<endl;

	string s2=s1;
	cout<<"s2:"<<s2<<s2.length()<<"   "<<s2.size()<<endl;
	
	string s3="shenzhen";
	string s4=s3+s1;
	cout<<"s4:"<<s4<<s4.length()<<"   "<<s4.size()<<endl;
	string s5=s1+s3;
	cout<<"s5:"<<s5<<s5.length()<<"   "<<s5.size()<<endl;

}
int  main()
{
	test1();
	 test2();
	 return 1;
}
