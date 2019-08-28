#include<iostream>
#include<vector>
#include<atomic>
class C
{
	int a;
	public:
	C()
	{
		std::cout<< "default constructor function \n";
	}
};
int main(void)
{
	int x(0);
	int y=0;
	int z{0};
	int u={0};

	std::vector<int> vec={1,2,3};
	std::vector<int> vec1{1,2,3};
	//std::vector<int> vec2(1,2,3); //不能使用()初始化容器
	//std::vector<int> vec3=1; //不能使用=初始化容器
	
	std::atomic<int> ai1{0};
	std::atomic<int> ai2={0};
	//std::atomic<int> ai3=0; //不可赋值对象，不能使用=初始化
	std::atomic<int> ai4(0);
	
	//int a={1.0};	 //{}禁止隐式缩窄转换
	//int b{1.0};      
	int c=1.0;      // =和()不会禁止缩窄转换
	int d(1.0);

	C c1; //调用无参构造函数
	//C c2();//C++优先认为是一个函数函数声明
	C c3{};//调用无参构造函数
	C c4={};//调用无参构造函数
	C c5=C();//先调用无参构造函数，在调用移动赋值构造函数
	return 0;
}
