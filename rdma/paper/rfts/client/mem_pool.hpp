#ifndef RFTS_CLIENT
	#define RFTS_CLIENT
#endif

#include<iostream>
#include<mutex>

namespace rfts
{
	using std::mutex;
	class mempool
	{
	private:
		void* addr;
		int length;

		int front;
		int rear;
#ifndef RFTS_CLIENT
		mutex mutext_mem_pool;
#endif
	public:
		mempool(int length);
		void* malloc(int length);
		int  free(void* addr);
		const void*  get_real_addr() const;
	};
}