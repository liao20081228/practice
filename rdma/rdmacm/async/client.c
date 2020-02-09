#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<string.h>
#include<errno.h>
#include<rdma/rdma_cma.h>
#include<rdma/rdma_verbs.h>
#include<pthread.h>
#include<semaphore.h>

#ifndef SUCCESS_FAILURE 
	#define SUCCESS 0
	#define FAILURE 1
#endif


struct context
{
	struct rdma_event_channel * rdma_chnnel;
	struct rdma_cm_id* rdma_id;
	struct sockaddr src_addr;
	struct sockaddr dst_addr;
};



int main(void)
{
	struct rdma_event_channel * rdma_chnnel = rdma_create_event_channel();
	struct rdma_cm_id* rdma_id = NULL;
	rdma_create_id(rdma_chnnel,&rdma_id,NULL,RDMA_PS_TCP);
	rdma_resolve_addr(rdma_id, NULL, )
}
