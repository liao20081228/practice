/*************************************************************************
    > File Name: computer1.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月12日 星期三 10时24分30秒
 ************************************************************************/
#include<myhead_cpp.h>/*myhead.h is a headfile defined in /usr/include*/
#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using namespace std;
class computer
{
	private:
		string _brand;
		float _price;
		void setprice(float price)
		{
			_price=price;
		}
	public:
		void print()
		{
			cout<<"brand:"<<_brand<<endl;
			cout<<"price:"<<_price<<endl;
		}
		void setbrand(const char* brand)
		{
			_brand.assign(brand);
		}
	protected:
		/* member */
};
int  main()
{
	computer com;
	com.setbrand("dell");
	//com.setprice(104.41);
	com.print();
	return 0;
}

