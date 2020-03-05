#pragma once
#ifndef RFTS_MEM_POOL_H
	#define RFTS_MEM_POOL_H
#include"trans_args.hpp"
#include<iostream>
#include<mutex>
#include<atomic>
#include<stdexcept>
#include<cstdlib>
namespace rfts
{
	const int MEM_POOL_CAPACITY = 1000;//1000次传输
	class spsc_seq_mem_pool
	{
	private:
		const int		elesize;	//每个队列元素的大小
		const int		length;		//buf长度
		unsigned char*		addr;		//buf地址
		std::atomic_int32_t	capacity;	//队列容量
		std::atomic_int32_t	front, rear;
	public:
		spsc_seq_mem_pool(const transargs& transargs) noexcept;
		
		spsc_seq_mem_pool(const spsc_seq_mem_pool & ref) = delete;
		spsc_seq_mem_pool& operator = (const spsc_seq_mem_pool & ref) = delete;
		~spsc_seq_mem_pool(void) noexcept;

		void*		rmalloc(void);
		void		rfree(void);
		const void*	get_mempool_addr(void) const noexcept;
		int		get_mempool_length(void) const noexcept;
	};



	class mpc_link_mem_pool
	{
	private:
		struct node
		{
			void* addr;
			struct node* next;
		};
		node* head;//链表头结点
		node* tail;//链表尾部节点
		std::atomic_int size;//已经使用的元素
		const int elesize;//每个队列元素的大小
		const int length;//buf长度
		const int capacity = MEM_POOL_CAPACITY;//buf容量
		unsigned char* addr;//buf地址
	public:
		mpc_link_mem_pool(const transargs& transargs) noexcept;
		mpc_link_mem_pool(const mpc_link_mem_pool&) = delete ;
		mpc_link_mem_pool&  operator = (const mpc_link_mem_pool&) = delete;
		~mpc_link_mem_pool(void) noexcept;
	};
}



#endif /* end of include guard: RFTS_MEM_POOL_H */
