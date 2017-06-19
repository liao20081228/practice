/*************************************************************************
    > File Name: virtual_function_access.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月13日 星期六 23时17分21秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
class base
{
	public:
		void print()
		{
			cout<<"base::print()"<<endl;
		}
		virtual  void display()
		{
			cout<<"base::display()"<<endl;
		}
};
class derived:public base
{
	public:
		void print() /* 派生类和基类的同名成员（除相同虚函数外）发生隐藏*/
		{
			cout<<"derived::print()"<<endl;
		}
		virtual  void display()/* 派生类和基类的相同虚函数会发生覆盖*/
		{
			cout<<"derived::display()"<<endl;
		}
};
class derived1:public derived
{
	public:
		void print() /* 派生类和基类的同名成员（除相同虚函数外）发生隐藏*/
		{
			cout<<"derived1::print()"<<endl;
		}
		virtual  void display()/* 派生类和基类的相同虚函数会发生覆盖*/
		{
			cout<<"derived1::display()"<<endl;
		}
};

/*访问 非虚函数 由指针或引用类型决定，访问虚函数由指针或引用所指对象决定*/
/* 多态发生条件
 *1 基类有虚函数
 *2 派生类覆盖了基类的虚函数
 *3 基类指针指向派生类对象,再利用改指针访问虚函数
 */
void print(base *p)/* 利用基类指针访问非虚函数*/
{
	p->print();
}
void display(base *p)/* 利用基类指针访问虚函数*/
{
	p->display();
}

void print1(base &p)/* 利用基类引用访问非虚函数*/
{
	p.print();
}
void display1(base &p)/* 利用基类引用访问虚函数*/
{
	p.display();
}

void print2(base p)/* 利用基类对象访问非虚函数*/
{
	p.print();
}
void display2(base p)/* 利用基类对象访问虚函数*/
{
	p.display();
}




int  main()
{
	base a;
	derived b;
	derived1 c;
	cout<<" 用基类指针访问非虚函数，调用哪一个取决于指针类型"<<endl;
	print(&a);
	print(&b);
	print(&c);
	 cout<<"用基类指针访问虚函数，调用哪一个取决与所指对象类型"<<endl;
	display(&a);
	display(&b);
	display(&c);
	cout<<"用基类引用访问非虚函数，调用哪一个取决于指针类型"<<endl;
	print1(a);
	print1(b);
	print1(c);
	cout<<" 用基类引用访问虚函数，调用哪一个取决与所指对象类型"<<endl;
	display1(a);
	display1(b);
	display1(c);
	cout<<" 用基类对象访问非虚函数，调用哪一个取决于对象类型"<<endl;
	print2(a);
	print2(b);
	print2(c);
	cout<<"用基类对象访问虚函数，调用哪一个取决与对象类型"<<endl;
	display2(a);
	display2(b);
	display2(c);
	return 0;
}
