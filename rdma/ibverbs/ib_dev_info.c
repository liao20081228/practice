#include<infiniband/verbs.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<getopt.h>
#include<unistd.h>
int get_attr(struct ibv_device* device)
{








	return 0;
}

int main(int argc , char* argv[])
{
	char devname[512] = {0};
	int  port = 1;
	int ch = 0;
	while((ch = getopt(argc, argv, "d:p:") != -1)
	{

	}

	ibv_fork_init();
	int num = 0;
	struct ibv_device** dev_list = ibv_get_device_list(&num);
	if (!dev_list)
	{
		perror("ibv_get_device_list");
		exit(errno);
	}
	for (int i = 0; i < num; ++i)
	{
		if (get_attr(dev_list[i]))
		{
			goto err;
		}
	}
err:
	ibv_free_device_list(dev_list);
}
