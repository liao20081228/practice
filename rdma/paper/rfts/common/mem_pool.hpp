#pragma once
#ifndef HPP_RFTS_MEM_POOL_HPP
	#define HPP_RFTS_MEM_POOL_HPP
#include"trans_args.hpp"
#include"custom_sem.hpp"
#include<iostream>
#include<mutex>
#include<atomic>
#include<stdexcept>
#include<cstdlib>
#include<infiniband/verbs.h>
#include<array>


#ifndef CUSTOM_PRINT_ERROR_INFO_AND_EXIT_WITH_ERRNO
	#define _PERR(a) {perror(#a);exit(errno);}
	#define PERR(c) _PERR(c() failed)
#endif
namespace rfts
{
const int MEM_POOL_CAPACITY = 1000;//1000次传输
class spsc_seq_mem_pool
{
private:
	const int		__elesize;	//每个队列元素的大小
	const int		__length;	//buf长度
	unsigned char*		__addr;		//buf地址
	std::atomic_int32_t	__front, __rear; //队首、队尾标记
	ibv_send_wr*		__ringqueue;
	ibv_sge*		__sg_list;
	uint64_t		__wr_id;
public:
	explicit spsc_seq_mem_pool(const trans_args& transargs) noexcept;
		 spsc_seq_mem_pool(const spsc_seq_mem_pool & ref) = delete;
		 spsc_seq_mem_pool(spsc_seq_mem_pool&& ref) = delete;

		~spsc_seq_mem_pool(void) noexcept;

	spsc_seq_mem_pool& operator = (spsc_seq_mem_pool& ref) = delete;
	spsc_seq_mem_pool& operator = ( spsc_seq_mem_pool&& ref) = delete;
	ibv_send_wr*	malloc(void) noexcept;
	void		free(void) noexcept;
	const void*	get_mempool_addr(void) const noexcept;
	int		get_mempool_length(void) const noexcept;
};

class spsc_fix_mem_pool
{
private:
	const int		__elesize;	//每个队列元素的大小
	const int		__length;	//buf长度
	unsigned char*		__addr;		//buf地址
	size_t			__front, __rear; //队首、队尾标记
	ibv_send_wr*		__wr;
	ibv_sge*		__sg_list;
	uint64_t		__wr_id;
	ibv_send_wr**		__ringqueue

public:
	explicit spsc_fix_mem_pool(const trans_args& transargs) noexcept;
		 spsc_fix_mem_pool(const spsc_fix_mem_pool & ref) = delete;
		 spsc_fix_mem_pool(spsc_fix_mem_pool&& ref) = delete;

		~spsc_fix_mem_pool(void) noexcept;

	spsc_fix_mem_pool& operator = (spsc_fix_mem_pool& ref) = delete;
	spsc_fix_mem_pool& operator = (spsc_fix_mem_pool&& ref) = delete;
	
	ibv_send_wr*	malloc(void) noexcept;
	void		free(void) noexcept;
	const void*	get_mempool_addr(void) const noexcept;
	int		get_mempool_length(void) const noexcept;
};

/*
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
};*/
} //namespace rfts



#endif /* end of include guard: HPP_RFTS_MEM_POOL_HPP */
