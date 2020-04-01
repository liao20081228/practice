#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<getopt.h>
#include<unistd.h>
#include<string.h>
#include<memory.h>
#include<infiniband/verbs.h>

#ifndef OUTPUT
	#define OUTPUT stdout
#endif /* ifndef OUTPUT */

#ifndef FPR
	#define _FPRT(a, b, c) fprintf(OUTPUT, #a, #b, c)
	#define FPRT(a, b, c, d) _FPRT(\t%-d : %-c\n,b, a)
	#define _FPRT2(a, b, c) fprintf(OUTPUT, #a, #b, c)
	#define FPRT2(a, b, c, d) _FPRT2(\t\t%-d : %-c\n,b, a)
#endif /* ifndef FPRINTF(a,b) __FPRINTF(#a,b) */

int get_attr(struct ibv_device* device, int port)
{
	fprintf(OUTPUT, "name : %-s\n", device->name);
	FPRT(device->dev_name, uverb name, s, 30s);
	FPRT(device->dev_path, infiniband verbs in sysfs, s, 30s);
	FPRT(device->ibdev_path, infiniband in sysfs, s, 30s);
	FPRT(device->node_type, node type, d, 30s);
	FPRT(device->transport_type, transport type, d, 30s);
	FPRT(ibv_get_device_name(device), ibv_get_device_name, s, 30s);
	char* GUID="xxxx:xxxx:xxxx:xxxx";
	uint64_t guid_temp = ibv_get_device_guid(device);
	uint16_t guid[4];
	for(unsigned int i = 0; i < 4; ++i)
	{
		memcpy((uint8_t*)&guid[3-i] + 1,(uint8_t*)&guid_temp + i * 2, 1);
		memcpy((uint8_t*)&guid[3-i],(uint8_t*)&guid_temp + i * 2 + 1, 1);
	}
	sprintf(GUID, "%4X:%4X:%4X:%4X", guid[0],guid[1],guid[2],guid[3]);
	FPRT(GUID, GUID, s, 30s);
	
	struct ibv_context* context = ibv_open_device(device);
	if (!context)
	{
		perror("ibv_open_device failed");
		return 1;
	}

	struct ibv_device_attr_ex dev_attr_ex;
	memset(&dev_attr_ex, 0, sizeof(struct ibv_device_attr_ex));
	if(ibv_query_device_ex(context, NULL, &dev_attr_ex))
	{
		perror("ibv_query_device_ex failed");
		goto close_device;
	}
	fprintf(OUTPUT,"\t%-30s\n", "device attr:");
	FPRT(dev_attr_ex.orig_attr.fw_ver, firmware version, s, 30s);
	

	return 0;
close_device:
	ibv_close_device(context);
	return 1;
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
		fprintf(OUTPUT, "no rdma device was found\n");
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
			fprintf(OUTPUT, "not find the rdma device: %s\n", devname);
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
