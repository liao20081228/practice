/*************************************************************************
    > File Name: virturalfunction.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月13日 星期六 20时53分12秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
/* 虚函数定义的方式在非静态成员函数原型前加上virtual*/
/* 一个函数在基类中是虚函数，则派生类中始终是虚函数*/
/* 在派生类中要对虚函数重定义，要求与声明完全相同，如果不同则会发生隐藏甚至错误*/
class base
{
	public:
		virtual int func(int x)/* 一个函数在基类中是虚函数，则派生类中始终是虚函数*/
		{
			cout<<"base::func(int x)"<<endl;
			return x;
		}

};
class derived1:public base
{
	public:
		virtual float func(float x) /* 如果虚函数重定义与声明的参数不同，则基类虚函数被隐藏，（基类与派生类有同名成员（相同的虚函数除外），就会导致隐藏，可以通过作用域限定符解决））*/
		{
			cout<<"derived ::func(float x )"<<endl;
			return (float)x;
		}
};
class derived2:public base
{
	public:
	virtual int func (int x)  /* 在派生类中仍然是虚函数，即使不加virtual关键字*/
		{
			cout<<"derived2::func(int x)"<<endl;
			return x;
		}
};

class derived3:public base
{
	public:
		//float func (int x)  /* 仅仅是返回值类型不同，不能构成覆盖也不能构成隐藏，只能导致错误*/
		/*{*/
			/*cout<<"derived2::func(int x)"<<endl;*/
			/*return x;*/
		/*}*/
};

int  main()
{
	derived1 test1;
	test1.func(5);
	test1.base::func(5);
	derived2 test2;
	test2.func(5);
	test2.base::func(5);
	return 0;
}
