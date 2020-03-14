#include"../trans_args.hpp"
#include"../mem_pool.hpp"
#include"../get_clock.h"
#include<thread>
#include<iostream>
#include<unistd.h>
#include"../queue.hpp"
using namespace rfts;
const int testnum=20;
rfts::spsc_queue<ibv_send_wr*> queue(MEM_POOL_CAPACITY);

void fun1(spsc_fix_mem_pool&);
void fun2(spsc_fix_mem_pool&);
int main()
{
	trans_args transargs=
	{	
		.afreq = 500,
		.tfreq = 1,
		.size_per_data = sizeof(data),
		.kind_per_sensor = 1,
		.sensor_num_per_node = 8,
		.node_num = 1
	};

	spsc_fix_mem_pool mempool(transargs);
	std::cout << mempool.get_mempool_length() << std::endl;
	std::cout << sizeof(ibv_send_wr*) << "," << sizeof(ibv_send_wr) <<"\n";
	std::thread b(fun2,std::ref(mempool));
	std::thread a(fun1,std::ref(mempool));
	a.join();
	b.join();
}

void fun1(spsc_fix_mem_pool& mempool)
{
	ibv_send_wr* addr = nullptr;
	long double mean1 = 0;
	cycles_t s=0;
	cycles_t e=0;
	double mhz;
	for(int i=0; i<testnum;i++)
	{ 
		mhz = get_cpu_mhz(0);
		s=get_cycles();
		addr=mempool.malloc();
		e=get_cycles();
		mean1= mean1 + ( e-s ) / mhz * 1000;
		std::cout << addr <<", malloc mean:" << mean1/(i+1) <<std::endl;
		queue.put(addr);
	}
}
void fun2(spsc_fix_mem_pool& mempool)
{
	long double mean1 = 0;
	cycles_t s=0;
	cycles_t e=0;
	double mhz =0;
	for(int i=0; i<testnum;i++)
	{ 
		mhz = get_cpu_mhz(0);
		ibv_send_wr* temp = queue.get();
		s=get_cycles();
		mempool.free(temp);
		e=get_cycles();
		mean1= mean1 + ( e-s ) / mhz * 1000;
		std::cout << temp << ",free mean:" << mean1/(i+1)<<std::endl;
	}
}

