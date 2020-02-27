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
