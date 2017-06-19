/*************************************************************************
    > File Name: point3.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月12日 星期三 13时47分38秒
 ************************************************************************/
#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
using std::string;
class point
{
//构造函数，析构函数，拷贝构造函数，运算符函数都是特殊的成员函数，都可以在类内定义或者类内声明类外实现
	private:
		int _x,_y;
	public:
		//explicit
		point()//一旦给出构造函数，系统不再提供默认的无参构造函数
		//如果要使用无参构造函数需要显示定义，构造函数不可主动调用
		{
			cout<<"这是默认构造函数point()"<<endl;
		}
		//explicit// 禁止隐形转换
		point(int x,int y);//构造函数声明，类外实现
		~point()//析构函数,有且只能有一个，不建议显式调用
		{
			cout<<"这是析构函数~point()"<<endl;
		}
		point(const point &a):_x(a._x),_y(a._y)//拷贝构造函数中的引用不可省略，const一般不建议省略
		{
			cout<<"这是拷贝构造函数"<<endl;
		}
		/*point(const point &)//默认拷贝构造函数，采取浅拷贝,当成员中有指针时，要采用深拷贝
		{
			cout<<"这是拷贝构造函数"<<endl;
		}*/
		void print(  )
		{
			cout<<"(x,y):"<<_x<<","<<_y<<endl;
		}
};
point::point(int x,int y=10):_x(x),_y(y)//构造函数的类外实现
{
	cout<<"这是构造函数point(int x,int y)"<<endl;
}
void fun1(point p)
{
	p.print();
}
point fun2()
{
	point p3(5,5);
	return p3; 
}
int  main()
{
	cout<<"创建p1"<<endl;
	point p1;// 调用默认的无参构造函数
	p1.print();
	cout<<"创建p2"<<endl;
	point p2(1);
	p2.print();
	cout<<"创建p3"<<endl;
	point p3(1,2);
	p3.print();
	cout<<"创建p4"<<endl;
	point p4(p3);// 对象作为实参，会调用拷贝构造函数
	p4.print();
	cout<<"创建p5"<<endl;
	point p5=p3;// 用一个已存在的对象初始化新建对象会调用拷贝构造函数
	p5.print();
	point p6();// 这是函数声明
	cout<<"创建fun1"<<endl;
	fun1(p3);// 实参和形参都是对象，函数调用时调用拷贝构造函数
	cout<<"创建fun2"<<endl;
	fun2();// 返回值是对象，函数调用返回时调用拷贝构造函数
	cout<<"创建p7=fun2"<<endl;
	point p7=fun2();//调用两次构造函数
	cout<<"创建p8"<<endl;
	point p8=1;//隐性转换，使用explicit来禁止
	return 0;
}
