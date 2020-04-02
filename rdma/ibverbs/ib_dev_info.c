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
	#define FPRT(a, b, c) ___FPRT(a, b, c, 32s)

	#define _FPRT2(a, b, c) fprintf(OUTPUT, #a, #b, c)
	#define __FPRT2(a, b, c, d) _FPRT2(\t\t%-d : %-c\n,b, a)
	#define FPRT2(a, b, c) __FPRT2(a, b, c, 32s)

	#define _FPRT3(a, b, c) fprintf(OUTPUT, #a, #b, c)
	#define __FPRT3(a, b, c, d) _FPRT3(\t\t\t%-d : %-c\n,b, a)
	#define FPRT3(a, b, c) __FPRT3(a, b, c, 32s)

	#define ___FPRTDF(a, b, c) fprintf(OUTPUT, #a, #b, c)
	#define __FPRTDF(a, b, c, d) ___FPRTDF(\t\t\t%-d%-c\n,b, a)
	#define _FPRTDF(a, b, c) __FPRTDF(a, b, c, 32s)
	#define FPRTDF(a) if (device_cap_flags & a) {_FPRTDF("", \t\t\t\x20\x20 a, s); device_cap_flags &= (~a);}
	
	#define FPRTOF(a,b) if (b & a) {_FPRTDF("", \t\t\t\x20\x20 a, s); b &= (~a);}
#endif /* ifndef FPRINTF(a,b) __FPRINTF(#a,b) */

void print_atomic_cap(enum ibv_atomic_cap atomic_cap)
{
	if (atomic_cap == IBV_ATOMIC_NONE)
		FPRT2("IBV_ATOMIC_NONE", atomic_cap, s);
	if (atomic_cap == IBV_ATOMIC_HCA)
		FPRT2("IBV_ATOMIC_HCA", atomic_cap, s);
	if (atomic_cap == IBV_ATOMIC_GLOB)
		FPRT2("IBV_ATOMIC_GLOB", atomic_cap, s);
;
	if (atomic_cap == IBV_ATOMIC_GLOB)
;
}

