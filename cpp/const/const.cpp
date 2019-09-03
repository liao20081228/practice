#include<iostream>

//const代替宏
#define TEST1 1000
const int TEST2=1000; 

//const 修饰传入指针，防止指针或指针的内容被修改
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


//const修视传入引用，防止实参被修改，主要用于传入非内部基本类型时，防止拷贝析构临时变量的开销
void fun2(const int & ref )   //c++没有  int& const ref ,因为引用本身就是不可改变,)
{

	ref=10; //报错
}

//const修饰函数返回值,
//返回常量指针，只能白指针赋值给同样的常量指针
const int * fun3()
{
	int * a= new int;
	return a;
}

int * const fun4() //const 没有意义
{
	int * a =new int;
       return a;	
}

//返回常量引用，一般用于类的成员函数(传入了引用)
const int & fun5(int &a )
{
	return a;
}


class bird
{
	int wing;
	int leg;

	public:
		bird(int wing, int leg):wing(wing),leg(leg)
	{

	}


};

int main(void)
{
	const int* p = fun3();
	 int* q = fun3(); //常量不能转为非常量
	int a=10;
	int b = fun5(a);

	return 0;
}
