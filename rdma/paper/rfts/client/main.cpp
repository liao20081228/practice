#include"../common/comm.hpp"
#include<thread>
#include<mutex>
#include<condition_variable>


int main()
{
	pshmem shmem("/rfts_pshmem", sysconf(_SC_PAGESIZE), O_RDWR | O_CREAT,
		   REGULAR_FILE_MODE, PROT_READ);
	psem ct_sem("/rfts_psem");
	ct_sem.wait();
	
	rfts::transargs tsas;
	shmem.mread(&tsas, sizeof(tsas), sizeof(tsas));
	tsas << std::cout;
	
}
