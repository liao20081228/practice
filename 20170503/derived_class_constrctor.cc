/*************************************************************************
    > File Name: derived_class_constrctor.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月11日 星期四 21时59分41秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
/*
 * 如果派生类缺省构造函数，则基类或缺省，或有无参构造函数，或有全部参数有默认值的有参构造函数
 * 如果派生类有显式构造函数，这基类必须有能够完成基类成员初始化的构造函数
 */
class base1
{
	private:
		int _x,_y;
	public:
		base1()
		{
			cout<<"base1()"<<endl;
		}
		base1(int x):_x(x)
		{
			cout<<"base1(int x)"<<endl;
		}
		base1(int x,int y=0):_x(x),_y(y) /* 如果某个参数带默认值，则之后的每个参数都要带默认值，如果某个参数省略，则之后的参数都要省略*/
		{
			cout<<"base1(int,int)"<<endl;
		}
};
class derived1 :public base1
{
	private:
		int _z;
	public:
		derived1():base1(1,2)
		{
			cout<<"derived1()"<<endl;
		}
};
int  main()
{
	derived1 a;
	return 0;
}
