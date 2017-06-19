/*************************************************************************
    > File Name: overload_friend_function.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月17日 星期一 23时30分42秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in /usr/include by user*/
class Test
{
	private:
		int _x,_y;
	public:
		Test(int x=10,int y=1):_x(x),_y(y)
		{
		}
		friend void print(Test p );
};
void print(Test p)
{
	cout<<p._x<<p._y<<endl;
}
void print(Test p1,Test p2)
{
	cout<<p1._x<<p1._y<<endl;
}

int  main()
{
	Test p(0),p1(1,1),p2(2,2);
	print(p);
	print(p2);
	print(p1,p2);
	return 0;
}
