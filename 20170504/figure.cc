/*************************************************************************
    > File Name: figure.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月15日 星期一 11时43分20秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
class figure
{
	public:
		virtual double area()=0;
		virtual void display()=0;
};
void display(figure *p)
{
	p->display();
	cout<<"的面积:" << p->area() << endl;
}

class circle:public figure
{
	private:
		double _r;
	public:
		circle(double r):_r(r)
		{

		}
		virtual  double area()
		{
			return 3.14159*pow(_r,2);
		}
		virtual void display()
		{
			cout<<"circle";
		}

};
class Rectangle:public figure
{
	private:
		double _a,_b,_h;
	public:
		Rectangle(double a,double b,double h):_a(a),_b(b),_h(h)
		{
		}
		virtual double area()
		{
			return (_a+_b)*_h/2;
		}
		virtual void display()
		{
			cout<<"Rectangle";
		}
};

int  main()
{
	circle *a=new circle(10);
	Rectangle *b=new Rectangle(10,10,10);
	display(a);
	display(b);
	return 0;
}

