/*************************************************************************
    > File Name: const_member.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月13日 星期四 17时57分38秒
 ************************************************************************/
#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
using std::string;
class point
{
	private:
		const int _x,_y;
	public:
		/*point(int x,int y)//构造函数
		{
			_x=x;
			_y=y;
		}*/
		point(int x,int y):_x(x),_y(y)//构造函数，const成员只能在初始化列表中设置
		{
		}
		void print(  )
		{
			cout<<"(x,y)"<<_x<<","<<_y<<endl;
		}
};
int  main()
{
	point p(1,2);
	p.print();
	return 0;
}
