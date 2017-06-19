/*************************************************************************
    > File Name: emptyclass.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月14日 星期五 09时16分53秒
 ************************************************************************/
#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
using std::string;
class empty
{};
int  main()
{
	empty a1;
	empty a2;
	printf("a1的大小是 %lu\n",sizeof(a1) );
	printf("a1的地址时%p\n",&a1 );
	printf("a2的大小是 %lu\n",sizeof(a2) );
	printf("a2的地址时%p\n",&a2 );
	return 0;
}
