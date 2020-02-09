#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void * fun1(void* arg)
{
	printf("before sleep\n");
	printf("after sleep\n");
	return NULL;
}

int main()
{
	pthread_t id =0;
	pthread_create(&id, NULL, fun1, NULL);
	if(pthread_cancel(id))
		printf("cancel faild\n");
	pthread_join(id, NULL);
}
