#include"mem_pool.hpp"

rfts::mempool::mempool(int afreq, int tfreq, int size, int tou, int nodenum):
	addr(new char[afreq / tfreq * size * kind* nodenum * 2]()),length(afreq/tfreq*2)
{
}
