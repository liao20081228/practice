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
	int head;
	int tail;
	int busy;
	void* (*r_malloc)(int size);
	void* (*r_free)(int size);
	int (*create)(struct mempool);
	int (*destory)(struct mempool);
	struct freelist free;
};



int create_pool(struct mempool* pool)
{
	pool->realbuf= malloc(2000*100);
	pool->head=0;
	pool->tail=0;
	pool->busy=0;
	return 0;
}

int destory (struct mempool* pool)
{
	while(1)
	{
		if(pool->head== pool->tail)
		{
			free(pool->realbuf);
			return 0;
		}
	}
}

void* mymalloc(struct mempool* pool)
{
	if(pool->busy==100)
		return NULL;
	void* addr=pool->realbuf+pool->head;
	pool->head=
	
}

int main()
{
}
