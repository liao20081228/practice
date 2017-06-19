/*************************************************************************
    > File Name: virtualinherit.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月16日 星期二 10时24分28秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
/* 虚基派生可以解决共同基派生的二义性问题*/
/* 虚继承的派生类的对象的第一个成员是指向虚基表虚基指针，占用8个字节*/
/* 如果采用虚基派生，则往下所有的派生类都是虚基派生*/
/* 派生类的构造函数要显示调用虚基类的构造函数，如果没有调用虚基类的无参构造函数*/
/* 对虚基类的构造函数的调用先与普通基类*/
class A
{
	public:
		A()
		{
			cout<<"A()"<<endl;
			
		}
};
class base
{
	private:
		int _x;
	public:
		base(int x):_x(x)
	{
		cout<<"base (int x)"<<endl;

	}
		virtual void f()
		{
			cout<<"base :: f()"<<endl;
			
		}
};
class derived:virtual public base
{
	private :
		int _y;
		A _a;
	public:
		derived(int x,int y):_y(y),base(x) 
		{
			cout<<"derived(int ,int )"<<endl;
			
		}
		void fb()
		{
			cout<<"derived ::fb()"<<endl;
		}
};

int  main()
{
	cout<<"sizeof(base)="<<sizeof(base)<<endl;
	cout<<"sizeof(derived)"<<sizeof(derived)<<endl;
	
	derived a(10,20);
	
	return 0;
}
