#include"mem_pool.hpp"

rfts::spsc_seq_mem_pool::spsc_seq_mem_pool(const transargs& transargs) noexcept
	: __elesize(transargs.afreq / transargs.tfreq * transargs.node_num *
		transargs.sensor_num_per_node * transargs.kind_per_sensor *
		transargs.size_per_data * 2)
	, __length(__elesize * MEM_POOL_CAPACITY)
	, __addr{new unsigned char[__length]()}
	, __front(0)
	, __rear(0)
	, __ringqueue(new ibv_send_wr [MEM_POOL_CAPACITY]())
	, __sg_list(new ibv_sge [MEM_POOL_CAPACITY]())
	, __wr_id(1)
{
	for(int i{0}; i < MEM_POOL_CAPACITY; ++i)
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
	int front = __front.load(std::memory_order_acquire);
	int rear  = __rear.load(std::memory_order_relaxed);
	if (++rear >= MEM_POOL_CAPACITY)
		rear -= MEM_POOL_CAPACITY;

}

void rfts::spsc_seq_mem_pool::free(void) noexcept
{
}



