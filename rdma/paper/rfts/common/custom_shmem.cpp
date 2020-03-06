#include"custom_shmem.hpp"

posix_pshmem::posix_pshmem(const char* name, size_t size, int oflag, mode_t mode, int prot,
		int flags, off_t offset) noexcept: __name(name)
	, __fd(shm_open(name, oflag, mode)),__length(size), __cur(0), __protect(prot)
{
	if (__fd < 0)
		PERR(posix_pshmem::shm_open);
	if (ftruncate(__fd, size))
	{
		close(__fd);
		PERR(posix_pshmem::ftruncate);
	}
	addr = mmap(nullptr, size, prot, flags, __fd, offset);
	if (addr == MAP_FAILED)
	{
		close(__fd);
		PERR(posix_pshmem::mmap);
	}
}


posix_pshmem::posix_pshmem(posix_pshmem&& ref) noexcept: name(ref.name),__fd(ref.__fd), addr(ref.addr)
	, length(ref.length),cur(ref.cur.load(std::memory_order_acquire))
	, protect(ref.protect)
{

	ref.__fd = -1;
	ref.addr = nullptr;
	ref.length = 0;
	ref.name = nullptr;
	ref.protect = 0;
	ref.cur = 0;
}


posix_pshmem::~posix_pshmem(void) noexcept
{
	if (addr)
		if(munmap(addr, length))
			PERR(posix_pshmem::munmap);
	if (__fd)
		close(__fd);
	if (name)
		shm_unlink(name);
}


void* posix_pshmem::getaddr(void) const noexcept
{
	return addr;
}

void posix_pshmem::mclear(void) noexcept
{
	memset(addr, 0, length);
	cur.store(0, std::memory_order_release);
}


int posix_pshmem::msync(int flags) const noexcept
{
	int ret = ::msync(addr, length, flags);
	if (ret && errno == EINVAL)
		PERR(posix_pshmem::msync);
	return ret;
}

size_t posix_pshmem::mseek(off_t offset, int whence) noexcept
{
	uint64_t temp = 0;
	switch(whence)
	{
		case SEEK_SET:
			if (offset < 0 || offset >= static_cast<off_t>(length))
			{
				errno = EINVAL;
				PERR(posix_pshmem::mseek);
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
					PERR(posix_pshmem::mseek);
				}
			}while (!cur.compare_exchange_weak(temp, temp + offset,
							std::memory_order_acq_rel,
							std::memory_order_acquire));
			return temp;
		case SEEK_END:
			if (offset > 0 || offset <= static_cast<off_t>(-length))
			{
				errno = EINVAL;
				PERR(posix_pshmem::mseek);
			}
			cur.store(length - 1  + offset, std::memory_order_release);
			return cur.load(std::memory_order_acquire);
		default:
			errno = EINVAL;
			PERR(posix_pshmem::mseek);
			break;
	}
}

size_t posix_pshmem::mtell(void) const noexcept
{
	return cur.load(std::memory_order_acquire);
}

void posix_pshmem::maccess(void* buf, size_t buf_len, size_t nbytes, bool reset,
		bool is_read) noexcept
{
	if ((is_read && !(protect & PROT_READ)) || (!is_read && !(protect & PROT_WRITE)))
	{
		errno = EPERM;
		if (is_read)
			PERR(posix_pshmem::mread);
		PERR(posix_pshmem::mwrite);
	}

	if (!buf || buf_len < nbytes)
	{
		errno =  EINVAL;
		if (is_read)
			PERR(posix_pshmem::mread);
		PERR(posix_pshmem::mwrite);
	}
	if (!nbytes)
		return;
	if (is_read)
		memset(buf, 0, buf_len);
	if (reset)
		mseek(0, SEEK_SET);
	uint64_t temp = cur.load(std::memory_order_acquire);
	do
	{
		if (temp + nbytes > length)
		{
			errno =  EINVAL;
			if (is_read)
				PERR(posix_pshmem::mread);
			PERR(posix_pshmem::mwrite);
		}
		if (is_read)
			memcpy(buf, static_cast<unsigned char*>(addr) + cur, nbytes);
		else
			memcpy(static_cast<unsigned char*>(addr) + temp, buf, nbytes);
	}while (!cur.compare_exchange_weak(temp, temp +nbytes, std::memory_order_acq_rel,
			std::memory_order_acquire));
}

void posix_pshmem::mread(void* buf, size_t buf_len, size_t nbytes, bool reset) noexcept
{
	maccess(buf, buf_len, nbytes, reset, true);
}

void posix_pshmem::mwrite(void* buf, size_t buf_len, size_t nbytes, bool reset) noexcept
{
	maccess(buf, buf_len, nbytes, reset, false);
}

