#include<memory.h>
#include<pthread.h>
struct node
{
	void * addr;
	struct node* next;
};

struct freelist
{
	int free_node;
	struct node linklist;
	pthread_mutex_t freelist_mutex;
};


struct mem_pool
{
	struct freelist free2;
};






