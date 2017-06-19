/*************************************************************************
    > File Name: same_base_inherit.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月11日 星期四 20时48分07秒
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
class B1:public A
{

};
class B2:public A
{

};

class C:public B1,public B2
{
	public:
		void dispaly()
		{
			//print();/* 在多条继承路径上有一个共同基类，在派生类内部或者外部在访问成员时，会造成访问路径二义性问题*/
			B1::print();
			B2::print();
		}
};

int  main()
{
	C test;
	//test.print();/* 在多条继承路径上有一个共同基类，在派生类内部或者外部在访问成员时，会造成访问路径二义性问题*/
	//test.A::print();
	test.B1::print(); /* 解决方式是指明具体路径*/
	test.B2::print();
		return 0;
}
