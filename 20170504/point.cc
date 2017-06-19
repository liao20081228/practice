/*************************************************************************
    > File Name: point.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月12日 星期五 16时08分55秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
class point
{
	private:
		int _x,_y;
	public:
		point(int x=0,int y=0):_x(x),_y(y)
	{

	}
		void display()
		{
			cout<<_x<<","<<_y<<endl;
		}
};

class point3d :public point
{
	private:
		int _z;
	public:
		point3d(int x,int y,int z):point(x,y),_z(z)
	{

	}
		void print()
		{
			display();
			cout<<","<<_z<<" "<<endl;
		}
};

void test0(point p)
{
	p.display();
}
void test1(point& p)
{
	p.display();
}
void test0(point* p)
{
	p->display();
}
int  main()
{
	point3d p(1,2,3);
	test0(p); /* 派生类适应基类，基类的方法，派生类都可以用，可以把派生类对象赋值给基类对象*/
	test0(&p);/* 可以把派生类对象赋值给基类对象的引用*/
	test1(p);/* 可以把指向派生类的指针赋值给指向基类的指针*/
	return 0;
}
