/*************************************************************************
    > File Name: virtual_sizeof.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月14日 星期日 11时34分13秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
/* 如果基类中有虚函数，则对象的第一个成员是虚函数指针，大小增加8字节，当一个类中有多个虚函数时也只会有一个虚函数指针
 * 当采用虚拟继承时，会再增加8个字节
 * */
class base0
{
	int _x;
	public:
	 void print()
		{
			cout<<"base::print()"<<endl;
		}
};
class base1
{
	int _x;
	public:
		virtual void  print()  /* 如果有虚函数，对象的第一个成员是指向虚函数表的指针,大小增加8个字节*/
		{
			cout<<"base::print()"<<endl;
		}
};
class base2
{
	int _x;
	public:
		virtual void  print()
		{
			cout<<"base::print()"<<endl;/* 即使虚函数有多个也只有一个虚指针*/
		}
		virtual void  display()
		{
			cout<<"base::display()"<<endl;
		}
};

class derived0 : public base0
{
	public:
		/*void pint()*/
		/*{*/
			/*cout<<"derived::print()"<<endl;*/
		/*}*/
};
class derived1 : public base0
{
	public:
		void print()  /* 对base0 隐藏，基类和派生类的同名成员（除了相同的虚函数之外）会发生隐藏*/
		{
			cout<<"derived::print()"<<endl;
		}
};
class derived2 : public base1
{
	public:
		/*void pint()*/
		/*{*/
			/*cout<<"derived::print()"<<endl;*/
		/*}*/
};
class derived3 : public base1
{
	public:
		void print()  /* 对base1 覆盖*/
		{
			cout<<"derived::print()"<<endl;
		}
};
class derived4 : public base1
{
	public:
		void print()  /* 对base1 会发生覆盖且新增了虚函数*/
		{
			cout<<"derived4::print()"<<endl;
		}
		virtual void display()
		{
			cout<<"derived4 ::display()"<<endl;
		}
};
class derived5 : virtual public base1
{
	public:
		void print()  /* 对base1 会发生覆盖且新增了虚函数,采用虚基继承会增加8字节*/
		{
			cout<<"derived4::print()"<<endl;
		}
};
class derived6 : virtual public base1
{
	public:
		void print()  /* 对base1 会发生覆盖且新增了虚函数,采用虚基继承会增加8字节*/
		{
			cout<<"derived4::print()"<<endl;
		}
		virtual void display()
		{
			cout<<"derived4 ::display()"<<endl;
		}
};
class derived7 : public base1
{
	public:
		virtual void display()
		{
			cout<<"derived4 ::display()"<<endl;
		}
};

int  main()
{
	cout<<"sizeof(base0)"<<sizeof(base0)<<endl;
	cout<<"sizeof(base1)"<<sizeof(base1)<<endl;
	cout<<"sizeof(base2)"<<sizeof(base2)<<endl;
	cout<<"sizeof(derived0)"<<sizeof(derived0)<<endl;
	cout<<"sizeof(derived1)"<<sizeof(derived1)<<endl;
	cout<<"sizeof(derived2)"<<sizeof(derived2)<<endl;
	cout<<"sizeof(derived3)"<<sizeof(derived3)<<endl;
	cout<<"sizeof(derived4)"<<sizeof(derived4)<<endl;
	cout<<"sizeof(derived5)"<<sizeof(derived5)<<endl;
	cout<<"sizeof(derived6)"<<sizeof(derived6)<<endl;
	cout<<"sizeof(derived7)"<<sizeof(derived7)<<endl;
	return 0;
}
