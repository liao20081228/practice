/*************************************************************************
    > File Name: template.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月23日 星期日 22时13分38秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
template<typename T> /* 定义在使用之前，不用声明*/ 
T add(T a,T b)   /* 模板的声明和实现必须在同一文件，而不能像函数那样在头文件声明，在其文件实现*/
{
	return a+b;
}
template <typename T> /* 定义在使用之后必须主函数和其它函数外在外声明*/
T  max(T a, T b);

template<typename T,int num> /* 模板类型参数，可以有非参数的常量，用int表示*/
T add(T a,T b)               /* 允许根据本质不同类型参数列表来重载同名模板*/
{
	return (a+b)*num;
}

/*template<typename T3> //不允许重复定义本质相同的同名模板
T3 add(T3 a,T3 b)
{
	return a+b;
}*/


/*template<typename T> // 不允许根据返回值不同来重载模板
int  add(T a,T b)
{
	return a+b;
}*/
char add(char a,char b)  /* 同名模板，模板与普通同名函数之间可以重载，但是普通函数优先于模板*/
{
	return a+b;
}

int  main()
{
	int x=10,y=20;
	cout<<add(x,y)<<endl;/* 隐式实例化由编译器自动推测*/ 
	cout<<add<int>(x,y)<<endl; /* 显式实例化*/
	cout<<add<int,3>(x,y)<<endl;  /*允许根据本质不同的类型参数列表来重载同名模板 */
	cout<<add('a',1)<<endl;  /* 模板可以普通同名函数一起重载，但是普通同名函数优先于模板*/
	cout<<max(x,y)<<endl;
	return 0;
}




template<typename T>
T max(T a,T b)
{
	return a>b?a:b;
}



