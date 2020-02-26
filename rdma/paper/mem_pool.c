#include<memory.h>
#include<pthread.h>
#include<math.h>
#include<stdlib.h>
struct node
{
	void* addr;
	struct node* next;
};

struct freelist
{
	struct node head;
	struct node tail;
	int busy;
	int free; 
	pthread_mutex_t mutext;
};

struct mempool
{
	void *realbuf;
	int relen;
	void* (*r_malloc)(int size);
	void* (*r_free)(int size);
	int (*create)(struct mempool);
	int (*destory)(struct mempool);
	struct freelist free;
};



int create_pool(struct mempool* pool)
{
	pool->realbuf= malloc(1024*100);	
	for(int i=0;i<100;i++)
	{
		struct node* rbuf=(void*)malloc(sizeof struct node);
		rbuf->addr=pool->realbuf;	
	}
}




int main()
{
}
