#include"semaphore.hpp"

semaphore::semaphore(const int pshared, const unsigned int value):sem(new sem_t)
{
	if(sem_init(sem, pshared, value))
	{
		delete sem;
		if(errno == EINVAL)
			throw std::invalid_argument("initial value exceeds SEM_VALUE_MAX");
		if(errno == ENOSYS)
			throw std::
	}

}
