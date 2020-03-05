#include"custom_shmem.hpp"

pshmem::pshmem(const char* name, size_t size, int oflag, mode_t mode, int prot,
		int flags, off_t offset) noexcept: name(name)
	, fd(shm_open(name, oflag, mode)),length(size), cur(0),protect(prot)
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


pshmem::pshmem(pshmem&& ref) noexcept: name(ref.name),fd(ref.fd), addr(ref.addr)
	, length(ref.length),cur(ref.cur.load(std::memory_order_acquire))
	, protect(ref.protect)
{

	ref.fd = -1;
	ref.addr = nullptr;
	ref.length = 0;
	ref.name = nullptr;
	ref.protect = 0;
	ref.cur = 0;
}


pshmem::~pshmem(void) noexcept
{
	if (addr)
		if(munmap(addr, length))
			PERR(pshmem::munmap);
	if (fd)
		close(fd);
	if (name)
		shm_unlink(name);
}


void* pshmem::getaddr(void) const noexcept
{
	return addr;
}

void pshmem::mclear(void) noexcept
{
	memset(addr, 0, length);
	cur.store(0, std::memory_order_release);
}


int pshmem::msync(int flags) const noexcept
{
	int ret = ::msync(addr, length, flags);
	if (ret && errno == EINVAL)
		PERR(pshmem::msync);
	return ret;
}

size_t pshmem::mseek(off_t offset, int whence) noexcept
{
	uint64_t temp = 0;
	switch(whence)
	{
		case SEEK_SET:
			if (offset < 0 || offset >= static_cast<off_t>(length))
			{
				errno = EINVAL;
				PERR(pshmem::mseek);
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
					PERR(pshmem::mseek);
				}
			}while (!cur.compare_exchange_weak(temp, temp + offset,
							std::memory_order_acq_rel,
							std::memory_order_acquire));
			return temp;
		case SEEK_END:
			if (offset > 0 || offset <= static_cast<off_t>(-length))
			{
				errno = EINVAL;
				PERR(pshmem::mseek);
			}
			cur.store(length - 1  + offset, std::memory_order_release);
			return cur.load(std::memory_order_acquire);
		default:
			errno = EINVAL;
			PERR(pshmem::mseek);
			break;
	}
}

size_t pshmem::mtell(void) const noexcept
{
	return cur.load(std::memory_order_acquire);
}

void pshmem::maccess(void* buf, size_t buf_len, size_t nbytes, bool reset,
		bool is_read) noexcept
{
	if ((is_read && !(protect & PROT_READ)) || (!is_read && !(protect & PROT_WRITE)))
	{
		errno = EPERM;
		if (is_read)
			PERR(pshmem::mread);
		PERR(pshmem::mwrite);
	}

	if (!buf || buf_len < nbytes)
	{
		errno =  EINVAL;
		if (is_read)
			PERR(pshmem::mread);
		PERR(pshmem::mwrite);
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
				PERR(pshmem::mread);
			PERR(pshmem::mwrite);
		}
		if (is_read)
			memcpy(buf, static_cast<unsigned char*>(addr) + cur, nbytes);
		else
			memcpy(static_cast<unsigned char*>(addr) + temp, buf, nbytes);
	}while (!cur.compare_exchange_weak(temp, temp +nbytes, std::memory_order_acq_rel,
			std::memory_order_acquire));
}

void pshmem::mread(void* buf, size_t buf_len, size_t nbytes, bool reset) noexcept
{
	maccess(buf, buf_len, nbytes, reset, true);
}

void pshmem::mwrite(void* buf, size_t buf_len, size_t nbytes, bool reset) noexcept
{
	maccess(buf, buf_len, nbytes, reset, false);
}

