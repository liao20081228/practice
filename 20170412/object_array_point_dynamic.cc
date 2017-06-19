/*************************************************************************
    > File Name: object_array_point_dynamic.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月14日 星期五 09时47分10秒
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
		point(int x=0,int y=0):_x(x),_y(y)//构造函数
		{
			cout<<"point(int,int)"<<endl;
		}
		~point()//析构函数
		{
			cout<<"~point()"<<endl;
		}
		point(const point &ref):_x(ref._x),_y(ref._y)//拷贝构造函数
		{
			cout<<"point(const point &ref)"<<endl;
		}
		point & operator=(const point &ref)//赋值运算符函数
		{
			if(this==&ref)
				return *this;
			_x=ref._x;
			_y=ref._y;
			return *this;
		}
};
int  main()
{
	point *p=new point(1,2);
	point *p1;
	point arr[5];
	point *p2=new point[5];
	return 0;
}
