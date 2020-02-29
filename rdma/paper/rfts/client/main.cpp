#include"trans_args.hpp"
#include"mem_pool.hpp"
#include<iostream>
#include"get_clock.h"
int main()
{
	using namespace rfts;
	struct trans_args transargs=
	{
		.afreq = 500,
		.tfreq = 1,
		.size = 20,
		.kind = 1,
		.sensor_num = 8,
		.node_num = 1
	};
	class mem_pool mempool(transargs);

	std::cout << mempool.get_real_length() << std::endl;

	void * addr = nullptr;
	mempool.rfree();
	double mean1 = 0;
	double mean2 = 0;
	cycles_t s=0;
	cycles_t e=0;
	double mhz = 0;
	for(int i=0; i<10000;i++)
	{
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
	}
	std::cout << "malloc mean:" << mean1/10000 << "," << "free mean:"<< mean2/10000<<std::endl;
	return 0;
}
