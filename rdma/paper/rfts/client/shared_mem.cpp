#include"shared_mem.hpp"

shmem::shmem(const char* name, int oflag, mode_t mode):
	fd(shm_open(name,oflag,mode))
{
}
