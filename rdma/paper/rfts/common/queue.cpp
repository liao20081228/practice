#include"queue.hpp"

template<typename T>
rfts::spsc_queue<T>::spsc_queue(unsigned int size) noexcept
	: __queue(new T[size]())
	, __front(0)
	, __rear(0)
	, __count(0,0)
{
}
