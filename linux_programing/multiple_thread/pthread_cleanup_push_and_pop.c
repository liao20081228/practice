#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
void clean(void * arg)
{
	printf("clean fun %d\n", (int)arg);
}

void* fun(void * arg)
{
	pthread_cleanup_push(clean, (void*)1);
	pthread_cleanup_push(clean, (void*)2);
	pthread_cleanup_push(clean, (void*)2);
	pthread_cleanup_push(clean, (void*)2);
	sleep(2);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(1);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
}
