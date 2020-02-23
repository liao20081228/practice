#include<memory.h>
#include<pthread.h>
#include<math.h>
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

struct mem_pool pool;
void* my_malloc(int n)
{
	double a = log10(n)/log10(2);
	if(a-)
		a++;
	switch(a)
	{
		case 2:
			pthread_mutex_lock(&pool.free2.freelist_mutex);
			if(pool.free2.free_node!=0)
			{
										
			}

	}
	
}



