#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<getopt.h>
#include<unistd.h>
#include<memory.h>
#include<errno.h>
#include<infiniband/verbs.h>

#ifndef OUTPUT
	#define OUTPUT stdout
#endif /* ifndef OUTPUT */

#ifndef FPR
	#define _FPRT(a, b, c) fprintf(OUTPUT, #a, #b, c)
	#define ___FPRT(a, b, c, d) _FPRT(\t%-d : %-c\n,b, a)
	#define FPRT(a, b, c) ___FPRT(a, b, c, 30s)

	#define _FPRT2(a, b, c) fprintf(OUTPUT, #a, #b, c)
	#define __FPRT2(a, b, c, d) _FPRT2(\t\t%-d : %-c\n,b, a)
	#define FPRT2(a, b, c) __FPRT2(a, b, c, 30s)

	#define _FPRT3(a, b, c) fprintf(OUTPUT, #a, #b, c)
	#define __FPRT3(a, b, c, d) _FPRT3(\t\t\t%-d : %-c\n,b, a)
	#define FPRT3(a, b, c) __FPRT3(a, b, c, 30s)
#endif /* ifndef FPRINTF(a,b) __FPRINTF(#a,b) */



void print_device_cap_flags(unsigned int device_cap_flags)
{
#ifndef FPRT3DF
#define FPRT3DF(a) if (device_cap_flags & a) FPRT3("", a,s)
#endif /* ifndef macro */
	FPRT3DF(IBV_DEVICE_RESIZE_MAX_WR);

}


char* be64tolestr(int64_t bigend, char* buf)
{
	uint16_t guid[4]= {0,0,0,0};
	memcpy(guid, &bigend, 8);
	sprintf(buf, "%0hX:%04hX:%04hX:%04hX",
			(uint16_t)(guid[0] << 8 | guid[0] >> 8),
			(uint16_t)(guid[1] << 8  | guid[1] >> 8),
			(uint16_t)(guid[2] << 8  | guid[2] >> 8),
			(uint16_t)(guid[3] << 8  | guid[3] >> 8));
	return buf;
}

int get_attr(struct ibv_device* device, int port)
{
	fprintf(OUTPUT, "name : %-s\n", device->name);
	FPRT(device->dev_name, uverb name, s);
	FPRT(device->dev_path, infiniband verbs in sysfs, s);
	FPRT(device->ibdev_path, infiniband in sysfs, s);
	FPRT(device->node_type, node type, d);
	FPRT(device->transport_type, transport type, d);
	FPRT(ibv_get_device_name(device), ibv_get_device_name(), s);
	char GUID[] ="xxxx:xxxx:xxxx:xxxx";
	FPRT(be64tolestr(ibv_get_device_guid(device), GUID), ibv_get_device_guid(), s);
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
	fprintf(OUTPUT,"\n\n\t%-30s\n", "device attr:");
	FPRT2(dev_attr_ex.orig_attr.fw_ver, fir_ver, s);
	memset(GUID, 0, sizeof(GUID));
	FPRT2(be64tolestr(dev_attr_ex.orig_attr.node_guid, GUID), node_guid, s);
	memset(GUID, 0, sizeof(GUID));
	FPRT2(be64tolestr(dev_attr_ex.orig_attr.sys_image_guid, GUID), sys_image_guid, s);
	FPRT2(dev_attr_ex.orig_attr.max_mr_size, max_mr_size, lu);
	FPRT2(dev_attr_ex.orig_attr.page_size_cap, page_size_cap, lu);
	FPRT2(dev_attr_ex.orig_attr.vendor_id, vendor_id,#X);
	FPRT2(dev_attr_ex.orig_attr.vendor_part_id, vendor_part_id,u);
	FPRT2(dev_attr_ex.orig_attr.hw_ver, hw_ver,u);
	FPRT2(dev_attr_ex.orig_attr.max_qp, max_qp,d);
	FPRT2(dev_attr_ex.orig_attr.max_qp_wr, max_qp_wr,d);
	FPRT2(dev_attr_ex.orig_attr.device_cap_flags, device_cap_flags,#X);
	print_device_cap_flags(dev_attr_ex.orig_attr.device_cap_flags);

	FPRT2(dev_attr_ex.orig_attr.max_qp, max_qp,d);
	FPRT2(dev_attr_ex.orig_attr.max_qp, max_qp,d);
	FPRT2(dev_attr_ex.orig_attr.max_qp, max_qp,d);
	FPRT2(dev_attr_ex.orig_attr.max_qp, max_qp,d);
	FPRT2(dev_attr_ex.orig_attr.max_qp, max_qp,d);
	FPRT2(dev_attr_ex.orig_attr.max_qp, max_qp,d);
	
	
	
	
	
	
	
	
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
