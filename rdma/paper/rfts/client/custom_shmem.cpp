#include"custom_shmem.hpp"

pshmem::pshmem(const char* name, size_t size, int oflag, mode_t mode, int prot,
		int flags, off_t offset) noexcept:
	fd(shm_open(name, oflag, mode)), offset(0), flag(0)
{
	if (fd < 0)
		PERR(pshmem::shm_open);
	if (ftruncate(fd, size))
	{
		close(fd);
		PERR(pshmem::ftruncate);
	}
	addr = mmap(nullptr, size, prot, flags, fd, offset);
	if (addr == MAP_FAILED)
	{
		close(fd);
		PERR(pshmem::mmap);
	}
}


pshmem::pshmem(pshmem&& ref) noexcept: fd(ref.fd), addr(ref.addr), length(ref.length)
{
	ref.fd = -1;
	ref.addr = nullptr;
	ref.length = 0;
}


pshmem::~pshmem(void) noexcept
{
	if (addr)
		if(munmap(addr, length))
			PERR(pshmem::munmap);
	if (fd)
		close(fd);
}


void* pshmem::getaddr(void) const noexcept
{
	return addr;
}

int pshmem::sync(int flags) const noexcept
{
	int ret = msync(addr, length, flags);
	if (ret && errno == EINVAL)
		PERR(pshmem::msync);
	return ret;
}

int lseek

ssize_t pshmem::read(void* buf, size_t buf_len, size_t len, off_t offset) const noexcept
{
	if (!buf)
	{
		errno =  EINVAL;
		PERR(pshmem::read);
	}
	memset(buf, 0, len);
	if (!buf_len || !len)
		return 0;
	if (offset > static_cast<off_t>(length - 1) || offset < 0 )
	{
		errno =  EINVAL;
		PERR(pshmem::read);
	}
}
