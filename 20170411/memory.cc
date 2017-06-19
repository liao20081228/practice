/*************************************************************************
    > File Name: memory.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月12日 星期三 09时28分11秒
 ************************************************************************/
#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
using std::string;
int a=0;// 全局静态区
char *p1;
int  main()
{
	int b;
	char str[]="123456";
	char *p2;
	const char  *p3="123456";
	static int c=0;
	p1=new char[10];
	strcpy(p1,str);
	printf("&b=%p\n",&b );
	printf("&p2=%p\n",&p2 );
	printf("&p3=%p\n",&p3 );
	printf("&c=%p\n",&c);
	printf("&p1=%p\n",&p1);
	
	return 0;
}
