/*************************************************************************
    > File Name: virtualdestuctor.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月15日 星期一 16时31分27秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
/* 如果一个类中有虚函数，则析构函数应该也是虚函数，因为基类指针指向派生类时，只会调用基类的析构函数,*/
/* 而不能调用派生类的析构函数，尤其是类中有动态内存的申请时，构造函数不能是虚函数
 * 析构函数一旦声明为虚函数，则其派生类也自动成为虚析构函数*/
class base 
{
	private:
		int *_p;
	public :
		base(int x):_p(new int[x])
		{
		}
		/*virtual*/  ~base()
		{
			cout<<"base"<<endl;
			delete[]_p;
		}
};
class derived:public base
{
	private:
		int *_q;
	public:
	derived(int x):base(x),_q(new int[x])
	{

	}
	/*virtual*/ ~derived()
	{
		cout<<"derived"<<endl;
		delete[]_q;
	}
};

int  main()
{
	base *p=new derived(10);
	cout<<p<<endl;
	delete p;
	return 0;
}
