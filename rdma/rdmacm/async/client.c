#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<string.h>
#include<errno.h>
#include<rdma/rdma_cma.h>
#include<rdma/rdma_verbs.h>
#include<pthread.h>
#include<semaphore.h>

int main(void)
{
	struct rdma_event_channel* cm_channel = rdma_create_event_channel();
	if(!cm_channel)
	{
		perror("create event channel failed");
		return 1;
	}

	struct rdma_cm_id
	int ret = rdma_create_id(cm_channel, 

	return 0;
}
