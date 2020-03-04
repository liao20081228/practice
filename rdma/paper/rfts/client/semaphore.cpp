#include"semaphore.hpp"

semaphore::semaphore(int pshared, unsigned int value) noexcept:
	sem(new sem_t), name(nullptr)
{
	if (sem_init(sem, pshared, value))
	{
		delete sem;
		perror("semaphore::sem_init() failed");
		exit(errno);
	}

}

semaphore::semaphore(const char* name, int oflag, mode_t mode, unsigned int value) noexcept:
		sem(sem_open(name, oflag, mode, value)), name(name)
{
	if (sem == SEM_FAILED)
	{
		perror("semaphore::sem_open() failed");
		exit(errno);
	}
}

semaphore::semaphore(semaphore&& ref) noexcept:sem(ref.sem),name(ref.name)
{
	ref.name = nullptr;
	ref.sem = nullptr;
}

semaphore::~semaphore(void) noexcept
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


void semaphore::post(void) noexcept
{
	if (sem_post(sem))
	{
		perror("semaphore::sem_post() failed");
		exit(errno);
	}
}

void semaphore::wait(void) noexcept
{
	if (sem_wait(sem))
	{
		perror("semaphore::sem_wait() failed");
		exit(errno);
	}
}


int semaphore::trywait(void) noexcept
{
	if (sem_trywait(sem))
	{
		if (errno != EAGAIN)
		{
			perror("semaphore::sem_trywait() failed");
			exit(errno);
		}
		else
			return EAGAIN;
	}
	return 0;
}

int semaphore::timewait(const struct timespec* abs_timeout) noexcept
{
	if (sem_timedwait(sem,abs_timeout))
	{
		if (errno != ETIMEDOUT)
		{
			perror("semaphore::sem_trywait() failed");
			exit(errno);
		}
		else
			return ETIMEDOUT;
	}
	return 0;
}

int semaphore::getvalue(int* val) noexcept
{
	int n  = 0;
	sem_getvalue(sem, &n);
	if (val)
		*val=n;
	return n;
}
