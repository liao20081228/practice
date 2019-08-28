#include<iostream>

template<typename T>
class TD;

int main(void)
{
	const int n = 42;
	auto x = n;
	auto y= &n;
	TD<decltype(x)> xtype;
	TD<decltype(y)> ytype;
	return 0;
}
