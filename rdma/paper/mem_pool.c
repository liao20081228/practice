#include<memory.h>
#include<pthread.h>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include"../rdma-examples/perftest/get_clock.h"
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
	pool->realbuf= malloc(8*10);
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
	if(pool->busy==10)
		return NULL;
	void* addr=pool->realbuf+pool->head*8;
	pool->head=(pool->head+1)%10;
	pool->busy++;
	return addr;
}

void myfree(struct mempool* pool)
{
	if(pool->busy==0)
		return;
	pool->tail=(pool->tail+1)%10;		
	pool->busy--;
}







int main()
{	
	struct mempool pool;
	create_pool(&pool);	
	int i=0;
	cycles_t s;
	cycles_t e;	
	double mhz=get_cpu_mhz(0);
	while(i<15)
	{
		s=get_cycles();
		mymalloc(&pool);
		e=get_cycles();
		printf("%lf\n",(e-s)/mhz);
		s=get_cycles();
		malloc(8);
		e=get_cycles();
		printf("%lf\n",(e-s)/mhz);
		i++;
	}
	myfree(&pool);
		printf("%p\n",mymalloc(&pool));
		return 0;
}
