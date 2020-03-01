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
	const int MEM_POOL_CAPACITY = 100;
	class spc_seq_mem_pool
	{
	private:
		const int elesize;//每个队列元素的大小
		const int length;//buf长度
		std::atomic_int  capacity;//队列容量
		unsigned char* addr;//buf地址
		int front;
		int rear;
	public:
		spc_seq_mem_pool(const trans_args& transargs) noexcept;
		spc_seq_mem_pool(const spc_seq_mem_pool & ref) = delete;
		spc_seq_mem_pool& operator = (const spc_seq_mem_pool & ref) = delete;
		~spc_seq_mem_pool(void) noexcept;

		void*		rmalloc(void);
		void		rfree(void);
		const void*	get_real_addr(void) const noexcept;
		int		get_real_length(void) const noexcept;
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
		mpc_link_mem_pool(const trans_args& transargs) noexcept;
		mpc_link_mem_pool(const mpc_link_mem_pool&) = delete ;
		mpc_link_mem_pool&  operator = (const mpc_link_mem_pool&) = delete;
		~mpc_link_mem_pool(void) noexcept;
	};
}



#endif /* end of include guard: RFTS_MEM_POOL_H */
