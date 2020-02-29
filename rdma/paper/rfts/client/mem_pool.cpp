#include"mem_pool.hpp"

rfts::mempool::mempool(const trans_args& transargs) noexcept:
	elesize(transargs.afreq / transargs.tfreq * 
		transargs.node_num * transargs.sensor_num *
		transargs.kind * transargs.size * 2),
	length(elesize * 100),capacity(length/elesize),addr(new unsigned char[length]()),front(0),rear(0)
{
}


rfts::mempool::~mempool(void) noexcept
{
	while(front == rear)
		delete [] addr;
}


const void* rfts::mempool::get_real_addr(void) const noexcept
{
	return addr;
}


int rfts::mempool::get_real_length(void) const noexcept
{
	return length;
}

void* rfts::mempool::rmalloc(void) noexcept
{
	if(rear-)
	void* temp = addr + front * elesize; 
	if()
	{
i		rear = (rear + 1) % capacity;
	}
}
