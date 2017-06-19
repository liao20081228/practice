/*************************************************************************
    > File Name: friend.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月17日 星期一 21时14分04秒
 ************************************************************************/
#include<myhead>/*myhead.h is a headfile defined in /usr/include by user*/
class Point
{
	private:
		int _x,_y;
	public:
		Point(int x=0,int y=0):_x(x),_y(y)//构造函数
		{
		}
		friend float Distance(const Point  &p1,const Point &p2);
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
};
float Distance(const Point &p1,const Point &p2)
{
	return hypotf((p2._x-p1._x),(p2._y-p1._y));
}
int  main()
{
	Point p1(1,1),p2(2,2);
	cout<<"the distance between p1 and p2 is :"<<Distance(p1,p2)<<endl;
	return 0;
}
