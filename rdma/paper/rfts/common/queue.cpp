#include"queue.hpp"

template<typename T>
rfts::spsc_queue<T>::spsc_queue(unsigned int size) noexcept
	: __queue(new T[size]())
	, __size(size)
	, __front(0)
	, __rear(0)
	, __count()
{
}

template<typename T>
rfts::spsc_queue<T>::~spsc_queue(void) noexcept
{
	delete [] __queue;
}

template<typename T>
void rfts::spsc_queue<T>::put(T e) noexcept
{
	__queue[__rear++] = e;
	if (__rear >= __size)
		__rear-=__size;
	__count.post();
}

template<typename T>
T rfts::spsc_queue<T>::get(void) noexcept
{
	__count.wait();
	T temp = __queue[__front++];
	if (__front >= __size)
		__front-=__size;
	return temp;
}
