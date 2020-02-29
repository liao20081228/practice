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
	using std::mutex;
	class mempool
	{
	private:
		void* const addr;//原始地址
		const int length;//长度

		int elesize;//每个元素的大小
		int front;//队首指针
		int rear;//队尾指针
		const int capacity;//队伍容量
		int full;//队满
#ifndef RFTS_CLIENT
		mutex mutext_mem_pool;
#endif
	public:
		mempool(const trans_args& transargs);
		void* malloc(int) noexcept;
		int  free(void*) noexcept;
		const void*  get_real_addr() const;
	};
}

#endif /* end of include guard: RFTS_MEM_POOL_H */
