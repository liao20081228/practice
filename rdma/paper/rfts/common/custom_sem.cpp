#include"custom_sem.hpp"

custom::posix_sem::posix_sem(int pshared, unsigned int value) noexcept
	: __sem(new sem_t)
	, __name("")
{
	if (sem_init(__sem, pshared, value))
	{
		delete __sem;
		PERR(posix_sem::sem_init);
	}
}

custom::posix_sem::posix_sem(const char* name, int oflag, mode_t mode, unsigned int value) noexcept
	: __sem(sem_open(name, oflag, mode, value))
	, __name(name)
{
	if (__sem == SEM_FAILED)
		PERR(posix_sem::sem_open);
}

custom::posix_sem::posix_sem(const std::string& name, int oflag, mode_t mode, unsigned int value) noexcept
	: __sem(sem_open(name.c_str(), oflag, mode, value))
	, __name(name)
{
	if (__sem == SEM_FAILED)
		PERR(posix_sem::sem_open);
}

custom::posix_sem::posix_sem(const std::string* name, int oflag, mode_t mode, unsigned int value) noexcept
	: __sem(sem_open(name->c_str(), oflag, mode, value))
	, __name(*name)
{
	if (__sem == SEM_FAILED)
		PERR(posix_sem::sem_open);
}

custom::posix_sem::posix_sem(posix_sem&& ref) noexcept
	:__sem(ref.__sem)
	, __name(ref.__name)
{
	ref.__sem = nullptr;
}

custom::posix_sem::~posix_sem(void) noexcept
{
	if (__sem)
	{
		if (__name.size())
		{
			sem_close(__sem);
			sem_unlink(__name.c_str());
			return;
		}
		delete __sem;
		sem_destroy(__sem);
	}
}


void custom::posix_sem::post(void) const noexcept
{
	if (sem_post(__sem))
		PERR(posix_sem::sem_post);
}

void custom::posix_sem::wait(void) const noexcept
{
	if (sem_wait(__sem))
		PERR(posix_sem::sem_wait);
}


int custom::posix_sem::trywait(void) const noexcept
{
	if (sem_trywait(__sem))
	{
		if (errno != EAGAIN)
		{
			PERR(posix_sem::sem_trywait);
		}
		else
			return EAGAIN;
	}
	return 0;
}

int custom::posix_sem::timewait(const struct timespec* abs_timeout) const noexcept
{
	if (sem_timedwait(__sem,abs_timeout))
	{
		if (errno != ETIMEDOUT)
		{
			PERR(posix_sem::sem_trywait);
		}
		else
			return ETIMEDOUT;
	}
	return 0;
}

int custom::posix_sem::getvalue(int* const val) const noexcept
{
	int n  = 0;
	sem_getvalue(__sem, &n);
	if (val)
		*val=n;
	return n;
}
