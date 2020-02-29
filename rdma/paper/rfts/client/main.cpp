#include"trans_args.hpp"
#include"mem_pool.hpp"
int main()
{
	using namespace rfts;
	trans_args transargs=
	{
		.afreq = 500,
		.tfreq = 1,
		.size = 20,
		.kind = 1,
		.sensor_num = 8,
		.node_num = 1
	};
	mempool(transargs);
}
