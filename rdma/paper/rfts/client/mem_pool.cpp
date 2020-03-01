#include"mem_pool.hpp"

rfts::spc_seq_mem_pool::spc_seq_mem_pool(const trans_args& transargs) noexcept:
	elesize(transargs.afreq / transargs.tfreq * 
		transargs.node_num * transargs.sensor_num *
		transargs.kind * transargs.size * 2)
	,length(elesize * MEM_POOL_CAPACITY),capacity(100)
	,addr(new unsigned char[length]())
	,front(0),rear(0)
{
}

rfts::spc_seq_mem_pool::spc_seq_mem_pool(spc_seq_mem_pool&& ref) noexcept:
	elesize(ref.elesize), length(ref.length), capacity(ref.capacity),
	addr(ref.addr)
{
	front = ref.front;
	rear = ref.rear;
	ref.elesize = 0;
	ref.length  = 0;
	ref.front   = 0;
	ref.rear    = 0;
	ref.addr = nullptr;
	ref.capacity = 0;
}


rfts::spc_seq_mem_pool& rfts::spc_seq_mem_pool::operator = (spc_seq_mem_pool&& ref) noexcept
{
	if(this == &ref)
		return *this;
	elesize = ref.elesize;
	length = ref.length;
	addr = ref.addr;
	capacity = ref.capacity;
	front = ref.front;
	rear = ref.rear;

	ref.elesize = 0;
	ref.length  = 0;
	ref.front   = 0;
	ref.rear    = 0;
	ref.addr = nullptr;
	ref.capacity = 0;
	return *this;
}

rfts::spc_seq_mem_pool::~spc_seq_mem_pool(void) noexcept
{
	while(front == rear && addr)
	{
		delete [] addr;
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
	int next = (rear + 1) % capacity;
	if( next == front)
		throw std::logic_error("no free mem");
	void* temp = addr + rear * elesize;
	rear = next;
	return temp;
}

void rfts::spc_seq_mem_pool::rfree(void)
{
	if(rear == front)
		return;
	front = (front + 1) % capacity;
}


rfts::mpc_link_mem_pool::mpc_link_mem_pool(const trans_args& transargs) noexcept:
	elesize(transargs.afreq / transargs.tfreq * 
		transargs.node_num * transargs.sensor_num *
		transargs.kind * transargs.size * 2)
	,length(elesize * MEM_POOL_CAPACITY),capacity(MEM_POOL_CAPACITY)
	,addr(new unsigned char[length]())
{
	tail = head = new node;
	head->addr = head->next =  nullptr;

	for(int i = 0; i< capacity; ++i)
	{
		
	}
}




