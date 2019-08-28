#include<iostream>
class C
{
	public:
	C(int a,bool b)
	{
		std::cout << "int a,bool b \n";	
	}

	C(int  a,double b)
	{
		std::cout << "int a,double b\n";
	}

	C(std::initializer_list<double> b,int a)
	{
		std::cout << "std::initializer_list<int> b\n";

	}
};

int main(void)
{
	//C W0; //一旦显式提供构造函数，系统就不会提供默认的无参构造函数，如果想要调用就必须显式的提供无参构造函数
	C w1(10,true);
	C w11(10,10.0);

	C w21=C(10,true);
	C w22=C(10,10.0);
	C W23=C{10,true};
	C W24=C{{10,10.0},10};

	C W31={10,true};
	C W32={10,10.0};
	C W41{10,true};
	C W42{10,10.0};
}
