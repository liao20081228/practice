#include"mem_pool.hpp"

rfts::spsc_seq_mem_pool::spsc_seq_mem_pool(const transargs& transargs) noexcept
	: __elesize(transargs.afreq / transargs.tfreq * transargs.node_num *
		transargs.sensor_num_per_node * transargs.kind_per_sensor *
		transargs.size_per_data * 2)
	, __length(__elesize * MEM_POOL_CAPACITY)
	, __addr{new unsigned char[__length]()}
	, __front(0)
	, __rear(0)
{
	for(int i{0}; i < MEM_POOL_CAPACITY; ++i)
	{
		__sg_list.at(i).addr = (uint64_t)(__addr + i * __elesize);
		__sg_list.at(i).length = __elesize;
	}
}


rfts::spsc_seq_mem_pool::~spsc_seq_mem_pool(void) noexcept
{
	while(front == rear && addr)
	{
		delete [] addr;
		addr=nullptr;
		break;
	}
}


const void* rfts::spsc_seq_mem_pool::get_real_addr(void) const noexcept
{
	return addr;
}


int rfts::spsc_seq_mem_pool::get_real_length(void) const noexcept
{
	return length;
}

void* rfts::spsc_seq_mem_pool::rmalloc(void)
{
	int temp = 0;

	do
	{
		temp = size;
	}while(cas())


	void* temp = addr + rear * elesize;
	
	rear = (rear+1) % MEM_POOL_CAPACITY;
	return temp;
}

void rfts::spsc_seq_mem_pool::rfree(void)
{
	if(rear == front)
		return;
	front = (front + 1) % MEM_POOL_CAPACITY;
}


rfts::mpc_link_mem_pool::mpc_link_mem_pool(const trans_args& transargs) noexcept:
	size(0),elesize(transargs.afreq / transargs.tfreq * 
		transargs.node_num * transargs.sensor_num *
		transargs.kind * transargs.size * 2)
	,length(elesize * MEM_POOL_CAPACITY)
	,addr(new unsigned char[length]())
{
	tail = head = (node*)malloc(sizeof(node));//头结点
	head->addr = head->next =  nullptr;

	for(int i = 0; i< capacity; ++i)
	{
		node* temp = (node*)malloc(sizeof(node));//new比malloc更加耗时
		temp->addr = addr + i * elesize;
		temp->next = nullptr;
		tail->next = temp;
	        tail = temp;
	}
}

rfts::mpc_link_mem_pool::~mpc_link_mem_pool(void) noexcept
{
	while(addr && size == 0)
	{

	}
}



