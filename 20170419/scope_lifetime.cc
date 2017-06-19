/*************************************************************************
  > File Name: scope_lifetime.cc
  > Author: liao20081228
  > Mail: liao20081228@126.com 
  > Created Time: 2017年04月20日 星期四 21时20分02秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
namespace A /* 命名空间作用域在整个程序，因此不能有同名的命名空间*/
{
	class line
	{
		private:
			class lineimpl;/* 类中类也可以在类内声明，类外实现*/
			lineimpl * _pimpl;
		public:
			line(int x1,int y1,int x2,int y2);//构造函数
			void print();
			~line();//析构函数
	};
	class line::lineimpl 
	{
		private:
			class point/* 定义在类，结构体，联合体中的类，结构体，联合体，相当于一个成员，其作用域只在该自定义类型，只有公共部分的成员才在定义内和定义外都可见性*/
			{
				private:
					int _x,_y;
				public:
					point(int x,int y):_x(x),_y(y)
				{
				}
					void print(/*arguments*/)
					{
						cout<<"("<<_x<<","<<_y<<")";
					}
			};
			point _p1,_p2;
		public:
			lineimpl(int x1, int y1, int x2, int y2):_p1(x1,y1),_p2(x2,y2)
		{
		}
			void print()
			{
				_p1.print();
				cout<<"---------------->";
				_p2.print();
				cout<<endl;
			}
	};
	line::line(int x1,int y1,int x2,int y2):_pimpl(new lineimpl(x1,y1,x2,y2))
	{	
	}
	line::~line()
	{
		delete _pimpl;
	}
	void line::print()
	{
		_pimpl->print();
	}
};
int  main()
{
	A::line l(1,2,3,4);
	l.print();
	return 0;
}

