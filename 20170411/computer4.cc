/*************************************************************************
    > File Name: computer4.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月12日 星期三 22时08分11秒
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
		~computer()//析构函数
		{
			cout<<"这是析构函数~computer"<<endl;
			delete _brand;//因为构造函数申请了新空间，则析构函数必须释放
		}
		computer(const char *brand,int price):_brand(new char[strlen(brand)]),_price(price)//构造函数
		{
			cout<<"这是构造函数computer(char *brand,int price)"<<endl;
			strcpy(_brand,brand);
		}
	 computer()//默认构造函数
	 {
		 cout<<"这是默认构造函数computer()"<<endl;
	 }
	 void print();// 类内声明，类外实现
	/*computer(const computer &ref):_brand(ref._brand),_price(ref._price)//默认构造函数使用搁浅拷贝
	{
		cout<<"这是默认的构造函数使用浅拷贝，当数据成员中有指针会导致析构函数double free错误"<<endl;
	}*/
	 computer(const computer &ref);//深拷贝构造函数,当数据成员中有指针时使用
};
computer ::computer(const computer &ref):_brand(new char[strlen(ref._brand)]),_price(ref._price)
{
	strcpy(_brand,ref._brand);
	cout<<"拷贝构造函数深拷贝"<<endl;
}
 void computer:: print()
{
	 cout<<"brand:"<<_brand<<"\n"<<"price:"<<_price<<endl;
}
int  main()
{
	cout<<"com1"<<endl;
	computer com1;
	//com1.print();//有指针时，默认构造函数不会对指针初始化，因此打印出错
	cout<<"com2"<<endl;
	computer com2("dell",1000);
	com2.print();
	cout<<"com3"<<endl;
	computer com3(com2);
	com3.print();
	cout<<"com4"<<endl;
	computer com4=com2;
	com4.print();
	return 0;
}
