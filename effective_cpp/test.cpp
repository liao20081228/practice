#include<iostream>
#include<vector>
struct t;

struct t
{
	class iter
	{
		int a;
	};
	int b;


};

template<typename T>
void fun()
{
	t::iter a;	
}


int main(void)
{
	fun<t>();
	return 0;
}
