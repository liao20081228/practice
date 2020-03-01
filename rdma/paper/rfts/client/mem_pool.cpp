#include"mem_pool.hpp"

rfts::seq_mem_pool::seq_mem_pool(const trans_args& transargs) noexcept:
	elesize(transargs.afreq / transargs.tfreq * 
		transargs.node_num * transargs.sensor_num *
		transargs.kind * transargs.size * 2)
	,length(elesize * 100),capacity(length/elesize)
	,addr(new unsigned char[length]())
	,front(0),rear(0)
{
}

rfts::seq_mem_pool::seq_mem_pool(seq_mem_pool&& ref) noexcept:
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


rfts::seq_mem_pool& rfts::seq_mem_pool::operator = (seq_mem_pool&& ref) noexcept
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

rfts::seq_mem_pool::~seq_mem_pool(void) noexcept
{
	while(front == rear && addr)
	{
		delete [] addr;
		break;
	}
}


const void* rfts::seq_mem_pool::get_real_addr(void) const noexcept
{
	return addr;
}


int rfts::seq_mem_pool::get_real_length(void) const noexcept
{
	return length;
}

void* rfts::seq_mem_pool::rmalloc(void)
{
	int next = (rear + 1) % capacity;
	if( next == front)
		throw std::logic_error("no free mem");
	void* temp = addr + rear * elesize;
	rear = next;
	return temp;
}

void rfts::seq_mem_pool::rfree(void)
{
	if(rear == front)
		return;
	front = (front + 1) % capacity;
}







