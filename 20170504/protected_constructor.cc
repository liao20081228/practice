/*************************************************************************
  > File Name: protected_constructor.cc
  > Author: liao20081228
  > Mail: liao20081228@126.com 
  > Created Time: 2017年05月14日 星期日 21时56分33秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
/* 所有构造函数是保护成员的类，也是抽象类，不可定义对象，但是可以派生新类*/
class base 
{
	private:
		int _x;
	protected:
		base(int x):_x(x)
	{
		cout<<"base(int x)"<<endl;
	}
	public :
		void display()
		{
			cout<<"base:: _x="<<_x<<endl;
		}
};
class derived:public base
{
	public:
		derived(int x):base(x)
	{
		cout<<"derived(int x )"<<endl;
	}
};
int  main()
{
	//base a(5); /* 不可定义对象*/
	derived a(10);
	return 0;
}
