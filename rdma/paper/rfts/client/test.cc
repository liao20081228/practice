#include"semaphore.hpp"

int main()
{
	semaphore a;
	semaphore b= semaphore(1,2);
	a=b;
	a=semaphore(1,2);
}
