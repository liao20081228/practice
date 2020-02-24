#include<memory.h>
#include<pthread.h>
#include<math.h>

struct real_mem
{
	void* addr;
	int length;
	struct real_mem*next;
};


struct mempool
{
	struct real_mem realbuf;
	
};


