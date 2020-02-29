#include<iostream>
#include<mutex>

#ifndef RFTS_CLIENT
	#define RFTS_CLIENT
#endif
namespace rfst
{
	using std::mutex;
	class mempool
	{
	private:
		void* addr;
		int length;
#ifndef RFTS_CLIENT
		mutex mutext_mem_pool;
#endif
	public:
		mempool(int length);
		void* malloc(int length);
		void  free();
		const void*  get_real_addr() const;
		int lock();
		int unlock;
	};
}
