#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
sem_t sem;
int a=0;

void* fun(void* n)
{
	sem_wait(&sem);
	a++;
	return NULL;
}


int main()
{
	sem_init(&sem, 0, 0);
	pthread_t id;
	pthread_create(&id,NULL,fun,NULL);
	pthread_create(&id,NULL,fun,NULL);
	pthread_create(&id,NULL,fun,NULL);
	pthread_create(&id,NULL,fun,NULL);
	sem_post(&sem);
	sleep(5);
	printf("%d,\n", a);
return 0;
}
