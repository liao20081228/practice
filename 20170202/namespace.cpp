//example1实体可见域
#include<iostream>
//using  std::cout;
//using std::endl;
namespace A//创建名称空间A
{
	void dispA()
	{
		std::cout<<"ThisisA"<<std::endl;
	}
}
namespace B//创建名称空间B
{
	void dispB()
	{
		A::dispA();//错误,应为A::dispA()
		std::cout<<"ThisisB"<<std::endl;
	}
}

int  main()
{
	B::dispB();//错误,应为B::dispB();
	return 0;
}

