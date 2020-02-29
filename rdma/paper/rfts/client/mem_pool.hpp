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
		mutex mutext_mem_pool;
	public:
		mempool(int length);
		void* malloc(int n);
		void  free();
	};
}
