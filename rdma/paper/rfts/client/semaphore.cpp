#include"semaphore.hpp"

semaphore::semaphore(const int pshared, const unsigned int value):
	sem(new sem_t), name(nullptr)
{
	if (sem_init(sem, pshared, value))
	{
		delete sem;
		throw std::system_error(errno, std::generic_category(),
				"class semaphore::sem_init()");
	}

}

semaphore::semaphore(const char* name, int oflag, mode_t mode, unsigned int value):
		sem(sem_open(name, oflag, mode, value)), name(name)
{
	if (sem == SEM_FAILED)
		throw std::system_error(errno, std::generic_category(),
				"class semaphore::sem_open()");
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
		perror("class semaphore::sem_post()");
		exit(errno);
	}
}

void semaphore::wait(void) noexcept
{
	if (sem_wait(sem))
	{
		perror("class semaphore::sem_wait()");
		exit(errno);
	}
}


int semaphore::trywait(void) noexcept
{
	if (sem_trywait(sem))
	{
		if (errno != EAGAIN)
		{
			perror("class semaphore::sem_trywait()");
			exit(errno);
		}
		else
			return EAGAIN;
	}
	return 0;
}

int semaphore::timewait(const struct timespec* abs_timeout) noexcept
{
	if (sem_timedwait(sem,abs_timeout) && errno != ETIMEDOUT)
	{
		perror("class semaphore::sem_trywait()");
		exit(errno);
	}
	return ETIMEDOUT;
}

int semaphore::getvalue(int* val) noexcept
{
	int n  = 0;
	sem_getvalue(sem, &n);
	if (val)
		*val=n;
	return n;
}
