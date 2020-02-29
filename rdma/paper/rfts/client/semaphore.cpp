#include"semaphore.hpp"

semaphore::semaphore(const int pshared, const unsigned int value)
{
	sem_init(&sem, pshared, value);
}
