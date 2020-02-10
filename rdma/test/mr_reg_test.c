#include<stdio.h>
#include"get_clock.h"
#include<rdma/rdma_cma.h>
#include<rdma/rdma_verbs.h>
#include<infiniband/verbs.h>
int main()
{
	cycles_t start= 0, end=0;
	double mzh=0;
	double reg[100]={0},max_reg=0,min_reg=0,sum_reg=0,mean_reg=0;
	double dereg[100]={0},max_dereg=0,min_dereg=0,sum_dereg=0,mean_dereg=0;

	while (1)	
	{
		for(int i=0; i< 100;++i)
		{
			mhz=get_cpu_mhz(0);
			start=get_cycles();
			
			end=get_cycles();
				
		}
	
	}
}

