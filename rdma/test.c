#include<infiniband/verbs.h>
#include<errno.h>
#include<stdio.h>
int main(void)
{
	struct ibv_device **dev=ibv_get_device_list(NULL);
	
	struct ibv_device * rd1=dev[0];
	
	ibv_free_device_list(dev);

	const char * p=ibv_get_device_name(rd1);
	if(!p) 
		printf("%d",errno);


	return 0;
}
