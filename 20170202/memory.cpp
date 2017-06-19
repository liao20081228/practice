/******
    > File Name: memory.cpp
> Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月04日 星期六 16时03分00秒
 ************************************************************************/

#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

class computer
{
	private:
			string _name;
			float _price;
			inline void Setprice(float price)
			{
				_price=price;
			}//私有成员函数，内联函数,类内实现
	public:
			void Print();//共有函数成员，类外实现
			void Setbrand(string name);
};
void computer::Print()
{
	Setprice(5000);
	cout<<"brand:"<<_name<<" "<<"price:"<<_price<<endl;
}
void computer::Setbrand(string name)
{
	_name=name;
}

int main()
{
	computer com;
	string p="thinkpad";
	com.Setbrand(p);
	com.Print();
	return 1;
}
