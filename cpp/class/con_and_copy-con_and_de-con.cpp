#include<iostream>
#include<string>
#include<cstring>
class animal
{
	int age;
	char * name;
public:
	//构造函数的作用
		//1.给对象标识 
		//2.数据成员开辟内存
		//3.数据成员初始化
	//1.无返回值，与类同名，可以重载，参数可带默认值，不可主动调用
	animal(int age=0 , char * p):age(age)
	{
		name=new char[std::string(p).length()+1];
		name=p;
	}
	animal(char*p )
	{
		name=new char[std::string(p).length()+1];
		name=p;
	}

	//析构函数：清理动态内存（含有指针数据成员）
	//无返回值，与类同名，不能重载，没有参数，可以主动调用
	~animal(void)
	{
		if (name)
			delete [] name;
	}
	//拷贝构造函数是特殊的构造函数
	//函数按值传递、是返回值、用已有对象初始化另一个对象
	animal(const animal & ref)
	{
		age=ref.age;
		name = new char[std::string(ref.name).length()+1]();
		strcpy(name,ref.name);
	}

	
};
