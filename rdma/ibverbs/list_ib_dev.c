#include<infiniband/verbs.h>
#include<stdio.h>
#include<endian.h>
int main(void)
{
	int dev_num = 0;
	struct ibv_device** dev_list = ibv_get_device_list(&dev_num);
	for(int i = 0; i < dev_num ; ++i)
	{
		printf("%s, %lx", ibv_get_device_name(dev_list[i]), be64toh(ibv_get_device_guid(dev_list[i])));
	}

	return 0;	
}
