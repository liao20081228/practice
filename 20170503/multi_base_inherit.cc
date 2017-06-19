/*************************************************************************
    > File Name: multi_base_inherit.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月11日 星期四 20时19分16秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
class A
{
	public:
		void print()
		{
			cout<<"A"<<endl;
		}
};
class B
{
	public:
		void print()
		{
			cout<<"B"<<endl;
		}
};
class C:public A,public B
{
	public:
		void diapaly()
		{
			//print()；/*多基继承时，如果多个基类有同名成员，就会在派生类内部或者外部访问同名成员时，导致二义性，解决方法是使用作用域限定符*/
			A::print();
			B::print();
		}
};
int  main()
{
	C test;
	//test.print(); /* 多基继承时，如果多个基类有相同成员,就会在派生类内部或者外部访问同名成员时，导致二义性，解决方法是使用作用域限定符*/
	test.A::print();
	test.B::print();
	return 0;
}
