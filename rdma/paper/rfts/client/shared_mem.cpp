#include"shared_mem.hpp"

shmem::shmem(const char* name, int size, int oflag, mode_t mode)
{
	fd= shm_open(name, oflag, mode);
	if(fd <= 0)
	{
		switch(errno)
		{
			case EACCES:
			err
		}
	}
}