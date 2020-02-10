#include<stdio.h>
#include"get_clock.h"
#include<rdma/rdma_cma.h>
#include<rdma/rdma_verbs.h>
#include<infiniband/verbs.h>
int main()
{
	cycles_t start= 0, end=0;
	double mhz=0;
	double reg=0,max_reg=0,min_reg=0,sum_reg=0,mean_reg=0;
	double dereg=0,max_dereg=0,min_dereg=0,sum_dereg=0,mean_dereg=0;
	
	struct ibv_device ** dev_list=ibv_get_device_list(NULL);
	struct ibv_context* context= ibv_open_device(dev_list[0]);
	ibv_free_device_list(dev_list);
	struct ibv_pd* pd=ibv_alloc_pd(context);	


	printf("mr size\tmax_reg\tmin_reg\tmean_reg\tmax_dereg\tmin_dereg\tmean_dereg\n");
	for(int k = 1; k<=64*1024*1024;k*=2)
	{
		for(int i=0; i< 100;++i)
		{
			mhz=get_cpu_mhz(0);
			start=get_cycles();
							
			end=get_cycles();
			reg=(end-start)/mhz;
			sum_reg+=reg;
			if(max_reg<reg)
				max_reg=reg;
			if(min_reg>reg)
				min_reg=reg;

			mhz=get_cpu_mhz(0);
			start=get_cycles();
			//dereg	
			end=get_cycles();
			dereg=(end-start)/mhz;
			sum_dereg+=dereg;
			if(max_dereg<reg)
				max_dereg=reg;
			if(min_dereg>reg)
				min_dereg=reg;		
		}
		mean_reg=sum_reg/100;
		mean_dereg=sum_dereg/100;
		printf("%d\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n",k,max_reg,min_reg,mean_reg,
							max_dereg,min_dereg,mean_dereg);
	}
}

