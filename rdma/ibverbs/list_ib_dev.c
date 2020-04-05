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
	
	fprintf(stdout, "%-24s %-24s %32s %32s, %s, %s ", "device name", "GUID",
		"node type", "transport layer type", "device path", "ib device path");

	for(int i = 0; i < dev_num ; ++i)
	{
	}

	ibv_free_device_list(dev_list);
	return 0;	
}
