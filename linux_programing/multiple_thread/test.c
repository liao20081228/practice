#include<stdio.h>
#include<pthread.h>

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

void* thread(void* arg)
{
	if(pthread_mutex_unlock(&mutex))
	{
		perror("unlock error");
	}
	return NULL;
}

int main()
{
	pthread_t id;
	pthread_create(&id, NULL, thread, NULL);
	pthread_mutex_lock(&mutex);
	pthread_join(id,NULL);
	pthread_mutex_destroy(&mutex);
}
