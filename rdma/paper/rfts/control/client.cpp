#include"../common/comm.hpp"

int main()
{
	rfts::transargs ctsas;
	ctsas.afreq = 500000000;
	ctsas.tfreq = 10000000;
	ctsas.size = sizeof(rfts::data);
	ctsas.kind = 1;
	ctsas.sensor_num = 8;
	ctsas.node_num = 1;

	pshmem sheme();
}
