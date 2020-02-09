#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

void *thread_fun(void* n)
{
	int *N = n;
	printf("this is child thread, val is %d",*N);
	sleep(10);//主线程先结束后，子线程会立即结束,解决办法是用pthread_join	
	switch(*N)
	{
		case 10:
			return (void*)10;
		case 9:
			return NULL;
		case 7:
	 		pthread_exit(NULL);
		default:
			pthread_exit((void*)*N);

	}
}
int main(void)
{
	pthread_t thread_id = 0;
	if(pthread_create(&thread_id, NULL,thread_fun,(void*)8))
	{
		printf("create thread failed\n");
	}
	printf("this is main thread, %lu \n", pthread_self());
	return 0;
}
