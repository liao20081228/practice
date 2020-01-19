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



int main(void)
{

	pthread_t productor,consumer;


	struct rdma_event_channel* cm_channel = rdma_create_event_channel();
	if(!cm_channel)
	{
		perror("create event channel failed");
		return FAILURE;
	}

	struct rdma_cm_id *cm_id = NULL;
	int ret = rdma_create_id(cm_channel, &cm_id, NULL, RDMA_PS_TCP);
	if (ret)
	{
		perror("create cm id failed");
		goto free_cm_channel;
	}

	
	



free_cm_channel:
	rdma_destroy_event_channel(cm_channel);
	return FAILURE;

	return SUCCESS;
}
