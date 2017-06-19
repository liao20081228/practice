/*************************************************************************
    > File Name: new_delete.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月11日 星期二 12时42分20秒
 ************************************************************************/
#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
int global=10;
int *test(void)
{
	int a=10;
	int  b=20;
	static int c=10;
	int *pa=(int *)malloc(sizeof(int));
	memset(pa,0,sizeof(int));
	*pa=1;
	printf("%d,%d,%d,%d\n",a,b,c,*pa);
	return pa;
}
int  main()
{
	int *pa=test();
	cout<<"*pa="<<*pa<<endl;
	free(pa);
	int *pb=new int(5);
	cout<<"*pb="<<*pb<<endl;
	delete  pb;
	int *pc=new int[10];
	delete []pc;
	return 0;
}
