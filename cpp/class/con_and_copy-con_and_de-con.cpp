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
	animal(const char* p ,int age=0):age(age) //如果一个参数带有默认参数，则之后的参数都要带有默认参数
	{
		name=new char[std::string(p).length()+1];
		strcpy(name,p);
		name=const_cast<char*>(p);
		std::cout<<"构造函数" <<std::endl;
	}

	//析构函数：清理动态内存（含有指针数据成员）
	//无返回值，与类同名，不能重载，没有参数，可以主动调用
	~animal(void)
	{
		if (name)
			delete [] name;
		std::cout << "析构函数" <<std::endl;
	 }
	//拷贝构造函数是特殊的构造函数
	//函数按值传递、是返回值、用已有对象初始化另一个对象
	animal(const animal & ref)
	{
		age=ref.age;
		name = new char[std::string(ref.name).length()+1]();
		strcpy(name,ref.name);
		std::cout << "拷贝构造函数" <<std::endl;
	}
	//运算符函数
	//默认提供赋值运算符函数
	//将一个已经对象赋值给另一个已经存在对象时调用
	animal& operator = (const animal& ref)
	{
		if (this == &ref)
		{
			std::cout<< "自赋值" <<std::endl;
			return *this;
		
		}
		delete []name;
		name= new char[strlen(ref.name)+1];
		strcpy(name,ref.name);
		std::cout << "赋值运算符函数" << std::endl;
		 return *this;
	}
};

int fun1(animal a)
{
	return 0;
}

int fun2(animal & a)
{
	return 0;
}
int fun3(animal* a)
{
	return 0;
}

int main(void)
{
	animal a("bird",10);
	animal b("bird");

	animal c=a;
	animal d(b);
	
	a=b;

	fun1(c);
	fun2(c);
	fun3(&c);
	return 0;
}





