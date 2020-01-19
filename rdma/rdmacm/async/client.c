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


	struct rdma_event_channel* chanel_event=rdma_create_event_channel();
	if(!chanel_event)
	{
		perror("create event channel failed");
		return 1;
	}

	

	return 0;
}
