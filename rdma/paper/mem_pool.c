#include<memory.h>
#include<pthread.h>
#include<math.h>

struct real_mem
{
	void* addr;
	int length;
	int ref;
	struct real_mem*next;
};

struct node
{
	void* node;
	length;
	struct node*next;
};

struct freelist
{
	
}

struct mempool
{
	struct real_mem realbuf;
};




int create_mem_pool(struct mem_pool *pool)
{
	
}




int main()
{
	struct mem_pool* pool = (struct mem_pool*)malloc(sizeof mem_pool);
	
	create_mem_pool(pool);	
}
