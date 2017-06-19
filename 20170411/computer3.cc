/*************************************************************************
    > File Name: computer3.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月12日 星期三 14时00分01秒
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
	public:
		computer(const char *brand,int price):_brand(new char[strlen(brand)+1]),_price(price)//构造函数
		{
			strcpy(_brand,brand);
			cout<<"computer (char *brand,int price)"<<endl;
		}
		~computer()//析构函数
		{
			delete [] _brand;
			cout<<"~computer()"<<endl;
		}
		void print(  )
		{
			cout<<"brand:"<<_brand<<"price:"<<_price<<endl;
		}
};
int main()
{
		computer com("mac",10000);
		com.print();
		//com.~computer();// 不建议显示的调用析构函数有可能会造成double free 错误
		return 0;
}
