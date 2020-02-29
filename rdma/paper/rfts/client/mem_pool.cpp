#include"mem_pool.hpp"

rfts::mempool::mempool(int afreq, int tfreq, int size, int sensor_num, int node_num, int kind):
	addr(new char[afreq / tfreq * size * kind* nodenum * 2]()),length(afreq/tfreq*2)
{
}
