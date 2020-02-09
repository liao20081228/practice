#include<stdio.h>
#include<pthread.h>

void* add(void * cnt)
{
	int * count = (int *)cnt;
	for(int i = 0; i < 20; ++i,(*count)++)
		printf("%lu, count is %d", pthread_self(),*count);
	if (*count == 20)
		pthread_exit((void*)20);
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
