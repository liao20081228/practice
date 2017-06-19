/*************************************************************************
    > File Name: point1.cpp
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月04日 星期六 21时28分18秒
 ************************************************************************/
#include<string.h>
#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
class point
{
	private:
		int _x,_y;
		char *p;
		
	public:
		point(int x=1,int y=1):_x(x),_y(y)
		{
			p=new char('c');
			cout<<"point(int x.int y)"<<endl;
		}
		~point()
		{
			delete p;
			cout<<"call ~point()"<<endl;
		}
		void print()
		{
			cout<<"ponit("<<_x<<","<<_y<<")"<<endl;
		}

};
int main()
{
	point p(3,4);
	p.~point();
	p.print();
	point p1(5);
	p1.print();
	point p2;
	p2.print();
}
