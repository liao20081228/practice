#include<cctype>
#include<iostream>
int main(void)
{
	char ch=0;
	int a=0,
	    b=0,
	    c=0,
	    d=0;
	while((ch=std::cin.get())!='\n')
	{
		if (isalpha(ch))
			++a;
		else if (isdigit(ch))
			++b;
		else if (ch==' ')
			++c;
		else
			++d;
	}
	std::cout <<  a <<","<<b<<","<<c<<","<<d<<std::endl;
	return 0;
}
