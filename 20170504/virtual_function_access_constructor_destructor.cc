/*************************************************************************
    > File Name: virtual_function_access_constructor_destructor.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月14日 星期日 18时16分36秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
/* 在构造函数和析构函数中访问虚函数是静态联编，默认情况访问自己的虚函数，如果不存在，
 * 则访问基类的虚函数，但不会访问派生类的虚函数
 */


class base
{
	private:
		int _x;
	public:
		base(int x=0):_x(x)
		{
			cout<<"base(int x) ";
			print();
		}
		~base()
		{
			cout<<"~base()  ";
			print();
		}
		virtual void print()
		{
			cout<<"base::_x="<<_x<<endl;
		}
};
class derived:public base
{
	private:
		int _y;
	public:
		derived(int x=0,int  y=0):base(x),_y(y)
		{
			cout<<"derived(int x,int y)   ";
			this->print();
		}
		~derived()
		{
			cout<<"~derived()  ";
			this->print();
		}
		virtual void print()
		{
			cout<<"derived:: _y="<<_y<<endl;
		}
};
class derived1:public base
{
	private:
		int _y;
	public:
		derived1(int x=0,int  y=0):base(x),_y(y)
		{
			cout<<"derived1(int x,int y)   ";
			this->print();
		}
		~derived1()
		{
			cout<<"~derived1()  ";
			print();
		}
};

int  main()
{
	cout<<"通过对象访问"<<endl;
	base a(5);
	derived b(10,15);
	derived1 c(20,25);
	cout<<endl;
	
	a.print();
	b.print();
	c.print();
	cout<<endl;
	
	cout<<"通过指针访问"<<endl;
	base *p;
	
	p=&a;
	p->print();
	cout<<endl;
	
	p=&b;
	p->print();
	cout<<endl;
	
	p=&c;
	p->print();
	cout<<endl;
	return 0;
}
