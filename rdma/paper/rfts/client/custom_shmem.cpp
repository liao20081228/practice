#include"custom_shmem.hpp"

pshmem::pshmem(const char* name, size_t size, int oflag, mode_t mode, int prot,
		int flags, off_t offset) noexcept:
	fd(shm_open(name, oflag, mode))
{
	if (fd < 0)
		PERR(pshmem::shm_open);
	if (ftruncate(fd, size))
	{
		close(fd);
		PERR(pshmem::ftruncate);
	}
	buf = mmap(nullptr, size, prot, flags, fd, offset);
	if (buf == MAP_FAILED)
	{
		close(fd);
		PERR(pshmem::mmap);
	}
}


pshmem::pshmem(pshmem&& ref) noexcept: fd(ref.fd), buf(ref.buf), length(ref.length)
{
	ref.fd = -1;
	ref.buf = nullptr;
	ref.length = 0;
}


pshmem::~pshmem(void) noexcept
{
	if (buf)
		munmap(buf, length);
	if (fd)
		close(fd);
}


void* pshmem::getaddr(void) const noexcept
{
	return buf;
}

int pshmem::sync(int flags) const noexcept
{
	int ret = msync(buf, length, flags);
	if (ret && errno == EINVAL)
		PERR(pshmem::msync);
	return ret;
}


ssize_t pshmem::read(void* buf, size_t len, off_t offset) const noexcept
{
	if (offset >= static_cast<off_t>(length))
	{
		errno = EINVAL;
		PERR(pshmem::read)
	}

}
