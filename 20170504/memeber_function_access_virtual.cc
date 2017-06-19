/*************************************************************************
    > File Name: memeber_function_access_virtual.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月14日 星期日 15时30分24秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
class base
{
	public:
		virtual void print()
		{
			cout<<"base::print()"<<endl;
		}
		void display1()
		{
			this->print();
		}
		void display2()
		{
			base::print();
		}
};
class derived :public base
{
	public:
		void print()
		{
			cout<<"derived :: print()"<<endl;
		}
		void display3()
		{
			this->print();
		}
		void display4()
		{
			derived::print();
		}
};
class base0
{
	public:
		virtual void print()
		{
			cout<<"base::print()"<<endl;
		}
		void display1()
		{
			print();
		}
		void display2()
		{
			print();
		}
};
class derived0 :public base0
{
	public:
		void print()
		{
			cout<<"derived :: print()"<<endl;
		}
		void display3()
		{
			print();
		}
		void display4()
		{
			print();
		}
};



int  main()
{
	cout<<"=====通过对象访问=========="<<endl;
	base a;
	derived b;
	base0 a0;
	derived0 b0;
	cout<<"有this指针和作用与限定符号"<<endl;
	a.display1();
	a.display2();
	b.display3();
	b.display4();
	cout<<"无this指针和作用与限定符号"<<endl;
	a0.display1();
	a0.display2();
	b0.display3();
	b0.display4();
	cout<<endl;

	cout<<"=====通过基类指针访问=========="<<endl;
	cout<<"有this指针和作用域限定符号"<<endl;
	base *pbase;
	pbase=&a; /* 指向基类对象，应该访问基类成员*/
	pbase->display1();
	pbase->display2();
	pbase->print();
	pbase=&b;/* 指向派生类对象，应该访问派生类成员，但是通过作用域限定符的限制也可以访问基类成员*/
	pbase->display1();
	pbase->display2();
	pbase->print();  
	/*pbase->diaplay3();*/ /*基类指针 不能访问派生类非虚函数*/
	/*pbase->display4();*//* 基类指针 不能访问派生类非墟函数*/
	cout<<"无this指针和作用与限定符号"<<endl;
	base0 *pbase0;
	pbase0=&a0;
	pbase0->display1();
	pbase0->display2();
	pbase0->print();
	pbase0=&b0;
	pbase0->display1();
	pbase0->display2();
	pbase0->print();
	/*pabase0->diaplay3();*/ /* 不能访问派生类非虚函数*/
	/*pabase0->display4();*//* 不能访问派生类非墟函数*/
	

	
	return 0;
}
