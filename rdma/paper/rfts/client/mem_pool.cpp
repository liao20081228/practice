#include"mem_pool.hpp"

rfts::mempool::mempool(int afreq, int tfreq, int size, int kind, int nodenum):
	addr(new char[afreq / tfreq * size * kind](0))
{
	
}
