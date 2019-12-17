#include<stdio.h>
#include<rdma/rdma_verbs.h>
#include<rdma/rdma_cma.h>
#include<getopt.h>


int main(void)
{
	struct rdma_event_channel*  rec=rdma_create_event_channel();
	
	rdma_destroy_event_channel(rec);
	 
	return 0;
}

