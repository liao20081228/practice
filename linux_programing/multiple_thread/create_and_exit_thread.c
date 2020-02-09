#include<stdio.h>
#include<pthread.h>

void* add(void * cnt)
{

}



int main()
{
	int counter = 0;

	pthread_t thread_id = 0;

	pthread_create(&thread_id, NULL, add, (void*)counter)

}
