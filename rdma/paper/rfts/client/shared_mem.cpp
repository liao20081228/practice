#include"shared_mem.hpp"

shmem::shmem(const char* name, off_t size, int oflag, mode_t mode, int prot,
		int flags, off_t offset):
	fd(shm_open(name, oflag, mode))
{
	if (fd < 0)
		throw std::system_error(errno, std::generic_category(),
					"call shm_open() failed");
	if (ftruncate(fd, size))
	{
		close(fd);
		throw std::system_error(errno, std::generic_category(),
					"call ftruncate failed");
	}
	buf = mmap(nullptr, size, prot, flags,fd, offset);
	if (buf)
}
