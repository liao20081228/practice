/*************************************************************************
    > File Name: reference_member_init.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月13日 星期四 19时25分44秒
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
		int _x,_y,&_a;
		double &_b;
	public:
		/*point(int x,int y,int z):_x(x),_y(y)//构造函数,引用数据成员必须在初始化列表中初始化。
		{
			_a=x;
			_b=z;
		}*/
		point(int x,int y,double &z):_x(x),_y(y),_a(_x),_b(z)//构造函数
		{
		}
		void print(  )
		{
			cout<<_x<<","<<_y<<","<<_a<<","<<_b<<endl;
		}
		void setx(int x)
		{
			_x=x;
		}
};
int  main()
{
	double z=5.0;
	point p1(3,4,z);
	p1.print();
	point p2(p1);
	p2.print();
	cout<<"modify"<<endl;
	p1.setx(7);
	p1.print();
	p2.print();
	 cout<<"modify z"<<endl;
	 z=50;
	 p1.print();
	 p2.print();
	return 0;
}
