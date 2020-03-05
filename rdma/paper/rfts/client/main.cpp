#include"../common/custom_sem.hpp"
#include"../common/custom_shmem.hpp"
#include"../common/trans_args.hpp"
#include"../common/mem_pool.hpp"
#include"../common/trans_args.hpp"

#include<thread>
#include<mutex>
#include<condition_variable>


int main()
{
	pshmem shmem("/rfts_pshmem", sysconf(_SC_PAGESIZE), O_RDWR | O_CREAT,
		   REGULAR_FILE_MODE, PROT_READ);
	psem sem;

}
