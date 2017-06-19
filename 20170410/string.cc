/*************************************************************************
    > File Name: string.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月11日 星期二 21时35分15秒
 ************************************************************************/
#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
using std::string;
int  main()
{
	string str;
	str="hello,world!";
	cout<<str<<endl;
	char buf[20];
	strcpy(buf,str.c_str());// .c_str()
	printf("%s\n", buf);
	str="";
	cout<<str<<endl;
	str.assign("hello,world");// .assign()
	cout<<str<<endl;
	str.erase();// .erase()
	cout<<str<<endl;
	str.assign("hello,world");// .assign()
	
	return 0;
}
