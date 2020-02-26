#include<memory.h>
#include<pthread.h>
#include<math.h>

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
	void *relbuf;
	int relen;
	void* (*r_malloc)(int size);
	void* (*r_free)(int size);
	int (*create)(struct mempool);
	int (*destory)(struct mempool);
	struct freelist free;
};








int main()
{
}
