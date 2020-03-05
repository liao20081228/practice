#include"../common/comm.hpp"
#include<thread>
#include<mutex>
#include<condition_variable>


int main()
{
	pshmem shmem("/rfts_pshmem", sysconf(_SC_PAGESIZE), O_RDWR | O_CREAT,
		   REGULAR_FILE_MODE, PROT_READ);
	psem sem("/rfts_psem");
	sem.wait();
	
	rfts::transargs tsas;
	if (sizeof(tsas) != shmem.mread(&tsas, sizeof(tsas), sizeof(tsas))
	{
		
	}

}
