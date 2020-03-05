#include"mem_pool.hpp"

rfts::spc_seq_mem_pool::spc_seq_mem_pool(const trans_args& transargs) noexcept:
	elesize(transargs.afreq / transargs.tfreq * 
		transargs.node_num * transargs.sensor_num *
		transargs.kind * transargs.size * 2)
	,length(elesize * MEM_POOL_CAPACITY), size(MEM_POOL_CAPACITY)
	,addr(new unsigned char[length]()),front(0),rear(0)
{
}


rfts::spc_seq_mem_pool::~spc_seq_mem_pool(void) noexcept
{
	while(front == rear && addr)
	{
		delete [] addr;
		addr=nullptr;
		break;
	}
}


const void* rfts::spc_seq_mem_pool::get_real_addr(void) const noexcept
{
	return addr;
}


int rfts::spc_seq_mem_pool::get_real_length(void) const noexcept
{
	return length;
}

void* rfts::spc_seq_mem_pool::rmalloc(void)
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

void rfts::spc_seq_mem_pool::rfree(void)
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


