#include"mem_pool.hpp"

template<typename T>
rfts::mem_pool<T>::mem_pool(const trans_args& transargs) noexcept:
	elesize(transargs.afreq / transargs.tfreq * 
		transargs.node_num * transargs.sensor_num *
		transargs.kind * transargs.size * 2),
	length(elesize * 100),capacity(length/elesize),addr(new unsigned char[length]()),front(0),rear(0)
{
}


rfts::mem_pool::~mem_pool(void) noexcept
{
	while(front == rear)
	{
		delete [] addr;
		break;
	}
}


const void* rfts::mem_pool::get_real_addr(void) const noexcept
{
	return addr;
}


int rfts::mem_pool::get_real_length(void) const noexcept
{
	return length;
}

void* rfts::mem_pool::rmalloc(void)
{
	int next = (rear + 1) % capacity;
	if( next == front)
		throw std::logic_error("no free mem");
	void* temp = addr + rear * elesize;
	rear = next;
	return temp;
}

void rfts::mem_pool::rfree(void)
{
	if(rear == front)
		return;
	front = (front + 1) % capacity;
}







