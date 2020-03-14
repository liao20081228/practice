#pragma once
#ifndef HPP_CUSTOM_QUEUE_HPP
#define HPP_CUSTOM_QUEUE_HPP

#include"custom_sem.hpp"

template<typename T>
class spsc_queue
{
	T* queue;
	unsigned int __front,__rear;
	posix_sem __count;
};










#endif /* end of include guard: HPP_CUSTOM_QUEUE_HPP */
