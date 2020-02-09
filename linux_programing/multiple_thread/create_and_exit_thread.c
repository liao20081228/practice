#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
void* add(void * cnt)
{
	int * count = (int *)cnt;
	for(int i = 0; i < 20; ++i,(*count)++)
	{
		printf("%lu, count is %d\n", pthread_self(),*count);
		sleep(1);
	}
		if (*count == 20)
		pthread_exit((void*)20);
	return (void*)(*count);
}



int main()
{
	int counter = 0;

	pthread_t thread_id1 = 0, thread_id2=0;

	if(pthread_create(&thread_id1, NULL, add, &counter))
	{
		perror("create thread failed!");
		return 1;
	}
	if(pthread_create(&thread_id2, NULL, add, &counter))
	{
		perror("create thread failed!");
		return 1;
	}
	int ret1 = 0,  ret2 = 0; 
	pthread_join(thread_id1,(void**)&ret1);
	pthread_join(thread_id2,(void**)&ret2);

	printf("%lu, ret1 is %d", thread_id1, ret1);

	printf("%lu, ret2 is %d", thread_id2, ret2);
	return 0;
}
