#include<memory.h>
#include<pthread.h>
#include<math.h>




struct mempool
{
	void *relbuf;
	int relen;
	void* (*r_malloc)(int size);
	void* (*r_free)(int size);
	free
};




int create_mem_pool(struct mem_pool *pool)
{
	
}




int main()
{
}
