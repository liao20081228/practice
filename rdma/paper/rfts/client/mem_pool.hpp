#pragma once
#ifndef RFTS_MEM_POOL_H
	#define RFTS_MEM_POOL_H

#ifndef RFTS_CLIENT
	#define RFTS_CLIENT
#endif

#include<iostream>
#include<mutex>
#include<atomic>
#include"trans_args.hpp"
namespace rfts
{
	class mempool
	{
	private:
		const int elesize;//每个队列元素的大小
		const int length;//长度
		void* const addr;//原始地址

		int front;//队首指针
		int rear;//队尾指针
	public:
		mempool(const trans_args& transargs) noexcept;
		void* malloc(int) noexcept;
		int  free(void*) noexcept;
		const void*  get_real_addr(void) const noexcept;
		int  get_read_length(void) const noexcept;
	};
}

#endif /* end of include guard: RFTS_MEM_POOL_H */
