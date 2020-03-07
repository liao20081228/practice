#include<iostream>
#include"mem_pool.hpp"

int main(void)
{

	rfts::trans_args c;
	rfts::spsc_seq_mem_pool a = rfts::spsc_seq_mem_pool(c);
	return 0;
}
