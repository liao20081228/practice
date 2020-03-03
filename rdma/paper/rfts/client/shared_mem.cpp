#include"shared_mem.hpp"

shmem::shmem(const std::string name, int oflag, mode_t mode):
	fd(shm_open(name.c_str(),oflag,mode))
{
}
