#include"../common/comm.hpp"

int main()
{
	rfts::transargs tsas;
	tsas.afreq = 500000000;
	tsas.tfreq = 10000000;
	tsas.size = sizeof(rfts::data);
	tsas.kind = 1;
	tsas.sensor_num = 8;
	tsas.node_num = 1;

	pshmem shmem("/rfts_pshmem", sysconf(_SC_PAGESIZE), O_RDWR | O_CREAT,
			REGULAR_FILE_MODE, PROT_WRITE);
	psem ct_sem("/rfts_psem");
	shmem.mwrite(&shmem, sizeof(tsas), sizeof(tsas) );
	tsas<<std::cout;
}
