#include"semaphore.hpp"

semaphore::semaphore(const int pshared, const unsigned int value):sem(new sem_t)
{
	if(sem_init(sem, pshared, value))
	{
		delete sem;
		if(errno == EINVAL)
			throw std::invalid_argument("initial value exceeds SEM_VALUE_MAX");
		if(errno == ENOSYS)
			throw std::invalid_argument("system not support");
	}

}

semaphore::semaphore(const char* name, int oflag, mode_t mode, unsigned int value):
		sem(sem_open(name, oflag, mode, value))
{
	if(sem == SEM_FAILED)
	{
		switch(errno)
		{
			case EACCES:
				throw std::invalid_argument("user have not permission to accsee");
			case EEXIST:
				throw std::invalid_argument("semaphore already exists");
			case EINVAL:
				throw std::invalid_argument("initial value exceeds SEM_VALUE_MAX");
			case EMFILE:
				throw std::invalid_argument("per-process limit on  the number of open fd has been reached");
			case ENAMETOOLONG:
				throw std::length_error("name was too long");
			case ENFILE:
				throw
			case ENOENT:
			case ENOMEM:
		}
	}
}
