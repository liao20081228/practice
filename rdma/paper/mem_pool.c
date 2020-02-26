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

void* mymalloc(int size)
{
	int n=size/2000;
		
}

int main()
{
}
