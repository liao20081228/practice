#include<iostream>

class test
{
	int a;
	int b;
	public:
	test(int c) :a(c), b(c)
	{
		std::cout<<"constructor" <<std::endl;
	}
	test (test && ref):a(ref.a), b(ref.b)
	{
		std::cout<<"move constructor" <<std::endl;
	}
	test (const test & ref):a(ref.a), b(ref.b)
	{
		  	  std::cout<<"copy constructor" <<std::endl;
	
	}

	test & operator = (const test& ref)
	{
		a=ref.a;
		b=ref.b;
		  	  std::cout<<"copy assign" <<std::endl;
		return *this;
	}
	test & operator = (test&& ref)
	{
		a=ref.a;
		b=ref.b;
		  	  std::cout<<"move assign" <<std::endl;
		return *this;
	}

	~test()
	{
		  	  std::cout<<"deconstructor" <<std::endl;
	}
};


int main(void)
{
	int x= 10;
	test a(x);
	std::cout<<"------------\n";
	test b = test(x);
	std::cout<<"------------\n";
	test c(a);
	std::cout<<"------------\n";
	a = b;
	std::cout<<"------------\n";
	return 0;
}
