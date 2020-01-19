#include"get_clock.h"
#include<unistd.h>
#include<stdio.h>
int main(void)
{
	double cpu_freq=get_cpu_mhz(0); 
	cycles_t c1, c2;
	c1=get_cycles();
	sleep(1);
	c2=get_cycles();
	printf("1s= %E us", (c2 - c1 ) / cpu_freq );
	return 0;
}
