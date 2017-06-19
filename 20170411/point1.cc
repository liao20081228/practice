/*************************************************************************
    > File Name: point1.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月12日 星期三 11时17分43秒
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
		int _x,_y;
	public:
		point()//构造函数
		{
			cout<<"这时构造函数"<<endl;
		}
		~point()//析构函数
		{
			cout<<"这是析构函数"<<endl;
		}
		void setpoint(int x,int y)
		{
			_x=x;
			_y=y;
		}
		void print()
		{
			cout<<_x<<","<<_y<<endl;
		}
};
int  main()
{
	point p;
	p.setpoint(10,10);
	p.print();
	return 0;
}
