#pragma once
#ifndef RFTS_MEM_POOL_H
	#define RFTS_MEM_POOL_H
#include"trans_args.hpp"
#include<iostream>
#include<mutex>
#include<atomic>
#include<exception>

namespace rfts
{
	class seq_mem_pool
	{
	private:
		int elesize;//每个队列元素的大小
		int length;//buf长度
		int capacity;//队列容量
		unsigned char*  addr;//buf地址
	
		int front;//队首指针
		int rear;//队尾指针
	public:
		seq_mem_pool(const trans_args& transargs) noexcept;
		seq_mem_pool(const seq_mem_pool & ref) = delete;
		//seq_mem_pool(seq_mem_pool&& ref) noexcept;
		seq_mem_pool& operator = (const seq_mem_pool & ref) = delete;
		//seq_mem_pool& operator = (seq_mem_pool&& ref) noexcept;
		~seq_mem_pool(void) noexcept;

		void*		rmalloc(void);
		void		rfree(void);
		const void*	get_real_addr(void) const noexcept;
		int		get_real_length(void) const noexcept;
	};

}


#endif /* end of include guard: RFTS_MEM_POOL_H */
