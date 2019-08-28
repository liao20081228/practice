 #include<iostream>
template<typename T>
void f0(T n)
{
	std::cout << n << std::endl;
}



template<typename T>
void f1(const T n)
{
	std::cout << n << std::endl;
}

template<typename T>
void f2(T& n)
{
	std::cout << n << std::endl;
}

template<typename T>
void f3(const T& n)
{
	std::cout << n << std::endl;
}

template<typename T>
void f4(T* n)
{
	std::cout << n << std::endl;
}
template<typename T>
void f5(T* n)
{
	std::cout << n << std::endl;
}

template<typename T>
void f6(const T* n)
{
	std::cout << n << std::endl;
}

template<typename T>
void f7(const T*const n)
{
	std::cout << n << std::endl;
}


template<typename T>
void f8(const T&& n)
{
	std::cout << n << std::endl;
}

template<typename T>
void f9(T&& n)
{
	std::cout << n << std::endl;
}



void fun(int n)
{
	std::cout<<n<<std::endl;
}




int main(void)
{
	int x=27;
	const int cx=x;
	const int& rx=x;
	const int* p1=&x;
	const int* const p2 =&x;
	const char array[]="I Love You";

	f0(x);
	f0(cx);
	f0(rx);
	f0(&x);
	f0(p1);
	f0(p2);
	f0(array);
	f0(fun);

	f1(x);
	f1(cx);
	f1(rx);
	f1(&x);
	f1(p1);
	f1(p2);
	f1(array);
	f1(fun);

	
}
