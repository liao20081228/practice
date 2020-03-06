#include<iostream>

class test
{
	int a;
	int b;
	public:
	test(int& a) :a(a), b(a)
	{
		std::cout<<"constructor" <<std::endl;
	}
	test (test && ref):a(ref.a), b(ref.b)
	{
		std::cout<<"move constructor" <<std::endl;
	}
};


int main(void)
{
	int a= 10;
	test b=test(a);
	return 0;
}
