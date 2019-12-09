#include<infiniband/verbs.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
int main(void)
{
	int ib_dev_num=0;
	struct ibv_device** ib_dev_list=ibv_get_device_list(&ib_dev_num);

	if(!ib_dev_list)
	{
		perror("not find ib device");
		exit(-1);
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

	struct ibv_context* ib_dev_context=ibv_open_device(ib_dev_list[0]);
	if(!ib_dev_context)
	{
		printf("open device failed\n");
		exit(-1);
	}
	
	struct ibv_device_attr * ib_dev_attr=(struct ibv_device_attr*)malloc(sizeof(struct ibv_device_attr));
	assert(0==ibv_query_device(ib_dev_context,ib_dev_attr));
	printf("fw_ver is : %s\n ",ib_dev_attr->fw_ver);
	printf("node_guid is : %lld\n ",ib_dev_attr->node_guid);
	printf("sys_image_guid is : %lld\n ",ib_dev_attr->sys_image_guid);
	printf("max_mr_size is : %ld\n ",ib_dev_attr->max_mr_size);
	printf(" is : %\n ",ib_dev_attr->);

	free(ib_dev_attr);
	ib_dev_attr=NULL;

	
	assert(0==ibv_close_device(ib_dev_context));
	ibv_free_device_list(ib_dev_list);
	return 0;
}

