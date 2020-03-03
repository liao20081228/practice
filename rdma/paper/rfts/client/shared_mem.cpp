#include"shared_mem.hpp"

shmem::shmem(const char* name, int size, int oflag, mode_t mode):
	fd(shm_open(name, oflag, mode))
{
	if(fd < 0)
		throw std::system_error(errno, std::generic_category(),
					"call shm_open() failed");
}
