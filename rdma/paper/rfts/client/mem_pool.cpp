#include"mem_pool.hpp"

rfts::mempool::mempool(const trans_args& transargs):
	length(transargs.afreq / transargs.tfreq * 
		transargs.node_num * transargs.sensor_num *
		transargs.kind * transargs.size * 100 * 2),
	addr(),front(),rear(),elesize()
{
}
