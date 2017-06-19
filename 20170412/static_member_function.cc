/*************************************************************************
  > File Name: static_member_function.cc
  > Author: liao20081228
  > Mail: liao20081228@126.com 
  > Created Time: 2017年04月13日 星期四 21时14分58秒
 ************************************************************************/
#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
using std::string;
class computer
{
	private:
		char *_brand;
		int _price;
		static int _totalprice;
	public:
		computer(const char *brand,int price=0):_brand(new char[strlen(brand)+1]),_price(price)//构造函数
	{
		_totalprice+=_price;
		strcpy(_brand,brand);
	}
		~computer()//析构函数
		{
			_totalprice-=_price;
			delete []_brand;
		}
		computer(const computer &ref):_brand(new char[strlen(ref._brand)+1]),_price(ref._price)//拷贝构造函数
	{
		strcpy(_brand,ref._brand);
	}
		computer & operator=(const computer &ref)//赋值运算符函数
		{
			if(this==&ref)
				return *this;
			delete []_brand;
			_brand=new char[strlen(ref._brand)+1];
			strcpy(_brand,ref._brand);
			return *this;
		}
		static void printTotal()
		{
			cout<<"totalprice:"<<_totalprice<<endl;
			//cout<<"brand:"<<_brand<<" "<<"price:"<<_price<<endl;静态成员函数只能访问静态数据成员和静态成员函数。
			//print();
		}
		void print()
		{
			cout<<"brand:"<<_brand<<" "<<"price:"<<_price<<endl;
		}
		static void print(computer &com)
		{
			cout<<"brand:"<<com._brand<<" "<<"price:"<<com._price<<endl;
		}
};
int computer::_totalprice=0;
typedef computer Computer;
int  main()
{
	computer pc1("IBM",7000);
	Computer::print(pc1);
	cout << "购买电脑１之后:";
	Computer::printTotal();//静态成员函数可以直接使用类名调用
	Computer pc2("ASUS", 5000);
	Computer::print(pc2);
	cout << "购买电脑2之后:";
	Computer::printTotal();//静态成员函数可以直接使用类名调用
	{
		Computer pc3("MAC", 10000);
		Computer::print(pc3);
		cout << "购买电脑3之后:";
		Computer::printTotal();//静态成员函数可以直接使用类名调用
	}
	cout << endl;
	cout << "退还电脑3之后:";
	Computer::printTotal();//静态成员函数可以直接使用类名调用
	return 0;
}
