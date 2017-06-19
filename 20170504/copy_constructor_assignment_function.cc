/*************************************************************************
    > File Name: copy_constructor_assignment_function.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月12日 星期五 19时15分06秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
/*
 * 如果派生类定义了拷贝构造函数、赋值运算符函数，则拷贝和赋值时，不会再自动调用基类的，只能手动调用
 * 如果派生类没有定义拷贝构造函数、赋值运算符函数，则派生部分采用默认操作，基类部分采取定义的操作
 */
class point  
{
	private:
		int _x,_y;
	public:
		point(int x,int y):_x(x),_y(y)//构造函数
		{
			/*fucntion_body*/
		}
		/*member*/
		~point()//析构函数
		{
			/*fucntion_body*/
		}
		point(const point &lref):_x(lref._x),_y(lref._y)//拷贝构造函数
		{
			cout<<"point(const point &lref)"<<endl;
		}
		 
		point & operator=(const point &lref)//拷贝赋值运算符函数
		{
			cout<<"operator="<<endl;
			if(this!=&lref)
			{
				_x=lref._x;
				_y=lref._y;
			}
			return *this;
		}
		void display()
		{
			cout<<_x<<","<<_y;
			
		}
};
class point3d :  public point
{
	private:
		int _z;
	public:
		point3d(int x=0,int y=0,int z=0):point(x,y),_z(z)//构造函数
		{
			/*fucntion_body*/
		}
		/*member*/
		~point3d()//析构函数
		{
			/*fucntion_body*/
		}
		point3d(const point3d &lref):point(lref),_z(lref._z)/* 派生类定义了拷贝构造函数就不会自动调用基类的，必须手动调用基类拷贝构造函数*/
		{

		}
		point3d & operator=(const point3d &lref) /* 派生类定义了赋值运算符函数就不会自动调用积累的，必须手动调用基类的赋值运算符函数*/
		{
			if(this!=&lref)
			{
				_z=lref._z;
				point::operator=(lref);
			}
			return *this;
		}
		void print()
		{
			display();
			cout<<","<<_z<<endl;
		}
};
class point3d2 :  public point
{
	private:
		int _z;
	public:
		point3d2(int x=0,int y=0,int z=0):point(x,y),_z(z)//构造函数
		{
			/*fucntion_body*/
		}
		/*member*/
		~point3d2()//析构函数
		{
			/*fucntion_body*/
		}
		void print()
		{
			display();
			cout<<","<<_z<<endl;
		}
};

int  main()
{
	point3d test(1,2,3);
	test.print();
	test.display();
	cout<<endl;
	
	point3d test1(test);
	test1.print();
	test1.display();
	cout<<endl;
	point3d test2;
	test2=test;

	point3d2 test3(1,2,3);
	test3.print();
	test3.display();
	cout<<endl;
	
	point3d2 test4(test3);
	test4.print();
	test4.display();
	cout<<endl;

	return 0;
}

