#include"trans_args.hpp"
#include"mem_pool.hpp"
#include<iostream>
#include"get_clock.h"
#include<thread>


using namespace rfts;
const int testnum=10;
void fun(seq_mem_pool&);
int main()
{
	trans_args transargs=
	{	
		.afreq = 500,
		.tfreq = 1,
		.size = 20,
		.kind = 1,
		.sensor_num = 8,
		.node_num = 1
	};

	seq_mem_pool mempool=seq_mem_pool(transargs);

	std::cout << mempool.get_real_length() << std::endl;
	
	std::thread a(fun,std::ref(mempool));
	std::thread b(fun,std::ref(mempool));
	std::thread c(fun,std::ref(mempool));
	a.join();
	b.join();
	c.join();
}

void fun(seq_mem_pool& mempool)
{
	void * addr = nullptr;
	mempool.rfree();
	long double mean1 = 0;
	long double mean2 = 0;
	cycles_t s=0;
	cycles_t e=0;
	double mhz = 0;
	for(int i=0; i<testnum;i++)
	{ 
		std::cout << "id: " << std::this_thread::get_id() << ",第几次: "<<i << std::endl;
		mhz=get_cpu_mhz(0);
		s=get_cycles();
		addr=mempool.rmalloc();
		e=get_cycles();
		mean1= mean1 + ( e-s ) / mhz * 1000;
		mhz=get_cpu_mhz(0);
		s=get_cycles();
		mempool.rfree();
		e=get_cycles();
		mean2= mean2 + ( e-s ) / mhz * 1000;
		std::cout<<"id "<< std::this_thread::get_id()<<","<<mempool.front<<","<<mempool.rear<<std::endl;
	}
	std::cout << "malloc mean:" << mean1/testnum << "," << "free mean:"<< mean2/testnum<<std::endl;
	return ;
}
