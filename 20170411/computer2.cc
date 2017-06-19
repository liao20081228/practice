/*************************************************************************
    > File Name: computer2.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月12日 星期三 10时55分39秒
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
		string _brand;
		float _price;
	public:
		void setbrand(const char* brand);
		void setprice(float price);
		void print()
		{
			cout<<"brand:"<<_brand<<"\n"<<"price"<<_price<<endl;
			
		}
};
void  computer::setbrand(const char *brand)
{
	_brand.assign(brand);
}
void computer::setprice(float price)
{
	_price=price;
}
int  main()
{
	computer com;
	com.setbrand("dell");
	com.setprice(100);
	com.print();
	return 0;
}

