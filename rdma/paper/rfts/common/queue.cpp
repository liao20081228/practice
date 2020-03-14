#include"queue.hpp"

template<typename T>
rfts::spsc_queue<T>::spsc_queue(unsigned int size) noexcept
	: __queue(new T[size]())
{

}
