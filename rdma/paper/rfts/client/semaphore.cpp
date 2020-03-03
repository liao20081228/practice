#include"semaphore.hpp"

semaphore::semaphore(const int pshared, const unsigned int value):
	sem(new sem_t), name(nullptr)
{
	if(sem_init(sem, pshared, value))
	{
		delete sem;
		throw std::system_error(errno, std::generic_category(),"sem_init()");
	}

}

semaphore::semaphore(const char* name, int oflag, mode_t mode, unsigned int value):
		sem(sem_open(name, oflag, mode, value)), name(name)
{
	if(sem == SEM_FAILED)
		throw std::system_error(errno, std::generic_category(),"sem_open()");
}

semaphore::semaphore(semaphore&& ref) noexcept:sem(ref.sem),name(ref.name) 
{
	ref.name = nullptr;
	ref.sem = nullptr;
}

semaphore& semaphore::operator = (semaphore&& ref) noexcept
{
	if(this == &ref)
		return *this;
	sem = ref.sem;
	name = ref.name;
	ref.name = nullptr;
	ref.sem = nullptr;
	return *this; 
}


semaphore::~semaphore(void) noexcept
{
	if(sem)
	{
		if (name)
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
	if(sem_post(sem))
	{
		perror("sem_post()");
		exit(errno);
	}
}

void semaphore::wait(void) noexcept
{
	if(sem_wait(sem))
	{
		perror("sem_wait()");
		exit(errno);
	}
}


int semaphore::trywait(void) noexcept
{
	if(sem_trywait(sem)||errno != EAGAIN)
	{
		perror("sem_trywait()");
		exit(errno);
	}
	return EAGAIN;
}

void semaphore::timewait(const struct timespec* abs_timeout)
{
	if(sem_timedwait(sem,abs_timeout))
		throw std::system_error(errno, std::generic_category(), "sem_timewait()");
}

int semaphore::getvalue(int * val) noexcept
{
	int n  = 0;
	sem_getvalue(sem, &n);
	if(val)
		*val=n;
	return n;
}
