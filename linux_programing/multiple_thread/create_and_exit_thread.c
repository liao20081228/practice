#include<stdio.h>
#include<pthread.h>

void* add(void * cnt)
{
	int * count = (int *)cnt;
	(*count)++;
	if (*count == 20)
		pthread_exit((void*)(20));
	return (void*)(*count);
}



int main()
{
	int counter = 0;

	pthread_t thread_id = 0;

	if(pthread_create(&thread_id, NULL, add, &counter))
	{
		perror("create thread failed!");
		return 1;
	}
	if(pthread_create(&thread_id, NULL, add, &counter))
	{
		perror("create thread failed!");
		return 1;
	}


}
