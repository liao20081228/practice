/*************************************************************************
    > File Name: overload.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月11日 星期二 13时54分02秒
 ************************************************************************/
#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
int add(int x,int y)
{
	return x+y;
}
int add(int x,int *y,int *z)
{
	return x+*y+*z;
}
int  main()
{
	int x=1,y=2,z=3;
	printf("%d,%d\n", add(x,y),add(x,&y,&z));
	return 0;
}
