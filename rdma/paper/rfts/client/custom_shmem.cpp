#include"custom_shmem.hpp"

pshmem::pshmem(const char* name, size_t size, int oflag, mode_t mode, int prot,
		int flags, off_t offset) noexcept:
	fd(shm_open(name, oflag, mode)), cur(0),protect(prot)
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

size_t pshmem::seek(off_t offset, int whence) noexcept
{
	uint64_t temp = 0;
	switch(whence)
	{
		case SEEK_SET:
			if (offset < 0 || offset >= static_cast<off_t>(length))
			{
				errno = EINVAL;
				PERR(pshmem::seek);
			}
			cur.store(offset, std::memory_order_release);
			return cur.load(std::memory_order_acquire);
		case SEEK_CUR:
			temp = cur.load(std::memory_order_acquire);
			do
			{
				if((static_cast<off_t>(temp) + offset)
					>= static_cast<off_t>(length)
					|| (temp + offset) < 0)
				{
					errno = EINVAL;
					PERR(pshmem::seek);
				}
			}while(!cur.compare_exchange_weak(temp, temp + offset,
							std::memory_order_acq_rel,
							std::memory_order_acquire));
			return temp;
		case SEEK_END:
			if (offset > 0 || offset <= static_cast<off_t>(-length))
			{
				errno = EINVAL;
				PERR(pshmem::seek);
			}
			cur.store(length - 1  + offset, std::memory_order_release);
			return cur.load(std::memory_order_acquire);
		default:
			errno = EINVAL;
			PERR(pshmem::seek);
			break;
	}
}

ssize_t pshmem::read(void* buf, size_t buf_len, size_t nbytes) const noexcept
{
	if ((protect & PROT_READ) == 0)
	{
		errno = EPERM;
		PERR(pshmem::read);
	}
	if (!buf || buf_len < nbytes)
	{
		errno =  EINVAL;
		PERR(pshmem::read);
	}
	if (!buf_len || !nbytes)
		return 0;
	memset(buf, 0, buf_len);
	uint64_t temp = cur.load(std::memory_order_acquire),
		 temp0 = 0,
		reallen = 0;
	do
	{
		reallen  =  (temp + nbytes) > length ? (length - temp) : nbytes;
		memcpy(buf, static_cast<unsigned char*>(addr) + cur, reallen);
		temp0 =( temp + nbytes) > length ? length - 1 : temp + nbytes;
	}while(!cur.compare_exchange_weak(temp, temp0));
	return reallen;
}