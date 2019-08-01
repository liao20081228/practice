#include<stdio.h>
union un
{
	int a;/* data */
	int fun(int b)
	{
		return 0;
	}
	short  c;
};


int main(void)
{
	union un a={1};
	a.fun(1);
	printf("%p,%p,%p\n",&a,&a.a,&a.c);
	return 0;
}


