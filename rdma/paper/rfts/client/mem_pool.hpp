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
#ifdef MEM_POOL_SEQ_QUEUE
	template<>
	class mem_pool
	{
	private:
		const int elesize;//每个队列元素的大小
		const int length;//buf长度
		const int capacity;//队列容量
		unsigned char* const addr;//buf地址
	
		int front;//队首指针
		int rear;//队尾指针
	public:
		mem_pool(const trans_args& transargs) noexcept;
		mem_pool(const mem_pool & ref) = delete;
		mem_pool& operator = (const mem_pool & ref) = delete;
		~mem_pool(void) noexcept;
		void*		rmalloc(void);
		void		rfree(void);
		const void*	get_real_addr(void) const noexcept;
		int		get_real_length(void) const noexcept;
	};

#elif defined MEM_POOL_LINK_QUEUE
	class mem_pool 
	{
		private:
		public:
	}


#endif


};


#endif /* end of include guard: RFTS_MEM_POOL_H */
