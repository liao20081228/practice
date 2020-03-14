#pragma once
#ifndef HPP_QUEUE_HPP
	#define HPP_QUEUE_HPP

#include"custom_sem.hpp"

namespace rfts
{
extern const unsigned int MEM_POOL_CAPACITY;
template<typename T>
class spsc_queue
{
private:
	T*			__queue;
	size_t			__size;
	unsigned int		__front,__rear;
	custom::posix_sem	__count;
public:
	explicit spsc_queue(unsigned int size = MEM_POOL_CAPACITY) noexcept;
	~spsc_queue(void) noexcept;
	spsc_queue(const spsc_queue&) = delete;
	spsc_queue(const spsc_queue&&) = delete;
	spsc_queue& operator=(const spsc_queue&) = delete;
	spsc_queue& operator=(spsc_queue&&) = delete;
	void put(T e) noexcept;
	T get(void) noexcept;
};

}








#endif /* end of include guard: HPP_CUSTOM_QUEUE_HPP */
