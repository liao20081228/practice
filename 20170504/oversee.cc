/*************************************************************************
    > File Name: oversee.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月12日 星期五 15时05分19秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
class base
{
	public:
		int _x;
		int _y;
		base(int x,int y):_x(x),_y(y)
		{
		}
		base()
		{}
		void print()
		{
			cout<<_x<<","<<_y<<endl;
		}
};
class derive:public base
{
	public:
		int _x;
		derive():base(1,2),_x(3)
	{}
		void print()
		{
			cout<<_x<<","<<_y<<endl;
		}
};
int  main()
{
	derive a;
	cout<<a._x<<endl;
	cout<<a.base::_x<<endl;
	a.print();
	a.base::print();

	return 0;
}
