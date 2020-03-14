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
		__ringqueue[i].next = nullptr,
		__ringqueue[i].sg_list = &__sg_list[i],
		__ringqueue[i].num_sge = 1,
		__ringqueue[i].opcode  = IBV_WR_SEND;
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
		return;
	if (++front >= MEM_POOL_CAPACITY)
		front -= MEM_POOL_CAPACITY;
	__front.store(front, std::memory_order_release);
}

//--------------------------
rfts::spsc_fix_mem_pool::spsc_fix_mem_pool(const trans_args& transargs) noexcept
	: __elesize(transargs.afreq / transargs.tfreq * transargs.node_num *
		transargs.sensor_num_per_node * transargs.kind_per_sensor *
		transargs.size_per_data * 2)
	, __length(__elesize * MEM_POOL_CAPACITY)
	, __addr{new unsigned char[__length]()}
	, __front(0)
	, __rear(0)
	, __wrs(new ibv_send_wr [MEM_POOL_CAPACITY])
	, __sg_lists(new ibv_sge [MEM_POOL_CAPACITY])
	, __wr_id(1)
	, __ringqueue(new ibv_send_wr*[MEM_POOL_CAPACITY])
	, __count(0, 0)
{
	for(int i = 0; i < MEM_POOL_CAPACITY; ++i)
	{
		__sg_lists[i].addr = (uint64_t)(__addr + i * __elesize);
		__sg_lists[i].length = __elesize;
		__wrs[i].next = nullptr,
		__wrs[i].sg_list = &__sg_lists[i],
		__wrs[i].num_sge = 1,
		__wrs[i].opcode  = IBV_WR_SEND;
		__ringqueue[i] = &__wrs[i];
		__count.post();
		__rear += 1;
	}
}

rfts::spsc_fix_mem_pool::~spsc_fix_mem_pool(void) noexcept
{
	while( __addr && __count.getvalue() != MEM_POOL_CAPACITY){};
	delete [] __ringqueue;
	__ringqueue = nullptr;
	delete [] __sg_lists;
	__sg_lists = nullptr;
	delete [] __wrs;
	__wrs = nullptr;
	delete [] __addr;
	__addr = nullptr;
}



const void* rfts::spsc_fix_mem_pool::get_mempool_addr(void) const noexcept
{
	return __addr;
}


int rfts::spsc_fix_mem_pool::get_mempool_length(void) const noexcept
{
	return __length;
}

ibv_send_wr* rfts::spsc_fix_mem_pool::malloc(void) noexcept
{
	int front = 0, rear = 0, temp = 0;

}

void rfts::spsc_seq_mem_pool::free(void) noexcept
{
	int front = 0, rear = 0;
	front = __front.load(std::memory_order_relaxed);
	rear = __rear.load(std::memory_order_acquire);
	if (rear == front)
		return;
	if (++front >= MEM_POOL_CAPACITY)
		front -= MEM_POOL_CAPACITY;
	__front.store(front, std::memory_order_release);
}

