/*************************************************************************
    > File Name: object_member_init.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月13日 星期四 19时50分19秒
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
		point(int x=0,int y=0):_x(x),_y(y)//构造函数
		{
			cout<<"point (int,int)"<<endl;
		}
		point(const point &ref):_x(ref._x),_y(ref._y)//拷贝构造函数
		{
			cout<<"point (const point &ref)"<<endl;
		}
		void print(  )
		{
			cout<<"("<<_x<<","<<_y<<")";
		}
};
class line
{
	private:
		point _start,_end;
	public:
		line(int x1=0,int y1=0,int x2=0,int y2=0):_start(x1,y1),_end(x2,y2)//构造函数
		{
			/*_start=point(x1,y1);
			_end=point(x2,y2);*/
		}
		line(const line &ref) //拷贝构造函数
		{
			_start=ref._start;
			_end=ref._end;
			cout<<"line(const line &ref)"<<endl;
		}
		line & operator=(const line &ref)//赋值运算符函数
		{
			cout<<"line &operator =(const line &ref)"<<endl;
			if(this==&ref)
				return *this;
			_start=ref._start;
			_end=ref._end;
			return *this;
		}
		void print(  )
		{
			_start.print();cout<<"-------->";_end.print();
			cout<<endl;
			
		}
};
int  main()
{
	line l1;
	l1.print();
	line l2(1,2,3,4);
	l2.print();
	line l3=line(5,6,7,8);
	l3.print();
	line l4(l2);
	l4.print();
	line l5=l2;
	l5.print();
	l1=l3;
	l1.print();
	return 0;
}
