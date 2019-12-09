#include<infiniband/verbs.h>
#include<errno.h>
#include<stdio.h>
int main(void)
{
	int ib_dev_num=0;
	struct ibv_device ** ib_dev_list=ibv_get_device_list(&ib_dev_num);

	if(!ib_dev_list)
	{
		perror("not find ib device");
	}
	printf("the number of ib device is:%d\n", ib_dev_num);
	for(int i=0;i<ib_dev_num;++i)
	{
		struct ibv_device *it=ib_dev_list[i];
		printf("%s\n", it->name);
		printf("%s\n", it->dev_name);
		printf("%s\n", it->dev_path);
		printf("%s\n", it->ibdev_path);
		printf("the device name is:%s\n ", ibv_get_device_name(it));
		printf("the device guid is:%lld \n ",ibv_get_device_guid(it));
		printf("the node_type is %s\n",ibv_node_type_str(it->node_type));
	}

	ibv_free_device_list(ib_dev_list);
	return 0;
}

