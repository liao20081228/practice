#include<infiniband/verbs.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define __PRINTF(aa,bb) printf(#aa, bb)
#define _PRINTF(aa,bb,cc,dd) __PRINTF(aa##bb##cc,dd)
#define PRINTF_FIELD(aa, bb, cc) _PRINTF(bb, \%, cc \n  ,aa->bb )

int main(void)
{
	//get IB device list
	int ib_dev_num=0;
	struct ibv_device** ib_dev_list=ibv_get_device_list(&ib_dev_num);

	if(!ib_dev_list)
	{
		perror("errno: not find ib device");
		exit(-1);
	}
	printf("the number of ib device is:%d\n", ib_dev_num);

	printf("---------struct ibv_device-----------------\n") ;
	for(int i=0;i<ib_dev_num;++i)
	{
		struct ibv_device *it=ib_dev_list[i];
		printf("name :%s\n", it->name);
		printf("dev_name: %s\n", it->dev_name);
		printf("dev_path: %s\n", it->dev_path);
		printf("ibdev_path: %s\n", it->ibdev_path);
		printf("transport_type : %d\n", it->transport_type);
		printf("---------ibv_get_device_name、ibv_get_device_guid、ibv_node_type_str-----------------\n") ;
		printf("the device name is:%s\n ", ibv_get_device_name(it));
		printf("the device guid is:%lld \n ",ibv_get_device_guid(it));
		printf("the node_type is :%d, %s\n",it->node_type,ibv_node_type_str(it->node_type));
		PRINTF_FIELD(it,dev_path,s);
	}

	//open IB device 
	struct ibv_context* ib_dev_context=ibv_open_device(ib_dev_list[0]);
	if(!ib_dev_context)
	{
		printf("open device failed\n");
		exit(-1);
	}
	

	//get IB device  attrs
	struct ibv_device_attr * ib_dev_attr=(struct ibv_device_attr*)malloc(sizeof(struct ibv_device_attr));
	assert(NULL!=ib_dev_attr);
	assert(0==ibv_query_device(ib_dev_context,ib_dev_attr));
	printf("===============================print ibv_device_attr====================================\n");
	printf("fw_ver is : %s\n ",ib_dev_attr->fw_ver);
	printf("node_guid is : %llu\n ",ib_dev_attr->node_guid);
	printf("sys_image_guid is : %llu\n ",ib_dev_attr->sys_image_guid);
	printf("max_mr_size is : %lu\n ",ib_dev_attr->max_mr_size);
	printf("page_size_cap is : %lu\n ",ib_dev_attr->page_size_cap);
	printf("vendor_id is : %u\n ",ib_dev_attr->vendor_id);
	printf("vendor_part_id is : %u\n ",ib_dev_attr->vendor_part_id);
	printf("hw_ver is : %u\n ",ib_dev_attr->hw_ver);
	printf("max_qp is : %d\n ",ib_dev_attr->max_qp);
	printf("max_qp_wr is : %d\n ",ib_dev_attr->max_qp_wr);
	printf("device _cap_flags is : %d\n ",ib_dev_attr->device_cap_flags);
	printf("max_sge is : %d\n ",ib_dev_attr->max_sge);
	printf("max_sge_rd is : %d\n ",ib_dev_attr->max_sge_rd);
	printf("max_cq is : %d\n ",ib_dev_attr->max_cq);
	printf("max_cqe is : %d\n ",ib_dev_attr->max_cqe);
	printf("max_mr is : %d\n ",ib_dev_attr->max_mr);
	printf("max_pd is : %d\n ",ib_dev_attr->max_pd);
	printf("max_qp_rd_atom is : %d\n ",ib_dev_attr->max_qp_rd_atom);
	printf("max_ee_rd_atom is : %d\n ",ib_dev_attr->max_ee_rd_atom);
	printf("max_res_rd_atom is : %d\n ",ib_dev_attr->max_res_rd_atom);
	printf("max_qp_init_rd_atom is : %d\n ",ib_dev_attr->max_qp_init_rd_atom);
	printf("max_ee_init_rd_atom is : %d\n ",ib_dev_attr->max_ee_init_rd_atom);
	printf("atomic_cap is : %d\n ",ib_dev_attr->atomic_cap);
	printf("max_ee is : %d\n ",ib_dev_attr->max_ee);
	printf("max_rdd is : %d\n ",ib_dev_attr->max_rdd);
	printf("max_mw is : %d\n ",ib_dev_attr->max_mw);
	printf("max_raw_ipv6_qp is : %d\n ",ib_dev_attr->max_raw_ipv6_qp);
	printf("max_raw_ethy_qp is : %d\n ",ib_dev_attr->max_raw_ethy_qp);
	printf("max_mcast_grp is : %d\n ",ib_dev_attr->max_mcast_grp);
	printf("max_mcast_qp_attach is : %d\n ",ib_dev_attr->max_mcast_qp_attach);
	printf("max_total_mcast_qp_attach is : %d\n ",ib_dev_attr->max_total_mcast_qp_attach);
	printf("max_ah is : %d\n ",ib_dev_attr->max_ah);
	printf("max_fmr is : %d\n ",ib_dev_attr->max_fmr);
	printf("max_map_per_fmr is : %d\n ",ib_dev_attr->max_map_per_fmr);
	printf("max_srq is : %d\n ",ib_dev_attr->max_srq);
	printf("max_srq_wr is : %d\n ",ib_dev_attr->max_srq_wr);
	printf("max_srq_sge is : %d\n ",ib_dev_attr->max_srq_sge);
	printf("max_pkeys is : %hu\n ",ib_dev_attr->max_pkeys);
	printf("local_ca_ack_delay is : %hhu\n ",ib_dev_attr->local_ca_ack_delay);
	printf("phys_port_cnt is : %hhu\n ",ib_dev_attr->phys_port_cnt);
	free(ib_dev_attr);
	ib_dev_attr=NULL;
	
	//get IB device port attrs
	struct ibv_port_attr* ib_port_attr=(struct ibv_port_attr*)malloc(sizeof(struct ibv_port_attr));
	assert(NULL!=ib_port_attr);
	assert(0==ibv_query_port(ib_dev_context, 1, ib_port_attr));
	printf("==============================print ibv_port_attrs====================\n");
	printf("ibv_port_state is : %d, state is %s\n ",ib_port_attr->state, ibv_port_state_str(ib_port_attr->state));
	printf("max_mtu is : %u\n ",ib_port_attr->max_mtu);
	printf("active_mtu s : %u\n ",ib_port_attr->active_mtu);
	printf("gid_tbl_len is : %u\n ",ib_port_attr->gid_tbl_len);
	printf("port_cap_flags is : %u\n ",ib_port_attr->port_cap_flags);
	printf("max_msg_sz is : %u\n ",ib_port_attr->max_msg_sz);
	printf("bad_pksy_cntr is : %u\n ",ib_port_attr->bad_pkey_cntr);
	printf("qkey_viol_cntr is : %u\n ",ib_port_attr->qkey_viol_cntr);
	printf("pkey_tbl_len is : %hu\n ",ib_port_attr->pkey_tbl_len);
	printf("lid is : %hu\n ",ib_port_attr->lid);
	printf("sm_lid is : %hu\n ",ib_port_attr->sm_lid);
	printf("lmc is : %hhu\n ",ib_port_attr->lmc);
	printf("max_vl_num is : %hhu\n ",ib_port_attr->max_vl_num);
	printf("sm_sl is : %hhu\n ",ib_port_attr->sm_sl);
	printf("subnet_timeout is : %hhu\n ",ib_port_attr->subnet_timeout);
	printf("init_type_reply  is : %hhu\n ",ib_port_attr->init_type_reply);
	printf("active_width is : %hhu\n ",ib_port_attr->active_width);
	printf("active_speed is : %hhu\n ",ib_port_attr->active_speed);
	printf("phys_state is : %hhu\n ",ib_port_attr->phys_state);
	free(ib_port_attr);
	ib_dev_attr=NULL;
	
	//get port gid
	union ibv_gid* ib_port_gid=(union ibv_gid*)malloc(sizeof(union ibv_gid));
	assert(NULL!=ib_port_gid);
	memset(ib_port_gid, 0, sizeof(union ibv_gid));
	assert(0==ibv_query_gid(ib_dev_context, 1, 0, ib_port_gid));
	free(ib_port_gid);
	ib_port_gid=NULL;

	//get pkey
	uint16_t pkey=0;
	assert(0==ibv_query_pkey(ib_dev_context, 1,0,&pkey));
	printf("pkey is %hu\n" ,pkey);

	assert(0==ibv_close_device(ib_dev_context));
	ibv_free_device_list(ib_dev_list);
	return 0;
}

