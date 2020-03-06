#include"trans_args.hpp"
#include"mem_pool.hpp"
#include"get_clock.h"
#include<thread>
#include<iostream>
#include<unistd.h>

using namespace rfts;
const int testnum=100;
void fun1(spsc_seq_mem_pool&);
void fun2(spsc_seq_mem_pool&);
int main()
{
	trans_args transargs=
	{	
		.afreq = 500,
		.tfreq = 1,
		.size_per_data = 20,
		.kind_per_sensor = 1,
		.sensor_num_per_node = 8,
		.node_num = 1
	};

	spsc_seq_mem_pool mempool(transargs);
	std::cout << mempool.get_mempool_length() << std::endl;

	std::thread a(fun1,std::ref(mempool));
	std::thread b(fun2,std::ref(mempool));
	a.join();
	b.join();
}

void fun1(spsc_seq_mem_pool& mempool)
{
	ibv_send_wr* addr = nullptr;
	long double mean1 = 0;
	cycles_t s=0;
	cycles_t e=0;
	double mhz = 0;
		mhz=get_cpu_mhz(0);
	for(int i=0; i<testnum;i++)
	{ 
		s=get_cycles();
		addr=mempool.malloc();
		e=get_cycles();
		std::cout<<addr->wr_id << "," << addr->sg_list->addr<< std::endl;
		mean1= mean1 + ( e-s ) / mhz * 1000;
	}
	std::cout << "malloc mean:" << mean1/testnum <<std::endl;
}
void fun2(spsc_seq_mem_pool& mempool)
{
	long double mean1 = 0;
	cycles_t s=0;
	cycles_t e=0;
	double mhz = 0;
		mhz=get_cpu_mhz(0);
	for(int i=0; i<testnum;i++)
	{ 
		s=get_cycles();
		mempool.free();
		e=get_cycles();
		mean1= mean1 + ( e-s ) / mhz * 1000;
	}
	std::cout << "free mean:" << mean1/testnum <<std::endl;
}

