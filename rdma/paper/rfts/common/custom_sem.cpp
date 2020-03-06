#include"custom_sem.hpp"

posix_sem::posix_sem(int pshared, unsigned int value) noexcept:
	__sem(new sem_t), __name(nullptr)
{
	if (sem_init(__sem, pshared, value))
	{
		delete __sem;
		PERR(seamphore::sem_init);
	}

}

posix_sem::posix_sem(const char* name, int oflag, mode_t mode, unsigned int value) noexcept:
		__sem(sem_open(name, oflag, mode, value)), __name(name)
{
	if (__sem == SEM_FAILED)
		PERR(seamphore::sem_open);
}

posix_sem::posix_sem(const std::string& name, int oflag, mode_t mode, unsigned int value) noexcept:
		__sem(sem_open(name.c_str(), oflag, mode, value)), __name(name.c_str())
{
	if (__sem == SEM_FAILED)
		PERR(seamphore::sem_open);
}

posix_sem::posix_sem(const std::string* name, int oflag, mode_t mode, unsigned int value) noexcept:
		__sem(sem_open(name->c_str(), oflag, mode, value)), __name(name->c_str())
{
	if (__sem == SEM_FAILED)
		PERR(seamphore::sem_open);
}

posix_sem::posix_sem(posix_sem&& ref) noexcept:__sem(ref.__sem), __name(ref.__name)
{
	ref.__name = nullptr;
	ref.__sem = nullptr;
}

posix_sem::~posix_sem(void) noexcept
{
	if (__sem)
	{
		if  (__name)
		{
			sem_close(__sem);
			sem_unlink(__name);
			return;
		}
		delete __sem;
		sem_destroy(__sem);
	}
}


void posix_sem::post(void) noexcept
{
	if (sem_post(__sem))
		PERR(seamphore::sem_post);
}

void posix_sem::wait(void) noexcept
{
	if (sem_wait(__sem))
		PERR(seamphore::sem_wait);
}


int posix_sem::trywait(void) noexcept
{
	if (sem_trywait(__sem))
	{
		if (errno != EAGAIN)
		{
			PERR(seamphore::sem_trywait);
		}
		else
			return EAGAIN;
	}
	return 0;
}

int posix_sem::timewait(const struct timespec* abs_timeout) noexcept
{
	if (sem_timedwait(__sem,abs_timeout))
	{
		if (errno != ETIMEDOUT)
		{
			PERR(seamphore::sem_trywait);
		}
		else
			return ETIMEDOUT;
	}
	return 0;
}

int posix_sem::getvalue(int* const val) noexcept
{
	int n  = 0;
	sem_getvalue(__sem, &n);
	if (val)
		*val=n;
	return n;
}
