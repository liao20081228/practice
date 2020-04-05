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
		return EXIT_SU

	}
	for(int i = 0; i < dev_num ; ++i)
	{
		printf("%s, %lx", ibv_get_device_name(dev_list[i]), be64toh(ibv_get_device_guid(dev_list[i])));
	}


	ibv_free_device_list(dev_list);
	return 0;	
}
