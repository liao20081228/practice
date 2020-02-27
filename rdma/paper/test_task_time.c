#include<stdio.h>
#include"get_clock.h"
#include<stdlib.h>
#include<time.h>
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
	srand(time(NULL));
	struct test a[4080]={0};
	for(int i = 0; i < 4000;i++)
	{	
		a[i].nodeid=3;
		a[i].time = i;
		a[i].number=i;
		a[i].kind=1;
		for(int m=1;i<9;i++)
		{
			a[i].senerid=m;
			a[i].data=rand()/(double)RAND_MAX+1;
		}
	}
	for(int i = 4000; i < 4080;i++)
	{	
		a[i].nodeid=3;
		a[i].time = i;
		a[i].number=i;
		a[i].kind=2;
		for(int m=0;i<7;i++)
		{
			a[i].senerid=m;
			a[i].data=3.123456+m;
		}
	}
double arg=0;
for(int k=0;k<100;k++)
{
	double arg_500_1=0;
	double arg_500_2=0;
	double arg_500_3=0;
	double arg_500_4=0;
	double arg_500_5=0;
	double arg_500_6=0;
	double arg_500_7=0;
	double arg_500_8=0;
	double arg_10_1=0;
	double arg_10_2=0;
	double arg_10_3=0;
	double arg_10_4=0;
	double arg_10_5=0;
	double arg_10_6=0;
	double arg_10_7=0;
	double arg_10_8=0;
	double mhz= get_cpu_mhz(0);
	cycles_t s=get_cycles();
	for(int i=0; i<4080;i++)
	{
		switch(a[i].nodeid)
		{
			case 1:
				switch(a[i].kind)
				{
					case 1:
						switch(a[i].senerid)
						{
							case 1:
								arg_500_1+=a[i].data;
								break;
							case 2:
								arg_500_2+=a[i].data;
								break;
							case 3:
								arg_500_3+=a[i].data;
								break;
							case 4:
								arg_500_4+=a[i].data;
								break;
							case 5:
								arg_500_5+=a[i].data;
								break;
							case 6:
								arg_500_6+=a[i].data;
								break;
							case 7:
								arg_500_7+=a[i].data;
								break;
							case 8:
								arg_500_8+=a[i].data;
								break;
							default:break;
						}
						break;
					case 2:
						switch(a[i].senerid)
						{
							case 1:
								arg_10_1+=a[i].data;
								break;
							case 2:
								arg_10_2+=a[i].data;
								break;
							case 3:
								arg_10_3+=a[i].data;
								break;
							case 4:
								arg_10_4+=a[i].data;
								break;
							case 5:
								arg_10_5+=a[i].data;
								break;
							case 6:
								arg_10_6+=a[i].data;
								break;
							case 7:
								arg_10_7+=a[i].data;
								break;
							case 8:
								arg_10_8+=a[i].data;
								break;
							default:break;
						}
						break;
					default:break;
				}
				break;
			case 2:
				switch(a[i].kind)
				{
					case 1:
						switch(a[i].senerid)
						{
							case 1:
								arg_500_1+=a[i].data;
								break;
							case 2:
								arg_500_2+=a[i].data;
								break;
							case 3:
								arg_500_3+=a[i].data;
								break;
							case 4:
								arg_500_4+=a[i].data;
								break;
							case 5:
								arg_500_5+=a[i].data;
								break;
							case 6:
								arg_500_6+=a[i].data;
								break;
							case 7:
								arg_500_7+=a[i].data;
								break;
							case 8:
								arg_500_8+=a[i].data;
								break;
							default:break;
						}
						break;
					case 2:
						switch(a[i].senerid)
						{
							case 1:
								arg_10_1+=a[i].data;
								break;
							case 2:
								arg_10_2+=a[i].data;
								break;
							case 3:
								arg_10_3+=a[i].data;
								break;
							case 4:
								arg_10_4+=a[i].data;
								break;
							case 5:
								arg_10_5+=a[i].data;
								break;
							case 6:
								arg_10_6+=a[i].data;
								break;
							case 7:
								arg_10_7+=a[i].data;
								break;
							case 8:
								arg_10_8+=a[i].data;
								break;
							default:break;
						}
						break;
					default:break;
				}
				break;
			case 3:
				switch(a[i].kind)
				{
					case 1:
						switch(a[i].senerid)
						{
							case 1:
								/*arg_500_1+=a[i].data;*/
								break;
							case 2:
								/*arg_500_2+=a[i].data;*/
								break;
							case 3:
								/*arg_500_3+=a[i].data;*/
								break;
							case 4:
								/*arg_500_4+=a[i].data;*/
								break;
							case 5:
								/*arg_500_5+=a[i].data;*/
								break;
							case 6:
								/*arg_500_6+=a[i].data;*/
								break;
							case 7:
								/*arg_500_7+=a[i].data;*/
								break;
							case 8:
								/*arg_500_8+=a[i].data;*/
								break;
							default:break;
						}
						break;
					case 2:
						switch(a[i].senerid)
						{
							case 1:
								/*arg_10_1+=a[i].data;*/
								break;
							case 2:
								/*arg_10_2+=a[i].data;*/
								break;
							case 3:
								/*arg_10_3+=a[i].data;*/
								break;
							case 4:
								/*arg_10_4+=a[i].data;*/
								break;
							case 5:
								/*arg_10_5+=a[i].data;*/
								break;
							case 6:
								/*arg_10_6+=a[i].data;*/
								break;
							case 7:
								/*arg_10_7+=a[i].data;*/
								break;
							case 8:
								/*arg_10_8+=a[i].data;*/
								break;
							default:break;
						}
						break;
					default:break;
				}
				break;
			default:
				break;
		}
	}
	/*printf("%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",arg_500_1/500,arg_500_2/500,arg_500_3/500,arg_500_4/500,arg_500_5/500,arg_500_6/500,arg_500_7/500,arg_500_8/500);*/
	/*printf("%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",arg_10_1/80,arg_10_2/80,arg_10_3/80,arg_10_4/80,arg_10_5/80,arg_10_6/80,arg_10_7/80,arg_10_8/80);*/
	cycles_t e=get_cycles();
	arg = arg+(e-s)/mhz;
}
printf("========     %lf=============\n",arg/100);

for(int i=0;i<4080;++i)
{
	printf("%lf,%hu,%d,%llu,%d,%llu\n",a[i].data,a[i].nodeid,a[i].kind,a[i].time,a[i].senerid,a[i].number);
}

}
