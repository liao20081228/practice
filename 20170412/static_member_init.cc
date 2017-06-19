/*************************************************************************
    > File Name: static_member_init.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月13日 星期四 20时41分01秒
 ************************************************************************/
#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
using std::string;
class num
{
	private:
		int _x;
	public:
		num(int x=0):_x(x)//构造函数
		{
		}
	void print()
	{
		cout<<_x<<"_"<<endl;
	}
};
class computer
{
	private:
		int _price;
		static int _totalprice;//静态数据成员必须早类外初始化
		static num _x;
	public:
		computer(int price=0):_price(price)//构造函数
		{
			cout<<"这是构造函数"<<endl;
			_totalprice+=price;
		}
		~computer()//析构函数
		{
			cout<<"这是析构函数"<<endl;
		}
		//computer(const computer &ref):_price(ref._price)//拷贝构造函数
		//{
		//}
		//computer & operator=(const computer &ref)//赋值运算符函数
		//{
			//if(this==&ref)
				//return *this;
			//_price=ref._price;
			//return *this;
		//}
		void print(  )
		{
			cout<<_totalprice<<endl;
			_x.print();
	}
};
int computer::_totalprice=0;
num computer::_x(1);
int  main()
{
	computer com(100);
	com.print();
	computer com2 (1000);
	com.print();
	computer com3(100);
	com3.print();
	com2=com3;
	com.print();
	return 0;
}
