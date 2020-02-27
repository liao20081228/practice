#include<stdio.h>
#include"get_clock.h"

struct test
{
	short int nodeid;
	unsigned char senerid;
	unsigned char kind;
	unsigned long long int time;
	unsigned long long int number;
	double data;
};

int main()
{
	struct test a[500*8]={0};
	for(int i = 0; i < 500*8;i++)
	{	
		a[i].nodeid=1;
		a[i].time = i;
		a[i].number=i;

		for(int m=0;i<7;i++)
		{
			a[i].senerid=m;
			a[i].data=3.123456+m;
		}
	}
	double mhz= get_cpu_mhz(0);

}
