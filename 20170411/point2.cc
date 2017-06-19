/*************************************************************************
    > File Name: point2.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月12日 星期三 11时31分07秒
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
	private:
		int _x;
		int _y;
	public:
		point(int x,int y);//构造函数，函数重载，类内声明，类外实现
		point()//构造函数,函数重载，类型定义
		{
			cout<<"这是无参数构造函数"<<endl;
		}
		~point();//析构函数
		void setpoint(int x,int y)
		{
			_x=x;
			_y=y;
		}
		void print(  )
		{
			cout<<_x<<","<<_y<<endl;
			
		}
		
};
point::point(int x,int y=5):_x(x),_y(y)
{
	cout<<"这是构造函数"<<endl;
}
point::~point()
{
	cout<<"这是析构函数"<<endl;
}
int  main()
{
	point	p;
	p.print();
	point p1(1);
	p1.print();
	point p2(10,10);
	p2.print();
	return 0;
}
