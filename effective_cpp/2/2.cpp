#include<iostream>

template<typename T>
void f(T n)
{

}


template<typename T>
void f(std::initializer_list<T> n)
{

}

auto createinitiallist()
{
	return {1,2,3};
}


int main(void)
{
	auto x=27;
	const auto cx=x;
	const auto& rx=x;
	auto&& uref1=x;
	auto&& uref2=cx;
	auto&& uref3=27;

	const char name[]="Ilove you";
	auto arr1=name;
	auto& arr2=name;
	auto* arr3=&name;


	auto x2(27);
	auto x3={27};
	auto x4{27};

	f({1,2,3 });

	std::initializer_list<int> a=createinitiallist();
	return 0;
}
