#include<stdio.h>
#include"get_clock.h"

struct data
{
	short int nodeid;
	unsigned char senerid;
	unsigned char varid;
	unsigned long long int time;
	unsigned long long int number;
	double data;
};

int main()
{
	printf("%lu\n",sizeof(char));
	printf("%lu\n",sizeof(short));
	printf("%lu\n",sizeof(int));
	printf("%lu\n",sizeof(long int));
	printf("%lu\n",sizeof(long long int));
	printf("%lu\n",sizeof(float));
	printf("%lu\n",sizeof(double ));
	printf("%lu\n",sizeof(long double));
}
