#include<iostream>
//const常见用法

//第一种：const代替宏
#define TEST1 1000
const int TEST2=1000; 

//第二种：const 修饰传入指针，防止指针或指针的内容被修改
void fun1(const int* p, int* const p1, const int* const p2)
{//常量指针和指针敞亮的区别
	int a=10;
	*p=100; //不能修改常量指针的容
	p=&a;  //但可以修改常量指针

	p1=&a; //不能修改指针常量
	*p1=100;//但可以修改指针常量的内容

	p2=&a;//不能修改指向常量的指针常量
	*p2=100//也不能修改指向常量的指针常量的内容
}


//第三种： const修视传入引用，防止实参被修改，主要用于传入非内部基本类型时，防止拷贝析构临时变量的开销
void fun2(const int & ref )   //c++没有  int& const ref ,因为引用本身就是不可改变,)
{

	ref=10; //报错
}

//const修饰函数返回值,传值形式，没有作用,因为会自动产生一个返回值的临时拷贝
const int funn()
{
	return 3;
}
//第四种：返回常量指针，只能赋值给常量指针
const int * fun3()
{
	int * a= new int;
	return a;//返回非常量的指针，会自动转为常量指针
}

int * const fun4() //const 没有意义，因为传指针实际是传值
{
	int * a =new int;
       return a;	
}

//第五种：返回常量引用，一般用于类的成员函数(传入了引用)
const int & fun5(int &a )
{
	return a;
}



class bird
{
	
	int wing;
	//第六中：将变量变为常变量
	const int leg;	//const 数据成员必须用初始化表达式 或者 就地初始化，
			//c++11只有静态非常量成员才需要类外初始化
			//c++98只有静态整形常量成员可以就地初始化

	public:
		bird(int wing, int leg):wing(wing),leg(leg)
	{

	}
	void fun()
	{
		wing =10;
	}
	//第七种：const修饰成员函数
	void fun() const//只能读不能修改数据成员，只能调用const成员函数，
	{
		fun();
	}


};

int main(void)
{
	//第六种：C++要求常量字符串必须使用const
	const char* pt="test";
	const int* p = fun3();
	 int* q = fun3(); //常量不能转为非常量,非常量可以自动转为常量
	int a=10;
	int b = fun5(a);

	return 0;
}
