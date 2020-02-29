#include"trans_args.hpp"
#include"mem_pool.hpp"
#include<iostream>
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
	for(int i = 0; ;i++)
	{
		addr = mempool.rmalloc();
	}
	return 0;
}
