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
	pthread_cleanup_push(clean, (void*)3);
	pthread_cleanup_push(clean, (void*)4);
	sleep(2);
	pthread_cleanup_pop(0);//正常退出时不执行，异常退出执行
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(1);//正常退出执行，异常退出执行
	pthread_cleanup_pop(1);
	return NULL;
}

int main()
{
	pthread_t id = 0;

	pthread_create(&id, NULL, fun, NULL);
	pthread_join(id, NULL);

	pthread_create(&id, NULL, fun, NULL);
	pthread_cancel(id);
	pthread_join(id, NULL);
	return 0;
}