void print_device_cap_flags(unsigned int device_cap_flags)
{
	FPRTDF(IBV_DEVICE_RESIZE_MAX_WR);
	FPRTDF(IBV_DEVICE_BAD_PKEY_CNTR);
	FPRTDF(IBV_DEVICE_BAD_QKEY_CNTR);
	FPRTDF(IBV_DEVICE_RAW_MULTI);
	FPRTDF(IBV_DEVICE_AUTO_PATH_MIG);
	FPRTDF(IBV_DEVICE_CHANGE_PHY_PORT);
	FPRTDF(IBV_DEVICE_UD_AV_PORT_ENFORCE);
	FPRTDF(IBV_DEVICE_CURR_QP_STATE_MOD);
	FPRTDF(IBV_DEVICE_SHUTDOWN_PORT);
	FPRTDF(IBV_DEVICE_INIT_TYPE);
	FPRTDF(IBV_DEVICE_PORT_ACTIVE_EVENT);
	FPRTDF(IBV_DEVICE_SYS_IMAGE_GUID);
	FPRTDF(IBV_DEVICE_RC_RNR_NAK_GEN);
	FPRTDF(IBV_DEVICE_SRQ_RESIZE);
	FPRTDF(IBV_DEVICE_N_NOTIFY_CQ);
	FPRTDF(IBV_DEVICE_MEM_WINDOW);
	FPRTDF(IBV_DEVICE_UD_IP_CSUM);
	FPRTDF(IBV_DEVICE_XRC);
	FPRTDF(IBV_DEVICE_MEM_MGT_EXTENSIONS);
	FPRTDF(IBV_DEVICE_MEM_WINDOW_TYPE_2A);
	FPRTDF(IBV_DEVICE_MEM_WINDOW_TYPE_2B);
	FPRTDF(IBV_DEVICE_RC_IP_CSUM);
	FPRTDF(IBV_DEVICE_RAW_IP_CSUM);
	FPRTDF(IBV_DEVICE_MANAGED_FLOW_STEERING);
	FPRT(device_cap_flags, \t\t\t\t\t\x20\x20 unkown flags, #X);
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

int print_device_attr(struct ibv_device_attr* device_attr)
{

	char GUID[] ="xxxx:xxxx:xxxx:xxxx";
	fprintf(OUTPUT,"\n\n\t%-30s\n", "device attr");
	FPRT2(device_attr->fw_ver, fir_ver, s);
	memset(GUID, 0, sizeof(GUID));
	FPRT2(be64tolestr(device_attr->node_guid, GUID), node_guid, s);
	memset(GUID, 0, sizeof(GUID));
	FPRT2(be64tolestr(device_attr->sys_image_guid, GUID), sys_image_guid, s);
	FPRT2(device_attr->max_mr_size, max_mr_size, lu);
	FPRT2(device_attr->page_size_cap, page_size_cap, lu);
	FPRT2(device_attr->vendor_id, vendor_id,#X);
	FPRT2(device_attr->vendor_part_id, vendor_part_id,u);
	FPRT2(device_attr->hw_ver, hw_ver,u);
	FPRT2(device_attr->max_qp, max_qp,d);
	FPRT2(device_attr->max_qp_wr, max_qp_wr,d);
	FPRT2(device_attr->device_cap_flags, device_cap_flags,#X);
	print_device_cap_flags(device_attr->device_cap_flags);
	FPRT2(device_attr->max_sge, max_sge, d);
	FPRT2(device_attr->max_sge_rd, max_sge_rd, d);
	FPRT2(device_attr->max_cq, max_cq, d);
	FPRT2(device_attr->max_cqe, max_cqe, d);
	FPRT2(device_attr->max_mr, max_mr, d);
	FPRT2(device_attr->max_pd, max_pd, d);
	FPRT2(device_attr->max_qp_rd_atom, max_qp_rd_atom, d);
	FPRT2(device_attr->max_ee_rd_atom, max_ee_rd_atom, d);
	FPRT2(device_attr->max_res_rd_atom, max_res_rd_atom, d);
	FPRT2(device_attr->max_qp_init_rd_atom, max_qp_init_rd_atom, d);
	FPRT2(device_attr->max_ee_init_rd_atom, max_ee_init_rd_atom, d);
	print_atomic_cap(device_attr->atomic_cap);
	FPRT2(device_attr->max_ee, max_ee, d);
	FPRT2(device_attr->max_rdd, max_rdd, d);
	FPRT2(device_attr->max_mw, max_mw, d);
	FPRT2(device_attr->max_raw_ipv6_qp, max_raw_ipv6_qp, d);
	FPRT2(device_attr->max_raw_ethy_qp, max_raw_ethy_qp, d);
	FPRT2(device_attr->max_mcast_grp, max_mcast_grp, d);
	FPRT2(device_attr->max_mcast_qp_attach, max_mcast_qp_attach, d);
	FPRT2(device_attr->max_total_mcast_qp_attach, max_total_mcast_qp_attach, d);
	FPRT2(device_attr->max_ah, max_ah, d);
	FPRT2(device_attr->max_fmr, max_fmr, d);
	FPRT2(device_attr->max_map_per_fmr, max_map_per_fmr, d);
	FPRT2(device_attr->max_srq, max_srq, d);
	FPRT2(device_attr->max_srq_wr, max_srq_wr, d);
	FPRT2(device_attr->max_srq_sge, max_srq_sge, d);
	FPRT2(device_attr->max_pkeys, max_pkeys, hu);
	FPRT2(device_attr->local_ca_ack_delay, local_ca_ack_delay, hhu);
	FPRT2(device_attr->phys_port_cnt, phys_port_cnt, hhu);
	return 0;
}


int print_device_attr_ex(struct ibv_device_attr_ex* dev_attr_ex)
{

	fprintf(OUTPUT,"\n\n\t%-30s\n", "device attr ex");
	FPRT2(dev_attr_ex->comp_mask, comp_mask, u);
	FPRT2(dev_attr_ex->odp_caps.general_caps , general_odp_caps, lX);
	FPRTOF(IBV_ODP_SUPPORT, dev_attr_ex->odp_caps.general_caps);
	FPRTOF(IBV_ODP_SUPPORT_IMPLICIT, dev_attr_ex->odp_caps.general_caps);

	FPRT2(dev_attr_ex->odp_caps.per_transport_caps.rc_odp_caps, rc_odp_caps, X);
	FPRTOF(IBV_ODP_SUPPORT_SEND, dev_attr_ex->odp_caps.per_transport_caps.rc_odp_caps);
	FPRTOF(IBV_ODP_SUPPORT_RECV, dev_attr_ex->odp_caps.per_transport_caps.rc_odp_caps);
	FPRTOF(IBV_ODP_SUPPORT_WRITE, dev_attr_ex->odp_caps.per_transport_caps.rc_odp_caps);
	FPRTOF(IBV_ODP_SUPPORT_READ, dev_attr_ex->odp_caps.per_transport_caps.rc_odp_caps);
	FPRTOF(IBV_ODP_SUPPORT_ATOMIC, dev_attr_ex->odp_caps.per_transport_caps.rc_odp_caps);
	FPRTOF(IBV_ODP_SUPPORT_SRQ_RECV, dev_attr_ex->odp_caps.per_transport_caps.rc_odp_caps);
	FPRT2(dev_attr_ex->odp_caps.per_transport_caps.uc_odp_caps, uc_odp_caps, X);
	FPRTOF(IBV_ODP_SUPPORT_SEND, dev_attr_ex->odp_caps.per_transport_caps.uc_odp_caps);
	FPRTOF(IBV_ODP_SUPPORT_RECV, dev_attr_ex->odp_caps.per_transport_caps.uc_odp_caps);
	FPRTOF(IBV_ODP_SUPPORT_WRITE, dev_attr_ex->odp_caps.per_transport_caps.uc_odp_caps);
	FPRTOF(IBV_ODP_SUPPORT_READ, dev_attr_ex->odp_caps.per_transport_caps.uc_odp_caps);
	FPRTOF(IBV_ODP_SUPPORT_ATOMIC, dev_attr_ex->odp_caps.per_transport_caps.uc_odp_caps);
	FPRTOF(IBV_ODP_SUPPORT_SRQ_RECV, dev_attr_ex->odp_caps.per_transport_caps.uc_odp_caps);
	FPRT2(dev_attr_ex->odp_caps.per_transport_caps.ud_odp_caps, ud_odp_caps, X);
	FPRTOF(IBV_ODP_SUPPORT_SEND, dev_attr_ex->odp_caps.per_transport_caps.ud_odp_caps);
	FPRTOF(IBV_ODP_SUPPORT_RECV, dev_attr_ex->odp_caps.per_transport_caps.ud_odp_caps);
	FPRTOF(IBV_ODP_SUPPORT_WRITE, dev_attr_ex->odp_caps.per_transport_caps.ud_odp_caps);
	FPRTOF(IBV_ODP_SUPPORT_READ, dev_attr_ex->odp_caps.per_transport_caps.ud_odp_caps);
	FPRTOF(IBV_ODP_SUPPORT_ATOMIC, dev_attr_ex->odp_caps.per_transport_caps.ud_odp_caps);
	FPRTOF(IBV_ODP_SUPPORT_SRQ_RECV, dev_attr_ex->odp_caps.per_transport_caps.ud_odp_caps);
	FPRT2(dev_attr_ex->completion_timestamp_mask, completion_timestamp_mask, lX);
	FPRT2(dev_attr_ex->hca_core_clock, hca_core_clock, ld);
	FPRT2(dev_attr_ex->device_cap_flags_ex, device_cap_flags_ex, lX);

	return 0;
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

	struct ibv_device_attr_ex* dev_attr_ex = (struct ibv_device_attr_ex*)malloc(sizeof(struct ibv_device_attr_ex));
	struct ibv_query_device_ex_input dev_attr_ex_input = {0};
	memset(dev_attr_ex, 0, sizeof(struct ibv_device_attr_ex));
	if(ibv_query_device_ex(context, &dev_attr_ex_input, dev_attr_ex))
	{
		perror("ibv_query_device_ex failed");
		goto close_device;
	}
	
	print_device_attr(&dev_attr_ex->orig_attr);
	print_device_attr_ex(dev_attr_ex);
	
	free(dev_attr_ex);
	ibv_close_device(context);
	return 0;
close_device:
	free(dev_attr_ex);
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
