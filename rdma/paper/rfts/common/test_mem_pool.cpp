#include"trans_args.hpp"
#include"mem_pool.hpp"
#include"get_clock.h"
#include<thread>
#include<iostream>


using namespace rfts;
const int testnum=10;
void fun(spsc_seq_mem_pool&);
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

	class spsc_seq_mem_pool mempool=spsc_seq_mem_pool(transargs);

	std::cout << mempool.get_real_length() << std::endl;
	
	std::thread a(fun,std::ref(mempool));
	std::thread b(fun,std::ref(mempool));
	a.join();
	b.join();
}

void fun(spsc_seq_mem_pool& mempool)
{
	void * addr = nullptr;
	mempool.free();
	long double mean1 = 0;
	long double mean2 = 0;
	cycles_t s=0;
	cycles_t e=0;
	double mhz = 0;
	for(int i=0; i<testnum;i++)
	{ 
		mhz=get_cpu_mhz(0);
		s=get_cycles();
		addr=mempool.malloc();
		e=get_cycles();
		mean1= mean1 + ( e-s ) / mhz * 1000;
		
		mhz=get_cpu_mhz(0);
		s=get_cycles();
		mempool.free();
		e=get_cycles();
		mean2= mean2 + ( e-s ) / mhz * 1000;
	}
	std::cout << "malloc mean:" << mean1/testnum << "," << "free mean:"<< mean2/testnum<<std::endl;
	return ;
}
