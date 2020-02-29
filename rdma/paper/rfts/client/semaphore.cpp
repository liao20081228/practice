#include"semaphore.hpp"

semaphore::semaphore(const int pshared, const unsigned int value)
{
	int ret = sem_init(&sem, pshared, value);

}
