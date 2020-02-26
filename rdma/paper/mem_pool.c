#include<memory.h>
#include<pthread.h>
#include<math.h>
#include<stdlib.h>

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
	void* addr=pool->realbuf+pool->head*2000;
	pool->head=(pool->head+1)%100;
	pool->busy++;
	return addr;
}

void myfree(struct mempool* pool)
{
	if(pool->busy==0)
		return;
	pool->tail=(pool->tail+1)%100;		
	pool->busy--;
}







int main()
{
}
