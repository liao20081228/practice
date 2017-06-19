/*************************************************************************
    > File Name: friend.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月17日 星期一 21时14分04秒
 ************************************************************************/
#include<myhead>/*myhead.h is a headfile defined in /usr/include by user*/
class Point;
class Line
{
	private:
		 Point *_p1,*_p2;
	public:
		Line(Point *p1,Point *p2):_p1(p1),_p2(p2)//构造函数
		{
			/*fucntion_body*/
		}
		~Line()//析构函数
		{
		}
		Line(const Line &ref):_p1(ref._p1),_p2(ref._p2)//拷贝构造函数
		{
			/*fucntion_body*/
		}
		Line & operator=(const Line &ref)//赋值运算符函数
		{
			if(this==&ref)
				return *this;
			_p1=ref._p1;
			_p2=ref._p1;
			return *this;
		}
		float Distance(const Point &p1,const Point &p2);
};
class Point
{
	private:
		int _x,_y;
	public:
		Point(int x=0,int y=0):_x(x),_y(y)//构造函数
		{
		}
		float Distance(const Point  &p1,const Point &p2);
		~Point()//析构函数
		{
		}
		Point(const Point &ref):_x(ref._x),_y(ref._y)//拷贝构造函数
		{
		}
		Point & operator=(const Point &ref)//赋值运算符函数
		{
			if(this==&ref)
				return *this;
			_x=ref._x;
			_y=ref._y;
			return *this;
		}
		friend float Line::Distance(const Point &p1,const Point &p2);
};
float Line::Distance(const Point &p1,const Point &p2)
{
		return hypotf((p2._x-p1._x),(p2._y-p1._y));
}
int  main()
{
	Point p1(1,1),p2(2,2);
	Line line(&p1,&p2); 
	cout<<"the distance between p1 and p2 is :"<<line.Distance(p1,p2)<<endl;
	return 0;
}
