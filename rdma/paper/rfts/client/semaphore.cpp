#include"semaphore.hpp"

semaphore::semaphore(const int pshared, const unsigned int value):sem(new sem_t)
{
	if(sem_init(sem, pshared, value))
	{
		if(errno == EINVAL)
		{
			delete sem;
			throw std::()
		}
	}

}
