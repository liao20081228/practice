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
		mempool(int afreq, int tfreq, int size,
			int kind = 1, int nodenum = 1);
		void* malloc(int) noexcept;
		int  free(void*) noexcept;
		const void*  get_real_addr() const;
	};
}
