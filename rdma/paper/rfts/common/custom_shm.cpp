#include"custom_shm.hpp"

posix_shmem::posix_shmem(const char* name, size_t size, int oflag, mode_t mode, int prot,
		int flags, off_t offset) noexcept: __name(name)
	, __fd(shm_open(__name, oflag, mode)),__length(size), __cur(0), __protect(prot)
{
	if (__fd < 0)
		PERR(posix_shmem::shm_open);
	if (ftruncate(__fd, size))
	{
		close(__fd);
		PERR(posix_shmem::ftruncate);
	}
	__addr = mmap(nullptr, size, prot, flags, __fd, offset);
	if (__addr == MAP_FAILED)
	{
		close(__fd);
		PERR(posix_shmem::mmap);
	}
}


posix_shmem::posix_shmem(posix_shmem&& ref) noexcept: __name(ref.__name),__fd(ref.__fd), __addr(ref.__addr)
	, __length(ref.__length),__cur(ref.__cur.load(std::memory_order_acquire))
	, __protect(ref.__protect)
{

	ref.__fd = -1;
	ref.__addr = nullptr;
	ref.__length = 0;
	ref.__name = nullptr;
	ref.__protect = 0;
	ref.__cur = 0;
}


posix_shmem::~posix_shmem(void) noexcept
{
	if (__addr)
		if(munmap(__addr, __length))
			PERR(posix_shmem::munmap);
	if (__fd)
		close(__fd);
	if (__name)
		shm_unlink(__name);
}


void* posix_shmem::get_addr(void) const noexcept
{
	return __addr;
}

void posix_shmem::clear(void) noexcept
{
	memset(__addr, 0, __length);
	__cur.store(0, std::memory_order_release);
}


int posix_shmem::sync(int flags) const noexcept
{
	int ret = ::msync(__addr, __length, flags);
	if (ret && errno == EINVAL)
		PERR(posix_shmem::sync);
	return ret;
}

size_t posix_shmem::seek(off_t offset, int whence) noexcept
{
	uint64_t temp = 0;
	switch(whence)
	{
		case SEEK_SET:
			if (offset < 0 || offset >= static_cast<off_t>(__length))
			{
				errno = EINVAL;
				PERR(posix_shmem::seek);
			}
			__cur.store(offset, std::memory_order_release);
			return __cur.load(std::memory_order_acquire);
		case SEEK_CUR:
			temp = __cur.load(std::memory_order_acquire);
			do
			{
				if((static_cast<off_t>(temp) + offset)
					>= static_cast<off_t>(__length)
					|| (temp + offset) < 0)
				{
					errno = EINVAL;
					PERR(posix_shmem::mseek);
				}
			}while (!__cur.compare_exchange_weak(temp, temp + offset,
							std::memory_order_acq_rel,
							std::memory_order_acquire));
			return temp;
		case SEEK_END:
			if (offset > 0 || offset <= static_cast<off_t>(-__length))
			{
				errno = EINVAL;
				PERR(posix_shmem::seek);
			}
			__cur.store(__length - 1  + offset, std::memory_order_release);
			return __cur.load(std::memory_order_acquire);
		default:
			errno = EINVAL;
			PERR(posix_shmem::seek);
			break;
	}
}

size_t posix_shmem::tell(void) const noexcept
{
	return __cur.load(std::memory_order_acquire);
}

void posix_shmem::__access(void* buf, size_t buf_len, size_t nbytes, bool reset,
		bool is_read) noexcept
{
	if ((is_read && !(__protect & PROT_READ)) || (!is_read && !(__protect & PROT_WRITE)))
	{
		errno = EPERM;
		if (is_read)
			PERR(posix_shmem::read);
		PERR(posix_shmem::mwrite);
	}

	if (!buf || buf_len < nbytes)
	{
		errno =  EINVAL;
		if (is_read)
			PERR(posix_shmem::read);
		PERR(posix_shmem::mwrite);
	}
	if (!nbytes)
		return;
	if (is_read)
		memset(buf, 0, buf_len);
	if (reset)
		seek(0, SEEK_SET);
	uint64_t temp = __cur.load(std::memory_order_acquire);
	do
	{
		if (temp + nbytes > __length)
		{
			errno =  EINVAL;
			if (is_read)
				PERR(posix_shmem::mread);
			PERR(posix_shmem::mwrite);
		}
		if (is_read)
			memcpy(buf, static_cast<unsigned char*>(__addr) + __cur, nbytes);
		else
			memcpy(static_cast<unsigned char*>(__addr) + temp, buf, nbytes);
	}while (!__cur.compare_exchange_weak(temp, temp +nbytes, std::memory_order_acq_rel,
			std::memory_order_acquire));
}

void posix_shmem::read(void* buf, size_t buf_len, size_t nbytes, bool reset) noexcept
{
	__access(buf, buf_len, nbytes, reset, true);
}

void posix_shmem::write(void* buf, size_t buf_len, size_t nbytes, bool reset) noexcept
{
	__access(buf, buf_len, nbytes, reset, false);
}

