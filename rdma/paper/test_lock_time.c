#include<pthread.h>
#include"get_clock.h"



void* fun(void*arg)
{
	double mean=0;
	pthread_mutex_t* mutex=(pthread_mutex_t*)arg;
	int n=1;
	int k=10000;
	cycles_t s=0;
	cycles_t e=0;
	for(int i = 0; i<1000;i++)
	{
		s=get_cycles();
		pthread_mutex_lock(mutex);
		n=n+1;
		if(n==k)
			break;
		pthread_mutex_unlock(mutex);
	}
}








int main()
{
	pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
	pthread_spinlock_t spin;
	pthread_spin_init(&spin, PTHREAD_PROCESS_PRIVATE);





}
