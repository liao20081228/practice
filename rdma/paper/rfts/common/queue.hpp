#pragma once
#ifndef HPP_QUEUE_HPP
	#define HPP_CUSTOM_QUEUE_HPP

#include"custom_sem.hpp"

namespace rtfs
{
template<typename T>
class spsc_queue
{
private:
	T* queue;
	unsigned int __front,__rear;
	custom::posix_sem __count;
public:
	explicit spsc_queue(unsigned int size) noexcept;
	~spsc_queue(void) noexcept;
	spsc_queue(const spsc_queue&) = delete;
	spsc_queue(const spsc_queue&&) = delete;
	spsc_queue& operator=(const spsc_queue&) = delete;
	spsc_queue& operator=(spsc_queue&&) = delete;
	T put(T e) noexcept;
	T get(T e) noexcept;
};

}








#endif /* end of include guard: HPP_CUSTOM_QUEUE_HPP */
