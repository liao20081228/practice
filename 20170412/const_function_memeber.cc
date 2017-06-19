/*************************************************************************
  > File Name: const_function_memeber.cc
  > Author: liao20081228
  > Mail: liao20081228@126.com 
  > Created Time: 2017年04月14日 星期五 00时01分31秒
 ************************************************************************/
#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
using std::string;
#define Point point
class Point
{
	private:
		int _x,_y;
	public:
		point(int x=0,int y=0):_x(x),_y(y)//构造函数
	{
		cout<<"point(int,int)"<<endl;
	}
#if 0
		void print(/* const Point * const this  */) const
		{
			cout << "void print()const" << endl;
			//_x = 10;//Error
			cout << "(" << _x<< "," << _y<< ")" << endl;
		}
#endif
#if 1
		//const成员函数是有可能修改数据成员的
		void setX(int x)
		{
			_x=x;
		}
		void print()
		{
			cout << "void print()" << endl;
			cout << "(" << _x<< "," << _y<< ")" << endl;
		}
#endif
};
int main(void)
{
	Point pt(1, 2);//非const对象可以使用const成员函数
	pt.print();
	const Point pt2(3,4);//const对象是不能修改其内部数据成员的, 所以
	pt2.print();
	return 0;
}
