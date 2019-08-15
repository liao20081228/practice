/***************************************************************************************90
    > File Name: cpp11_lambda.cpp
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年07月26日 星期三 14时44分31秒
*****************************************************************************************/
#include<myhead_cpp.h>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
//c++11新增lambda表达式
//[capture list](parameter list) mutable exception attribution->retvaltype{expr};
//除了捕获列表表达式体都可省略
//默认不可改变父作用域的变量，如果要改变则需要设置mutable，此时（）不可省略
//exception 为异常申明
//默认为inline函数，应该尽量短小
//返回值类型可以省略，由return推测，如果没有return则是void
//捕获列表[var1,&var2]值传递捕获var1，引用传递捕获var2，[=]值传递捕获所有，[&]引用传递捕获所有，[this]捕获this指针，[]不捕获
void lambda(void)
{
	int a = 10;
	int b = 20;
	std::function<int(int,int)> sum = [](int a,int b) mutable noexcept(true) ->int {return a + b;};//如果出现异常调用std::teminate()函数，可用set_terminate()设置
	cout<< sum(a,b) << endl;
	//sum = [&sum](a,b) mutable noexcept ->int {return a+b;};//与noexcept(ture)一样
	//sum = [&sum](a,b) mutable throw() ->int {return a+b;};//如果抛出异常则调用std::unexcepted()函数，该函数也可能抛出异常
}


template<typename T>//将一个表示符号定义为类型标识符
auto  retvaltrace(T a, T b)->decltype(a+b)  //auto 类型自动推导，->返回值追踪
{
	typedef int int8;//给已有标识符取一个新名字
	decltype(a) sum = a + b;  //返回表达式的类型
	cout<< typeid(sum).name() << endl; //返回type_info，name()方法可以看类型
	cout << (typeid(sum) == typeid(int8)) <<endl;//重载了==与！=
	return sum;
}



int main(void)
{
	lambda();
	retvaltrace<int>(10,2);
	return 0;
}
