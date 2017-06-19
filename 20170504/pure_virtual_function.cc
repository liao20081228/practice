/*************************************************************************
    > File Name: pure_virtual_function.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月14日 星期日 21时29分21秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
class base/* 含有纯虚函数的类是抽象类，不能定义对象，但可以定义指针，和派生新类*/
{
	public:
		virtual void print()=0;/* 纯虚函数的定义形式*/
};
class derived0:public base
{
	public:
};
class derived1:public derived0
{
	public:
		void print()
		{
		cout<<"derived1"<<endl;
		}
};

int  main()
{
	//base a;/* 含有纯虚函数的类是抽象类，不能定义对象，但可以定义指针，和派生新类*/
	base *p;
	//derived0 c; /* 含有纯虚函数的类是抽象类，不能定义对象，但可以定义指针，和派生新类*/
	derived0 *q;
	derived1 c;
	derived1 *r=&c;
	r->print();
	q=&c;
	q->print();
	p=&c;
	p->print();
	return 0;
}
