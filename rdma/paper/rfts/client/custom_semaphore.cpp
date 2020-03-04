#include"custom_semaphore.hpp"

psem::psem(int pshared, unsigned int value) noexcept:
	sem(new sem_t), name(nullptr)
{
	if (sem_init(sem, pshared, value))
	{
		delete sem;
		PERR(seamphore::sem_init);
	}

}

psem::psem(const char* name, int oflag, mode_t mode, unsigned int value) noexcept:
		sem(sem_open(name, oflag, mode, value)), name(name)
{
	if (sem == SEM_FAILED)
		PERR(seamphore::sem_open);
}

psem::psem(psem&& ref) noexcept:sem(ref.sem),name(ref.name)
{
	ref.name = nullptr;
	ref.sem = nullptr;
}

psem::~psem(void) noexcept
{
	if (sem)
	{
		if  (name)
		{
			sem_close(sem);
			sem_unlink(name);
			return;
		}
		delete sem;
		sem_destroy(sem);
	}
}


void psem::post(void) noexcept
{
	if (sem_post(sem))
		PERR(seamphore::sem_post);
}

void psem::wait(void) noexcept
{
	if (sem_wait(sem))
		PERR(seamphore::sem_wait);
}


int psem::trywait(void) noexcept
{
	if (sem_trywait(sem))
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

int psem::timewait(const struct timespec* abs_timeout) noexcept
{
	if (sem_timedwait(sem,abs_timeout))
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

int psem::getvalue(int* val) noexcept
{
	int n  = 0;
	sem_getvalue(sem, &n);
	if (val)
		*val=n;
	return n;
}
