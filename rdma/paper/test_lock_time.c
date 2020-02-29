#include<pthread.h>
#include"get_clock.h"
#include<stdio.h>


void* fun(void*arg)
{
	double mean=0;
	pthread_mutex_t* mutex=(pthread_mutex_t*)arg;
	int n=1;
	int k=10000;
	double mhz=0;
	cycles_t s=0;
	cycles_t e=0;
	for(int i = 0; i<1000;i++)
	{
		mhz=get_cpu_mhz(0);
		s=get_cycles();
		pthread_mutex_lock(mutex);
		n=n+1;
		if(n==k)
			break;
		pthread_mutex_unlock(mutex);
		e=get_cycles();
		mean=mean+(e-s)/mhz*1000;
	}
	printf("mutex mean %lf\n", mean/1000);
	return NULL;
}

void* fun1(void*arg)
{
	double mean=0;
	pthread_spinlock_t* mutex=(pthread_spinlock_t*)arg;
	int n=1;
	int k=10000;
	double mhz=0;
	cycles_t s=0;
	cycles_t e=0;
	for(int i = 0; i<1000;i++)
	{
		mhz=get_cpu_mhz(0);
		s=get_cycles();
		pthread_spin_lock(mutex);
		n=n+1;
		if(n==k)
			break;
		pthread_spin_unlock(mutex);
		e=get_cycles();
		mean=mean+(e-s)/mhz*1000;
	}
	printf("pthread_spin  mean %lf\n", mean/1000);
	return NULL;
}







int main()
{
	pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
	pthread_spinlock_t spin;
	pthread_spin_init(&spin, PTHREAD_PROCESS_PRIVATE);

	pthread_t id[4];
	for(int i=0;i < 4;i++)
		pthread_create(&id[i],NULL,fun,(void*)&mutex);
	for(int i=0;i < 4;i++)
		pthread_join(id[i],NULL);
	
	for(int i=0;i < 4;i++)
		pthread_create(&id[i],NULL,fun1,(void*)&spin);
	for(int i=0;i < 4;i++)
		pthread_join(id[i],NULL);
	return 0;



}
