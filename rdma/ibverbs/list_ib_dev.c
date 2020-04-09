#include<infiniband/verbs.h>
#include<stdio.h>
#include<stdlib.h>
#include<endian.h>


int main(void)
{
	int dev_num = 0;
	struct ibv_device** dev_list = ibv_get_device_list(&dev_num);
	
	if (!dev_list)
	{
		perror("ibv_get_device_list failed()");
		return EXIT_FAILURE;
	}

	if (!dev_num)
		fprintf(stdout, "no RDMA device is found\n");
	
	fprintf(stdout, "%s %s ");
	for(int i = 0; i < dev_num ; ++i)
	{
		fprintf(stdout, "%s:\n", ibv_get_device_name(dev_list[i]));
	}
	fprintf(stdout, "");

	ibv_free_device_list(dev_list);
	return 0;	
}
