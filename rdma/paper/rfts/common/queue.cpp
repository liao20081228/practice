#include"queue.hpp"

template<typename T>
rfts::spsc_queue<T>::spsc_queue(unsigned int size) noexcept
	: __queue(new T[size]())
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
T rfts::spsc_queue<T>::put(T e) noexcept
{

}
