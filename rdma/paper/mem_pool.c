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
	struct freelist free4;
	struct freelist free6;
	struct freelist free8;
	struct freelist free16;
	struct freelist free32;
	struct freelist free64;
};


void* my_malloc(int n)
{
	
}



