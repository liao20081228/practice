#include"mem_pool.hpp"

rfts::spsc_seq_mem_pool::spsc_seq_mem_pool(const trans_args& transargs) noexcept
	: __elesize(transargs.afreq / transargs.tfreq * transargs.node_num *
		transargs.sensor_num_per_node * transargs.kind_per_sensor *
		transargs.size_per_data * 2)
	, __length(__elesize * MEM_POOL_CAPACITY)
	, __addr{new unsigned char[__length]()}
	, __front(0)
	, __rear(0)
	, __ringqueue(new ibv_send_wr [MEM_POOL_CAPACITY])
	, __sg_list(new ibv_sge [MEM_POOL_CAPACITY])
	, __wr_id(1)
{
	for(int i = 0; i < MEM_POOL_CAPACITY; ++i)
	{
		__sg_list[i].addr = (uint64_t)(__addr + i * __elesize);
		__sg_list[i].length = __elesize;
		__ringqueue[i] =
		{
			.next = nullptr,
			.sg_list = &__sg_list[i],
			.num_sge = 1,
			.opcode  = IBV_WR_SEND,
		};
	}
}

rfts::spsc_seq_mem_pool::spsc_seq_mem_pool(spsc_seq_mem_pool&& ref) noexcept
	: __elesize(ref.__elesize)
	, __length(ref.__length)
	, __addr(ref.__addr)
	, __front(ref.__front.load(std::memory_order_relaxed))
	, __rear(ref.__rear.load(std::memory_order_relaxed))
	, __ringqueue(ref.__ringqueue)
	, __sg_list(ref.__sg_list)
	, __wr_id(ref.__wr_id)
{
	__addr = nullptr;
}

rfts::spsc_seq_mem_pool::~spsc_seq_mem_pool(void) noexcept
{
	while( __addr && __front.load(std::memory_order_relaxed)
			== __rear.load(std::memory_order_relaxed))
	{
		delete [] __addr;
		__addr = nullptr;
		delete [] __ringqueue;
		__ringqueue = nullptr;
		delete [] __sg_list;
		__sg_list = nullptr;
		break;
	}
}



const void* rfts::spsc_seq_mem_pool::get_mempool_addr(void) const noexcept
{
	return __addr;
}


int rfts::spsc_seq_mem_pool::get_mempool_length(void) const noexcept
{
	return __length;
}

ibv_send_wr* rfts::spsc_seq_mem_pool::malloc(void) noexcept
{
	int front = 0, rear = 0, temp = 0;
	do
	{
		front = __front.load(std::memory_order_acquire);
		temp = rear  = __rear.load(std::memory_order_relaxed);
		
		if (++rear >= MEM_POOL_CAPACITY)
			rear -= MEM_POOL_CAPACITY;
	}while(rear == front);
	__rear.store(rear, std::memory_order_release);
	__ringqueue[temp].wr_id = __wr_id++;
	return &__ringqueue[temp];
}

void rfts::spsc_seq_mem_pool::free(void) noexcept
{
	int front = 0, rear = 0;
	front = __front.load(std::memory_order_relaxed);
	rear = __rear.load(std::memory_order_acquire);
	if (rear == front)
	{
		std::cout << "outof" <<std::endl;
		return;
	}
		if (++front >= MEM_POOL_CAPACITY)
		front -= MEM_POOL_CAPACITY;
	__front.store(front, std::memory_order_release);
}



