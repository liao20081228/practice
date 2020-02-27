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
	struct test a[4080]={0};
	for(int i = 0; i < 4080;i++)
	{	
		a[i].nodeid=3;
		a[i].time = i;
		a[i].number=i;

		for(int m=0;i<7;i++)
		{
			a[i].senerid=m;
			a[i].data=3.123456+m;
		}
	}
	double mhz= get_cpu_mhz(0);
	cycles_t s=get_cycles();
	double arg_500_1;
	double arg_500_2;
	double arg_500_3;
	double arg_500_4;
	double arg_500_5;
	double arg_500_6;
	double arg_500_7;
	double arg_10_1;
	double arg_10_1;
	double arg_10_2;
	double arg_10_3;
	for(int i=0; i<4080;i++)
	{
		switch(a[i].nodeid)
		{
			case 1:
				printf("%d\n",a[i].nodeid);
				switch(a[i].kind)
				{
					case 1:
						printf("%d\n",a[i].kind);
						switch(a[i].number)
						{
							case 1: 
								switch(a[i].senerid)
								{
									case 1:

								}
						}
				}
		}
	}
}
