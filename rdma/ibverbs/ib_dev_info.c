#include<infiniband/verbs.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<getopt.h>
#include<unistd.h>


#ifndef OUTPUT
#define OUTPUT stdout
#endif /* ifndef OUTPUT */

#ifndef FPR
#define __FPR(a,b) fprintf(OUTPUT, #a, b)
#define FPR(b,a) __FPR(a\n ,b)

#define __FPRT(a,b) fprintf(OUTPUT, #a, b)
#define FPRT(b,a) __FPRT(\ta\n ,b)

#define __FPRT2(a,b) fprintf(OUTPUT, #a, b)
#define FPRT2(b,a) __FPRT2(\ta\n ,b)

#define __FPRT3(a,b) fprintf(OUTPUT, #a, b)
#define FPRT3(b,a) __FPRT3(\t\ta\n ,b)
#endif /* ifndef FPRINTF(a,b) __FPRINTF(#a,b) */

int get_attr(struct ibv_device* device, int port)
{
	FPR(device->name, %s);
	FPRT(device->dev_name)
	return 0;
}

int main(int argc , char* argv[])
{
	char devname[512] = {0};
	int  port = -1;
	int ch = 0;
	while((ch = getopt(argc, argv, "d:p:") != -1))
	{
		switch (ch)
		{
			case 'd':
				strncpy(devname, optarg, 512);
				break;
			case 'p':
				port = atoi(optarg);
			default:
				break;
		}
	}

	ibv_fork_init();
	int num = 0;
	struct ibv_device** dev_list = ibv_get_device_list(&num);
	if (!dev_list)
	{
		perror("ibv_get_device_list");
		exit(1);
	}
	else if (num == 0)
	{
		FPR(%s, "no rdma device was found");
		goto err;
	}

	if (strlen(devname) != 0)
	{
		int i = 0;
		for (; i < num; ++i)
		{
			if (strcmp(devname, ibv_get_device_name(dev_list[i])))
				continue;
			else
			{
				get_attr(dev_list[i], port);
				goto err;
			}
		}
		if (i == num)
		{
			printf("not find the rdma device: %s\n", devname);
			goto err;
		}
	}
	else
		for (int i = 0; i < num; ++i)
		{
			get_attr(dev_list[i], port);
				goto err;
		}
err:
	ibv_free_device_list(dev_list);
}
