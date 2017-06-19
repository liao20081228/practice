/*************************************************************************
    > File Name: function_pointer.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月03日 星期三 00时25分39秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
int add(int x,int y)
{
	return x+y;
}

int red(int x,int y)
{
	return x-y;
}
int  main()
{
	/* 第一种方式*/
	int (*pfun)(int,int);
	pfun= add;
	cout<<pfun(1,2)<<endl;
	pfun= red;
	cout<<pfun(1,2)<<endl;
	/* 第二种方式*/
	typedef int(*fun)(int,int);
	fun p=add;
	cout<<p(1,3)<<endl;
	p=red;
	cout<<p(1,3)<<endl;
	return 0;
}
